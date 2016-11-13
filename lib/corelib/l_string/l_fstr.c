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

      #include "corelib/l_string/l_fstr.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FSTR_RWTillStr           ( INOUT  FILE    *fin,
                                           INOUT  FILE    *fout,
                                           IN     T_CHAR  *str,
                                           IN     T_BOOL   CaseSense )
      {
        T_CHAR chR ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(fout) ;
        NULL__SET_ERROR__RET_FALSE(str) ;

        /* ... rwtillstr ... */
        do
        {
          chR = fgetc(fin) ;
          if (chR == str[0])
             {
               if (L_FSTR_AcceptStr(fin,&(str[1]),CaseSense) == TRUE)
                   return TRUE ;
             }
          fputc(chR,fout) ;
        } while (! feof(fin)) ;
        return FALSE ;
      }

     T_BOOL L_FSTR_SkipTillStr ( INOUT  FILE    *fin,
                                 IN     T_CHAR  *patron,
                                 IN     T_BOOL   CaseSense )
     {
       T_CHAR  ch ;
       T_CHAR *pch ;
       T_BOOL  found ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(patron) ;

        /* ... skipTillStr ... */
        found = FALSE ;
        ch    = '\0' ;
        while ( 
                ( ! feof(fin) )
                      && 
                (found == FALSE) 
              )
        {
          pch = patron ;
          if (CaseSense == TRUE) 
             {
               do
               {
                 ch = getc(fin) ;
                 if (ch == pch[0]) 
                     break ; 
               } while ( ! feof(fin) ) ;
             }
          if (CaseSense != TRUE) 
             {
               do
               {
                 ch = getc(fin) ;
                 if (toupper(ch) == toupper(*pch)) 
                     break ; 
               } while ( ! feof(fin) ) ;
             }
          if (feof(fin))
                   return FALSE ;
              else ungetc(ch,fin) ;
          found = TRUE ;
          for(;(*pch);pch++)
          {
            ch = getc(fin) ;
            if (feof(fin))
                return FALSE ;
            if ( ((CaseSense == TRUE) && (ch != (*pch)))
                               ||
               ((CaseSense == FALSE) && (toupper(ch) != toupper(*pch))) )
               {
                 found = FALSE ;
                 break ;
               }
          }
          TRUE_RET_TRUE(found) ;
       }

       return FALSE ;
     }
 
      T_BOOL  L_FSTR_AcceptStr           ( INOUT  FILE   *fin,
                                           IN     T_CHAR *pattern,
                                           IN     T_BOOL  CaseSensetive )
      {
        T_CHAR chR ;
        T_LONG ipos ;
        T_INT  i ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(pattern) ;

        /* ... AcceptStr ... */
        ipos=ftell(fin) ;
        chR=fgetc(fin) ;
        if (feof(fin))
           return FALSE ;
        if (CaseSensetive==FALSE)
          {
            for (i=0;
                      (pattern[i]!='\0')
                              &&
                      (toupper(pattern[i])==toupper(chR)); i++)
           {
             chR=fgetc(fin) ;
           }
          } else {
                   for (i=0; (pattern[i]!='\0')
                                     &&
                             (pattern[i]==chR); i++)
                   {
                     chR=fgetc(fin) ;
                   }
                 }
        if (pattern[i]=='\0')
           {
             /**/ungetc(chR,fin) ;
             return TRUE ;
           }
        fseek(fin,ipos,SEEK_SET) ;
        return FALSE ;
      }
 
     T_CHAR *L_FSTR_GetItemValue ( INOUT  FILE    *fin,
                                   IN     T_CHAR  *item,
                                   IN     T_BOOL   CaseSense,
                                   IN     T_CHAR  *deli )
     {
       T_CHAR *pch ;
       T_BOOL ok ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;

        /* ... GetItemValue ... */
        L_FCHSET_SkipCharSet(fin,deli) ;
        ok = L_FSTR_AcceptStr(fin,item,CaseSense) ;
        if (ok  ==  FALSE)
           {
             errno = ERR__NOT_FOUND ;
             return NULL ;
           }
        L_FCHSET_SkipCharSet(fin,deli) ;
        pch = L_FCHSET_ReadTillCharSet(fin,deli,FALSE) ;
        if (X_STRING_Equal(pch,"\"") == TRUE)
           {
             L_FCHSET_SkipCharSet(fin,"\"") ;
             X_ALLOC_Free((void **)&pch) ;
             pch = L_FCHSET_ReadTillCharSet(fin,"\"",FALSE) ;
             L_FCHSET_SkipCharSet(fin,"\"") ;
           }
       return pch ;
     }
 
     T_BOOL L_FSTR_SearchStr ( INOUT  FILE   *f,
                               IN     T_CHAR *str,
                               IN     T_BOOL  CaseSense )
     {
       T_LONG ipos ;
       T_BOOL ok ;
 
       NULL__SET_ERROR__RET_FALSE(f) ;
       ipos=ftell(f) ;
       ok=L_FSTR_SkipTillStr(f,str,CaseSense) ;
       TRUE_RET_TRUE(ok) ;
       fseek(f,ipos,SEEK_SET) ;
       return FALSE ;
     }
 
      T_BOOL  L_FSTR_SkipCharSetAndAcceptStr ( INOUT  FILE    *f,
                                               IN     T_CHAR  *pattern,
                                               IN     T_BOOL   CaseSense,
                                               IN     T_CHAR  *deli )
      {
        T_LONG ipos ;
 
        NULL__SET_ERROR__RET_FALSE(f) ;
        ipos=ftell(f) ;
        L_FCHSET_SkipCharSet(f,deli) ;
        if (feof(f))
          {
            fseek(f,ipos,SEEK_SET) ;
            return FALSE ;
          }
        return L_FSTR_AcceptStr(f,pattern,CaseSense) ;
      }
 

  /* ..................................................................... */

