/* ....................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 * See documentation for more information.
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * .................................................................... */



   /* ... Includes / Inclusiones ...................................... */

      #include "corelib/l_time/x_time.h"


   /* ... Functions / Funciones ....................................... */

      T_DOUBLE   X_TIME_Get_time      ( void )
      {
        struct timeval tp;
        struct timezone tzp;

        gettimeofday(&tp,&tzp);
        return((double) tp.tv_sec + .000001 * (double) tp.tv_usec);
      }

      T_DOUBLE   X_TIME_Get_tick      ( void )
      {
        static double tickval = -1.0 ;
        double t1, t2 ;
        int    cnt ;
        int    icnt ;

        if (tickval < 0.0) 
           {
             tickval = 1.0e6 ;
             for (icnt=0; icnt<10; icnt++) 
                 {
                   cnt = 1000 ;
                   t1  = X_TIME_Get_time() ;
                   while (cnt-- && (t2 = X_TIME_Get_time()) <= t1)  ;
                   if (cnt && t2 - t1 < tickval)
                   tickval = t2 - t1 ;
                 }
           }
        return tickval ;
      }


   /* ................................................................. */


