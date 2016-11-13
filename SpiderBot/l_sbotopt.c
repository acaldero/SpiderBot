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

      #include "SpiderBot/l_sbotopt.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_SBOTOPT_MakeEmpty   ( OUT   t_wppOptions  *wOpt )
      {
        NULL_RET_FALSE(wOpt) ;
        wOpt->help_f          = OFF ;
        wOpt->makeRelative_f  = ON ;
        wOpt->verbose_f       = ON ;
        wOpt->scanGlobal_f    = OFF ;
        wOpt->fromSamePath_f  = ON ;
        wOpt->skipBin_f       = OFF ;
        wOpt->skipEL_f        = OFF ;
        wOpt->rentry_f        = OFF ;
        wOpt->detectHttp_f    = OFF ;
        wOpt->in1Page_f       = OFF ;
        wOpt->onlyHttp_f      = ON ;
        wOpt->maxBytes        = LONG_MAX ;
        wOpt->maxUrls         = LONG_MAX ;
        wOpt->delay           = 0L ;
        wOpt->resumeFrec      = 1L ;
        wOpt->bufSize         = LONG_MAX ;
        wOpt->timeLimit       = LONG_MAX ;
        wOpt->verbose_f       = ON ;
        wOpt->makeQuery_f     = OFF ;
        X_ALLOC_Free((void **)&(wOpt->href)) ;
        X_ALLOC_Free((void **)&(wOpt->proxy)) ;
        X_ALLOC_Free((void **)&(wOpt->recoverFile)) ;
        X_ALLOC_Free((void **)&(wOpt->identification)) ;
        return TRUE ;
      }

      T_BOOL   L_SBOTOPT_activeWppOptToFile  ( IN    t_wppOptions  *wOpt )
      {
        X_PRINT_printf("\tSpy Options setup...\n") ;

        /* ... Options ... */
        if (wOpt->href != NULL)
            X_PRINT_printf("\tURL ------------------- %-14s\n", 
                    wOpt->href) ;
        if (wOpt->proxy       != NULL)
            X_PRINT_printf("\tProxy ----------------- %-14s\n", 
                    wOpt->proxy) ;
        if (wOpt->recoverFile != NULL)
            X_PRINT_printf("\tRecoverFile ----------- %-14s\n", 
                    wOpt->recoverFile) ;
        if (wOpt->identification != NULL)
            X_PRINT_printf("\tIdentification -------- %-14s\n", 
                    wOpt->identification) ;
        if (wOpt->maxBytes   != LONG_MAX)
            X_PRINT_printf("\tMaxBytes -------------- %-14li\n",
                    wOpt->maxBytes) ;
        if (wOpt->maxUrls    != LONG_MAX)
            X_PRINT_printf("\tMaxUrls --------------- %-14li\n",
                    wOpt->maxUrls) ;
        if (wOpt->bufSize    != LONG_MAX)
            X_PRINT_printf("\tBufferSize ------------ %-14li\n",
                    wOpt->bufSize) ;

        /* ... Flags ... */
        if (wOpt->skipBin_f != OFF)
            X_PRINT_printf("\tSkipBin --------------- ON\n") ;
        if (wOpt->verbose_f != OFF)
            X_PRINT_printf("\tVerbose --------------- ON\n") ;
        if (wOpt->scanGlobal_f != OFF)
            X_PRINT_printf("\tFrom All hosts -------- ON\n") ;
        if (wOpt->fromSamePath_f == OFF)
            X_PRINT_printf("\tFrom same host -------- ON\n") ;
        if (wOpt->detectHttp_f != OFF)
            X_PRINT_printf("\tDetectHttp ------------ ON\n") ;
        if (wOpt->rentry_f != OFF)
            X_PRINT_printf("\tRentry ---------------- ON\n") ;
        if (wOpt->skipEL_f != OFF)
            X_PRINT_printf("\tSkip Exclusion List --- ON\n") ;
        if (wOpt->makeQuery_f != OFF)
            X_PRINT_printf("\tMake Querys ----------- ON\n") ;
        if (wOpt->onlyHttp_f != OFF)
            X_PRINT_printf("\tIn 1 page ------------- ON\n") ;

        X_PRINT_printf("\n") ;
        return TRUE ;
      }

      T_BOOL   L_SBOTOPT_wppOptToFile  ( IN    t_wppOptions   *wOpt )
      {
        X_PRINT_printf("\tSpy Options...\n") ;

        X_PRINT_printf(
                 "\tURL ------------------- %-14s\n",
                 ((wOpt->href        == NULL) ? "none" : wOpt->href) 
               ) ;
        X_PRINT_printf(
                 "\tProxy ----------------- %-14s\n",
                 ((wOpt->proxy       == NULL) ? "none" : wOpt->proxy) 
               ) ;
        X_PRINT_printf(
                 "\tRecoverFile ----------- %-14s\n",
                 ((wOpt->recoverFile == NULL) ? "none" : wOpt->recoverFile) 
               ) ;
        X_PRINT_printf(
                 "\tIdentification -------- %-14s\n",
                 ((wOpt->identification == NULL) ? "none" : wOpt->identification) 
               ) ;
        X_PRINT_printf(
                 "\tMaxBytes -------------- %-14li\n",
                 wOpt->maxBytes
               ) ;
        X_PRINT_printf(
                 "\tMaxUrls --------------- %-14li\n",
                 wOpt->maxUrls
               ) ;
        X_PRINT_printf(
                 "\tBufferSize ------------ %-14li\n",
                 wOpt->bufSize
               ) ;
        X_PRINT_printf(
                 "\tSkipBin --------------- %-14s\n",
                 ((wOpt->skipBin_f == ON) ? "ON" : "OFF")
               ) ;
        X_PRINT_printf(
                 "\tVerbose --------------- %-14s\n",
                 ((wOpt->verbose_f == ON) ? "ON" : "OFF")
               ) ;
        X_PRINT_printf(
                 "\tFrom all hosts -------- %-14s\n",
                 ((wOpt->scanGlobal_f == ON) ? "ON" : "OFF") 
               ) ;
        X_PRINT_printf(
                 "\tFrom same host -------- %-14s\n",
                 ((wOpt->fromSamePath_f == ON) ? "ON" : "OFF") 
               ) ;
        X_PRINT_printf(
                 "\tDetectHttp ------------ %-14s\n",
                 ((wOpt->detectHttp_f == ON) ? "ON" : "OFF") 
               ) ;
        X_PRINT_printf(
                 "\tRentry ---------------- %-14s\n",
                 ((wOpt->rentry_f == ON) ? "ON" : "OFF") 
               ) ;
        X_PRINT_printf(
                 "\tSkip Exclusion List --- %-14s\n",
                 ((wOpt->skipEL_f == ON) ? "ON" : "OFF") 
               ) ;
        X_PRINT_printf(
                 "\tMake Querys ----------- %-14s\n",
                 ((wOpt->makeQuery_f == ON) ? "ON" : "OFF") 
               ) ;
        X_PRINT_printf(
                 "\tIn 1 page ------------- %-14s\n",
                 ((wOpt->onlyHttp_f == ON) ? "ON" : "OFF") 
               ) ;

        X_PRINT_printf("\n") ;
        return TRUE ;
      }

      T_BOOL   L_SBOTOPT_CheckValid    ( IN    t_wppOptions  *wOpt )
      {
        X_PRINT_printf("\tSpy Options check...\n") ;

        if (
             (wOpt->href == NULL) 
                     && 
             (wOpt->recoverFile == NULL) 
           )
           {
             X_PRINT_printf(
                     "\tSorry, you forgot tell me a URL or resume file to work on.\n") ;
             return FALSE ;
           }
        if (
             (wOpt->href != NULL) 
                      &&  
             (wOpt->recoverFile != NULL) 
           )
           {
             X_PRINT_printf(
                     "\tSorry, I can NOT recover and download at same time\n") ;
             return FALSE ;
           }
        if (
             (wOpt->href == NULL) 
                      &&  
             (wOpt->proxy != NULL) 
           )
           {
             X_PRINT_printf(
                     "\tSorry, I need url to download throught the proxy\n") ;
             return FALSE ;
           }
        if (wOpt->maxBytes == 0L)
           {
             X_PRINT_printf(
                     "\tSorry, but maxBytes limit is zero !!!\n") ;
             return FALSE ;
           }
        if (wOpt->maxUrls == 0L)
           {
             X_PRINT_printf(
                     "\tSorry, but maxUrls limit is zero !!!\n") ;
             return FALSE ;
           }
        if (wOpt->scanGlobal_f > ON)
           {
             X_PRINT_printf("\tWARNING, Global option is set!!!\n") ;
             if (wOpt->fromSamePath_f > ON)
                 X_PRINT_printf("\tWARNING, 'From same path' is apply to all web sites!!!\n") ;
           }

        /* ... Finally, ok ... */
        X_PRINT_printf("\tok.\n") ;
        X_PRINT_printf("\n") ;
        return TRUE ;
      }


   /* ................................................................... */

