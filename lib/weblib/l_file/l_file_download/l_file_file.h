

 #ifndef L_FILE_FILE_H
 #define L_FILE_FILE_H

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
      #include "weblib/l_verbose/l_verbose_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FILE_FILE_DownLoadFile  ( INOUT  t_downLoadWS   *dlws,
                                          IN     t_fileCfg      *fileCfg,
                                          INOUT  FILE          **fpage,
                                          INOUT  t_url          *url,
                                          IN     T_LONG          fsize ) ;
      /* - "Download" file at 'url' to '(*fpage)'. */
      /* - Transfiere fichero indicado por 'url' a '(*fpage)'. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

