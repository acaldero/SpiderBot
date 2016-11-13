

 #ifndef L_FINGER_DOWNLOAD_H
 #define L_FINGER_DOWNLOAD_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_finger/l_finger_server.h"
      #include "weblib/l_finger/l_finger_log.h"
      #include "weblib/l_finger/l_finger_command.h"
      #include "weblib/l_finger/l_finger_download/l_finger_user.h"
      #include "weblib/l_finger/l_finger_download/l_finger_machine.h"
      #include "weblib/l_verbose/l_verbose_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FINGER_DOWNLOAD_DownLoadUrl    ( INOUT  t_downLoadWS   *dlws,
                                                 IN     t_fingerCfg    *fingerCfg,
                                                 INOUT  FILE          **fpage,
                                                 IN     t_url          *url ) ;
      /* - download ONLY url (not recursive) */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

