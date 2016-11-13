/* ........................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "weblib/l_http/l_http_download/l_http09_page.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP09_PAGE_rwfile           ( INOUT  t_downLoadWS     *dlws,
                                               IN     t_http_response *httpr,
                                               IN     t_httpCfg        *webCfg,
                                               INOUT  FILE            **fpage )
      {
        #define c_RNSACK_BSIZE (32*1024)

        T_CHAR   *buff ;
        T_CHAR   *httph ;
        T_LONG    total_a_leer, leidos ;
        T_INT     result, size_buff ;
        T_LONG    number_urls ;

        buff = X_ALLOC_Malloc(c_RNSACK_BSIZE) ;
        NULL_RET_FALSE(buff) ;
        leidos       = 0L ;
        httph        = L_HTTP_RESPONSE_getField(httpr,"Content-Length") ;
        if (httph != NULL)
                 total_a_leer = atoi(httph) ;
            else total_a_leer = 0L ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), c_RNSACK_BSIZE ) ;
        number_urls = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        /* ... first read is out of while ... */
        if (dlws->timeLimit == LONG_MAX)
                 result = L_HTTP09_COMMAND_Read(&(webCfg->sd),
                                                    buff,size_buff) ;
            else result = L_HTTP09_COMMAND_TryRead(&(webCfg->sd),
                                                   buff,size_buff,
                                                   dlws->timeLimit) ;
        while ( result > 0 )
        {
          L_FILE_COMMAND_Write(buff,result,(*fpage)) ;
          leidos = leidos + result ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_a_leer) ;
          if (dlws->timeLimit == LONG_MAX)
                   result = L_HTTP09_COMMAND_Read(&(webCfg->sd),
                                                    buff,size_buff) ;
              else result = L_HTTP09_COMMAND_TryRead(&(webCfg->sd),
                                                     buff,size_buff,
                                                     dlws->timeLimit) ;
        }
        dlws->currentBytes += leidos ;
        X_ALLOC_Free( (void **)&buff ) ;
        if ( result < 0 )
             return FALSE ;
        return TRUE ;
      }

      T_BOOL  L_HTTP09_PAGE_DownLoadPage     ( INOUT  t_downLoadWS   *dlws,
                                               IN     t_httpCfg      *webCfg,
                                               INOUT  FILE          **fpage,
                                               INOUT  t_url          *url )
      {
        t_http_response  *httpr ;
        T_INT              codigo ;
        T_BOOL             ok ;

        L_HTTP_SERVER_GetConnection(webCfg,url,dlws) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_HTTP09_COMMAND_GET(&(webCfg->sd),
                                  url->file,
                                  "HTTP/0.9",
                                  dlws->clientNameToSend) ;
        FALSE_RET_FALSE(ok) ;
        httpr = L_HTTP_RESPONSE_Creat() ;
        NULL_RET_FALSE(httpr) ;
        L_HTTP_RESPONSE_Read(&(webCfg->sd),httpr) ;
        if (dlws->finfo != NULL)
           {
             L_HTTP_LOG_PrintUrl(dlws->finfo,url) ;
           }
        L_VERBOSE_DOWNLOAD_currentPage(dlws,NULL,url) ;

        codigo = atoi( L_HTTP_RESPONSE_getField(httpr,"Codigo") ) ;
        if ( (codigo == 301) 
                   ||
             (codigo == 302) )
           {
	     T_BOOL    ok ;
	     T_CHAR   *org_machine ;

             L_HTTP09_COMMAND_Close(&(webCfg->sd)) ;
	     org_machine = X_STRING_StrDup(url->machine) ;
             ok = L_URLFILE_OpenInsideUrl(url,
                                          url,
                                       L_HTTP_RESPONSE_getField(httpr,"Location")) ;
	     FALSE_RET_FALSE(ok) ;
	     if (X_STRING_Equal(url->machine,org_machine) == TRUE)
	              ok = L_HTTP09_PAGE_DownLoadPage(dlws,webCfg,fpage,url) ;
		 else ok = TRUE ;
             X_ALLOC_Free((void **)&org_machine) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return ok ;
           }

        /* ... unrecover error ... */
        if ( (codigo >= 400)
                    &&
             (codigo != 400)
                    &&
             (codigo != 500) )
           {
             L_HTTP09_COMMAND_Close(&(webCfg->sd)) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return FALSE ;
           }

        /* ... CAN recover error ... */
        if ( (codigo == 400)
                   ||
             (codigo == 500) )
           {
             L_HTTP09_COMMAND_Close(&(webCfg->sd)) ;
             (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return FALSE ;
           }

        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
	NULL_RET_FALSE((*fpage)) ;
        ok = L_HTTP09_PAGE_rwfile(dlws,httpr,webCfg,fpage) ;
        L_HTTP09_COMMAND_Close(&(webCfg->sd)) ;
        L_HTTP_RESPONSE_Destroy(&(httpr)) ;

        return ok ;
      }


   /* ................................................................... */

