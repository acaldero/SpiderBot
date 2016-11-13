

 #ifndef L_WLSDL_H
 #define L_WLSDL_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_string/x_string.h"
      #include "weblib/l_ws/l_setws.h"
      #include "wpplib/l_robot/l_lsbot.h"
      #include "wpplib/l_data/l_log.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wdir/c_wdir.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_WLSDL_DownLoad     ( IN    t_wppOptions    *wlsOpt ) ;
      /* - Start download with option defined in 'wlsOpt'. */
      /* - */


   /* ................................................................... */


#endif

