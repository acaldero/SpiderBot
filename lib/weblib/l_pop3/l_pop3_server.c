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

      #include "weblib/l_pop3/l_pop3_server.h"


   /* ... Functions / Funciones ......................................... */
  
      /*  Main Functions *
       * --------------- */
      T_BOOL  L_POP3_SERVER_GetConnection   ( IN      t_pop3Cfg     *pop3Cfg,
                                              IN      t_url         *url,
                                              INOUT   t_downLoadWS  *dlws )
      {
        T_BOOL           ok ;
        t_pop3_response  pop3r ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... connect ... */
        L_VERBOSE_LOG_newMsg(dlws,
                             "Trying connect %s... ",
                             url->machine) ;
        ok = L_POP3_COMMAND_Connect(&(pop3Cfg->sd),
                                    url->machine,
                                    url->port,
                                    &(pop3r)) ;
        L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
        L_POP3_RESPONSE_Empty(&pop3r) ;
        FALSE_RET_FALSE(ok) ;

        /* ... intro ... */
        if ( 
              (dlws->identification == NULL) 
                           || 
              (dlws->identification[0] == '\0') 
           )
           {
             L_VERBOSE_LOG_newMsg(dlws,"Trying intro as anonymous (pop3)... ") ;
             ok = L_POP3_COMMAND_user( &(pop3Cfg->sd),
                                       "anonymous",
                                       &pop3r) ;
             L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
             L_POP3_RESPONSE_Empty(&pop3r) ;
             FALSE_RET_FALSE(ok) ;
             ok = L_POP3_COMMAND_pass( &(pop3Cfg->sd),
                                       "joe@localdomain.localhost",
                                       &pop3r) ;
             L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
             L_POP3_RESPONSE_Empty(&pop3r) ;
             FALSE_RET_FALSE(ok) ;
           }
        else
           {
             T_CHAR *pch ;

             L_VERBOSE_LOG_newMsg(dlws,"Trying intro as user... ") ;
             pch = strchr(dlws->identification,':') ;
             if (pch != NULL)
                {
                      pch[0] = '\0' ;
                      ok = L_POP3_COMMAND_user( &(pop3Cfg->sd),
                                                dlws->identification,
                                                &pop3r ) ;
                      L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
                      L_POP3_RESPONSE_Empty(&pop3r) ;
                      pch[0] = ':' ;
                      FALSE_RET_FALSE(ok) ;
                      ok = L_POP3_COMMAND_pass( &(pop3Cfg->sd),
                                                pch+1,
                                                &pop3r ) ;
                      L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
                      L_POP3_RESPONSE_Empty(&pop3r) ;
                      FALSE_RET_FALSE(ok) ;
                }
             else /* (pch == NULL) */
                {
                      ok = L_POP3_COMMAND_user( &(pop3Cfg->sd),
                                                dlws->identification,
                                                &pop3r ) ;
                      L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
                      L_POP3_RESPONSE_Empty(&pop3r) ;
                      FALSE_RET_FALSE(ok) ;
                      ok = L_POP3_COMMAND_pass( &(pop3Cfg->sd),
                                                "",
                                                &pop3r ) ;
                      L_POP3_LOG_PrintResponse(dlws->finfo,&pop3r) ;
                      L_POP3_RESPONSE_Empty(&pop3r) ;
                      FALSE_RET_FALSE(ok) ;
                }
           }

        /* ... end ... */
        pop3Cfg->connected = TRUE ;
        return TRUE ;
      }

      T_BOOL   L_POP3_SERVER_Empty         ( INOUT  t_pop3Cfg   *pop3Cfg )
      {
        t_pop3_response  pop3r ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;

        if (pop3Cfg->connected == TRUE)
           {
             L_POP3_COMMAND_Close(&(pop3Cfg->sd),&pop3r) ;
             pop3Cfg->connected = FALSE ;
           }
        X_ALLOC_Free((void **)&(pop3Cfg->host)) ;
        return TRUE ;
      }

      T_BOOL   L_POP3_SERVER_Setup          ( OUT     t_pop3Cfg      *pop3Cfg,
                                              IN      t_url          *urlHost,
                                              INOUT   t_downLoadWS   *dlws )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;
        NULL__SET_ERROR__RET_FALSE(urlHost) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        pop3Cfg->host      = L_URL_UrlDup(urlHost) ;
	NULL_RET_FALSE(pop3Cfg->host) ;
        pop3Cfg->connected = FALSE ;
        ok = L_POP3_SERVER_GetConnection(pop3Cfg,urlHost,dlws) ;
        if (ok == FALSE)
            L_VERBOSE_LOG_newMsg(dlws,"Server refuse me (:-<)... ") ;
        L_VERBOSE_LOG_newMsg(dlws,"\n\n") ;
	return ok ;
      }


   /* ................................................................... */

