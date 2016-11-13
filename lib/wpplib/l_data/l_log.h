

 #ifndef L_LOG_H
 #define L_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_time/v_time.h"
      #include "corelib/l_debug/l_debug.h"
      #include "weblib/l_url/l_url.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_LOG_Setup         ( INOUT  FILE   *flog,
                                     IN     T_CHAR *progname ) ;
      /* - Setup log file contents. */
      /* - Inicializa el contenido del fichero de estado. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

