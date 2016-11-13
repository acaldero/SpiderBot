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

      #include "weblib/l_http/l_http_server.h"
      #include "weblib/l_http/l_http_download/l_http10_page.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_HTTP_SERVER_ID_HttpVersion  
      ( 
        INOUT t_http_ver       *httpVer,
        IN    t_http_response  *httpr,
        IN    t_downLoadWS     *dlws 
      )
      {
        T_CHAR  *httpVersion ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(httpVer) ;
        NULL__SET_ERROR__RET_FALSE(httpr) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... Get version ... */
        httpVersion = L_HTTP_RESPONSE_getField(httpr,"HttpVersion") ;
        if (X_STRING_Equal(httpVersion,"HTTP/0.9") == TRUE)
            (*httpVer) = v_0_9 ;
        if (X_STRING_Equal(httpVersion,"HTTP/1.0") == TRUE)
            (*httpVer) = v_1_0 ;
        if (X_STRING_Equal(httpVersion,"HTTP/1.1") == TRUE)
            (*httpVer) = v_1_1 ;

        switch ((*httpVer))
        {
          case v_0_9 :
               L_VERBOSE_LOG_appendMsg(dlws,"-> 0.9") ;
               break ;
          case v_1_0 :
               L_VERBOSE_LOG_appendMsg(dlws,"-> 1.0") ;
               break ;
          case v_1_1 :
               L_VERBOSE_LOG_appendMsg(dlws,"-> 1.1") ;
               break ;
          default :
        }

        return TRUE ;
      }

      T_BOOL  L_HTTP_SERVER_ID_GetVersion     ( IN     t_httpCfg      *webCfg,
                                                IN     t_url          *url,
                                                INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL            ok ;
        t_http_response  *httpr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... request / ... */
        if (dlws->proxy == NULL)
           {
             L_VERBOSE_LOG_newMsg(dlws,
                                  "Trying connect %s... ",
                                  url->machine) ;
           }
        else 
           {
             L_VERBOSE_LOG_newMsg(dlws,
                                  "Trying connect to proxy %s... ",
                                  (dlws->proxyUrl).machine) ;
           }
        ok = L_HTTP10_PAGE_OpenPage2ToReadFile(dlws,
                                               webCfg,
                                               url->machine,
                                               url->port,
                                               "/",
                                               &httpr) ;
        FALSE_RET_FALSE(ok) ;
        L_VERBOSE_LOG_appendMsg(dlws,"-> OK") ;

        /* ... Get version ... */
        L_VERBOSE_LOG_newMsg(dlws,"Trying detect http version... ") ;
        ok = L_HTTP_SERVER_ID_HttpVersion( &(webCfg->httpVer),
                                              httpr,
                                              dlws ) ;
        FALSE_RET_FALSE(ok) ;

        /* ... ret resources ... */
        L_HTTP_RESPONSE_Destroy(&(httpr)) ;
        L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
        webCfg->connected = FALSE ;
        return ok ;
      }


   /* ................................................................... */

