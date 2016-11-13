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

      #include "corelib/l_string/l_fre.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FRE_RWTillRE        ( IN     FILE     *fin,
                                     OUT    FILE     *fout,
                                     IN     T_CHAR  **toklist,
                                     INOUT  T_INT    *tokfound,
                                     IN     T_CHAR   *delimitadores,
                                     IN     T_BOOL    casesense )
      {
        T_BOOL    ok ;
        T_INT     ntok, i ;
        T_U_INT   tokenlen ;
        T_CHAR   *espa, *token, ch ;
        T_LONG    posnow ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(fout) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* ... make with auxiliar data ... */
        ntok = 0 ;
        if (toklist != NULL)
            for (; toklist[ntok] != NULL; ntok++) 
                 /* nothing */ ;
        espa = X_ALLOC_AllocAndSet(ntok+1,0) ;
        NULL_RET_FALSE(espa) ;
        for (i = 0; i<ntok; i++)
             espa[i] = (toklist[i])[0] ;

        /* ... and begin search */
        while (TRUE)
        {
          ok = L_FCHSET_ReadBinTillCharSet(fin,espa,casesense,
                                           &token,&tokenlen) ;
          if ( (ok == FALSE) || (feof(fin)) )
             {
               if (token != NULL)
                  {
                    fwrite(token,1,tokenlen,fout) ;
                    X_ALLOC_Free((void **)&token) ;
                  }
               X_ALLOC_Free((void **)&espa) ;
               return FALSE ;
             }
          if (token != NULL)
             {
               fwrite(token,1,tokenlen,fout) ;
               X_ALLOC_Free((void **)&token) ;
             }

          /* 
           *   analyze if found beginnig of target word,
           *   before char must be delimiter
           */
          posnow = ftell(fin) ;
          if ((posnow-1) > 0)
             {
               fseek(fin,(posnow-1),SEEK_SET) ;
               ch = fgetc(fin) ;
               if (X_STRING_StrChr(delimitadores,ch) == FALSE)
                  {
                    L_FCHSET_ReadBinTillCharSet(fin,delimitadores,casesense,
                                                &token,&tokenlen) ;
                    fwrite(token,1,tokenlen,fout) ;
                    X_ALLOC_Free((void **)&token) ;
                    continue ;
                  }
             }

          /* Read full token and scan it */
          L_FCHSET_ReadBinTillCharSet(fin,delimitadores,casesense,
                                      &token,&tokenlen) ;
          ok = L_BUFFA_CatOneByteToCache(&token,&tokenlen,'\0') ;
          FALSE_RET_FALSE(ok) ;
          tokenlen-- ; /* last char are not data */

          for (i = 0; i<ntok; i++)
              {
                if (X_STRING_Match(token,toklist[i],casesense) == TRUE)
                   {
                     X_ALLOC_Free((void **)&token) ;
                     X_ALLOC_Free((void **)&espa) ;
                     (*tokfound) = i ;
                     return TRUE ;
                   }
              }/*for(i = ...*/

          /* 
           *  empieza como uno de toklist, pero nada mas,
           *  almaceno lo leido y continuo buqueda ...    
           */
          fwrite(token,1,tokenlen,fout) ;
          X_ALLOC_Free((void **)&token) ;
        } /*while(TRUE)*/
      }

      T_BOOL L_FRE_ReadTillRE        ( IN     FILE     *f,
                                       IN     T_CHAR  **toklist,
                                       INOUT  T_CHAR  **buff,
                                       INOUT  T_U_INT  *buffsize,
                                       INOUT  T_INT    *tokfound,
                                       IN     T_CHAR   *delimitadores,
                                       IN     T_BOOL    casesense )
      {
        T_BOOL  ok ;
        T_INT   ntok, i ;
        T_CHAR  *espa, *token, ch ;
        T_LONG  posnow ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(f) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* ... setup auxiliar data ... */
        ntok = 0 ;
        if (toklist != NULL)
            for (; toklist[ntok] != NULL; ntok++)
                 /* averiguo numero de tokens */ ;
        espa = X_ALLOC_AllocAndSet(ntok+1,0) ;
        NULL__SET_ERROR__RET_FALSE(espa) ;
        for (i = 0; i<ntok; i++)
            {
              espa[i] = (toklist[i])[0] ;
              /* primeros caracteres */
            }

        /* ... and begin search ... */
        while (TRUE)
        {
          token = L_FCHSET_ReadTillCharSet(f,espa,FALSE) ;
          if (!token)
             {
               X_ALLOC_Free((void **)&espa) ;
               return FALSE ;
             }
          ok = L_BUFFA_CatNBytesToCache(buff,buffsize,
                                        token,X_STRING_StrLen(token)) ;
          X_ALLOC_Free((void **)&token) ;
          if (ok == FALSE)
             {
               X_ALLOC_Free((void **)&espa) ;
               return FALSE ;
             }
          /* analizo que sea comienzo de palabra, que el *
           * caracter anterior sea delimitador           */
          posnow = ftell(f) ;
         if ((posnow-1) > 0)
             {
              fseek(f,(posnow-1),SEEK_SET) ;
               ch = fgetc(f) ;
              if (X_STRING_StrChr(delimitadores,ch) == FALSE)
                 {
                    token = L_FCHSET_ReadTillCharSet(f,delimitadores,FALSE) ;
                    ok = L_BUFFA_CatNBytesToCache(buff,buffsize,
                                                  token,strlen(token)) ;
                   X_ALLOC_Free((void **)&token) ;
                   if (ok == FALSE)
                      {
                        X_ALLOC_Free((void **)&espa) ;
                        return FALSE ;
                      }
                   continue ;
                 }
             }
          /* Leo el token completo y lo analizo */
          token = L_FCHSET_ReadTillCharSet(f,delimitadores,FALSE) ;
          for (i = 0; i<ntok; i++)
              {
                if (X_STRING_Match(token,toklist[i],casesense) == TRUE)
                   {
                     X_ALLOC_Free((void **)&token) ;
                     X_ALLOC_Free((void **)&espa) ;
                     *tokfound = i ;
                     return TRUE ;
                   }
              }/*for(i = ...*/
          /* empieza como uno de toklist, pero nada mas, *
           * almaceno lo leido y continuo buqueda ...    */
          ok = L_BUFFA_CatNBytesToCache(buff,buffsize,token,strlen(token)) ;
          X_ALLOC_Free((void **)&token) ;
          if (ok == FALSE)
             {
               X_ALLOC_Free((void **)&espa) ;
               return FALSE ;
             }
        } /*while(TRUE)*/
      }

      T_BOOL L_FRE_SkipTillRE       ( IN     FILE     *fin,
                                      IN     T_CHAR  **toklist,
                                      INOUT  T_INT    *tokfound,
                                      IN     T_CHAR   *delimitadores,
                                      IN     T_BOOL    casesense )
      {
        T_INT   ntok, i ;
        T_CHAR  *espa, *token, ch ;
        T_LONG  posnow ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* ... make with auxiliar data ... */
        ntok = 0 ;
        if (toklist != NULL)
            for (; toklist[ntok] != NULL; ntok++) 
                 /* nothing */ ;
        espa = X_ALLOC_AllocAndSet(ntok+1,0) ;
        NULL_RET_FALSE(espa) ;
        for (i = 0; i<ntok; i++)
             espa[i] = (toklist[i])[0] ;

        /* ... and begin search */
        while (TRUE)
        {
          token = L_FCHSET_ReadTillCharSet(fin,espa,casesense) ;
          if ( (token == NULL) || feof(fin) )
             {
               X_ALLOC_Free((void **)&token) ;
               X_ALLOC_Free((void **)&espa) ;
               return FALSE ;
             }
          X_ALLOC_Free((void **)&token) ;

          /* analyze if found beginnig of target word, *
           * before char must be delimiter             */
          posnow = ftell(fin) ;
          if ((posnow-1) > 0)
             {
               fseek(fin,(posnow-1),SEEK_SET) ;
               ch = fgetc(fin) ;
               if (X_STRING_StrChr(delimitadores,ch) == FALSE)
                  {
                    token = L_FCHSET_ReadTillCharSet(fin,
                                                     delimitadores,
                                                     casesense) ;
                    X_ALLOC_Free((void **)&token) ;
                    continue ;
                  }
             }

          /* Read full token and scan it */
          token = L_FCHSET_ReadTillCharSet(fin,delimitadores,casesense) ;
          for (i = 0; i<ntok; i++)
              {
                if (X_STRING_Match(token,toklist[i],casesense) == TRUE)
                   {
                     X_ALLOC_Free((void **)&token) ;
                     X_ALLOC_Free((void **)&espa) ;
                     *tokfound = i ;
                     return TRUE ;
                   }
              }/*for(i = ...*/

          /* empieza como uno de toklist, pero nada mas, *
           * almaceno lo leido y continuo buqueda ...    */
          X_ALLOC_Free((void **)&token) ;
        } /*while(TRUE)*/
      }


  /* ..................................................................... */
    
