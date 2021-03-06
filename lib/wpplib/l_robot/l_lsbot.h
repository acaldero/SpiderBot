

 #ifndef L_LSBOT_H
 #define L_LSBOT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "wpplib/l_data/l_ws_manager.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_LSBOT_DownLoadWeb      ( INOUT  t_downLoadWS   *dlws,
                                         IN     t_url          *url ) ;
      /* - List all url links that can be acceded
           from 'url' in any way. */
      /* - Lista todos los url que pueden ser acedidos
           desde 'url' directa o indirectamente. */

      T_BOOL  L_LSBOT_DownLoadRecover  ( INOUT  t_downLoadWS   *dlws ) ;
      /* - Continue listing from a previous download 
           process started, but ended improperly. */
      /* - Continua listando de un proceso que
           fue cortado. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

