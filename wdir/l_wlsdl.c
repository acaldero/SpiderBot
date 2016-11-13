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

      #include "wdir/l_wlsdl.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_WLSDL_DownLoadStart   ( IN    t_wppOptions  *wppOpt )
      {
        T_CHAR         *fname ;
        t_url           url ;
        T_BOOL          ok ;
        FILE           *flog, *fres ;
        t_downLoadWS    dlws ;

        ok    = L_URLSTR_StringToUrl(&url,wppOpt->href) ;
        FALSE_RET_FALSE(ok) ;

        /* ... fichero traza */
        fname = X_STRING_ConcatInStr("resume",".",url.machine) ;
        NULL_RET_FALSE(fname) ;
        fres  = fopen(fname,"w") ;
        X_ALLOC_Free((void **)&fname) ;
        NULL_RET_FALSE(fres) ;
        setbuf(fres,NULL) ;

        /* ... fichero log */
        fname = X_STRING_ConcatInStr("log",".",url.machine) ;
        if (fname == NULL)
           {
             fclose(fres) ;
             return FALSE ;
           }
        flog  = fopen(fname,"a") ;
        X_ALLOC_Free((void **)&fname) ;
        if (flog == NULL)
           {
             fclose(fres) ;
             return FALSE ;
           }
        setbuf(flog,NULL) ;
        ok    = L_LOG_Setup(flog,c_WDIR_VER) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }

        /* ... setup options */
        ok    = L_SETWS_WorkSpaceSetup
                ( 
                  &dlws,
                   flog,
                   fres,
                   c_WDIR_VER,
                   c_WDIR_ID,
                   wppOpt->identification,
                   wppOpt->proxy,
                   (wppOpt->makeRelative_f == ON) ? c_RS_ALL_SITE : c_RS_NONE,
                   (wppOpt->scanGlobal_f   == ON) ? c_SS_GLOBAL : c_SS_LOCAL,
                   (wppOpt->onlyHttp_f     == ON) ? c_PS_HTTP : c_PS_ALL,
                   c_MS_N_DIRECTORY,
                   wppOpt->detectHttp_f,
                   wppOpt->verbose_f,
                   wppOpt->fromSamePath_f,
                   wppOpt->skipBin_f,
                   wppOpt->skipEL_f,
                   wppOpt->rentry_f,
                   wppOpt->makeQuery_f,
                   wppOpt->maxBytes,
                   wppOpt->maxUrls,
                   wppOpt->delay,
                   wppOpt->bufSize,
                   wppOpt->timeLimit,
                   wppOpt->resumeFrec
                ) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }
        ok    = L_LSBOT_DownLoadWeb(&dlws,&url) ;
        fclose(flog) ;
        fclose(fres) ;
        return ok ;
      }

      T_BOOL  L_WLSDL_DownLoadRecover    ( IN    t_wppOptions  *wppOpt )
      {
        T_CHAR         *fname ;
        T_CHAR         *bname ;
        T_BOOL          ok ;
        FILE           *flog, *fres ;
        t_downLoadWS    dlws ;

        /* ... fichero traza */
        fres  = fopen(wppOpt->recoverFile,"r+") ;
        if (fres == NULL)
           {
             X_PRINT_printf(" Recover file ('%s') can NOT be open, sorry.\n",
                            wppOpt->recoverFile) ;
             return FALSE ;
           }
        setbuf(fres,NULL) ;

        /* ... fichero log */
        bname = wppOpt->recoverFile ;
        if (bname != NULL)
            bname = X_STRING_StrChr(bname,'.') ;
        if (bname == NULL)
            bname = ".unknow" ;
        fname = X_STRING_ConcatInStr("log","",bname) ;
        if (fname == NULL)
           {
             fclose(fres) ;
             return FALSE ;
           }
        flog  = fopen(fname,"a") ;
        X_ALLOC_Free((void **)&fname) ;
        if (flog == NULL)
           {
             fclose(fres) ;
             return FALSE ;
           }
        ok    = L_LOG_Setup(flog,c_WDIR_VER) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }

        /* ... setup options */
        ok    = L_SETWS_WorkSpaceSetup
                ( 
                  &dlws,
                   flog,
                   fres,
                   c_WDIR_VER,
                   c_WDIR_ID,
                   wppOpt->identification,
                   wppOpt->proxy,
                   (wppOpt->makeRelative_f == ON) ? c_RS_ALL_SITE : c_RS_NONE,
                   (wppOpt->scanGlobal_f   == ON) ? c_SS_GLOBAL : c_SS_LOCAL,
                   (wppOpt->onlyHttp_f     == ON) ? c_PS_HTTP : c_PS_ALL,
                   c_MS_N_DIRECTORY,
                   wppOpt->detectHttp_f,
                   wppOpt->verbose_f,
                   wppOpt->fromSamePath_f,
                   wppOpt->skipBin_f,
                   wppOpt->skipEL_f,
                   wppOpt->rentry_f,
                   wppOpt->makeQuery_f,
                   wppOpt->maxBytes,
                   wppOpt->maxUrls,
                   wppOpt->delay,
                   wppOpt->bufSize,
                   wppOpt->timeLimit,
                   wppOpt->resumeFrec
                ) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }
        ok = L_SETWS_WorkSpaceRecover(fres,&dlws) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }

        /* ... go recover ... */
        ok = L_LSBOT_DownLoadRecover(&dlws) ;
        fclose(flog) ;
        fclose(fres) ;
        return ok ;
      }

      T_BOOL  L_WLSDL_DownLoad    ( IN   t_wppOptions    *wppOpt )
      {
        T_BOOL      ok ;

        ok = FALSE ;
        if ( (wppOpt->href == NULL) && (wppOpt->recoverFile != NULL) )
              ok = L_WLSDL_DownLoadRecover(wppOpt) ;
        if ( (wppOpt->href != NULL) && (wppOpt->recoverFile == NULL) )
              ok = L_WLSDL_DownLoadStart(wppOpt) ;
        return ok ;
      }


   /* ................................................................... */

