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

      #include "wpplib/l_cl_wpp/l_wpp_opt.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_WPP_OPT_DupHref         ( INOUT  t_wppOptions   *wppOpt,
                                           IN     T_CHAR         *href )
      {
        NULL__SET_ERROR__RET_FALSE(wppOpt) ;
        NULL__SET_ERROR__RET_FALSE(href) ;
        (wppOpt->href) = X_STRING_StrDup(href) ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_DupProxy        ( INOUT  t_wppOptions   *wppOpt,
                                           IN     T_CHAR         *proxy )
      {
        NULL__SET_ERROR__RET_FALSE(wppOpt) ;
        NULL__SET_ERROR__RET_FALSE(proxy) ;
        (wppOpt->proxy) = X_STRING_StrDup(proxy) ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_DupRecoverFile  ( INOUT  t_wppOptions   *wppOpt,
                                           IN     T_CHAR        *recoverFile )
      {
        NULL__SET_ERROR__RET_FALSE(wppOpt) ;
        NULL__SET_ERROR__RET_FALSE(recoverFile) ;
        (wppOpt->recoverFile) = X_STRING_StrDup(recoverFile) ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_DupIdentification ( INOUT  t_wppOptions   *wppOpt,
                                             IN     T_CHAR        *id )
      {
        NULL__SET_ERROR__RET_FALSE(wppOpt) ;
        NULL__SET_ERROR__RET_FALSE(id) ;
        (wppOpt->identification) = X_STRING_StrDup(id) ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_MakeEmpty   ( OUT   t_wppOptions   *wppOpt )
      {
        NULL__SET_ERROR__RET_FALSE(wppOpt) ;
        wppOpt->help_f          = OFF ;
        wppOpt->makeRelative_f  = OFF ;
        wppOpt->scanGlobal_f    = OFF ;
        wppOpt->fromSamePath_f  = OFF ;
        wppOpt->skipBin_f       = OFF ;
        wppOpt->skipEL_f        = OFF ;
        wppOpt->rentry_f        = OFF ;
        wppOpt->detectHttp_f    = OFF ;
        wppOpt->onlyHttp_f      = OFF ;
        wppOpt->in1Page_f       = OFF ;
        wppOpt->maxBytes        = LONG_MAX ;
        wppOpt->maxUrls         = LONG_MAX ;
        wppOpt->delay           = 0L ;
        wppOpt->resumeFrec      = 0L ;
        wppOpt->bufSize         = LONG_MAX ;
        wppOpt->timeLimit       = LONG_MAX ;
        wppOpt->verbose_f       = ON ;
        wppOpt->makeQuery_f     = OFF ;
        X_ALLOC_Free((void **)&(wppOpt->href)) ;
        X_ALLOC_Free((void **)&(wppOpt->proxy)) ;
        X_ALLOC_Free((void **)&(wppOpt->recoverFile)) ;
        X_ALLOC_Free((void **)&(wppOpt->identification)) ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_activeOptToFile  ( OUT   FILE           *fout,
                                            IN    t_wppOptions   *wppOpt )
      {
        fprintf(fout,"\tOptions setup...\n") ;

        /* ... Options ... */
        if (wppOpt->href != NULL)
            fprintf(fout,"\tURL ------------------- %-14s\n", 
                    wppOpt->href) ;
        if (wppOpt->proxy       != NULL)
            fprintf(fout,"\tProxy ----------------- %-14s\n", 
                    wppOpt->proxy) ;
        if (wppOpt->recoverFile != NULL)
            fprintf(fout,"\tRecoverFile ----------- %-14s\n", 
                    wppOpt->recoverFile) ;
        if (wppOpt->identification != NULL)
            fprintf(fout,"\tIdentification -------- %-14s\n", 
                    "x:x") ;
        if (wppOpt->maxBytes   != LONG_MAX)
            fprintf(fout,"\tMaxBytes -------------- %-14li\n",
                    wppOpt->maxBytes) ;
        if (wppOpt->maxUrls    != LONG_MAX)
            fprintf(fout,"\tMaxUrls --------------- %-14li\n",
                    wppOpt->maxUrls) ;
        if (wppOpt->bufSize    != LONG_MAX)
            fprintf(fout,"\tBufferSize ------------ %-14li\n",
                    wppOpt->bufSize) ;

        /* ... Flags ... */
        if (wppOpt->skipBin_f != OFF)
            fprintf(fout,"\tSkipBin --------------- ON\n") ;
        if (wppOpt->verbose_f != OFF)
            fprintf(fout,"\tVerbose --------------- ON\n") ;
        if (wppOpt->scanGlobal_f != OFF)
            fprintf(fout,"\tFrom All hosts -------- ON\n") ;
        if (wppOpt->fromSamePath_f == OFF)
            fprintf(fout,"\tFrom same host -------- ON\n") ;
        if (wppOpt->detectHttp_f != OFF)
            fprintf(fout,"\tDetectHttp ------------ ON\n") ;
        if (wppOpt->rentry_f != OFF)
            fprintf(fout,"\tRentry ---------------- ON\n") ;
        if (wppOpt->skipEL_f != OFF)
            fprintf(fout,"\tSkip Exclusion List --- ON\n") ;
        if (wppOpt->makeQuery_f != OFF)
            fprintf(fout,"\tMake Querys ----------- ON\n") ;
        if (wppOpt->in1Page_f != OFF)
            fprintf(fout,"\tInside page ----------- ON\n") ;

        fprintf(fout,"\n") ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_wppOptToFile  ( OUT   FILE           *fout,
                                         IN    t_wppOptions   *wppOpt )
      {
        fprintf(fout,"\tOptions...\n") ;

        fprintf( fout,
                 "\tURL ------------------- %-14s\n",
                 ((wppOpt->href        == NULL) ? "none" : wppOpt->href) 
               ) ;
        fprintf( fout,
                 "\tProxy ----------------- %-14s\n",
                 ((wppOpt->proxy       == NULL) ? "none" : wppOpt->proxy) 
               ) ;
        fprintf( fout,
                 "\tRecoverFile ----------- %-14s\n",
                 ((wppOpt->recoverFile == NULL) ? "none" : wppOpt->recoverFile) 
               ) ;
        fprintf( fout,
                 "\tIdentification -------- %-14s\n",
                 ((wppOpt->identification == NULL) ? "none" : wppOpt->identification) 
               ) ;
        fprintf( fout,
                 "\tMaxBytes -------------- %-14li\n",
                 wppOpt->maxBytes
               ) ;
        fprintf( fout,
                 "\tMaxUrls --------------- %-14li\n",
                 wppOpt->maxUrls
               ) ;
        fprintf( fout,
                 "\tBufferSize ------------ %-14li\n",
                 wppOpt->bufSize
               ) ;
        fprintf( fout,
                 "\tSkipBin --------------- %-14s\n",
                 ((wppOpt->skipBin_f == ON) ? "ON" : "OFF")
               ) ;
        fprintf( fout,
                 "\tVerbose --------------- %-14s\n",
                 ((wppOpt->verbose_f == ON) ? "ON" : "OFF")
               ) ;
        fprintf( fout,
                 "\tFrom all hosts -------- %-14s\n",
                 ((wppOpt->scanGlobal_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tFrom same host -------- %-14s\n",
                 ((wppOpt->fromSamePath_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tDetectHttp ------------ %-14s\n",
                 ((wppOpt->detectHttp_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tRentry ---------------- %-14s\n",
                 ((wppOpt->rentry_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tSkip Exclusion List --- %-14s\n",
                 ((wppOpt->skipEL_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tMake Querys ----------- %-14s\n",
                 ((wppOpt->makeQuery_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tIn 1 page ------------- %-14s\n",
                 ((wppOpt->in1Page_f == ON) ? "ON" : "OFF") 
               ) ;

        fprintf(fout,"\n") ;
        return TRUE ;
      }

      T_BOOL   L_WPP_OPT_CheckValid    ( OUT   FILE           *fout,
                                         IN    t_wppOptions   *wppOpt )
      {
        fprintf(fout,"\tOptions check...\n") ;

        if (
             (wppOpt->href == NULL) 
                     && 
             (wppOpt->recoverFile == NULL) 
           )
           {
             fprintf(fout,
                     "\tSorry, you forgot tell me a URL or resume file to work on.\n") ;
             return FALSE ;
           }
        if (
             (wppOpt->href != NULL) 
                      &&  
             (wppOpt->recoverFile != NULL) 
           )
           {
             fprintf(fout,
                     "\tSorry, I can NOT recover and download at same time\n") ;
             return FALSE ;
           }
        if (
             (wppOpt->href == NULL) 
                      &&  
             (wppOpt->proxy != NULL) 
           )
           {
             fprintf(fout,
                     "\tSorry, I need url to download throught the proxy\n") ;
             return FALSE ;
           }
        if (wppOpt->maxBytes == 0L)
           {
             fprintf(fout,
                     "\tSorry, but maxBytes limit is zero !!!\n") ;
             return FALSE ;
           }
        if (wppOpt->maxUrls == 0L)
           {
             fprintf(fout,
                     "\tSorry, but maxUrls limit is zero !!!\n") ;
             return FALSE ;
           }
        if (wppOpt->scanGlobal_f > ON)
           {
             fprintf(fout,"\tWARNING, Global option is set!!!\n") ;
             if (wppOpt->fromSamePath_f > ON)
                 fprintf(fout,"\tWARNING, 'From same path' is apply to all web sites!!!\n") ;
           }

        /* ... Finally, ok ... */
        fprintf(fout,"\tok.\n") ;
        fprintf(fout,"\n") ;
        return TRUE ;
      }


   /* ................................................................... */

