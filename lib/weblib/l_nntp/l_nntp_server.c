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

      #include "weblib/l_nntp/l_nntp_server.h"


   /* ... Functions / Funciones ......................................... */
  
      /*  Main Functions *
       * --------------- */
      T_BOOL  L_NNTP_SERVER_GetConnection   ( IN     t_nntpCfg      *nntpCfg,
                                              IN     t_url          *url,
                                              INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL           ok ;
        t_nntp_response  nntpr ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(nntpCfg,"NULL nntpCfg") ;
        L_DEBUG_NULL_E_F(url,"NULL url") ;
        L_DEBUG_NULL_E_F(dlws,"NULL dlws") ;

        /* ... connect ... */
        L_VERBOSE_LOG_newMsg(dlws,
                             "Trying connect %s... ",
                             url->machine) ;
        ok = L_NNTP_COMMAND_Connect( &(nntpCfg->sd),
                                     url->machine,
                                     url->port,
                                     &nntpr) ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... mode reader ... */
        ok = L_NNTP_COMMAND_mode_reader(&(nntpCfg->sd),&nntpr) ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... end ... */
        nntpCfg->connected = TRUE ;
        return TRUE ;
      }

      T_BOOL   L_NNTP_SERVER_Empty         ( INOUT  t_nntpCfg   *nntpCfg )
      {
        /* ... check params ... */
        L_DEBUG_NULL_E_F(nntpCfg,"NULL nntpCfg") ;

        X_ALLOC_Free((void **)&(nntpCfg->host)) ;
        if (nntpCfg->connected == TRUE)
           {
             X_SOCKET_Close(&(nntpCfg->sd)) ;
           }
        return TRUE ;
      }

      T_BOOL   L_NNTP_SERVER_Setup          ( OUT     t_nntpCfg      *nntpCfg,
                                              IN      t_url          *urlHost,
                                              INOUT   t_downLoadWS   *dlws )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(nntpCfg,"NULL nntpCfg") ;
        L_DEBUG_NULL_E_F(urlHost,"NULL urlHost") ;
        L_DEBUG_NULL_E_F(dlws,"NULL dlws") ;

        nntpCfg->host      = L_URL_UrlDup(urlHost) ;
	NULL_RET_FALSE(nntpCfg->host) ;
        nntpCfg->connected = FALSE ;
        ok = L_NNTP_SERVER_GetConnection(nntpCfg,urlHost,dlws) ;
        L_VERBOSE_LOG_newMsg(dlws,"\n\n") ;
	return ok ;
      }


   /* ................................................................... */

