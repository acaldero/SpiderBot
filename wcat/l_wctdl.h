

 #ifndef L_WCTDL_H
 #define L_WCTDL_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_string/x_string.h"
      #include "weblib/l_ws/l_setws.h"
      #include "wpplib/l_robot/l_ctbot.h"
      #include "wpplib/l_data/l_log.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wcat/c_wcat.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_WCTDL_DownLoad     ( IN    t_wppOptions    *wcOpt ) ;
      /* - Start download with option defined in 'wcOpt'. */
      /* - */


   /* ................................................................... */


#endif

