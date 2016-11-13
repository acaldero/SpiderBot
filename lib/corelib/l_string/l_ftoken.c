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

      #include "corelib/l_string/l_ftoken.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FTOKEN_RWTillToken  ( IN     FILE     *fin,
                                     OUT    FILE     *fout,
                                     IN     T_CHAR  **toklist,
                                     INOUT  T_INT    *tokfound,
                                     IN     T_CHAR   *delimitadores,
                                     IN     T_BOOL    casesense )
      {
        T_BOOL    *tokli_lock ;
        T_BOOL     isDelimit, equalCh ;
        T_LONG    *tokli_len, *tokli_pos ;
        T_INT      i, j, ntok ;
        T_CHAR     ch ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(fout) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* ... check number of tokens ... */
        for (ntok = 0; toklist[ntok] != NULL; ntok++) 
            {
              /* count number of tokens */ ;
            }

        /* ... setup auxiliar data ... */
        tokli_len = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        NULL_RET_FALSE(tokli_len) ;
        tokli_pos = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        if (tokli_pos == NULL)
           {
             X_ALLOC_Free( (void **)&(tokli_len) ) ;
             return FALSE ;
           }
        tokli_lock = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        if (tokli_lock == NULL)
           {
             X_ALLOC_Free( (void **)&(tokli_len) ) ;
             X_ALLOC_Free( (void **)&(tokli_pos) ) ;
             return FALSE ;
           }
        for (i = 0; i < ntok; i++)
            {
              tokli_len[i]  = X_STRING_StrLen( (toklist[i]) ) ;
              tokli_pos[i]  = 0L ;
              tokli_lock[i] = FALSE ;
            }

        /* ... and begin search */
        while (TRUE)
        {
          if ( feof(fin) )
             {
               X_ALLOC_Free( (void **)&(tokli_len) ) ;
               X_ALLOC_Free( (void **)&(tokli_pos) ) ;
               X_ALLOC_Free( (void **)&(tokli_lock) ) ;
               (*tokfound) = -1 ; 
               return FALSE ;
             }

          /* read char */
          ch = fgetc(fin) ;

          if ( X_STRING_StrChr(delimitadores,ch) != NULL )
                    isDelimit = TRUE ;
               else isDelimit = FALSE ;

          /* analyze token list */
          for (i = 0; i < ntok; i++)
              {

                /* reset tokli_lock[i] */ 
                if (
                     (tokli_pos[i] == 0L)
                              &&
                     (isDelimit == TRUE)
                   )
                   {
                     (tokli_lock[i]) = FALSE ;
                     continue ;
                   }

                /* middle of other token, skip toklist[i] */ 
                if (
                     (tokli_pos[i] == 0L)
                              &&
                     (tokli_lock[i] == TRUE) 
                   )
                   {
                     continue ;
                   }

                /* token readed, end here ? */ 
                if ( tokli_pos[i] == tokli_len[i] )
                   {
                     if (isDelimit == TRUE)
                        {
                          X_ALLOC_Free( (void **)&(tokli_len) ) ;
                          X_ALLOC_Free( (void **)&(tokli_pos) ) ;
                          X_ALLOC_Free( (void **)&(tokli_lock) ) ;
                          (*tokfound) = i ; 
                          ungetc(ch,fin) ;
                          return TRUE ;
                        }
                     else 
                        {
                          (tokli_pos[i]) = 0L ;
                          (tokli_lock[i]) = TRUE ;
                        }
                   }

                /* move tokli_pos[i] */ 
                j = tokli_pos[i] ;
                if (casesense == TRUE)
                   {
                     if (toklist[i][j] == ch)
                              equalCh = TRUE ;
                         else equalCh = FALSE ;
                   }
                else
                   {
                     /* (casesense == TRUE) */
                     if (toupper(toklist[i][j]) == toupper(ch))
                              equalCh = TRUE ;
                         else equalCh = FALSE ;
                   }

                if ( equalCh == TRUE )
                   {
                     (tokli_pos[i])++ ;
                   }
                else  
                   {
                     (tokli_pos[i]) = 0L ;
                     (tokli_lock[i]) = TRUE ;
                   }

              }  /* end for */

          /* write to a file */
          if ( ch != EOF )
               fputc(ch,fout) ;

        } /* end while */

        return FALSE ;  /* dead code */
      }

      T_BOOL L_FTOKEN_ReadTillToken  ( IN     FILE     *fin,
                                       IN     T_CHAR  **toklist,
                                       INOUT  T_CHAR  **buff,
                                       INOUT  T_U_INT  *buffsize,
                                       INOUT  T_INT    *tokfound,
                                       IN     T_CHAR   *delimitadores,
                                       IN     T_BOOL    casesense )
      {
        T_BOOL    *tokli_lock ;
        T_BOOL     ok, isDelimit, equalCh ;
        T_LONG    *tokli_len, *tokli_pos ;
        T_INT      i, j, ntok ;
        T_CHAR     ch ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(buff) ;
        NULL__SET_ERROR__RET_FALSE(buffsize) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* ... check number of tokens ... */
        for (ntok = 0; toklist[ntok] != NULL; ntok++) 
            {
              /* count number of tokens */ ;
            }

        /* ... setup auxiliar data ... */
        tokli_len = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        NULL_RET_FALSE(tokli_len) ;
        tokli_pos = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        if (tokli_pos == NULL)
           {
             X_ALLOC_Free( (void **)&(tokli_len) ) ;
             return FALSE ;
           }
        tokli_lock = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        if (tokli_lock == NULL)
           {
             X_ALLOC_Free( (void **)&(tokli_len) ) ;
             X_ALLOC_Free( (void **)&(tokli_pos) ) ;
             return FALSE ;
           }
        for (i = 0; i < ntok; i++)
            {
              tokli_len[i]  = X_STRING_StrLen( (toklist[i]) ) ;
              tokli_pos[i]  = 0L ;
              tokli_lock[i] = FALSE ;
            }

        /* ... and begin search */
        while (TRUE)
        {
          if ( feof(fin) )
             {
               X_ALLOC_Free( (void **)&(tokli_len) ) ;
               X_ALLOC_Free( (void **)&(tokli_pos) ) ;
               X_ALLOC_Free( (void **)&(tokli_lock) ) ;
               (*tokfound) = -1 ; 
               return FALSE ;
             }

          /* read char */
          ch = fgetc(fin) ;

          if ( X_STRING_StrChr(delimitadores,ch) != NULL )
                    isDelimit = TRUE ;
               else isDelimit = FALSE ;

          /* analyze token list */
          for (i = 0; i < ntok; i++)
              {

                /* reset tokli_lock[i] */ 
                if (
                     (tokli_pos[i] == 0L)
                              &&
                     (isDelimit == TRUE)
                   )
                   {
                     (tokli_lock[i]) = FALSE ;
                     continue ;
                   }

                /* middle of other token, skip toklist[i] */ 
                if (
                     (tokli_pos[i] == 0L)
                              &&
                     (tokli_lock[i] == TRUE) 
                   )
                   {
                     continue ;
                   }

                /* token readed, end here ? */ 
                if ( tokli_pos[i] == tokli_len[i] )
                   {
                     if (isDelimit == TRUE)
                        {
                          X_ALLOC_Free( (void **)&(tokli_len) ) ;
                          X_ALLOC_Free( (void **)&(tokli_pos) ) ;
                          X_ALLOC_Free( (void **)&(tokli_lock) ) ;
                          (*tokfound) = i ; 
                          ungetc(ch,fin) ;
                          return TRUE ;
                        }
                     else 
                        {
                          (tokli_pos[i]) = 0L ;
                          (tokli_lock[i]) = TRUE ;
                        }
                   }

                /* move tokli_pos[i] */ 
                j = tokli_pos[i] ;
                if (casesense == TRUE)
                   {
                     if (toklist[i][j] == ch)
                              equalCh = TRUE ;
                         else equalCh = FALSE ;
                   }
                else
                   {
                     /* (casesense == TRUE) */
                     if (toupper(toklist[i][j]) == toupper(ch))
                              equalCh = TRUE ;
                         else equalCh = FALSE ;
                   }

                if ( equalCh == TRUE )
                   {
                     (tokli_pos[i])++ ;
                   }
                else  
                   {
                     (tokli_pos[i]) = 0L ;
                     (tokli_lock[i]) = TRUE ;
                   }

              }  /* end for */

          /* store in a buffer */
          if ( ch != EOF )
             {
               ok = L_BUFFA_CatOneByteToCache(buff,buffsize,ch) ;
               FALSE_RET_FALSE(ok) ;
             }

        } /* end while */

        return FALSE ;  /* dead code */
      }

      T_BOOL L_FTOKEN_SkipTillToken ( IN     FILE     *fin,
                                      IN     T_CHAR  **toklist,
                                      INOUT  T_INT    *tokfound,
                                      IN     T_CHAR   *delimitadores,
                                      IN     T_BOOL    casesense )
      {
        T_BOOL    *tokli_lock ;
        T_BOOL     isDelimit, equalCh ;
        T_LONG    *tokli_len, *tokli_pos ;
        T_INT      i, j, ntok ;
        T_CHAR     ch ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* ... check number of tokens ... */
        for (ntok = 0; toklist[ntok] != NULL; ntok++) 
            {
              /* count number of tokens */ ;
            }

        /* ... setup auxiliar data ... */
        tokli_len = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        NULL_RET_FALSE(tokli_len) ;
        tokli_pos = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        if (tokli_pos == NULL)
           {
             X_ALLOC_Free( (void **)&(tokli_len) ) ;
             return FALSE ;
           }
        tokli_lock = X_ALLOC_AllocAndSet((c_LONG) * ntok, 0) ;
        if (tokli_lock == NULL)
           {
             X_ALLOC_Free( (void **)&(tokli_len) ) ;
             X_ALLOC_Free( (void **)&(tokli_pos) ) ;
             return FALSE ;
           }
        for (i = 0; i < ntok; i++)
            {
              tokli_len[i]  = X_STRING_StrLen( (toklist[i]) ) ;
              tokli_pos[i]  = 0L ;
              tokli_lock[i] = FALSE ;
            }

        /* ... and begin search */
        while (TRUE)
        {
          if ( feof(fin) )
             {
               X_ALLOC_Free( (void **)&(tokli_len) ) ;
               X_ALLOC_Free( (void **)&(tokli_pos) ) ;
               X_ALLOC_Free( (void **)&(tokli_lock) ) ;
               (*tokfound) = -1 ; 
               return FALSE ;
             }

          /* read char */
          ch = fgetc(fin) ;

          if ( X_STRING_StrChr(delimitadores,ch) != NULL )
                    isDelimit = TRUE ;
               else isDelimit = FALSE ;

          /* analyze token list */
          for (i = 0; i < ntok; i++)
              {

                /* reset tokli_lock[i] */ 
                if (
                     (tokli_pos[i] == 0L)
                              &&
                     (isDelimit == TRUE)
                   )
                   {
                     (tokli_lock[i]) = FALSE ;
                     continue ;
                   }

                /* middle of other token, skip toklist[i] */ 
                if (
                     (tokli_pos[i] == 0L)
                              &&
                     (tokli_lock[i] == TRUE) 
                   )
                   {
                     continue ;
                   }

                /* token readed, end here ? */ 
                if ( tokli_pos[i] == tokli_len[i] )
                   {
                     if (isDelimit == TRUE)
                        {
                          X_ALLOC_Free( (void **)&(tokli_len) ) ;
                          X_ALLOC_Free( (void **)&(tokli_pos) ) ;
                          X_ALLOC_Free( (void **)&(tokli_lock) ) ;
                          (*tokfound) = i ; 
                          ungetc(ch,fin) ;
                          return TRUE ;
                        }
                     else 
                        {
                          (tokli_pos[i]) = 0L ;
                          (tokli_lock[i]) = TRUE ;
                        }
                   }

                /* move tokli_pos[i] */ 
                j = tokli_pos[i] ;
                if (casesense == TRUE)
                   {
                     if (toklist[i][j] == ch)
                              equalCh = TRUE ;
                         else equalCh = FALSE ;
                   }
                else
                   {
                     /* (casesense == TRUE) */
                     if (toupper(toklist[i][j]) == toupper(ch))
                              equalCh = TRUE ;
                         else equalCh = FALSE ;
                   }

                if ( equalCh == TRUE )
                   {
                     (tokli_pos[i])++ ;
                   }
                else  
                   {
                     (tokli_pos[i]) = 0L ;
                     (tokli_lock[i]) = TRUE ;
                   }

              }  /* end for */
        } /* end while */

        return FALSE ;  /* dead code */
      }

      T_BOOL L_FTOKEN_ReadAndExpandTillToken
             ( 
               IN     FILE     *f,
               IN     T_CHAR  **toklist,
               INOUT  T_CHAR  **buff,
               INOUT  T_U_INT  *buffsize,
               INOUT  T_INT    *tokfound,
               IN     T_CHAR   *delimitadores,
               IN     T_CHAR   *tabhits,
               IN     T_INT     width,
               IN     T_CHAR    chclear 
             )
      {
        T_BOOL  ok ;
        T_INT   ntok, i ;
        T_CHAR  *espa, *token, ch ;
        T_LONG  posnow ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(f) ;
        NULL__SET_ERROR__RET_FALSE(toklist) ;
        NULL__SET_ERROR__RET_FALSE(buff) ;
        NULL__SET_ERROR__RET_FALSE(buffsize) ;
        NULL__SET_ERROR__RET_FALSE(tokfound) ;
        NULL__SET_ERROR__RET_FALSE(delimitadores) ;

        /* preparo datos auxiliares ... */
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
        /* ... y comienzo la busqueda */
        while (TRUE)
        {
          token = L_FCHSET_ReadAndExpandTillCharSet(f,espa,chclear,
                                                    tabhits,width,*buffsize) ;
          if (!token)
             {
               X_ALLOC_Free((void **)&espa) ;
               return FALSE ;
             }
          ok = L_BUFFA_CatNBytesToCache(buff,buffsize,token,strlen(token)) ;
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
                if (X_STRING_Equal(token,toklist[i]) == TRUE)
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


  /* ..................................................................... */
    
