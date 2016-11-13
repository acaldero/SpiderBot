

 #ifndef L_NNTP_GROUP_H
 #define L_NNTP_GROUP_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/l_line.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_nntp/l_nntp_log.h"
      #include "weblib/l_nntp/l_nntp_server.h"
      #include "weblib/l_nntp/l_nntp_response.h"
      #include "weblib/l_nntp/l_nntp_command.h"
      #include "weblib/l_file/l_file_upload.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_NNTP_GROUP_DownLoad      ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_nntpCfg      *nntpCfg,
                                           INOUT  FILE          **fpage,
                                           IN     t_url          *url ) ;
      /* - download news list group. */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

