

 #ifndef L_FILE_SERVER_H
 #define L_FILE_SERVER_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_verbose/l_verbose_log.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        FILE        *sd ;
        T_BOOL       connected ;
      } t_fileCfg ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_FILE_SERVER_SetDefault    ( INOUT   t_fileCfg   *fileCfg ) ;
      /* - Setup componets to default values (NULL). */
      /* - */

      T_BOOL   L_FILE_SERVER_Setup         ( OUT     t_fileCfg      *fileCfg,
                                             IN      t_url          *urlHost,
                                             INOUT   t_downLoadWS   *dlws ) ;
      /* - Autodetect filesystem, and configure it. */
      /* - */

      T_BOOL   L_FILE_SERVER_Empty          ( INOUT   t_fileCfg    *fileCfg ) ;
      /* - Free componets and disconnect. */
      /* - */


   /* ... Inline / Expansiones .......................................... */

      #define L_FILE_SERVER_SetDefault(wcfg)  \
              X_ALLOC_MemSet((wcfg),0,sizeof(t_fileCfg))


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

