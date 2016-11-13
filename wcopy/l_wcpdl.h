

 #ifndef L_WCPDL_H
 #define L_WCPDL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_string/x_string.h"
      #include "weblib/l_ws/l_setws.h"
      #include "wpplib/l_robot/l_dlbot.h"
      #include "wpplib/l_data/l_log.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wcopy/c_wcopy.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_WCPDL_DownLoad     ( IN    t_wppOptions    *wOpt ) ;
      /* - Start download with option defined in 'wcOpt'. */
      /* - */


   /* ................................................................... */


#endif

