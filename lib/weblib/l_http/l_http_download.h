

 #ifndef L_HTTP_DOWNLOAD_H
 #define L_HTTP_DOWNLOAD_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_http/l_http_download/l_http09_page.h"
      #include "weblib/l_http/l_http_download/l_http10_page.h"
      #include "weblib/l_http/l_http_download/l_http11_page.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_httpCfg      *webCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url ) ;
      /* - Use webServer http version, and download
           using http/x.x according to. */
      /* - Transferencia segun la version de http. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

