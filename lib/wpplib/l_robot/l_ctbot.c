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

      #include "wpplib/l_robot/l_ctbot.h"


   /* ... Functions / Funciones ......................................... */

      T_INT   L_CTBOT_Print          ( IN     const T_CHAR   *fto,
                                       IN     va_list         va )
      {
        return vfprintf(stderr,fto,va) ;
      }

      T_BOOL  L_CTBOT_CoreDownLoad  ( INOUT  t_downLoadWS   *dlws )
      {
        t_url      *purl, *purlAnt ;
        T_BOOL      ok, skip ;
        T_CHAR     *fnpage ;
        FILE       *fpage ;
        t_siteCfg   siteCfg ;

        ok      = TRUE ;
        purlAnt = NULL ;
        X_PRINT_setPrintWrapper(L_CTBOT_Print) ;
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
          fnpage = tmpnam(NULL) ;          /* very important */
          NULL_RET_FALSE(fnpage) ;         /* very important */
          fpage  = fopen(fnpage,"w+b") ;   /* very important */
          NULL_RET_FALSE(fpage) ;          /* very important */
          ok     = L_VP_DOWNLOAD_DownLoadUrl( dlws,
                                              &siteCfg,
                                               purl, 
                                              &fpage,
                                              &skip ) ;
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
          if (
               (dlws->skipBin == ON)
                        &&
               (L_URLFILE_IsBin(purl->file) == TRUE)
             )
             {
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
               fclose(fpage) ;
               continue ;
             }
          if (dlws->mirrorSelection != c_MS_1_PAGE)
             {
               T_BOOL  updated ;

               /* ... page content ... */
               rewind(fpage) ;
               ok = L_URLXML_AjustPageUrls(fpage,stdout,&updated,dlws,purl) ;
               fclose(fpage) ;
               unlink(fnpage) ;
               FALSE_RET_FALSE(ok) ;

               /* ... next page ... */
               purlAnt = purl ;
               L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
               continue ;
             }
          if (L_URLFILE_IsBin(purl->file) == FALSE)
             {
               T_CHAR *strurl ;
               T_BOOL  updated ;

               /* ... page name ... */
               strurl = L_URLFILE_MirrorUrlName(purl,c_MS_1_PAGE) ;
               fprintf(stdout,
                       "\n"
                       "<a name=\"%s\"><hr></a>"
                       "\n",
                       strurl+1 /* skip '#' */) ;
               X_ALLOC_Free((void **)&strurl) ;

               /* ... page content ... */
               rewind(fpage) ;
               ok = L_URLXML_AjustPageUrls(fpage,stdout,&updated,dlws,purl) ;
               fclose(fpage) ;
               unlink(fnpage) ;
               FALSE_RET_FALSE(ok) ;
             }
          else 
             {
               T_CHAR *strurl ;

               /* ... page name ... */
               strurl = L_URLFILE_MirrorUrlName(purl,c_MS_N_DIRECTORY) ;

               /* ... store page ... */
               fclose(fpage) ;
               L_FILE_Move(fnpage,strurl) ;
               X_ALLOC_Free((void **)&strurl) ;
             }
          purlAnt = purl ;
          L_WS_MANAGER_getNextUrl(dlws,&(purl)) ;
        } 
        L_WS_MANAGER_ResumeWS(dlws) ;
        if (dlws->verbose == ON)
            X_PRINT_printf("\r   End cat process.             \n\n") ;
        L_VP_SERVER_FinalizeSite(&siteCfg) ;
        return ok ;
      }
  
      T_BOOL  L_CTBOT_DownLoadWeb  ( INOUT  t_downLoadWS  *dlws,
                                     IN     t_url         *url )
      {
        T_BOOL      ok ;
        pthread_t   pth_id_1 ;
        void       *pth_ret_1 ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... init ... */
        ok = L_WS_MANAGER_initUrlList(dlws,url) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_WS_MANAGER_initUrlListAccess(1) ;
        FALSE_RET_FALSE(ok) ;

        /* ... work ... */
        ok = X_THREAD_createJoinable(&pth_id_1,
                                     (t_thcode)L_CTBOT_CoreDownLoad,
                                     (void *)dlws) ;
        FALSE_RET_FALSE(ok) ;
        X_THREAD_join(pth_id_1,&pth_ret_1) ;

        /* ... finalize ... */
        L_WS_MANAGER_finalizeUrlListAccess() ;
        L_URLLI_Destroy(&(dlws->urllist)) ;
        return ok ;
      }

      T_BOOL  L_CTBOT_DownLoadRecover  ( INOUT  t_downLoadWS   *dlws )
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
                                     (t_thcode)L_CTBOT_CoreDownLoad,
                                     (void *)dlws) ;
        FALSE_RET_FALSE(ok) ;
        X_THREAD_join(pth_id_1,&pth_ret_1) ;

        /* ... finalize ... */
        L_WS_MANAGER_finalizeUrlListAccess() ;
        L_URLLI_Destroy(&(dlws->urllist)) ;
        return ok ;
      }
  

   /* ................................................................... */

