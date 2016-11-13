

 #ifndef L_HTTP09_PAGE_H
 #define L_HTTP09_PAGE_H

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
      #include "weblib/l_url/l_urlxml.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_http/l_http_server.h"
      #include "weblib/l_http/l_http_log.h"
      #include "weblib/l_http/l_http_download/l_http09_command.h"
      #include "weblib/l_file/l_file_upload.h"
      #include "weblib/l_verbose/l_verbose_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP09_PAGE_DownLoadPage     ( INOUT  t_downLoadWS   *dlws,
                                               IN     t_httpCfg      *webCfg,
                                               INOUT  FILE          **fpage,
                                               IN     t_url          *url ) ;
      /* - */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

