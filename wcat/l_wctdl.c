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

      #include "wcat/l_wctdl.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_WCTDL_DownLoadStart   ( IN    t_wppOptions  *wcOpt )
      {
        T_CHAR         *fname ;
        t_url           url ;
        T_BOOL          ok ;
        FILE           *flog, *fres ;
        t_downLoadWS    dlws ;

        ok    = L_URLSTR_StringToUrl(&url,wcOpt->href) ;
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
        ok    = L_LOG_Setup(flog,c_WCAT_VER) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }

        /* ... setup options */
        ok    = L_SETWS_WorkSpaceSetup
                ( &dlws,
                   flog,
                   fres,
                   c_WCAT_VER,
                   c_WCAT_ID,
                   wcOpt->identification,
                   wcOpt->proxy,
                   (wcOpt->in1Page_f    == ON) ? c_RS_SAME_SITE : c_RS_NONE,
                   (wcOpt->scanGlobal_f == ON) ? c_SS_GLOBAL : c_SS_LOCAL,
                   (wcOpt->onlyHttp_f   == ON) ? c_PS_HTTP : c_PS_ALL,
                   (wcOpt->in1Page_f    == ON) ? c_MS_1_PAGE : c_MS_N_DIRECTORY,
                   wcOpt->detectHttp_f,
                   wcOpt->verbose_f,
                   wcOpt->fromSamePath_f,
                   wcOpt->skipBin_f,
                   wcOpt->skipEL_f,
                   wcOpt->rentry_f,
                   wcOpt->makeQuery_f,
                   wcOpt->maxBytes,
                   wcOpt->maxUrls,
                   wcOpt->delay,
                   wcOpt->bufSize,
                   wcOpt->timeLimit,
                   wcOpt->resumeFrec
                 ) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }
        ok    = L_CTBOT_DownLoadWeb(&dlws,&url) ;
        L_URL_Empty(&url) ;
        fclose(flog) ;
        fclose(fres) ;
        return ok ;
      }

      T_BOOL  L_WCTDL_DownLoadRecover    ( IN    t_wppOptions  *wcOpt )
      {
        T_CHAR         *fname ;
        T_CHAR         *bname ;
        T_BOOL          ok ;
        FILE           *flog, *fres ;
        t_downLoadWS    dlws ;

        /* ... fichero traza */
        fres  = fopen(wcOpt->recoverFile,"r+") ;
        if (fres == NULL)
           {
             X_PRINT_printf(" Recover file ('%s') can NOT be open, sorry.\n",
                            wcOpt->recoverFile) ;
             return FALSE ;
           }
        setbuf(fres,NULL) ;

        /* ... fichero log */
        bname = wcOpt->recoverFile ;
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
        ok    = L_LOG_Setup(flog,c_WCAT_VER) ;
        if (ok == FALSE)
           {
             fclose(flog) ;
             fclose(fres) ;
             return FALSE ;
           }

        /* ... setup options */
        ok    = L_SETWS_WorkSpaceSetup
                ( &dlws,
                   flog,
                   fres,
                   c_WCAT_VER,
                   c_WCAT_ID,
                   wcOpt->identification,
                   wcOpt->proxy,
                   (wcOpt->in1Page_f    == ON) ? c_RS_SAME_SITE : c_RS_NONE,
                   (wcOpt->scanGlobal_f == ON) ? c_SS_GLOBAL : c_SS_LOCAL,
                   (wcOpt->onlyHttp_f   == ON) ? c_PS_HTTP : c_PS_ALL,
                   (wcOpt->in1Page_f    == ON) ? c_MS_1_PAGE : c_MS_N_DIRECTORY,
                   wcOpt->detectHttp_f,
                   wcOpt->verbose_f,
                   wcOpt->fromSamePath_f,
                   wcOpt->skipBin_f,
                   wcOpt->skipEL_f,
                   wcOpt->rentry_f,
                   wcOpt->makeQuery_f,
                   wcOpt->maxBytes,
                   wcOpt->maxUrls,
                   wcOpt->delay,
                   wcOpt->bufSize,
                   wcOpt->timeLimit,
                   wcOpt->resumeFrec
                 ) ;
        if (ok == FALSE)
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
        ok = L_CTBOT_DownLoadRecover(&dlws) ;
        fclose(flog) ;
        fclose(fres) ;
        return ok ;
      }

      T_BOOL  L_WCTDL_DownLoad    ( IN   t_wppOptions    *wcOpt )
      {
        T_BOOL      ok ;

        ok = FALSE ;
        if ( (wcOpt->href == NULL) && (wcOpt->recoverFile != NULL) )
              ok = L_WCTDL_DownLoadRecover(wcOpt) ;
        if ( (wcOpt->href != NULL) && (wcOpt->recoverFile == NULL) )
              ok = L_WCTDL_DownLoadStart(wcOpt) ;
        return ok ;
      }


   /* ................................................................... */

