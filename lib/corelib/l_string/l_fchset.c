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

      #include "corelib/l_string/l_fchset.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL L_FCHSET_SkipCharSet ( INOUT  FILE   *f,
                                    IN     T_CHAR *s )
      {
        T_CHAR ch ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_TRUE(f) ;
        NULL__SET_ERROR__RET_TRUE(s) ;

        /* ... SkipCharSet ... */
        do
        {
          ch = getc(f) ;
        } while ( 
                  ( ! feof(f) ) 
                      && 
                  ( X_STRING_StrChr(s,ch) )
                ) ;
        if ( !feof(f) )
           {
               ungetc(ch,f) ;
               return TRUE ;
           }
        return FALSE ;
      }
  
      T_BOOL L_FCHSET_ChSkipingCharSet ( INOUT  FILE   *f,
                                         IN     T_CHAR *s )
      {
        T_CHAR  ch ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_TRUE(f) ;
        NULL__SET_ERROR__RET_TRUE(s) ;

        /* ... ChSkipingCharSet ... */
        do
        {
          ch = getc(f) ;
        } while ( 
                  ( ! feof(f) ) 
                      && 
                  ( X_STRING_StrChr(s,ch) )
                ) ;
        if ( feof(f) )
            return FALSE ;
        return TRUE ;
      }
  
      T_CHAR *L_FCHSET_ReadTillCharSet  ( INOUT  FILE    *f,
                                          IN     T_CHAR  *s,
                                          IN     T_BOOL   cs )
      {
        T_CHAR    ch, *buff ;
        T_U_INT   cbuff ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_NULL(f) ;
        NULL__SET_ERROR__RET_NULL(s) ;

        /* ... ReadTillCharSet ... */
        buff  = NULL ;
        cbuff = 0 ;
        ch    = getc(f) ;
        if (cs == TRUE)
           {
             while ( (!feof(f)) && (!X_STRING_StrChr(s,ch)) )
             {
               if (L_BUFFA_CatOneByteToCache(&buff,&cbuff,ch) == FALSE)
                   return NULL ;
                    ch = getc(f) ;
             }
           }
        else 
           {
             while ( 
                     (!feof(f)) 
                         && 
                     (!X_STRING_StrChr(s,ch)) 
                         && 
                     (!X_STRING_StrChr(s,toupper(ch))) 
                   )
             {
               if (L_BUFFA_CatOneByteToCache(&buff,&cbuff,ch) == FALSE)
                   return NULL ;
                    ch = getc(f) ;
             }
           }
        if (!feof(f))
            ungetc(ch,f) ;
        if (L_BUFFA_CatOneByteToCache(&buff,&cbuff,'\0') == FALSE)
            return NULL ;
        return buff ;
      }
  
      T_BOOL  L_FCHSET_ReadBinTillCharSet  ( INOUT  FILE     *f,
                                             IN     T_CHAR   *s,
                                             IN     T_BOOL    cs,
                                             OUT    T_CHAR  **buff,
                                             OUT    T_U_INT  *bufflen )
      {
        T_BOOL  ok ;
        T_CHAR  ch ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_TRUE(f) ;
        NULL__SET_ERROR__RET_TRUE(s) ;
        NULL__SET_ERROR__RET_TRUE(buff) ;
        NULL__SET_ERROR__RET_TRUE(bufflen) ;

        /* ... ReadBinTillCharSet ... */
        (*buff)    = NULL ;
        (*bufflen) = 0 ;
        ch         = getc(f) ;
        if (cs == TRUE)
           {
             while ( (!feof(f)) && (!X_STRING_StrChr(s,ch)) )
             {
               ok = L_BUFFA_CatOneByteToCache(&(*buff),&(*bufflen),ch) ;
               FALSE_RET_FALSE(ok) ;
                    ch = getc(f) ;
             }
           }
        else 
           {
             while ( 
                     (!feof(f)) 
                         && 
                     (!X_STRING_StrChr(s,ch)) 
                         && 
                     (!X_STRING_StrChr(s,toupper(ch))) 
                   )
             {
               ok = L_BUFFA_CatOneByteToCache(&(*buff),&(*bufflen),ch) ;
               FALSE_RET_FALSE(ok) ;
                    ch = getc(f) ;
             }
           }
        if (!feof(f))
            ungetc(ch,f) ;
        return TRUE ;
      }
  
      T_CHAR *L_FCHSET_ReadAndExpandTillCharSet
              ( 
                INOUT  FILE   *f,
                IN     T_CHAR *s,
                IN     T_CHAR  ch_clear,
                IN     T_CHAR *tabhits,
                IN     T_INT   width,
                IN     T_INT   wpos 
              )
      {
        T_CHAR   ch, *buff, *auxbuff ;
        T_U_INT  cbuff ;
        T_INT    tofill ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_NULL(f) ;
        NULL__SET_ERROR__RET_NULL(s) ;
        NULL__SET_ERROR__RET_NULL(tabhits) ;

        ch    = getc(f) ;
        buff  = NULL ;
        cbuff = 0 ;
        while ( (!feof(f)) && (!X_STRING_StrChr(s,ch)) )
        {
          if (L_FCHSET_ReadCRLF(f,ch) != TRUE)
             {
               T_BOOL ok ;
  
               switch(ch)
               {
                 case '\t' :
                        ok = L_BUFFA_CatNBytesToCache(&buff,&cbuff,
                                                      tabhits,
                                                      strlen(tabhits)) ;
                      break ;
                 default :
                      ok = L_BUFFA_CatOneByteToCache(&buff,&cbuff,ch) ;
               }
               if (ok == FALSE)
                  {
                    X_ALLOC_Free((void **)&buff) ;
                    return NULL ;
                  }
             }
          else  /* (L_FCHSET_ReadCRLF(f,ch) == TRUE) */
             {
               tofill = width - ((wpos + cbuff) % width) ;
               auxbuff = X_ALLOC_AllocAndSet(tofill,ch_clear) ;
               if (auxbuff == NULL)
                  {
                    X_ALLOC_Free((void **)&buff) ;
                    return NULL ;
                  }
               if (
                    L_BUFFA_CatNBytesToCache(&buff,&cbuff,auxbuff,tofill)
                    == 
                    FALSE
                  )
                  {
                    X_ALLOC_Free((void **)&buff) ;
                    return NULL ;
                  }
               X_ALLOC_Free((void **)&auxbuff) ;
             }
          ch = getc(f) ;
        }
        if (!feof(f))
            ungetc(ch,f) ;
        if (L_BUFFA_CatOneByteToCache(&buff,&cbuff,'\0') == FALSE)
            return NULL ;
        L_BUFFA_AjustCache(&buff,cbuff) ;
        return buff ;
      }
  
      T_BOOL L_FCHSET_ReadCRLF ( INOUT  FILE    *f,
                                 IN     T_CHAR   c )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_TRUE(f) ;

        switch(c)
        {
          case '\n' : return TRUE ;
          case '\r' : {
                        T_CHAR ch ;

                        ch = getc(f) ;
                        switch (ch)
                        {
                          case '\n' : return TRUE ;
                          default   :
                                      /* si estamos en fichero-DOS, ... */
                                      ungetc(ch,f) ;
                                      return TRUE ;
                        }
                    }
          default : return FALSE ;
        }
      }

  
   /* ..................................................................... */

