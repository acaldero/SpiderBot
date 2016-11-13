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

      #include "weblib/l_vp/l_vp_server.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_VP_SERVER_SetupWebCfg   ( INOUT  t_downLoadWS   *dlws,
                                          OUT    t_httpCfg      *webCfg,
                                          IN     t_url          *purl )
      {
        T_BOOL     ok ;

        ok = L_HTTP_SERVER_Setup(webCfg,
                                 purl,
                                 dlws) ;
        FALSE_RET_FALSE(ok) ;
        if (dlws->detect_http == OFF)
           {
             webCfg->httpVer = v_1_0 ;
           }
        return TRUE ;
      }

      T_BOOL  L_VP_SERVER_SetupFtpCfg   ( INOUT  t_downLoadWS   *dlws,
                                          OUT    t_httpCfg      *webCfg,
                                          OUT    t_ftpCfg       *ftpCfg,
                                          IN     t_url          *purl )
      {
        T_BOOL  ok ;

        ok = L_FTP_SERVER_Setup(ftpCfg,
                                purl,
                                dlws) ;
        FALSE_RET_FALSE(ok) ;
        if (dlws->proxy != NULL)
           {
             ok = L_HTTP_SERVER_Setup(webCfg,
                                     &(dlws->proxyUrl),
                                      dlws) ;
             FALSE_RET_FALSE(ok) ;
           }
        return TRUE ;
      }

      T_BOOL  L_VP_SERVER_SetupFileCfg  ( INOUT  t_downLoadWS   *dlws,
                                          OUT    t_fileCfg      *fileCfg,
                                          IN     t_url          *purl )
      {
        T_BOOL  ok ;

        ok = L_FILE_SERVER_Setup(fileCfg,
                                 purl,
                                 dlws) ;

        return ok ;
      }

      T_BOOL  L_VP_SERVER_SetupNntpCfg   ( INOUT  t_downLoadWS   *dlws,
                                           OUT    t_httpCfg      *webCfg,
                                           OUT    t_nntpCfg      *nntpCfg,
                                           IN     t_url          *purl )
      {
        T_BOOL  ok ;

        ok = L_NNTP_SERVER_Setup(nntpCfg,
                                 purl,
                                 dlws) ;
        FALSE_RET_FALSE(ok) ;
        if (dlws->proxy != NULL)
           {
             ok = L_HTTP_SERVER_Setup(webCfg,
                                     &(dlws->proxyUrl),
                                      dlws) ;
             FALSE_RET_FALSE(ok) ;
           }
        return TRUE ;
      }

      T_BOOL  L_VP_SERVER_SetupPop3Cfg   ( INOUT  t_downLoadWS   *dlws,
                                           OUT    t_httpCfg      *webCfg,
                                           OUT    t_pop3Cfg      *pop3Cfg,
                                           IN     t_url          *purl )
      {
        T_BOOL  ok ;

        ok = L_POP3_SERVER_Setup(pop3Cfg,
                                 purl,
                                 dlws) ;
        FALSE_RET_FALSE(ok) ;
        if (dlws->proxy != NULL)
           {
             ok = L_HTTP_SERVER_Setup(webCfg,
                                     &(dlws->proxyUrl),
                                      dlws) ;
             FALSE_RET_FALSE(ok) ;
           }
        return TRUE ;
      }

      T_BOOL  L_VP_SERVER_SetupFingerCfg   ( INOUT  t_downLoadWS   *dlws,
                                             OUT    t_fingerCfg    *fingerCfg,
                                             IN     t_url          *purl )
      {
        T_BOOL  ok ;

        ok = L_FINGER_SERVER_Setup(fingerCfg,
                                   purl,
                                   dlws) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }


      T_BOOL  L_VP_SERVER_SetupSite     ( INOUT  t_downLoadWS   *dlws,
                                          INOUT  t_siteCfg      *siteCfg,
                                          IN     t_url          *purl )
      {
        T_BOOL ok ;

        ok = FALSE ;
        if (X_STRING_Equal(purl->protocol,"http") == TRUE)
           {
             ok = L_VP_SERVER_SetupWebCfg(dlws,
                                       &(siteCfg->webCfg),
                                       purl) ;
           }
        if (X_STRING_Equal(purl->protocol,"ftp") == TRUE)
           {
             ok = L_VP_SERVER_SetupFtpCfg(dlws,
                                       &(siteCfg->webCfg),
                                       &(siteCfg->ftpCfg),
                                       purl) ;
           }
        if (X_STRING_Equal(purl->protocol,"file") == TRUE)
           {
             ok = L_VP_SERVER_SetupFileCfg(dlws,
                                        &(siteCfg->fileCfg),
                                        purl) ;
           }
        if (
             (X_STRING_Equal(purl->protocol,"nntp") == TRUE)
                                ||
             (X_STRING_Equal(purl->protocol,"news") == TRUE)
           )
           {
             ok = L_VP_SERVER_SetupNntpCfg(dlws,
                                        &(siteCfg->webCfg),
                                        &(siteCfg->nntpCfg),
                                        purl) ;
           }
        if (X_STRING_Equal(purl->protocol,"pop3") == TRUE)
           {
             ok = L_VP_SERVER_SetupPop3Cfg(dlws,
                                        &(siteCfg->webCfg),
                                        &(siteCfg->pop3Cfg),
                                        purl) ;
           }
        if (X_STRING_Equal(purl->protocol,"finger") == TRUE)
           {
             ok = L_VP_SERVER_SetupFingerCfg(dlws,
                                        &(siteCfg->fingerCfg),
                                        purl) ;
           }
        return ok ;
      }

      T_BOOL  L_VP_SERVER_InitSite      ( OUT    t_siteCfg      *siteCfg )
      {
        L_HTTP_SERVER_SetDefault(&(siteCfg->webCfg)) ;
        L_FTP_SERVER_SetDefault(&(siteCfg->ftpCfg)) ;
        L_FILE_SERVER_SetDefault(&(siteCfg->fileCfg)) ;
        L_NNTP_SERVER_SetDefault(&(siteCfg->nntpCfg)) ;
        L_POP3_SERVER_SetDefault(&(siteCfg->pop3Cfg)) ;
        L_FINGER_SERVER_SetDefault(&(siteCfg->fingerCfg)) ;
        return TRUE ;
      }

      T_BOOL  L_VP_SERVER_FinalizeSite  ( OUT    t_siteCfg      *siteCfg )
      {
        L_HTTP_SERVER_Empty(&(siteCfg->webCfg)) ;
        L_FTP_SERVER_Empty(&(siteCfg->ftpCfg)) ;
        L_FILE_SERVER_Empty(&(siteCfg->fileCfg)) ;
        L_NNTP_SERVER_Empty(&(siteCfg->nntpCfg)) ;
        L_POP3_SERVER_Empty(&(siteCfg->pop3Cfg)) ;
        L_FINGER_SERVER_Empty(&(siteCfg->fingerCfg)) ;
        return TRUE ;
      }


   /* ................................................................... */

