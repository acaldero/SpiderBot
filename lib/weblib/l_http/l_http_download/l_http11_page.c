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

      #include "weblib/l_http/l_http_download/l_http11_page.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP11_PAGE_rwblock     ( INOUT  t_downLoadWS     *dlws,
                                          IN     T_LONG            total_a_leer,
                                          IN     T_LONG            total_readed,
                                          INOUT  T_CHAR           *buff,
                                          IN     T_INT             size_buff,
                                          IN     T_LONG            number_urls,
                                          IN     t_httpCfg        *webCfg,
                                          INOUT  FILE            **fpage )
      {
        T_LONG  leidos ;
        T_INT   result ;

        size_buff = MIN(size_buff,total_a_leer) ;
        leidos    = 0L ;
        while ( (leidos) < total_a_leer )
        {
          if (dlws->timeLimit == LONG_MAX)
                   result = L_HTTP11_COMMAND_Read(&(webCfg->sd),
                                                  buff,size_buff) ;
              else result = L_HTTP11_COMMAND_TryRead(&(webCfg->sd),
                                                  buff,size_buff,
                                                  dlws->timeLimit) ;
          if (result < 0)
              return FALSE ;
          L_FILE_COMMAND_Write(buff,result,(*fpage)) ;
          (leidos) = (leidos) + result ;
          L_VERBOSE_DOWNLOAD_currentChunked(dlws,
                                            total_readed,
                                            0,
                                            leidos,
                                            total_a_leer) ;
        }
        return TRUE ;
      }

      T_BOOL  L_HTTP11_PAGE_rwfile      ( INOUT  t_downLoadWS     *dlws,
                                          IN     t_http_response *httpr,
                                          IN     t_httpCfg        *webCfg,
                                          INOUT  FILE            **fpage )
      {
        #define c_RNSACK_BSIZE (32*1024)

        T_CHAR   *buff ;
        T_CHAR   *httph ;
        T_CHAR   *transferEncoding ;
        T_LONG    total_a_leer ;
        T_INT     size_buff, more, total_readed ;
        T_BOOL    ok ;
        T_LONG    number_urls ;

        /* ... i/o buffer ... */
        buff = X_ALLOC_Malloc(c_RNSACK_BSIZE) ;
        NULL_RET_FALSE(buff) ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize < 16)
            size_buff = 16 ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), c_RNSACK_BSIZE ) ;

        /* ... data control ... */
        httph = L_HTTP_RESPONSE_getField(httpr,"Content-Length") ;
        if (httph != NULL)
                 total_a_leer = atoi(httph) ;
            else total_a_leer = 0L ;
        number_urls  = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;
        transferEncoding = L_HTTP_RESPONSE_getField(httpr,"Transfer-Encoding") ;

        /* ... copy data ... */
        total_readed = 0 ;
        if (transferEncoding == NULL)
           {
             ok = L_HTTP11_PAGE_rwblock(dlws,
                                   total_a_leer,
                                   0,
                                   buff,
                                   size_buff,
                                   number_urls,
                                   webCfg,
                                   fpage) ;
             total_readed = total_a_leer ;
           }
        if (X_STRING_Equal(transferEncoding,"chunked") == TRUE)
           {
             more = L_HTTP_RESPONSE_readChuckSize(&(webCfg->sd)) ;
             while (more > 0)
             {
               ok = L_HTTP11_PAGE_rwblock(dlws,
                                          more,
                                          total_readed,
                                          buff,
                                          size_buff,
                                          number_urls,
                                          webCfg,
                                          fpage) ;
               FALSE_RET_FALSE(ok) ;
               total_readed += more ;
               more = L_HTTP_RESPONSE_readChuckSize(&(webCfg->sd)) ;
             }
           }
        dlws->currentBytes += total_readed ;

        X_ALLOC_Free( (void **)&buff ) ;
        return TRUE ;
      }

      T_BOOL  L_HTTP11_PAGE_OpenPageToRead  ( INOUT  t_downLoadWS     *dlws,
                                              IN     t_httpCfg        *webCfg,
                                              INOUT  t_url            *url,
                                              INOUT  t_http_response **httpr )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        (*httpr) = NULL ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... request page ... */
        if (webCfg->connected == FALSE)
           {
             ok = L_HTTP_SERVER_GetConnection(webCfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }
        ok = L_HTTP11_COMMAND_GET ( &(webCfg->sd),
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

      T_BOOL  L_HTTP11_PAGE_OpenPage2ToReadFile ( INOUT  t_downLoadWS  *dlws,
                                                  IN     t_httpCfg     *webCfg,
                                                  IN     T_CHAR        *machine,
                                                  IN     int            port,
                                                  IN     T_CHAR        *page,
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
        ok = L_HTTP11_PAGE_OpenPageToRead(dlws,webCfg,tmpUrl,httpr) ;
        L_URL_Destroy(&tmpUrl) ;
        return ok ;
      }

      T_BOOL  L_HTTP11_PAGE_AnalizeCode     ( INOUT  t_downLoadWS     *dlws,
                                              IN     t_httpCfg        *webCfg,
                                              IN     t_http_response  *httpr,
                                              INOUT  FILE            **fpage,
                                              INOUT  t_url            *url )
      {
        T_INT  codigo ;


        codigo = atoi(L_HTTP_RESPONSE_getField(httpr,"Codigo")) ;

        /* ... page moved ... */
        if ( (codigo == 301) 
                   ||
             (codigo == 302) )
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
                    "\tsorry, this page has been move <A HREF=\"%s\">here</A>\n"
                    "</CENTER>\n"
                    "<HR/>\n",
                    location 
                  ) ;
                }
             L_HTTP11_COMMAND_Close(&(webCfg->sd)) ;
             (webCfg->connected) = FALSE ;
             return ok ;
           }

        /* ... unrecover error ... */  
        if (
             ( (codigo > 400) && (codigo < 500) )  /* user error */
                              ||
             ( (codigo > 500) && (codigo < 506) )  /* server error */
           )
           {                           
             L_HTTP11_COMMAND_Close(&(webCfg->sd)) ;
             (webCfg->connected) = FALSE ;
             return FALSE ;
           }

        /* ... CAN recover error ... */
        if ( (codigo == 400)
                    ||
             (codigo == 500) )
           {
             /* ... need wait some time ? ... */
             if (dlws->rentry == TRUE)
                {
                  T_CHAR  *hr ;
                  T_INT    tSleeping ;

                  hr = L_HTTP_RESPONSE_getField(httpr,"Rentry_After") ;
                  if (hr == NULL)
                     {
                       tSleeping = 10 ;
                     }
                  else
                     {
                       tSleeping = atoi(hr) ;
                       if (tSleeping == 0)
                          {
                            X_PRINT_printf(
                              "\n   server will become available at %s...\n") ;
                            tSleeping = 60 ;
                          }
                     }
                  X_PRINT_printf("\n   waiting %i seconds to server...\n") ;
                  sleep(tSleeping) ;
                }

             (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
             L_HTTP11_COMMAND_Close(&(webCfg->sd)) ;
             (webCfg->connected) = FALSE ;
             return FALSE ;
           }

        return TRUE ;
      }

      T_BOOL  L_HTTP11_PAGE_DownLoadPage    ( INOUT  t_downLoadWS   *dlws,
                                              IN     t_httpCfg      *webCfg,
                                              INOUT  FILE          **fpage,
                                              INOUT  t_url          *url )
      {
        t_http_response   *httpr ;
        T_BOOL             ok ;
        void (*oldHandle) (int) ;

        oldHandle = signal(SIGPIPE,SIG_IGN) ;
        httpr = NULL ;
        ok = L_HTTP11_PAGE_OpenPageToRead(dlws,webCfg,url,&httpr) ;
        if (ok == FALSE)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_VERBOSE_DOWNLOAD_currentPage(dlws,httpr,url) ;
        if (ok == TRUE)
            ok = L_HTTP11_PAGE_AnalizeCode(dlws,webCfg,httpr,fpage,url) ;
        if (ok == FALSE)
           {
             signal(SIGPIPE,oldHandle) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return FALSE ;
           }

        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        if ((*fpage) == NULL)
           {
             signal(SIGPIPE,oldHandle) ;
             return FALSE ;
           }

        ok = L_HTTP11_PAGE_rwfile(dlws,httpr,webCfg,fpage) ;
        if (ok == FALSE)
           {
             fseek(*fpage,0,SEEK_SET) ;    
             L_HTTP11_COMMAND_Close(&(webCfg->sd)) ;
             (webCfg->connected) = FALSE ;
             signal(SIGPIPE,oldHandle) ;
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             return FALSE ;
           }

        signal(SIGPIPE,oldHandle) ;
        L_HTTP_RESPONSE_Destroy(&(httpr)) ;
        return ok ;
      }


   /* ................................................................... */

