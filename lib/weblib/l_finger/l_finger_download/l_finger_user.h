

 #ifndef L_FINGER_USER_H
 #define L_FINGER_USER_H

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
      #include "weblib/l_finger/l_finger_log.h"
      #include "weblib/l_finger/l_finger_server.h"
      #include "weblib/l_finger/l_finger_response.h"
      #include "weblib/l_finger/l_finger_command.h"
      #include "weblib/l_file/l_file_upload.h"
      #include "weblib/l_verbose/l_verbose_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FINGER_USER_Open          ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg,
                                            IN     t_url          *url ) ;
      /* - */
      /* - */

      T_BOOL  L_FINGER_USER_Close         ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg ) ;
      /* - */
      /* - */

      T_BOOL  L_FINGER_USER_DownLoad      ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url ) ;
      /* - Download ONLY user connected. */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

