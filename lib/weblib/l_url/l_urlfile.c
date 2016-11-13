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

      #include "weblib/l_url/l_urlfile.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_URLFILE_OpenInsideUrl        ( INOUT  t_url    *urlRel,
                                                IN     t_url    *urlBase,
                                                IN     T_CHAR   *relPath )
      {
        T_BOOL  ok ;

        ok = TRUE ;
        if ( X_STRING_Match(relPath,"*://*",FALSE) == TRUE )
                  ok = L_URLSTR_StringToUrl(urlRel,relPath) ;
             else if ( X_STRING_Match(relPath,"*:*",FALSE) == FALSE )
                       ok = L_URLFILE_OpenReativePath(urlRel,urlBase,relPath) ;
                  else if ( X_STRING_Match(relPath,"mailto:*",FALSE) == TRUE)
                            ok = L_URLSTR_StringToUrl(urlRel,relPath) ;
                       else ok = FALSE ;
        return ok ;
      }

      T_BOOL    L_URLFILE_OpenReativePath     ( INOUT  t_url    *urlRel,
                                                IN     t_url    *urlBase,
                                                IN     T_CHAR   *relPath )
      {
        T_CHAR *saux, *pfname ;
        T_CHAR *retPath, *retProtocol, *retMachine, 
               *retFile, *retRelative, *retParams ;
        T_INT   retPort ;
        T_BOOL  ok ;

        /* ... checking */
        NULL__SET_ERROR__RET_FALSE(urlBase) ;
        NULL__SET_ERROR__RET_FALSE(urlRel) ;
        NULL__SET_ERROR__RET_FALSE(relPath) ;

        /* ... auxiliar path */
        retPath = X_STRING_StrDup(relPath) ;
        NULL_RET_FALSE(retPath) ;

        /* ... port */
        retPort = urlBase->port ;

        /* ... protocol */
        retProtocol = X_STRING_StrDup(urlBase->protocol) ;
        NULL_RET_FALSE(retProtocol) ;

        /* ... machine */
        retMachine  = X_STRING_StrDup(urlBase->machine ) ;
        NULL_RET_FALSE(retMachine) ;

        /* ... relative offset */
        retRelative = NULL ;
        saux = X_STRING_StrChr(retPath,'#') ;
        if (saux != NULL)
           {
             retRelative = X_STRING_StrDup(saux+1) ;
             (*saux) = '\0' ;
           }

        /* ... cgi-prog?commands */
        retParams = NULL ;
        saux = X_STRING_StrChr(retPath,'?') ;
        if (saux != NULL)
           {
             retParams = X_STRING_StrDup(saux+1) ;
             (*saux) = '\0' ;
           }

        /* ... retFile */
        if (retPath[0] == '/')
           { /* ... ABSOLUTE ... */
	     retFile = X_STRING_StrDup(retPath) ;
           }    
        if (retPath[0] != '/')
           { /* ... RELATIVE ... */
             pfname = strrchr(urlBase->file,'/') ;
             if (pfname == NULL)
                {
                  retFile = X_STRING_ConcatInStr(urlBase->file,"/",retPath) ;
                }
             if (pfname != NULL)
                {
                  T_CHAR  saveCH ;

                  saveCH = pfname[1] ;
                  pfname[1] = '\0' ;
                  if (retPath[0] == '/')
                           retFile = X_STRING_ConcatInStr(urlBase->file,
                                                          "",retPath+1) ;
                      else retFile = X_STRING_ConcatInStr(urlBase->file,
                                                          "",retPath) ;
                  pfname[1] = saveCH ;
                }
           }    
        NULL_RET_FALSE(retFile) ;
        L_FILE_SimplifyPath(retFile) ;

        /* ... ok */
        X_ALLOC_Free( (void **)&(retPath) ) ;
        if (urlRel == urlBase)
           {
             L_URL_Empty(urlRel) ;
           }
        ok = L_URL_FillFrom(urlRel,
                            retProtocol,
                            retMachine,
                            retFile,
                            retRelative,
                            retParams,
                            retPort) ;
        FALSE_RET_FALSE(ok) ;
        return TRUE ;
      }

      T_CHAR   *L_URLFILE_MirrorUrlName        ( IN     t_url  *url,
                                                 IN     T_INT   tms )
      {
        T_CHAR  *fname, *sorg, *saux ;

        /* ... checking */
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... work at file ... */
        if (url->params != NULL)
           {
                 fname = X_STRING_ConcatInStr(url->file,"/",url->params) ;
                 NULL_RET_FALSE(fname) ;
                 sorg  = X_STRING_ConcatInStr(fname,"",".html") ;
                 NULL_RET_FALSE(sorg) ;
                 X_ALLOC_Free((void **)&fname) ;
                 fname = sorg ;
           }
        else 
           {
                 fname = X_STRING_StrDup(url->file) ;
                 NULL_RET_NULL(fname) ;
           }
        if (fname[0] == '/')
            X_ALLOC_MemMove(fname,fname+1,X_STRING_StrLen(fname)) ;
        if (fname[0] == '~')
            X_ALLOC_MemMove(fname,fname+1,X_STRING_StrLen(fname)) ;
        if (!strncmp(fname,"%7e",3))
            X_ALLOC_MemMove(fname,fname+3,X_STRING_StrLen(fname)) ;
        if (!strncmp(fname,"%7E",3))
            X_ALLOC_MemMove(fname,fname+3,X_STRING_StrLen(fname)) ;
        while (
                  /* test */
                  /* (../) && (..\) */
                (!strncmp(fname,"../",3))
                          ||
                (!strncmp(fname,"..\\",3))
              )
            {
              X_ALLOC_MemMove(fname,fname+3,X_STRING_StrLen(fname)) ;
            }
        sorg = strrchr(fname,'/') ;
        if (
             ( (X_STRING_Equal(fname,"/") == TRUE) )
                              ||
             ( (sorg != NULL) && (*(sorg+1) == '\0') )            /* /~user/ */
                              ||
             ( (sorg == NULL) && (strrchr(fname,'.') == NULL) )   /* /~user */
           )
           {
             if ( 
                  (X_STRING_StrLen(fname) != 0)
                             &&
                  (X_STRING_LastChar(fname) == '/')
                )
                      sorg = X_STRING_ConcatInStr(fname,"","index.html") ;
                 else sorg = X_STRING_ConcatInStr(fname,"/","index.html") ;
             NULL_RET_FALSE(sorg) ;
             X_ALLOC_Free((void **)&fname) ;
             fname = sorg ;
           }
        /* ... work at params ... */
        X_STRING_StrChrSetChange(fname,"&|",'/') ;
        X_STRING_StrChrSetChange(fname,"=:;",'_') ;
        X_STRING_StrChrSetChange(fname,"%%!@$",'_') ;

        /* ... add machine name ... */
        saux = X_STRING_ConcatInStr(url->machine,"/",fname) ;
        X_ALLOC_Free((void **)&fname) ;
        L_FILE_SimplifyPath(saux) ;

        /* ... if 1page, update name ... */
        if ( 
             (tms == c_MS_1_PAGE)
                       &&
             (L_URLFILE_IsBin(url->file) == FALSE)
           )
           {
             T_CHAR  *nsaux ;

             X_STRING_StrChrSetChange(saux,"/\\.",'_') ;
             nsaux = X_STRING_Dsprintf("#_%s_%s",
                                       saux,
                                       (url->relative != NULL) ? url->relative : "") ;
             X_ALLOC_Free((void **)&saux) ;
             saux = nsaux ;
           }

        return saux ;
      }

      T_CHAR   *L_URLFILE_MirrorUrlNameFrom    ( IN     t_url  *url,
                                                 IN     t_url  *purlFrom,
                                                 IN     T_INT   tms )
      {
        T_CHAR  *mirrorName ;
     
        /* ... if (tms == 1page) => only mirrorName ... */
        if (tms == c_MS_1_PAGE)
           {
             mirrorName = L_URLFILE_MirrorUrlName(url,tms) ;
             return mirrorName ;
           }

        /* ... if (tms == n_directory) => make path ... */
        if (tms == c_MS_N_DIRECTORY)
           {
             T_CHAR  *mirrorPath ;
             T_INT    i, deep ;

             deep = X_STRING_StrChrNumber(purlFrom->file,'/') - 1 ;
             mirrorName = L_URLFILE_MirrorUrlName(url,tms) ;
             mirrorPath = X_STRING_StrDup(CURR_DIR) ;

             for (i=0; i<deep; i++)
                  X_STRING_AddStrToStr(&(mirrorPath),UP_DIR) ;
             X_STRING_AddStrToStr(&(mirrorPath),UP_DIR) ;
             X_STRING_AddStrToStr(&(mirrorPath),mirrorName) ;

             /* ... free resources ... */
             X_ALLOC_Free( (void **)&(mirrorName) ) ;
             L_FILE_SimplifyPath(mirrorPath) ;
             return mirrorPath ;
           }

        return NULL ;
      }

      T_BOOL  L_URLFILE_MakeIndexUrl   ( IN     t_url         *url )
      {
        NULL_RET_FALSE(url) ;

        if (
             (X_STRING_LastChar(url->file) != '\\')
                            &&
             (X_STRING_LastChar(url->file) != '/')
           )
           {
             T_CHAR *pch ;

             pch = X_STRING_ConcatInStr(url->file,"/","") ;
             NULL_RET_FALSE(pch) ;
             X_ALLOC_Free((void **)&(url->file)) ;
             url->file = pch ;
           }

        return TRUE ;
      }

      T_BOOL  L_URLFILE_IsBin      ( IN     T_CHAR        *strurl )
      {
        T_INT    i ;
        T_CHAR  *binExtensions[] = 
                 {
                   "*.png", "*.gif", "*.jpg", "*.jpeg", "*.bmp",
                   "*.mov", "*.viv", "*.avi",
                   "*.wav", "*.mp3", "*.au",
                   "*.zip", "*.arj", "*.gz",  "*.lha", "*.Z",
                   "*.ps",  "*.ps.gz", "*.doc", "*.pdf",
                   "*.exe", "*.com",
                   NULL
                 } ;

        for (i=0; (binExtensions[i] != NULL); i++)
            {
              if (X_STRING_Match(strurl,binExtensions[i],FALSE) == TRUE)
                  return TRUE ;
            }
        return FALSE ;
      }

      T_BOOL  L_URLFILE_FromSamePath   ( IN     t_url         *purl,
                                         IN     T_CHAR        *strurl )
      {
	t_url    urlaux ;
        T_CHAR  *pstr ;
        T_CHAR   savech ;
        T_INT    ret ;
        T_BOOL   ok ;

        NULL_RET_FALSE(purl) ;
        NULL_RET_FALSE(strurl) ;

        /* ... build url ... */
        ok = TRUE ;
        if ( X_STRING_Match(strurl,"*://*",FALSE) == TRUE )
                  ok = L_URLSTR_StringToUrl(&urlaux,strurl) ;
             else if ( X_STRING_Match(strurl,"*:*",FALSE) == FALSE )
                       ok = L_URLFILE_OpenReativePath(&urlaux,purl,strurl) ;
                  else ok = FALSE ;
        FALSE_RET_FALSE(ok) ;

        /* ... same path ? ... */
        pstr = strrchr(purl->file,'/') ;
        NULL_RET_FALSE(pstr) ;
        savech = pstr[1] ;
        pstr[1] = '\0' ;
        ret = strncmp(purl->file,
                      urlaux.file,
                      X_STRING_StrLen(purl->file)) ;
        pstr[1] = savech ;

        /* ... return ... */
        L_URL_Empty(&urlaux) ;
        if (ret != 0)
            return FALSE ;
        return TRUE ;
      }


  /* ...................................................................... */

