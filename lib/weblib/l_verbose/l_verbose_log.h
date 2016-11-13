

 #ifndef L_VERBOSE_LOG_H
 #define L_VERBOSE_LOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"


   /* ... Functions / Funciones ......................................... */

      void   L_VERBOSE_LOG_applyTo     ( IN     t_downLoadWS     *dlws,
                                         IN     T_CHAR           *msg ) ;
      /* - */
      /* - */

      void   L_VERBOSE_LOG_newMsg      ( IN     t_downLoadWS     *dlws,
                                         IN     T_CHAR           *msgFto,
                                         IN     ...                       ) ;
      /* - */
      /* - */

      void   L_VERBOSE_LOG_appendMsg   ( IN     t_downLoadWS     *dlws,
                                         IN     T_CHAR           *msgFto,
                                         IN     ...                       ) ;
      /* - */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

