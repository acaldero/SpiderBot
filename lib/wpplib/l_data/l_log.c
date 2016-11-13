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

      #include "wpplib/l_data/l_log.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_LOG_Setup         ( INOUT  FILE   *flog,
                                     IN     T_CHAR *progname )
      {
        T_CHAR   *now ;

        NULL__SET_ERROR__RET_FALSE(flog) ;
        now  = V_TIME_CurrCTime() ;
        fprintf(flog,
                "\n"
                "\n"
                "*********************************************************\n"
                "* %s begin up at %s\n"
                "*********************************************************\n",
                progname,now) ;
        return TRUE ;
      }


   /* ................................................................... */

