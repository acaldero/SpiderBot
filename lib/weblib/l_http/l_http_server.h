

 #ifndef L_HTTP_SERVER_H
 #define L_HTTP_SERVER_H

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
      #include "weblib/l_http/l_http_download/l_http09_command.h"
      #include "weblib/l_http/l_http_download/l_http10_command.h"
      #include "weblib/l_http/l_http_download/l_http11_command.h"
      #include "weblib/l_http/l_http_server/l_http_server_httpcfg.h"
      #include "weblib/l_http/l_http_server/l_http_server_id.h"
      #include "weblib/l_http/l_http_server/l_http_server_header.h"
      #include "weblib/l_http/l_http_server/l_http_server_disallow.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_HTTP_SERVER_Setup          ( OUT     t_httpCfg      *webCfg,
                                              IN      t_url          *urlHost,
                                              INOUT   t_downLoadWS   *dlws ) ;
      /* - Autodetect Http version, and get 'robots.txt', building
           a list of directory not allowed to access. */
      /* - Autodetecta la version de http y obtiene la lista
           de exclusion ('robots.txt') */

      T_BOOL   L_HTTP_SERVER_SetDefault     ( INOUT   t_httpCfg    *webCfg ) ;
      /* - Setup componets to default values. */
      /* - Asigna los valores por defecto. */

      T_BOOL   L_HTTP_SERVER_Empty          ( INOUT   t_httpCfg    *webCfg ) ;
      /* - Free componets and set default values. */
      /* - Libera los recursos y pone valores por defecto. */

      T_BOOL   L_HTTP_SERVER_IsDisallow     ( IN      t_httpCfg   *webCfg,
                                              IN      t_url       *url ) ;
      /* - Return TRUE if 'url' is forbidden. */
      /* - Retorna TRUE si el 'url' esta prohibido. */

      T_BOOL  L_HTTP_SERVER_GetConnection   ( IN     t_httpCfg      *webCfg,
                                              IN     t_url          *url,
                                              INOUT  t_downLoadWS   *dlws ) ;
      /* - Reconnect to host 'url->machine', 
           port 'url->port' */
      /* - Conecta de nuevo a la maquina 'url->machine', 
           puerto 'url->port' */


   /* ... Inline / Expansiones .......................................... */

      #define L_HTTP_SERVER_IsDisallow(wcfg,url)                         \
              (                                                          \
                (                                                        \
                  X_STRING_Equal(((wcfg)->host)->machine,(url)->machine) \
                  ==                                                     \
                  FALSE                                                  \
                ) ?                                                      \
                FALSE                                                    \
                :                                                        \
                L_DISALLOWLI_IsDisallow(&((wcfg)->disallowList),(url))   \
              )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

