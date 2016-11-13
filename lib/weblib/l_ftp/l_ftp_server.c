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

      #include "weblib/l_ftp/l_ftp_server.h"


   /* ... Functions / Funciones ......................................... */
  
      /*  Main Functions *
       * --------------- */
      T_BOOL  L_FTP_SERVER_GetConnection   ( IN     t_ftpCfg       *ftpCfg,
                                             IN     t_url          *url,
                                             INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL         ok ;
        t_ftp_response ftpr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(ftpCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... connect ... */
        L_VERBOSE_LOG_newMsg(dlws,
                             "Trying connect %s... ",
                             url->machine) ;
        ok = L_FTP_COMMAND_Connect( &(ftpCfg->sd),
                                    url->machine,
                                    url->port,    /*check* htons(21),*/
                                    &(ftpr) ) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... intro ... */
        if ( 
             (dlws->identification == NULL) 
                    || 
             (dlws->identification[0] == '\0')
           )
           {
             L_VERBOSE_LOG_newMsg(dlws,"Trying intro as anonymous (ftp)... ") ;
             ok = L_FTP_COMMAND_user( &(ftpCfg->sd),
                                      "anonymous",
                                      &ftpr ) ;
             L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
             L_FTP_RESPONSE_Empty(&ftpr) ;
             FALSE_RET_FALSE(ok) ;
             ok = L_FTP_COMMAND_pass( &(ftpCfg->sd),
                                      "joe@localdomain.localhost",
                                      &ftpr ) ;
             L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
             L_FTP_RESPONSE_Empty(&ftpr) ;
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
                      ok = L_FTP_COMMAND_user( &(ftpCfg->sd),
                                               dlws->identification,
                                               &ftpr ) ;
                      L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
                      L_FTP_RESPONSE_Empty(&ftpr) ;
                      pch[0] = ':' ;
                      FALSE_RET_FALSE(ok) ;
                      ok = L_FTP_COMMAND_pass( &(ftpCfg->sd),
                                               pch + 1,
                                               &ftpr ) ;
                      L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
                      L_FTP_RESPONSE_Empty(&ftpr) ;
                      FALSE_RET_FALSE(ok) ;
                }
             if (pch == NULL)
                {
                      ok = L_FTP_COMMAND_user( &(ftpCfg->sd),
                                               dlws->identification,
                                               &ftpr ) ;
                      L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
                      L_FTP_RESPONSE_Empty(&ftpr) ;
                      FALSE_RET_FALSE(ok) ;
                      ok = L_FTP_COMMAND_pass( &(ftpCfg->sd),
                                               "",
                                               &ftpr ) ;
                      L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
                      L_FTP_RESPONSE_Empty(&ftpr) ;
                      FALSE_RET_FALSE(ok) ;
                }
          }

        /* ... bin ... */
        L_VERBOSE_LOG_newMsg(dlws,"Trying set binary... ") ;
        ok = L_FTP_COMMAND_bin(&(ftpCfg->sd),&ftpr) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... end ... */
        ftpCfg->connected = TRUE ;
        return TRUE ;
      }

      T_BOOL   L_FTP_SERVER_Empty         ( INOUT  t_ftpCfg   *ftpCfg )
      {
        t_ftp_response ftpr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(ftpCfg) ;

        if (ftpCfg->connected == TRUE)
           {
             L_FTP_COMMAND_Close(&(ftpCfg->sd),&ftpr) ;
             ftpCfg->connected = FALSE ;
           }
        X_ALLOC_Free((void **)&(ftpCfg->host)) ;
        return TRUE ;
      }

      T_BOOL   L_FTP_SERVER_Setup          ( OUT     t_ftpCfg      *ftpCfg,
                                             IN      t_url         *urlHost,
                                             INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(ftpCfg) ;
        NULL__SET_ERROR__RET_FALSE(urlHost) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;

        ftpCfg->host      = L_URL_UrlDup(urlHost) ;
	NULL_RET_FALSE(ftpCfg->host) ;
        ftpCfg->connected = FALSE ;
        ok = L_FTP_SERVER_GetConnection(ftpCfg,urlHost,dlws) ;
        if (ok == FALSE)
            L_VERBOSE_LOG_newMsg(dlws,"Server refuse me (:-<)... ") ;
        L_VERBOSE_LOG_newMsg(dlws,"\n\n") ;
	return ok ;
      }


   /* ................................................................... */

