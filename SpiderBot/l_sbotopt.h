

 #ifndef L_SBOTOPT_H
 #define L_SBOTOPT_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_string/x_string.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_SBOTOPT_MakeEmpty       ( INOUT  t_wppOptions  *wOpt ) ;
      /* - Free memory in 'wOpt' componets */
      /* - */

      T_BOOL   L_SBOTOPT_wppOptToFile    ( IN    t_wppOptions    *wOpt ) ;
      /* - Print a human readable 
           representacion of 'wOpt'. */
      /* - */

      T_BOOL   L_SBOTOPT_activeWppOptToFile  ( IN    t_wppOptions   *wOpt ) ;
      /* - like L_SBOTOPT_wOptToFile, but only 
           print option that are ON */
      /* - */

      T_BOOL   L_SBOTOPT_CheckValid      ( IN    t_wppOptions    *wOpt ) ;
      /* - Check if values of 'wOpt' are valid. */
      /* - */


   /* ................................................................... */


 #endif

