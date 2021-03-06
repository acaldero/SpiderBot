

 #ifndef L_FTP_LOG_H
 #define L_FTP_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_ftp/l_ftp_response.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_FTP_LOG_PrintUrl         ( INOUT  FILE   *flog,
                                            IN     t_url  *url ) ;
      /* - Write at log file current url request. */
      /* - Escribe en el fichero de estado 
           el url 'url'. */

      T_BOOL   L_FTP_LOG_PrintResponse    ( INOUT  FILE            *flog,
                                            IN     t_ftp_response  *ftpr ) ;
      /* - Write at log file codigo and first 
           response line (msg). */
      /* - Escribe en el fichero de estado el codigo y 
           primera linea de la respuesta (msg). */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

