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

      #include "corelib/l_time/i_time_ms.h"


   /* ... functions / funciones ......................................... */

 #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))

      void     I_TIME_MS_GetTime    ( IN  T_TIMEMS  *ins )
      {
	gettimeofday(ins,NULL) ;
      }

      T_ACCTIMEMS    I_TIME_MS_DiffTime  ( IN  T_TIMEMS  *fin,
                                           IN  T_TIMEMS  *ini ) 
      { 
	T_LONG sf, si, hf, hi ;
	T_LONG s, us ;

        sf = (fin->tv_sec) ;
        si = (ini->tv_sec) ;
        hf = (fin->tv_usec) ;
        hi = (ini->tv_usec) ;
	if (hf >= hi)
	   {
	     us = hf - hi ;
	   } 
           else {
		  us = 1000000 + hf - hi ;
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
        return (T_ACCTIMEMS)(s*1000000 + us) ;
      }

      T_CHAR  *I_TIME_MS_timeToString ( IN  T_TIMEMS  *t )
      {
        T_CHAR *pch ;

        NULL__SET_ERROR__RET_NULL(t) ;
        pch = X_STRING_Dsprintf("(sec=%li,usec=%li)",
                                (T_LONG)t->tv_sec,
                                (T_LONG)t->tv_usec) ;
        return (T_CHAR *)pch ;
      }

 #endif


      T_CHAR  *I_TIME_MS_CurrCTime  ( void )
      { 
        time_t tnow ;
        T_CHAR *pcr, *tstr ;

        tnow = time(NULL) ;
	tstr = (T_CHAR *)ctime(&tnow) ;
        pcr  = strrchr(tstr,'\n') ;
        *pcr = '\0' ;
        return tstr ; 
      }

      T_CHAR  *I_TIME_MS_acctimeToString ( IN  T_ACCTIMEMS  *t )
      {
        T_CHAR *pch ;

        NULL__SET_ERROR__RET_NULL(t) ;
	pch = X_STRING_Dsprintf(pch,"acctime=%g",
                                (*t)) ;
	return (T_CHAR *)pch ;
      }


   /* ................................................................... */

