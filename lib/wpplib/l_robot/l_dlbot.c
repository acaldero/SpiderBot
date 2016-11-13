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

      #include "wpplib/l_robot/l_dlbot.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_DLBOT_CoreDownLoad  ( INOUT  t_downLoadWS   *dlws )
      {
        t_url       *purl, *purlAnt ;
        T_BOOL       ok, skip ;
        FILE        *fpage ;
        t_siteCfg    siteCfg ;

        /* ... thread started ... */
        X_THREAD_lock( &(dlws->ws_mtsda) ) ;
        X_THREAD_signalReady( &(dlws->ws_mtsda) ) ;
        X_THREAD_unlock( &(dlws->ws_mtsda) ) ;

        ok      = TRUE ;
        purlAnt = NULL ;
        L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
        if (purl != NULL)
           {
             L_WS_MANAGER_ResumeWS(dlws) ;
           }
        L_VP_SERVER_InitSite(&siteCfg) ;

        while (purl != NULL)
        {
          if (
               (
                 (purlAnt == NULL)
               )
                 ||
               (
                 (L_URL_EqualProtocol(purlAnt,purl) == FALSE)
               )
                 ||
               (
                 (L_URL_EqualMachine(purlAnt,purl) == FALSE)
                                &&
                 (dlws->scanSelection == c_SS_GLOBAL) 
               )
             )
             {
               L_VP_SERVER_FinalizeSite(&siteCfg) ;
               fflush(stdout) ;
               ok = L_VP_SERVER_SetupSite(dlws,
                                        &siteCfg,
                                        purl) ;
               if (ok == FALSE)
                  {
                    purlAnt = purl ;
                    L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
	            continue ;
                  }
             }
          if (dlws->currentBytes > dlws->maxBytes)
             {
               L_WS_MANAGER_ResumeWS(dlws) ;
               if (dlws->verbose == ON)
                   X_PRINT_printf("\n\r   End download : reached maxBytes     \n\n") ;
               return TRUE ;
             }
          if (dlws->i > dlws->maxUrls)
             {
               L_WS_MANAGER_ResumeWS(dlws) ;
               if (dlws->verbose == ON)
                   X_PRINT_printf("\n\r   End download : reached maxUrls      \n\n") ;
               return TRUE ;
             }
          if (dlws->delay != 0)
             {
               sleep(dlws->delay) ;
             }

          /* ... download ... */
	  fpage = NULL ; /* very important */
          ok    = L_VP_DOWNLOAD_DownLoadUrl(dlws,
                                            &siteCfg,
                                            purl,
                                            &fpage,
                                            &skip) ;
          if (skip == TRUE)
             {
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
     	       continue ;
             }
     
	  if (ok == FALSE)
	     {
	       if (fpage != NULL)
                  {
                    fclose(fpage) ;
                    if (dlws->rentry == TRUE)
                       {
                         X_PRINT_printf("\n   try full download again...\n") ;
	                 continue ;
                       }
                  }
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
	       continue ;
	     }
          if (fpage == NULL)
             {
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
               continue ;
             }
          if (L_WS_MANAGER_SkipParser(purl) == FALSE)
             {
               L_WS_MANAGER_AddPageUrls(dlws,purl,fpage) ;
             }
          fclose(fpage) ;
          purlAnt = purl ;
          L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
        } 
        L_WS_MANAGER_ResumeWS(dlws) ;
        if (dlws->verbose == ON)
            X_PRINT_printf("\r   End download process.             \n\n") ;
        L_VP_SERVER_FinalizeSite(&siteCfg) ;
        return ok ;
      }
  
      T_BOOL  L_DLBOT_LaunchDownLoad ( INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL      ok ;
        T_INT       i, nprocessors ;
        pthread_t   *pth_id ;
        void       **pth_ret ;

        /* ... init ... */
        nprocessors = 1 ;
#if (defined(HAVE_PTHREAD_H))
        nprocessors = sysconf(_SC_NPROCESSORS_CONF) ;
        if (nprocessors < c_MIN_CLONES)
            nprocessors = c_MIN_CLONES ;
        if (nprocessors > c_MAX_CLONES)
            nprocessors = c_MAX_CLONES ;
#endif
        ok = L_WS_MANAGER_initUrlListAccess(nprocessors) ;
        FALSE_RET_FALSE(ok) ;

        /* ... work ... */
        pth_id  = X_ALLOC_Malloc(nprocessors * sizeof(pthread_t)) ;
        NULL_RET_FALSE(pth_id) ;
        pth_ret = X_ALLOC_Malloc(nprocessors * sizeof(void *)) ;
        NULL_RET_FALSE(pth_ret) ;
        X_THREAD_init( &(dlws->ws_mtsda) ) ;
        for (i=0; i<nprocessors; i++)
            {
              if (dlws->verbose == ON)
                 {
                   if (nprocessors > 1)
                      {
                        fflush(stdout) ;
                        X_PRINT_printf("\tNew Clone[%i] ...", i) ;
                      }
                   fflush(stdout) ;
                 }
              X_THREAD_lock( &(dlws->ws_mtsda) ) ;
              ok = X_THREAD_createJoinable( &(pth_id[i]),
                                            (t_thcode)L_DLBOT_CoreDownLoad,
                                            (void *)dlws ) ;
              X_THREAD_waitReady( &(dlws->ws_mtsda) ) ;
              X_THREAD_unlock( &(dlws->ws_mtsda) ) ;
              if (ok == FALSE)
                  break ;
            }
        X_THREAD_destroy( &(dlws->ws_mtsda) ) ;
        for (i=0; i<nprocessors; i++)
            {
              X_THREAD_join(pth_id[i],&(pth_ret[i])) ;
            }
        X_ALLOC_Free((void **)&pth_id) ;
        X_ALLOC_Free((void **)&pth_ret) ;

        /* ... finalize ... */
        L_WS_MANAGER_finalizeUrlListAccess() ;
        L_URLLI_Destroy(&(dlws->urllist)) ;
        return ok ;
      }

      T_BOOL  L_DLBOT_DownLoadWeb  ( INOUT  t_downLoadWS  *dlws,
                                     IN     t_url         *url )
      {
        T_BOOL      ok ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        ok = L_WS_MANAGER_initUrlList(dlws,url) ;
        FALSE_RET_FALSE(ok) ;
        return L_DLBOT_LaunchDownLoad(dlws) ;
      }

      T_BOOL  L_DLBOT_DownLoadRecover  ( INOUT  t_downLoadWS   *dlws )
      {
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        return L_DLBOT_LaunchDownLoad(dlws) ;
      }
  

   /* ................................................................... */

