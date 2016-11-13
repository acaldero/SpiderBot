

 #ifndef L_SBOTDL_H
 #define L_SBOTDL_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/x_print.h"
      #include "weblib/l_ws/l_setws.h"
      #include "wpplib/l_robot/l_sbbot.h"
      #include "wpplib/l_data/l_log.h"
      #include "SpiderBot/c_spiderbot.h"
      #include "SpiderBot/l_sbotopt.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_SBOTDL_DownLoad     ( IN    t_wppOptions    *wOpt ) ;
      /* - Start download with option defined in 'wOpt'. */
      /* - */


   /* ................................................................... */


#endif

