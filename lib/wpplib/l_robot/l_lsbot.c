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

      #include "wpplib/l_robot/l_lsbot.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_LSBOT_CoreDownLoad  ( INOUT  t_downLoadWS   *dlws )
      {
        t_url      *purl, *purlAnt ;
        T_BOOL      ok, skip ;
        FILE       *fpage ;
        t_siteCfg   siteCfg ;

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
                 (X_STRING_Equal(purlAnt->protocol,purl->protocol) == FALSE)
               )
                 ||
               (
                 (X_STRING_Equal(purlAnt->machine,purl->machine) == FALSE)
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
	  fpage = tmpfile() ;      /* very important */
          NULL_RET_FALSE(fpage) ;  /* very important */
          ok    = L_VP_DOWNLOAD_DownLoadUrl(dlws,
                                            &siteCfg,
                                            purl,&fpage,&skip) ;
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
                         X_PRINT_printf("\n   try get it again...\n") ;
	                 continue ;
                       }
                  }
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
	       continue ;
	     }
          if (fpage == NULL)
             {
               /* url point to other machine, so no -global is set. */
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
               continue ;
             }
          if (L_WS_MANAGER_SkipParser(purl) == FALSE)
             {
               t_urlLi  diffUrlLi ;
 
               diffUrlLi.neltos = (dlws->urllist)->neltos ;
               rewind(fpage) ;
               ok = L_URLXML_GetPageUrls(fpage,dlws,purl) ;
               FALSE_RET_FALSE(ok) ;
               diffUrlLi.table  = (dlws->urllist)->table  + diffUrlLi.neltos ;
               diffUrlLi.neltos = (dlws->urllist)->neltos - diffUrlLi.neltos ;
               ok = L_URLLI_UrlLiToFile(&diffUrlLi,stdout) ;
               FALSE_RET_FALSE(ok) ;
             }
          fclose(fpage) ;
          purlAnt = purl ;
          L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
        } 
        L_WS_MANAGER_ResumeWS(dlws) ;
        if (dlws->verbose == ON)
            X_PRINT_printf("\r   End list process.             \n\n") ;
        L_VP_SERVER_FinalizeSite(&siteCfg) ;
        return ok ;
      }
  
      T_BOOL  L_LSBOT_DownLoadWeb  ( INOUT  t_downLoadWS  *dlws,
                                     IN     t_url         *url )
      {
        T_BOOL      ok ;
        pthread_t   pth_id_1 ;
        void       *pth_ret_1 ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... init ... */
        ok = L_WS_MANAGER_initUrlList(dlws,url) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_WS_MANAGER_initUrlListAccess(1) ;
        FALSE_RET_FALSE(ok) ;

        /* ... work ... */
        ok = X_THREAD_createJoinable(&pth_id_1,
                                     (t_thcode)L_LSBOT_CoreDownLoad,
                                     (void *)dlws) ;
        FALSE_RET_FALSE(ok) ;
        X_THREAD_join(pth_id_1,&pth_ret_1) ;

        /* ... finalize ... */
        L_WS_MANAGER_finalizeUrlListAccess() ;
        L_URLLI_Destroy(&(dlws->urllist)) ;
        return ok ;
      }

      T_BOOL  L_LSBOT_DownLoadRecover  ( INOUT  t_downLoadWS   *dlws )
      {
        T_BOOL      ok ;
        pthread_t   pth_id_1 ;
        void       *pth_ret_1 ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;

        /* ... init ... */
        ok = L_WS_MANAGER_initUrlListAccess(1) ;
        FALSE_RET_FALSE(ok) ;

        /* ... work ... */
        ok = X_THREAD_createJoinable(&pth_id_1,
                                     (t_thcode)L_LSBOT_CoreDownLoad,
                                     (void *)dlws) ;
        FALSE_RET_FALSE(ok) ;
        X_THREAD_join(pth_id_1,&pth_ret_1) ;

        /* ... finalize ... */
        L_WS_MANAGER_finalizeUrlListAccess() ;
        L_URLLI_Destroy(&(dlws->urllist)) ;
        return ok ;
      }
  

   /* ................................................................... */

