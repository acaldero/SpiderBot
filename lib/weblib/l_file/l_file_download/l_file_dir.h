

 #ifndef L_FILE_DIR_H
 #define L_FILE_DIR_H

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
      #include "weblib/l_file/l_file_command.h"
      #include "weblib/l_file/l_file_server.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FILE_DIR_DownLoadDir    ( INOUT  t_downLoadWS   *dlws,
                                          IN     t_fileCfg      *fileCfg,
                                          INOUT  FILE          **fpage,
                                          IN     t_url          *url ) ;
      /* - Write at `*fpage` file, directory contents
           from ftp directory pointer by `url`. */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

