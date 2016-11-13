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

      #include "corelib/l_alloc/i_alloc_final.h"


   /* ... Functions / Funciones ......................................... */

      /*  Control Memory Functions  *
       * -------------------------- */
      T_U_LONG   I_ALLOC_FINAL_Available ( void )
      {
        #if defined(__MSDOS__)
            #if (!defined(_Windows))
                 return (T_U_LONG) farcoreleft() ;
            #else
                 return 0L ;
            #endif
        #endif

        #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
             struct rlimit rl ;

             getrlimit(RLIMIT_DATA,&rl) ;
             return rl.rlim_cur ;
        #endif

      }


   /* ................................................................... */

