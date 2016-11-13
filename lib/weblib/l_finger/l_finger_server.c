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

      #include "weblib/l_finger/l_finger_server.h"


   /* ... Functions / Funciones ......................................... */
  
      /*  Main Functions *
       * --------------- */
      T_BOOL  L_FINGER_SERVER_GetConnection   ( IN     t_fingerCfg       *fingerCfg,
                                                IN     t_url          *url,
                                                INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL         ok ;
        t_finger_response fingerr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... connect ... */
        L_VERBOSE_LOG_newMsg(dlws,
                             "Trying connect %s... ",
                             url->machine) ;
        ok = L_FINGER_COMMAND_Connect( &(fingerCfg->sd),
                                       url->machine,
                                       url->port,    /*check* htons(79),*/
                                       &(fingerr) ) ;
        L_FINGER_LOG_PrintResponse(dlws->finfo,&fingerr) ;
        L_FINGER_RESPONSE_Empty(&fingerr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... end ... */
        fingerCfg->connected = TRUE ;
        return TRUE ;
      }

      T_BOOL   L_FINGER_SERVER_Empty         ( INOUT  t_fingerCfg   *fingerCfg )
      {
        t_finger_response fingerr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;

        if (fingerCfg->connected == TRUE)
           {
             L_FINGER_COMMAND_Close(&(fingerCfg->sd),&fingerr) ;
             fingerCfg->connected = FALSE ;
           }
        X_ALLOC_Free((void **)&(fingerCfg->host)) ;
        return TRUE ;
      }

      T_BOOL   L_FINGER_SERVER_Setup          ( OUT     t_fingerCfg      *fingerCfg,
                                                IN      t_url         *urlHost,
                                                INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;
        NULL__SET_ERROR__RET_FALSE(urlHost) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        fingerCfg->host = L_URL_UrlDup(urlHost) ;
	NULL_RET_FALSE(fingerCfg->host) ;
        fingerCfg->connected = FALSE ;
        ok = L_FINGER_SERVER_GetConnection(fingerCfg,urlHost,dlws) ;
        if (ok == FALSE)
            L_VERBOSE_LOG_newMsg(dlws,"Server refuse me (:-<)... ") ;
        L_VERBOSE_LOG_newMsg(dlws,"\n\n") ;
	return ok ;
      }


   /* ................................................................... */

