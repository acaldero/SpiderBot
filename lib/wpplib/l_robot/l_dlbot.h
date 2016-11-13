

 #ifndef L_DLBOT_H
 #define L_DLBOT_H

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


   /* ... Constants / Constantes ........................................ */

      #define c_MIN_CLONES 2
      #define c_MAX_CLONES 8


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_DLBOT_DownLoadWeb      ( INOUT  t_downLoadWS   *dlws,
                                         IN     t_url          *url ) ;
      /* - Download all url that can be acceded
           from 'url' in any way. */
      /* - Descarga todos los url que pueden ser acedidos
           desde 'url' directa o indirectamente. */

      T_BOOL  L_DLBOT_DownLoadRecover  ( INOUT  t_downLoadWS   *dlws ) ;
      /* - Continue dowloading from a previous download 
           process started, but ended improperly. */
      /* - Continua la descarga de un proceso de 
           descarga que fue terminado impropiamente. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

