

 #ifndef L_POP3_SERVER_H
 #define L_POP3_SERVER_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_cdt/l_strli.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_verbose/l_verbose_log.h"
      #include "weblib/l_pop3/l_pop3_response.h"
      #include "weblib/l_pop3/l_pop3_command.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        t_url       *host ;
        t_sock       sd ;
        T_BOOL       connected ;
      } t_pop3Cfg ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_POP3_SERVER_SetDefault   ( INOUT   t_pop3Cfg   *pop3Cfg ) ;
      /* - Setup componets to default values (NULL). */
      /* - */

      T_BOOL   L_POP3_SERVER_Setup        ( OUT     t_pop3Cfg      *pop3Cfg,
                                            IN      t_url          *urlHost,
                                            INOUT   t_downLoadWS   *dlws ) ;
      /* - Autodetect Ftp, and connect with host. */
      /* - */

      T_BOOL   L_POP3_SERVER_Empty        ( INOUT   t_pop3Cfg    *pop3Cfg ) ;
      /* - Free componets and disconnect. */
      /* - */

      T_BOOL  L_POP3_SERVER_GetConnection ( IN      t_pop3Cfg     *pop3Cfg,
                                            IN      t_url         *url,
                                            INOUT   t_downLoadWS  *dlws ) ;
      /* - Connect again. */
      /* - */


   /* ... Inline / Expansiones .......................................... */

      #define L_POP3_SERVER_SetDefault(wcfg)  \
              X_ALLOC_MemSet((wcfg),0,sizeof(t_pop3Cfg))


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

