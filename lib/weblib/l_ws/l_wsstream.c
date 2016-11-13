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

      #include "weblib/l_ws/l_wsstream.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL    L_WSSTREAM_WSToFile      ( IN     t_downLoadWS  *dlws,
                                           OUT    FILE          *fout )
      {
        switch (dlws->scanSelection)
        {
          case c_SS_LOCAL :
               fprintf(fout,"scanSelection \t\t= LOCAL\n") ;
               break ;
          case c_SS_GLOBAL :
               fprintf(fout,"scanSelection \t\t= GLOBAL\n") ;
               break ;
          case c_SS_COUNTRY :
               fprintf(fout,"scanSelection \t\t= COUNTRY\n") ;
               break ;
          default : ;
        }

        if (dlws->rentry == ON)
                 fprintf(fout,"rentry \t\t\t= ON\n") ;
            else fprintf(fout,"rentry \t\t\t= OFF\n") ;

        if (dlws->fromSamePath == ON)
                 fprintf(fout,"fromSamePath \t\t= ON\n") ;
            else fprintf(fout,"fromSamePath \t\t= OFF\n") ;

        switch (dlws->rewriteSelection)
        {
          case c_RS_NONE :
               fprintf(fout,"rewriteSelection \t= NONE\n") ;
               break ;
          case c_RS_SAME_SITE :
               fprintf(fout,"rewriteSelection \t= SAME_SITE\n") ;
               break ;
          case c_RS_ALL_SITE :
               fprintf(fout,"rewriteSelection \t= ALL_SITE\n") ;
               break ;
          default : ;
        }

        switch (dlws->mirrorSelection)
        {
          case c_MS_1_PAGE :
               fprintf(fout,"mirrorSelection \t= 1_PAGE\n") ;
               break ;
          case c_MS_N_DIRECTORY :
               fprintf(fout,"mirrorSelection \t= N_DIRECTORY\n") ;
               break ;
          default : ;
        }

        switch (dlws->protocolSelection)
        {
          case c_PS_HTTP :
               fprintf(fout,"protocolSelection \t= HTTP\n") ;
               break ;
          case c_PS_FTP :
               fprintf(fout,"protocolSelection \t= FTP\n") ;
               break ;
          case c_PS_ALL :
               fprintf(fout,"protocolSelection \t= ALL\n") ;
               break ;
          default : ;
        }

        if (dlws->detect_http == ON)
                 fprintf(fout,"detectHttp \t\t= ON\n") ;
            else fprintf(fout,"detectHttp \t\t= OFF\n") ;

        if (dlws->skipBin == ON)
                 fprintf(fout,"skipBin \t\t= ON\n") ;
            else fprintf(fout,"skipBin \t\t= OFF\n") ;

        if (dlws->makeQuery == ON)
                 fprintf(fout,"makeQuery \t\t= ON\n") ;
            else fprintf(fout,"makeQuery \t\t= OFF\n") ;

        if (dlws->proxy == NULL)
                 fprintf(fout,"proxy \t\t\t= NONE\n") ;
            else fprintf(fout,"proxy \t\t\t= %s\n",dlws->proxy) ;

        if (dlws->maxBytes == LONG_MAX)
                 fprintf(fout,"maxBytes \t\t= NO_LIMITS\n") ;
            else fprintf(fout,"maxBytes \t\t= %li\n",dlws->maxBytes) ;

        if (dlws->maxUrls  == LONG_MAX)
                 fprintf(fout,"maxUrls \t\t= NO_LIMITS\n") ;
            else fprintf(fout,"maxUrls \t\t= %li\n",dlws->maxUrls) ;

        fprintf(fout,"currentBytes \t\t= %li\n",dlws->currentBytes) ;

        fprintf(fout,"currentUrl \t\t= %li\n",(dlws->i)) ;

        L_URLLI_UrlLiToFile(dlws->urllist,fout) ;

        return TRUE ;
      }

      T_BOOL    L_WSSTREAM_FileToWS       ( OUT     t_downLoadWS  *dlws,
                                            INOUT   FILE          *fin )
      {                                             
        T_BOOL      ok ;
        T_CHAR    *pch ;

        NULL_RET_FALSE(fin) ;
        dlws->urllist = L_URLLI_Creat() ;
        NULL_RET_FALSE(dlws->urllist) ;

        /* ... read recovering data ... */
        dlws->scanSelection = c_SS_LOCAL ;
        pch = L_FSTR_GetItemValue(fin,"scanSelection",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"GL*",FALSE) == TRUE)
                 dlws->scanSelection = c_SS_GLOBAL ;
             if (X_STRING_Match(pch,"CO*",FALSE) == TRUE)
                 dlws->scanSelection = c_SS_COUNTRY ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->rentry = OFF ; 
        pch = L_FSTR_GetItemValue(fin,"rentry",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"ON*",FALSE) == TRUE) 
                 dlws->rentry = ON ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->fromSamePath = OFF ; 
        pch = L_FSTR_GetItemValue(fin,"fromSamePath",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"ON*",FALSE) == TRUE) 
                 dlws->fromSamePath = ON ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->rewriteSelection = c_RS_NONE ; 
        pch = L_FSTR_GetItemValue(fin,"rewriteSelection",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"SAME*",FALSE) == TRUE) 
                 dlws->rewriteSelection = c_RS_SAME_SITE ;
             if (X_STRING_Match(pch,"ALL*",FALSE) == TRUE) 
                 dlws->rewriteSelection = c_RS_ALL_SITE ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->mirrorSelection = c_MS_N_DIRECTORY ; 
        pch = L_FSTR_GetItemValue(fin,"mirrorSelection",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"1_PAGE*",FALSE) == TRUE) 
                 dlws->rewriteSelection = c_MS_1_PAGE ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->protocolSelection = c_PS_ALL ; 
        pch = L_FSTR_GetItemValue(fin,"protocolSelection",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"HTT*",FALSE) == TRUE) 
                 dlws->protocolSelection = c_PS_HTTP ;
             if (X_STRING_Match(pch,"FT*",FALSE) == TRUE) 
                 dlws->protocolSelection = c_PS_FTP ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->detect_http = OFF ;
        pch = L_FSTR_GetItemValue(fin,"detectHttp",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"ON*",FALSE) == TRUE) 
                 dlws->detect_http = ON ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->skipBin = OFF ; 
        pch = L_FSTR_GetItemValue(fin,"skipBin",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"ON*",FALSE) == TRUE) 
                 dlws->detect_http = ON ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->makeQuery = OFF ; 
        pch = L_FSTR_GetItemValue(fin,"makeQuery",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Match(pch,"ON*",FALSE) == TRUE) 
                 dlws->makeQuery = ON ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->proxy = NULL ; 
        pch = L_FSTR_GetItemValue(fin,"proxy",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (X_STRING_Equal(pch,"NONE") == FALSE) 
                {
                  dlws->proxy = pch ;
                  L_URLSTR_StringToUrl(&(dlws->proxyUrl),pch) ;
                }
             else X_ALLOC_Free((void **)&(pch)) ;
           }

        pch = L_FSTR_GetItemValue(fin,"maxBytes ",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (dlws->maxBytes == LONG_MAX) 
                {
                  if (X_STRING_Match(pch,"NO_*",FALSE) == FALSE) 
                      dlws->maxBytes = atoi(pch) ;
                }
             X_ALLOC_Free((void **)&(pch)) ;
           }

        pch = L_FSTR_GetItemValue(fin,"maxUrls",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             if (dlws->maxUrls == LONG_MAX) 
                {
                  if (X_STRING_Match(pch,"NO_*",FALSE) == FALSE) 
                      dlws->maxUrls = atoi(pch) ;
                }
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->currentBytes = 0L ; 
        pch = L_FSTR_GetItemValue(fin,"currentBytes ",FALSE," \t=\n") ;
        if (pch != NULL) 
           {
             dlws->currentBytes = atoi(pch) ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        dlws->i = 0 ; 
        pch = L_FSTR_GetItemValue(fin,"currentUrl",FALSE," \t=\n") ;
        if (pch != NULL)
           {
             dlws->i = atoi(pch) - 1 ;
             X_ALLOC_Free((void **)&(pch)) ;
           }

        L_FCHSET_SkipCharSet(fin,"\n\t ") ;
        ok = L_URLLI_FileToUrlLi(dlws->urllist,fin) ;

        return ok ;
      }
  

   /* ................................................................... */

