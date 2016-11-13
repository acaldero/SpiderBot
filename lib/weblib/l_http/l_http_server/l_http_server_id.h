

 #ifndef L_HTTP_SERVER_ID_H
 #define L_HTTP_SERVER_ID_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_cdt/l_strli.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_verbose/l_verbose_log.h"
      #include "corelib/l_string/l_fstr.h"
      #include "weblib/l_http/l_http_server/l_http_server_httpcfg.h"
      #include "weblib/l_http/l_http_download/l_http09_command.h"
      #include "weblib/l_http/l_http_download/l_http10_command.h"
      #include "weblib/l_http/l_http_download/l_http11_command.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP_SERVER_ID_GetVersion     ( IN     t_httpCfg      *webCfg,
                                                IN     t_url          *url,
                                                INOUT  t_downLoadWS   *dlws ) ;
      /* - Get server http version. */
      /* - Obtiene la version del servidor http. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

