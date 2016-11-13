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

      #include "SpiderBot/l_sbotdl.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_SBOTDL_DownLoadStart   ( IN    t_wppOptions  *wOpt )
      {
        T_CHAR         *fname ;
        t_url           url ;
        T_BOOL          ok ;
        FILE           *flog, *fres ;
        t_downLoadWS    dlws ;

        ok    = L_URLSTR_StringToUrl(&url,wOpt->href) ;
        FALSE_RET_FALSE(ok) ;

        /* ... fichero traza */
        fname = X_STRING_ConcatInStr("resume",".",L_URL_Machine(&url)) ;
        NULL_RET_FALSE(fname) ;
        fres  = fopen(fname,"w") ;
        X_ALLOC_Free((void **)&fname) ;
        NULL_RET_FALSE(fres) ;
        setbuf(fres,NULL) ;

        /* ... fichero log */
        fname = X_STRING_ConcatInStr("log",".",L_URL_Machine(&url)) ;
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
        ok    = L_LOG_Setup(flog,c_SPIDERBOT_VER) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }

        /* ... setup options */
        ok    = L_SETWS_WorkSpaceSetup( &dlws,flog,fres,
                                        c_SPIDERBOT_VER,
                                        c_SPIDERBOT_ID,
                                        wOpt->identification,
                                        wOpt->proxy,
                                        (wOpt->makeRelative_f == ON) ? c_RS_ALL_SITE : c_RS_NONE,
                                        (wOpt->scanGlobal_f   == ON) ? c_SS_GLOBAL : c_SS_LOCAL,
                                        (wOpt->onlyHttp_f     == ON) ? c_PS_HTTP : c_PS_ALL,
                                        c_MS_N_DIRECTORY,
                                        wOpt->detectHttp_f,
                                        wOpt->verbose_f,
                                        wOpt->fromSamePath_f,
                                        wOpt->skipBin_f,
                                        wOpt->skipEL_f,
                                        wOpt->rentry_f,
                                        wOpt->makeQuery_f,
                                        wOpt->maxBytes,
				        wOpt->maxUrls,
                                        wOpt->delay,
                                        wOpt->bufSize,
                                        wOpt->timeLimit,
                                        wOpt->resumeFrec) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }
        ok    = L_SBBOT_DownLoadWeb(&dlws,&url) ;
        L_URL_Empty(&url) ;
        fclose(flog) ;
        fclose(fres) ;
        return ok ;
      }

      T_BOOL  L_SBOTDL_DownLoadRecover    ( IN    t_wppOptions  *wOpt )
      {
        T_CHAR         *fname ;
        T_CHAR         *bname ;
        T_BOOL          ok ;
        FILE           *flog, *fres ;
        t_downLoadWS    dlws ;

        /* ... fichero traza */
        fres  = fopen(wOpt->recoverFile,"r+") ;
        if (fres == NULL)
           {
             X_PRINT_printf(" Recover file ('%s') can NOT be open, sorry.\n",
                            wOpt->recoverFile) ;
             return FALSE ;
           }
        setbuf(fres,NULL) ;

        /* ... fichero log */
        bname = wOpt->recoverFile ;
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
        ok    = L_LOG_Setup(flog,c_SPIDERBOT_VER) ;
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
                  c_SPIDERBOT_VER,
                  c_SPIDERBOT_ID,
                  wOpt->identification,
                  wOpt->proxy,
                  (wOpt->makeRelative_f == ON) ? c_RS_ALL_SITE : c_RS_NONE,
                  (wOpt->scanGlobal_f   == ON) ? c_SS_GLOBAL : c_SS_LOCAL,
                  (wOpt->onlyHttp_f     == ON) ? c_PS_HTTP : c_PS_ALL,
                  c_MS_N_DIRECTORY,
                  wOpt->detectHttp_f,
                  wOpt->verbose_f,
                  wOpt->fromSamePath_f,
                  wOpt->skipBin_f,
                  wOpt->skipEL_f,
                  wOpt->rentry_f,
                  wOpt->makeQuery_f,
                  wOpt->maxBytes,
                  wOpt->maxUrls,
                  wOpt->delay,
                  wOpt->bufSize,
                  wOpt->timeLimit,
                  wOpt->resumeFrec
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
        ok = L_SBBOT_DownLoadRecover(&dlws) ;
        fclose(flog) ;
        fclose(fres) ;
        return ok ;
      }

      T_BOOL  L_SBOTDL_DownLoad    ( IN   t_wppOptions    *wOpt )
      {
        T_BOOL      ok ;

        ok = FALSE ;
        if ( (wOpt->href == NULL) && (wOpt->recoverFile != NULL) )
              ok = L_SBOTDL_DownLoadRecover(wOpt) ;
        if ( (wOpt->href != NULL) && (wOpt->recoverFile == NULL) )
              ok = L_SBOTDL_DownLoadStart(wOpt) ;
        return ok ;
      }


   /* ................................................................... */

