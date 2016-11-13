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

      #include "wpplib/l_data/l_ws_manager.h"


   /* ... Global var. / Var. Globales ................................... */

      t_mtsda   L_WS_MANAGER_urlli ;
      T_INT     L_WS_MANAGER_nThreads = 0 ;
      T_INT     L_WS_MANAGER_nWaiting = 0 ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_WS_MANAGER_initUrlListAccess   ( IN     T_INT       nThreads )
      {
        X_THREAD_init( &(L_WS_MANAGER_urlli) ) ;
        L_WS_MANAGER_nThreads = nThreads ;
        return TRUE ;
      }

      T_BOOL  L_WS_MANAGER_finalizeUrlListAccess ( void )
      {
        X_THREAD_destroy( &(L_WS_MANAGER_urlli) ) ;
        return TRUE ;
      }

      T_BOOL  L_WS_MANAGER_ResumeWS            ( IN     t_downLoadWS  *dlws )
      {
        X_THREAD_lock( &(L_WS_MANAGER_urlli) ) ;
        L_SETWS_WorkSpaceResume(dlws) ;
        X_THREAD_unlock( &(L_WS_MANAGER_urlli) ) ;
        return TRUE ;
      }

      T_BOOL  L_WS_MANAGER_initUrlList   ( INOUT  t_downLoadWS  *dlws,
                                           IN     t_url         *url )
      {
        T_BOOL  ok ;

        NULL_RET_FALSE(url) ;
        dlws->urllist      = L_URLLI_Creat() ;
        NULL_RET_FALSE(dlws->urllist) ;
        ok = L_URLLI_Insert(dlws->urllist,url) ;
        FALSE_RET_FALSE(ok) ;
        dlws->currentBytes = 0L ;
        dlws->i            = 0 ;
        return ok ;
      }

      T_BOOL  L_WS_MANAGER_getNextUrl    ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_url         **purl )
      {
        X_THREAD_lock( &(L_WS_MANAGER_urlli) ) ;

        /* try get urllist[i] ... */
        (*purl) = L_URLLI_UrlIn(dlws->urllist,dlws->i) ;
        if ( (*purl) == NULL )
           {
             L_WS_MANAGER_nWaiting ++ ;
             if (L_WS_MANAGER_nWaiting >= L_WS_MANAGER_nThreads)
                {
                  X_THREAD_signalReady( &(L_WS_MANAGER_urlli) ) ;
                }
             else 
                {
                  X_THREAD_waitReady( &(L_WS_MANAGER_urlli) ) ;
                  (*purl) = L_URLLI_UrlIn(dlws->urllist,dlws->i) ;
                }
             L_WS_MANAGER_nWaiting -- ;
           }

        /* urllist[i] or NULL ... */
        (dlws->i)++ ;
        if ( (dlws->i) % (dlws->resumeFrec) == 0)
              L_SETWS_WorkSpaceResume(dlws) ;

        X_THREAD_unlock( &(L_WS_MANAGER_urlli) ) ;
        return TRUE ;
      }

      T_BOOL  L_WS_MANAGER_AddPageUrls   ( INOUT  t_downLoadWS   *dlws,
                                           INOUT  t_url          *purl,
                                           INOUT  FILE           *fpage )
      {
        T_BOOL  ok ;

        ok = TRUE ;

        X_THREAD_lock( &(L_WS_MANAGER_urlli) ) ;
        if (dlws->rewriteSelection == c_RS_NONE)
           {
             rewind(fpage) ;
             ok = L_URLXML_GetPageUrls(fpage,dlws,purl) ;
           }

        if (dlws->rewriteSelection != c_RS_NONE)
           {
             FILE   *fajust ;
             T_BOOL  ok, updated ;
             T_INT   nbytes ;
 
             fajust = tmpfile() ;
             rewind(fpage) ;
             ok = L_URLXML_AjustPageUrls( fpage,
                                          fajust,
                                          &updated,
                                          dlws,
                                          purl) ;
             if ( (ok == TRUE) && (updated == TRUE) )
                {
                  fseek(fajust,0,SEEK_END) ;
                  nbytes = ftell(fajust) ;
                  rewind(fpage) ;
                  rewind(fajust) ;
                  ftruncate(fileno(fpage),0) ;
                  ok = L_FILE_CopyFile(fajust,fpage,nbytes) ;
                }
             fclose(fajust) ;
           }

        X_THREAD_signalReady( &(L_WS_MANAGER_urlli) ) ;
        X_THREAD_unlock( &(L_WS_MANAGER_urlli) ) ;
        return ok ;
      }


   /* ................................................................... */

