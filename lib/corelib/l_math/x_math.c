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

      #include "corelib/l_math/x_math.h"


   /* ... Functions / Funciones ......................................... */

     /* Usually Math Functions *
      * ---------------------- */
      T_INT   X_MATH_Ipow ( IN     T_INT  base,
                            IN     T_INT  expo )
      {
        T_INT result, i ;

        result=1 ;
        for (i=0; i<expo; i++)
             result*=base ;
        return result ;
      }

      void  X_MATH_Randomize ( T_U_INT base )
      {
#if defined(__MSDOS__)
        randomize() ;
#endif
#if (defined(__LINUX__) || defined(__SUNOS__))
        srand(base) ;
#endif
      }

      T_INT X_MATH_Random    ( T_U_INT limit )
      {
#if defined(__MSDOS__)
        return random(limit) ;
#endif
#if (defined(__LINUX__) || defined(__SUNOS__))
        T_INT rn ;

        rn = rand() ;
        if (rn > limit)
                 return (rn % limit) ;
            else return rn ;
#endif
      }


   /* ................................................................... */

