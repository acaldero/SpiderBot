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

      #include "weblib/l_wdt/l_disallowli.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_DISALLOWLI_ReadDisallow    ( INOUT t_disallowLi *disli,
                                              INOUT FILE         *fbot ) 
      {
        T_BOOL   ok ;
        T_CHAR  *ToDissallow ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(disli,"NULL disli") ;
        L_DEBUG_NULL_E_F(fbot,"NULL fbot") ;

	ok = L_FSTR_SkipTillStr(fbot,"Disallow",FALSE) ;
        FALSE_RET_TRUE(ok) ;
	do
	{
	  ToDissallow = L_FSTR_GetItemValue(fbot,":",FALSE," \t\n") ;
	  if (ToDissallow != NULL)
	     {
	       ok = L_STRLI_Insert(disli,ToDissallow) ;
	       FALSE_RET_FALSE(ok) ;
	     }
	  L_FSTR_SkipTillStr(fbot,"Disallow",FALSE) ;
	} while ( !feof(fbot) ) ;
        return TRUE ;
      }

      T_BOOL   L_DISALLOWLI_IsDisallow      ( IN    t_disallowLi *disli,
                                              IN    t_url        *url )
      {
	T_U_LONG   i, Total, nchar ;
        T_BOOL     ok ;
        T_CHAR    *pchar ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(disli,"NULL disli") ;
        L_DEBUG_NULL_E_F(url,"NULL url") ;

        Total = L_STRLI_NumberStrings(disli) ;
        for (i=0; i<Total; i++)
	    {
              pchar = L_STRLI_StringIn(disli,i) ;
              nchar = X_STRING_StrLen(pchar) ;
	      ok = (strncmp(pchar,url->file,nchar) == 0) ;
	      TRUE_RET_TRUE(ok) ;
	    }
	return FALSE ;
      }


   /* ................................................................... */

