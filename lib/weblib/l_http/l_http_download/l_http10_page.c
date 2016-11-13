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

      #include "weblib/l_http/l_http_download/l_http10_page.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP10_PAGE_rwfile           ( INOUT  t_downLoadWS     *dlws,
                                               IN     t_http_response *httpr,
                                               IN     t_httpCfg        *webCfg,
                                               INOUT  FILE            **fpage )
      {
        #define c_RNSACK_BSIZE (32*1024)
 
        T_CHAR   *buff ;
        T_CHAR   *content_length ;
        T_LONG    total_a_leer, leidos ;
        T_INT     result, size_buff ;
        T_LONG    number_urls ;

        buff = X_ALLOC_Malloc(c_RNSACK_BSIZE) ;
        NULL_RET_FALSE(buff) ;
        leidos         = 0L ;
        content_length = L_HTTP_RESPONSE_getField(httpr,"Content-Length") ;
        if (content_length != NULL)
                 total_a_leer = atoi(content_length) ;
            else total_a_leer = 0L ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), c_RNSACK_BSIZE ) ;
        number_urls  = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        /* ... first read is out of while ... */
        if (dlws->timeLimit == LONG_MAX)
                 result = L_HTTP10_COMMAND_Read(&(webCfg->sd),
                                                buff,size_buff) ;
            else result = L_HTTP10_COMMAND_TryRead(&(webCfg->sd),
                                                buff,size_buff,
                                                dlws->timeLimit) ;
        while ( result > 0 )
        {
          L_FILE_COMMAND_Write(buff,result,(*fpage)) ;
          leidos = leidos + result ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_a_leer) ;
          if (dlws->timeLimit == LONG_MAX)
                   result = L_HTTP10_COMMAND_Read(&(webCfg->sd),
                                                  buff,size_buff) ;
              else result = L_HTTP10_COMMAND_TryRead(&(webCfg->sd),
                                                  buff,size_buff,
                                                  dlws->timeLimit) ;
        }
        dlws->currentBytes += leidos ;
        X_ALLOC_Free( (void **)&buff ) ;
        if ( result < 0 )
             return FALSE ;
        return TRUE ;
      }

      T_BOOL  L_HTTP10_PAGE_OpenPageToReadFile ( INOUT  t_downLoadWS    *dlws,
                                                 IN     t_httpCfg       *webCfg,
                                                 INOUT  t_url           *url,
                                                 INOUT  t_http_response **httpr )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        (*httpr) = NULL ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... try connect ... */
        ok = L_HTTP_SERVER_GetConnection(webCfg,url,dlws) ;
        FALSE_RET_FALSE(ok) ;

        /* ... try request page ... */
        ok = L_HTTP10_COMMAND_GET( &(webCfg->sd),
                                   url,
                                   dlws->clientNameToSend,
                                   dlws->identification,
                                   webCfg->acceptFullUrl,
                                   webCfg->acceptHost ) ;
        FALSE_RET_FALSE(ok) ;

        /* ... read response ... */
        (*httpr) = L_HTTP_RESPONSE_Creat() ;
        NULL_RET_FALSE((*httpr)) ;
        ok = L_HTTP_RESPONSE_Read(&(webCfg->sd),(*httpr)) ;
        if (dlws->finfo != NULL)
           {
             L_HTTP_LOG_PrintUrl(dlws->finfo,url) ;
             L_HTTP_LOG_PrintHeader(dlws->finfo,(*httpr)) ;
           }

        return ok ;
      }

      T_BOOL  L_HTTP10_PAGE_OpenPage2ToReadFile  ( INOUT  t_downLoadWS *dlws,
                                                   IN     t_httpCfg    *webCfg,
                                                   IN     T_CHAR       *machine,
                                                   IN     int           port,
                                                   IN     T_CHAR       *page,
                                                   INOUT  t_http_response **httpr )
      {
        T_BOOL  ok ;
        t_url  *tmpUrl ;

        tmpUrl = L_URL_Creat("http",
                             machine,
                             page,
                             NULL,
                             NULL,
                             port) ;
        NULL_RET_FALSE(tmpUrl) ;
        ok = L_HTTP10_PAGE_OpenPageToReadFile(dlws,webCfg,tmpUrl,httpr) ;
        L_URL_Destroy(&tmpUrl) ;
        return ok ;
      }

      T_BOOL  L_HTTP10_PAGE_AnalizeCode      ( INOUT  t_downLoadWS     *dlws,
                                               IN     t_httpCfg        *webCfg,
                                               IN     t_http_response  *httpr,
                                               INOUT  FILE            **fpage,
                                               INOUT  t_url            *url )
      {
        T_INT  codigo ;


        codigo = atoi(L_HTTP_RESPONSE_getField(httpr,"Codigo")) ;

        /* ... page moved ... */
        if ( 
             (codigo == 301)
                   ||
             (codigo == 302) 
           )
           {
             T_BOOL    ok ;
             T_CHAR   *location ;

             location = L_HTTP_RESPONSE_getField(httpr,"Location") ;
             (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
             ok = FALSE ;
             if ( (*fpage) != NULL )
                {
                  ok = TRUE ;
                  fprintf
                  (
                    (*fpage),
                    "<HR/>\n"
                    "<CENTER>\n"
                    "\tsorry, this page has been move <A HREF=\"%s\">here</A>\n"                    "</CENTER>\n"
                    "<HR/>\n",
                    location
                  ) ;
                }
             return ok ;
           }

        /* ... unrecover error ... */
        if (
             ( (codigo > 400) && (codigo < 500) )  /* user error */
                              ||
             ( (codigo > 500) && (codigo < 506) )  /* server error */
           )
           {
             L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return FALSE ;
           }  

        /* ... CAN recover error ... */   
        if ( (codigo == 400)    
                   ||
             (codigo == 500) )
           {
             if (dlws->rentry == TRUE)
                {
                  T_INT  tSleeping ;

                  tSleeping = 10 ;
                  X_PRINT_printf("\n   waiting %i seconds to server...\n") ;
                  sleep(tSleeping) ;
                }

             L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
             (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return FALSE ;
           } 

        return TRUE ;
      }

      T_BOOL  L_HTTP10_PAGE_DownLoadPage     ( INOUT  t_downLoadWS   *dlws,
                                               IN     t_httpCfg      *webCfg,
                                               INOUT  FILE          **fpage,
                                               INOUT  t_url          *url )
      {
        t_http_response   *httpr ;
        T_BOOL             ok ;

        ok = L_HTTP10_PAGE_OpenPageToReadFile(dlws,webCfg,url,&httpr) ;
        L_VERBOSE_DOWNLOAD_currentPage(dlws,httpr,url) ;
        FALSE_RET_FALSE(ok) ;

        ok = L_HTTP10_PAGE_AnalizeCode(dlws,webCfg,httpr,fpage,url) ;
        FALSE_RET_FALSE(ok) ;

        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
	NULL_RET_FALSE((*fpage)) ;
        ok = L_HTTP10_PAGE_rwfile(dlws,httpr,webCfg,fpage) ;

        L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
        L_HTTP_RESPONSE_Destroy(&(httpr)) ;

        return ok ;
      }


   /* ................................................................... */

