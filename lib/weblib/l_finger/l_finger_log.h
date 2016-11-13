

 #ifndef L_FINGER_LOG_H
 #define L_FINGER_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_finger/l_finger_response.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_FINGER_LOG_PrintUrl         ( INOUT  FILE   *flog,
                                               IN     t_url  *url ) ;
      /* - Write at log file current url request. */
      /* - Escribe en el fichero de estado 
           el url 'url'. */

      T_BOOL   L_FINGER_LOG_PrintResponse    ( INOUT  FILE            *flog,
                                               IN     t_finger_response  *fingerr ) ;
      /* - Write at log file codigo and 
           response (msg). */
      /* - Escribe en el fichero de estado el 
           codigo y la respuesta (msg). */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

