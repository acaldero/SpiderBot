

 #ifndef L_NNTP_LOG_H
 #define L_NNTP_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_nntp/l_nntp_response.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_NNTP_LOG_PrintUrl       ( INOUT  FILE   *flog,
                                           IN     t_url  *url ) ;
      /* - Write at log file current url request. */
      /* - Escribe en el fichero de estado 
           el url 'url'. */

      T_BOOL   L_NNTP_LOG_PrintResponse  ( INOUT  FILE             *flog,
                                           IN     t_nntp_response  *nntpr ) ;
      /* - Write at log file response from server. */
      /* - Escribe en el fichero la respuesta del servidor. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

