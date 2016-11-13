

 #ifndef L_FILE_LOG_H
 #define L_FILE_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlstr.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_FILE_LOG_PrintUrl      ( INOUT  FILE   *flog,
                                          IN     t_url  *url ) ;
      /* - Write at log file current url request. */
      /* - Escribe en el fichero de estado el url 'url'. */

      T_BOOL   L_FILE_LOG_PrintHeader   ( INOUT  FILE          *flog,
                                          INOUT  struct stat   *stath ) ;
      /* - Write at log file response from server. */
      /* - Escribe en el fichero de estado la respuesta
           del servidor dada en 'httpr'. */

      T_BOOL   L_FILE_LOG_PrintNotFound ( INOUT  FILE          *flog ) ;
      /* - Write at log file that file is not present. */
      /* - Escribe en el fichero de estado que no
           existe el fichero. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

