

 #ifndef L_NNTP_SERVER_H
 #define L_NNTP_SERVER_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_cdt/l_strli.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_verbose/l_verbose_log.h"
      #include "weblib/l_nntp/l_nntp_response.h"
      #include "weblib/l_nntp/l_nntp_command.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        t_url       *host ;
        t_sock       sd ;
        T_BOOL       connected ;
      } t_nntpCfg ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_NNTP_SERVER_SetDefault   ( INOUT   t_nntpCfg    *nntpCfg ) ;
      /* - Setup componets to default values (NULL). */
      /* - */

      T_BOOL   L_NNTP_SERVER_Setup        ( OUT     t_nntpCfg      *nntpCfg,
                                            IN      t_url          *urlHost,
                                            INOUT   t_downLoadWS   *dlws ) ;
      /* - Autodetect Ftp, and connect with host. */
      /* - */

      T_BOOL   L_NNTP_SERVER_Empty        ( INOUT   t_nntpCfg    *nntpCfg ) ;
      /* - Free componets and disconnect. */
      /* - */

      T_BOOL  L_NNTP_SERVER_GetConnection ( IN      t_nntpCfg      *nntpCfg,
                                            IN      t_url          *url,
                                            INOUT   t_downLoadWS   *dlws ) ;
      /* - Connect again. */
      /* - */


   /* ... Inline / Expansiones .......................................... */

      #define L_NNTP_SERVER_SetDefault(wcfg)  \
              X_ALLOC_MemSet((wcfg),0,sizeof(t_nntpCfg))


   /* ................................................................... */


#endif

