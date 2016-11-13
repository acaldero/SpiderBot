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
  
      T_BOOL  L_HTTP_SERVER_DISALLOW_GetDisallow 
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

        L_VERBOSE_LOG_newMsg(dlws,"Trying get /robots.txt... ") ;
        if (dlws->skipEL == TRUE)
           {
             L_VERBOSE_LOG_appendMsg(dlws,"-> SKIPED") ;
           }
        if (dlws->skipEL == FALSE)
           {
             /* ... Get /robots.txt ... */
             ok = L_HTTP10_PAGE_OpenPage2ToReadFile(dlws,
                                                    webCfg,
                                                    url->machine,
                                                    url->port,
                                                    "/robots.txt",
                                                    &httpr) ;
             FALSE_RET_FALSE(ok) ;

             /* ... read disallow ... */
             codigo = atoi(L_HTTP_RESPONSE_getField(httpr,"Codigo")) ;
             if (codigo < 400)
                 ok = L_DISALLOWLI_ReadDisallow( &(webCfg->disallowList),
                                                  (webCfg->sd).fsocket ) ;
             if (codigo < 400)
                      L_VERBOSE_LOG_appendMsg(dlws,"-> YES") ;
                 else L_VERBOSE_LOG_appendMsg(dlws,"-> NO") ;

             /* ... return resource ... */
             L_HTTP_RESPONSE_Destroy(&(httpr)) ;
             L_HTTP10_COMMAND_Close(&(webCfg->sd)) ;
             webCfg->connected = FALSE ;
           }

        return TRUE ;
      }


   /* ................................................................... */

