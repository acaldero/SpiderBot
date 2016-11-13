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

      #include "corelib/l_time/i_time_sg.h"


   /* ... Functions / Funciones ......................................... */

      T_CHAR  *I_TIME_SG_CurrCTime  ( void ) 
      { 
        T_TIMESG tnow ;
        T_CHAR *pcr, *tstr ;

        tnow = time(NULL) ;
        tstr = ctime(&tnow) ;
        pcr  = strrchr(tstr,'\n') ;
        *pcr = '\0' ;
        return tstr ; 
      }

      T_CHAR  *I_TIME_SG_CurrCTime  ( void )
      {
        time_t tnow ;
        T_CHAR *pcr, *tstr ;

        tnow = time(NULL) ;
        tstr = ctime(&tnow) ;
        pcr  = strrchr(tstr,'\n') ;
        *pcr = '\0' ;
        return tstr ;
      }

      T_CHAR  *I_TIME_SG_acctimeToString ( IN  T_ACCTIMESG  *t )
      {
        T_CHAR *pch ;

        NULL__SET_ERROR_RET_NULL(t) ;
        pch = (T_CHAR *)X_ALLOC_Malloc(2*c_STR_LONG + 3 + 1 + c_STR_DOUBLE) ;
        NULL_RET_NULL(pch) ;
        sprintf(pch,"%g",(*t)) ;
        return (T_CHAR *)pch ;
      }


   /* ................................................................... */

