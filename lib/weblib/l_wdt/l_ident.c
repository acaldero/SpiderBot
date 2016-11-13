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

      #include "weblib/l_wdt/l_ident.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_IDENT_ParseFromString   ( INOUT  t_ident  *ident,
                                            IN     T_CHAR   *str )
      {
        T_CHAR *pch ;

        NULL__SET_ERROR__RET_FALSE(ident) ;

        L_IDENT_MakeEmpty(ident) ;
        NULL_RET_TRUE(str) ;
        pch = strchr(str,':') ;
        if (pch != NULL)
           {
             pch[0] = '\0' ;
             ident->user = X_STRING_StrDup(pch) ;
             pch[0] = ':' ;
             ident->pass = X_STRING_StrDup(pch + 1) ;
           }
        else 
           {
             ident->user = X_STRING_StrDup(str) ;
             ident->pass = X_STRING_StrDup("") ;
           }
        ident->user = (char *)memfrob( ident->user,
                                       X_STRING_StrLen(ident->user) ) ;
        ident->pass = (char *)memfrob( ident->pass,
                                       X_STRING_StrLen(ident->pass) ) ;
        return TRUE ;
      }

      T_BOOL    L_IDENT_Destroy   ( INOUT  t_ident  **ident )
      {
        NULL_RET_TRUE(ident) ;
        NULL_RET_TRUE((*ident)) ;

        X_ALLOC_Free( (void **) &( (*ident)->user ) ) ;
        X_ALLOC_Free( (void **) &( (*ident)->pass ) ) ;
        X_ALLOC_Free( (void **) ident ) ;

        return TRUE ;
      }

      T_BOOL    L_IDENT_MakeEmpty   ( INOUT  t_ident   *ident )
      {
        NULL_RET_TRUE(ident) ;

        ident->user  = NULL ;
        ident->pass  = NULL ;

        return TRUE ;
      }

      T_BOOL    L_IDENT_Empty       ( INOUT  t_ident   *ident )
      {
        NULL_RET_TRUE(ident) ;

        X_ALLOC_Free( (void **) &(ident->user) ) ;
        X_ALLOC_Free( (void **) &(ident->pass) ) ;
        ident->user  = NULL ;
        ident->pass  = NULL ;

        return TRUE ;
      }

      T_CHAR   *L_IDENT_getUser   ( INOUT  t_ident   *ident )
      {
        T_CHAR  *user ;

        NULL_RET_NULL(ident) ;
        user = X_STRING_StrDup(ident->user) ;
        user = (char *)memfrob(user,X_STRING_StrLen(user)) ;
        return user ;
      }

      T_CHAR   *L_IDENT_getPass   ( INOUT  t_ident   *ident )
      {
        T_CHAR  *pass ;

        NULL_RET_NULL(ident) ;
        pass = X_STRING_StrDup(ident->pass) ;
        pass = (char *)memfrob(pass,X_STRING_StrLen(pass)) ;
        return pass ;
      }


  /* ................................................................... */

