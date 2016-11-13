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

      #include "weblib/l_ws/l_setws.h"


   /* ... Functions / Funciones ......................................... */
  
      /*  L_SETWS_WorkSpaceSetup  *
       * ------------------------ */
      T_BOOL  L_SETWS_WorkSpaceSetup (    IN     t_downLoadWS *dlws,
                                          IN     FILE         *finfo,
                                          IN     FILE         *fresume,
                                          IN     T_CHAR       *clientNameReal,
                                          IN     T_CHAR       *clientNameToSend,
                                          IN     T_CHAR       *identification,
                                          IN     T_CHAR       *proxy,
                                          IN     T_INT         rewriteSelection,   
                                          IN     T_INT         scanSelection,   
                                          IN     T_INT         protocolSelection,
                                          IN     T_INT         mirrorSelection,
                                          IN     T_FLAG        detectHttp,
                                          IN     T_FLAG        verbose,
                                          IN     T_FLAG        fromSamePath,   
                                          IN     T_FLAG        skipBin,
                                          IN     T_FLAG        skipEL,
                                          IN     T_FLAG        rentry,
                                          IN     T_FLAG        makeQuery,
                                          IN     T_LONG        maxBytes,
                                          IN     T_LONG        maxUrls,
                                          IN     T_LONG        delay,
                                          IN     T_LONG        bufSize,
                                          IN     T_LONG        timeLimit,
                                          IN     T_LONG        resumeFrec )
      {
        /* ... set 'dlws' using params values ... */
        dlws->finfo          = finfo ;
        dlws->fresume        = fresume ;
        if (clientNameReal == NULL)
                 dlws->clientNameReal = "weblib/0" ;
            else dlws->clientNameReal = clientNameReal ;
        if (clientNameToSend == NULL)
                 dlws->clientNameToSend = "weblib/0" ;
            else dlws->clientNameToSend = clientNameToSend ;
        dlws->identification    = identification ;
        dlws->proxy             = proxy ;
        if (proxy != NULL)
            L_URLSTR_StringToUrl(&(dlws->proxyUrl),proxy) ;
        dlws->rewriteSelection  = rewriteSelection ;
        dlws->scanSelection     = scanSelection ;
        dlws->protocolSelection = protocolSelection ;
        dlws->mirrorSelection   = mirrorSelection ;
        dlws->detect_http       = detectHttp ;
        dlws->verbose           = verbose ;
        dlws->fromSamePath      = fromSamePath ;
        dlws->skipBin           = skipBin ;
        dlws->skipEL            = skipEL ;
        dlws->rentry            = rentry ;
        dlws->makeQuery         = makeQuery ;
        dlws->maxBytes          = maxBytes ;
        dlws->maxUrls           = maxUrls ;
        dlws->delay             = delay ;
        dlws->bufSize           = bufSize ;
        dlws->timeLimit         = timeLimit ;
        if (resumeFrec == 0)
                 dlws->resumeFrec = 1 ;
            else dlws->resumeFrec = resumeFrec ;

        return TRUE ;
      }


      /*  L_SETWS_WorkSpaceResume  *
       * ------------------------- */
      void    L_SETWS_WorkSpaceResume ( IN     t_downLoadWS *dlws )
      {
        if (dlws->fresume != NULL)
           {
             T_CHAR   *now, *pcr ;
             time_t    tnow ;

             tnow   = time(NULL) ;
             now    = ctime(&tnow) ;
             pcr    = strrchr(now,'\n') ;
             (*pcr) = '\0' ;
	     signal(SIGINT,SIG_IGN) ; 

             fseek(dlws->fresume,0,SEEK_SET) ;
             fprintf(dlws->fresume,
                     "\n"
                     "\n"
                     "# %s's work space, at %s\n",
                     dlws->clientNameReal,now) ;

             L_WSSTREAM_WSToFile(dlws,dlws->fresume) ;

	     signal(SIGINT,SIG_DFL) ; 
           }
      }


      /*  L_SETWS_WorkSpaceRecover *
       * ------------------------- */
      T_BOOL  L_SETWS_SkipComment       ( IN     FILE         *frecov )
      {
        T_CHAR      ch ;

        /* ... skip comment ... */
        fseek(frecov,0,SEEK_SET) ;
        do
        {
	  ch = fgetc(frecov) ;
	} while ( (ch != '#') && (!feof(frecov)) ) ;
        do
        {
	  ch = fgetc(frecov) ;
	} while ( (ch != '\n') && (!feof(frecov)) ) ;

        /* ... is corrupted or empty ? ... */
	if (feof(frecov))
           {
             X_PRINT_printf(" Resume process STOP: corrupted or empty resume file, sorry\n") ;
	     return FALSE ;
           }
        return TRUE ;
      }

      T_BOOL  L_SETWS_WorkSpaceRecover  ( IN     FILE         *frecov,
                                          OUT    t_downLoadWS *dlws )
      {
        T_BOOL  ok ;

        NULL_RET_FALSE(frecov) ;
        dlws->urllist = L_URLLI_Creat() ;
        NULL_RET_FALSE(dlws->urllist) ;

        /* ... seek to recovering data ... */
        ok = L_SETWS_SkipComment(frecov) ;
        FALSE_RET_FALSE(ok) ;

        /* ... read and check ... */
        ok = L_WSSTREAM_FileToWS(dlws,frecov) ;
	if (ok == FALSE)
           {
             X_PRINT_printf(" Resume process STOP: corrupted resume file, sorry\n") ;
             X_PRINT_printf(" Try to edit resume file and delete bad lines\n") ;
	     return FALSE ;
           }
	if (L_URLLI_NumberUrls(dlws->urllist) < dlws->i)
           {
             X_PRINT_printf(" Resume process STOP: all url's had been download.\n") ;
	     return FALSE ;
           }
	if (L_URLLI_NumberUrls(dlws->urllist) == 0L)
           {
             X_PRINT_printf(" Resume process STOP: empty valid url list at resume file.\n") ;
	     return FALSE ;
           }

        return ok ;
      }
  

   /* ................................................................... */

