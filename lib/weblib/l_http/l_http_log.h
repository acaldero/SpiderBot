

 #ifndef L_HTTP_LOG_H
 #define L_HTTP_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlstr.h"
      #include "weblib/l_http/l_http_response.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_HTTP_LOG_PrintUrl      ( INOUT  FILE   *flog,
                                          IN     t_url  *url ) ;
      /* - Write at log file current url request. */
      /* - Escribe en el fichero de estado el url 'url'. */

      T_BOOL   L_HTTP_LOG_PrintHeader   ( INOUT  FILE              *flog,
                                          INOUT  t_http_response  *httpr ) ;
      /* - Write at log file response from server. */
      /* - Escribe en el fichero de estado la respuesta
           del servidor dada en 'httpr'. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

