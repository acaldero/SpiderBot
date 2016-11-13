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

      #include "corelib/l_time/i_time_hs.h"


   /* ... Functions / Funciones ......................................... */

 #if defined(__MSDOS__)

      void     I_TIME_HS_GetTime    ( IN  T_TIMEHS  *ins )
      {
	gettime(ins) ;
      }

      T_ACCTIMEHS    I_TIME_HS_DiffTime  ( IN  T_TIMEHS  *fin,
                                           IN  T_TIMEHS  *ini ) 
      { 
	T_LONG sf, si, hf, hi ;
	T_LONG s, us ;

        sf = (fin->ti_sec) ;
        si = (ini->ti_sec) ;
        hf = (fin->ti_hund) ;
        hi = (ini->ti_hund) ;
	if (hf >= hi)
	   {
	     us = hf - hi ;
	   } 
           else {
		  us = 1000 + hf - hi ;
		  if (sf)
	              sf-- ;
		}
	if (sf >= si)
	   {
	     s = sf - si ;
	   } 
           else {
		  us = 0 ;
		  s  = 0 ;
		}
	return (T_ACCTIMEHS)(s*1000 + us) ;
      }

      T_CHAR  *I_TIME_HS_timeToString ( IN  T_TIMEHS  *t )
      {
        T_CHAR *pch ;

        NULL__SET_ERROR__RET_NULL(t) ;
	pch = X_STRING_Dsprintf(pch,"(sec=%i,hundsec=%i)",
                                t->ti_sec,
                                t->ti_hund) ;
        return (T_CHAR *)pch ;
      }

 #endif

      T_CHAR  *I_TIME_HS_CurrCTime  ( void )
      { 
        time_t tnow ;
        T_CHAR *pcr, *tstr ;

        tnow = time(NULL) ;
	tstr = (T_CHAR *)ctime(&tnow) ;
        pcr  = strrchr(tstr,'\n') ;
        *pcr = '\0' ;
        return tstr ; 
      }

      T_CHAR  *I_TIME_HS_acctimeToString ( IN  T_ACCTIMEHS  *t )
      {
        T_CHAR *pch ;

        NULL__SET_ERROR__RET_NULL(t) ;
	pch = X_STRING_Dsprintf(pch,"acctime=%g",
                                (*t)) ;
	return (T_CHAR *)pch ;
      }


   /* ................................................................... */

