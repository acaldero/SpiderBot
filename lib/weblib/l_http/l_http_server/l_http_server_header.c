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
  
      T_BOOL  L_HTTP_SERVER_HEADER_acceptFullURL     
      ( 
        IN     t_httpCfg      *webCfg,
        IN     t_url          *url,
        INOUT  t_downLoadWS   *dlws 
      )
      {
        T_BOOL            ok ;
        t_http_response  *httpr ;
        T_INT             codigo ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... request full url ... */
        L_VERBOSE_LOG_newMsg(dlws,"Trying uses full url... ") ;
        webCfg->acceptFullUrl = TRUE ;
        ok = L_HTTP10_PAGE_OpenPage2ToReadFile(dlws,
                                               webCfg,
                                               url->machine,
                                               url->port,
                                               "/",
                                               &httpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... read code ... */
        codigo = atoi(L_HTTP_RESPONSE_getField(httpr,"Codigo")) ;
        if (codigo < 400)
                 webCfg->acceptFullUrl = TRUE ;
            else webCfg->acceptFullUrl = FALSE ;
        if (codigo < 400)
                 L_VERBOSE_LOG_appendMsg(dlws,"-> YES") ;
            else L_VERBOSE_LOG_appendMsg(dlws,"-> NO") ;

        /* ... return resource ... */
        L_HTTP_RESPONSE_Destroy(&(httpr)) ;
        L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
        webCfg->connected = FALSE ;
        return ok ;
      }

      T_BOOL  L_HTTP_SERVER_HEADER_acceptHost        
      ( 
        IN     t_httpCfg      *webCfg,
        IN     t_url          *url,
        INOUT  t_downLoadWS   *dlws 
      )
      {
        T_BOOL            ok ;
        t_http_response  *httpr ;
        T_INT             codigo ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(webCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... request full url ... */
        L_VERBOSE_LOG_newMsg(dlws,"Trying uses host field... ") ;
        webCfg->acceptHost = TRUE ;
        ok = L_HTTP10_PAGE_OpenPage2ToReadFile(dlws,
                                               webCfg,
                                               url->machine,
                                               url->port,
                                               "/",
                                               &httpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... read code ... */
        codigo = atoi(L_HTTP_RESPONSE_getField(httpr,"Codigo")) ;
        if (codigo < 400)
                 webCfg->acceptHost = TRUE ;
            else webCfg->acceptHost = FALSE ;
        if (codigo < 400)
                 L_VERBOSE_LOG_appendMsg(dlws,"-> YES") ;
            else L_VERBOSE_LOG_appendMsg(dlws,"-> NO") ;

        /* ... return resource ... */
        L_HTTP_RESPONSE_Destroy(&(httpr)) ;
        L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
        webCfg->connected = FALSE ;
        return ok ;
      }


   /* ................................................................... */

