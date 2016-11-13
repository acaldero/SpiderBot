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


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_HTTP_SERVER_GetConfiguration  ( IN     t_httpCfg      *webCfg,
                                                IN     t_url          *url,
                                                INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL   ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        ok = L_HTTP_SERVER_ID_GetVersion(webCfg,url,dlws) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_HTTP_SERVER_DISALLOW_GetDisallow(webCfg,url,dlws) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_HTTP_SERVER_HEADER_acceptFullURL(webCfg,url,dlws) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_HTTP_SERVER_HEADER_acceptHost(webCfg,url,dlws) ;
        L_VERBOSE_LOG_newMsg(dlws,"\n\n") ;
        return ok ;
      }


      /*  Main Functions *
       * --------------- */
      T_BOOL   L_HTTP_SERVER_SetDefault    ( INOUT  t_httpCfg   *webCfg )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;

        X_ALLOC_MemSet((webCfg),0,sizeof(t_httpCfg)) ;
        webCfg->httpVer       = v_1_0 ;
        webCfg->connected     = FALSE ;
        webCfg->acceptFullUrl = FALSE ;
        return TRUE ;

      }

      T_BOOL   L_HTTP_SERVER_Empty         ( INOUT  t_httpCfg   *webCfg )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;

        L_DISALLOWLI_Empty(&(webCfg->disallowList)) ;
        L_URL_Destroy(&(webCfg->host)) ;
        return TRUE ;
      }

      T_BOOL  L_HTTP_SERVER_GetConnection   ( IN     t_httpCfg      *webCfg,
                                              IN     t_url          *url,
                                              INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... re-connect ... */
        if (webCfg->httpVer == v_0_9)
           {
             ok = L_HTTP09_COMMAND_Connect( &(webCfg->sd),
                                            url->machine,
                                            url->port ) ;
             FALSE_RET_FALSE(ok) ;
           }
        if (webCfg->httpVer == v_1_0)
           {
             if (dlws->proxy == NULL)
                 ok = L_HTTP10_COMMAND_Connect( &(webCfg->sd),
                                                url->machine,
                                                url->port ) ;
             if (dlws->proxy != NULL)
                 ok = L_HTTP10_COMMAND_Connect( &(webCfg->sd),
                                                 (dlws->proxyUrl).machine,
                                                 (dlws->proxyUrl).port ) ;
             FALSE_RET_FALSE(ok) ;
           }
        if (webCfg->httpVer == v_1_1)
           {
             if (dlws->proxy == NULL)
                 ok = L_HTTP11_COMMAND_Connect( &(webCfg->sd),
                                                url->machine,
                                                url->port ) ;
             if (dlws->proxy != NULL)
                 ok = L_HTTP11_COMMAND_Connect( &(webCfg->sd),
                                                 (dlws->proxyUrl).machine,
                                                 (dlws->proxyUrl).port ) ;
             FALSE_RET_FALSE(ok) ;
             webCfg->connected = TRUE ;
           }

        return TRUE ;
      }

      T_BOOL   L_HTTP_SERVER_Setup          ( OUT     t_httpCfg      *webCfg,
                                              IN      t_url          *urlHost,
                                              INOUT   t_downLoadWS   *dlws )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(urlHost) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        webCfg->host          = L_URL_UrlDup(urlHost) ;
	NULL_RET_FALSE(webCfg->host) ;
        webCfg->httpVer       = v_1_0 ;
        webCfg->connected     = FALSE ;
        webCfg->acceptFullUrl = FALSE ;
        L_DISALLOWLI_Empty(&(webCfg->disallowList)) ;
        ok = L_HTTP_SERVER_GetConfiguration(webCfg,
                                            urlHost,
                                            dlws) ;
        if (ok == FALSE)
            L_VERBOSE_LOG_newMsg(dlws,"Server don't love me (:-<)... ") ;
	return ok ;
      }


   /* ................................................................... */

