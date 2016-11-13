

 #ifndef L_VERBOSE_DOWNLOAD_H
 #define L_VERBOSE_DOWNLOAD_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_http/l_http_response.h"


   /* ... Functions / Funciones ......................................... */

      void   L_VERBOSE_DOWNLOAD_currentReaded ( INOUT  t_downLoadWS  *dlws,
                                                IN     T_LONG         readed,
                                                IN     T_LONG         total ) ;
      /* - */
      /* - */

      void   L_VERBOSE_DOWNLOAD_currentChunked ( INOUT  t_downLoadWS *dlws,
                                                 IN     T_LONG        creaded,
                                                 IN     T_LONG        ctotal,
                                                 IN     T_LONG        freaded,
                                                 IN     T_LONG        ftotal ) ;
      /* - */
      /* - */

      void   L_VERBOSE_DOWNLOAD_currentUrl  ( INOUT  t_downLoadWS   *dlws,
                                              IN     T_CHAR         *codigo,
                                              IN     T_LONG          size,
                                              IN     t_url          *url ) ;
      /* - */
      /* - */

      void   L_VERBOSE_DOWNLOAD_currentPage ( INOUT  t_downLoadWS     *dlws,
                                              IN     t_http_response *httpr,
                                              IN     t_url            *url ) ;
      /* - */
      /* - */

      void   L_VERBOSE_DOWNLOAD_TimeOut       ( void ) ;
      /* - */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

