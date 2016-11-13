

 #ifndef L_VP_SERVER_H
 #define L_VP_SERVER_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlfile.h"
      #include "weblib/l_url/l_urlxml.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_http/l_http_server.h"
      #include "weblib/l_http/l_http_download.h"
      #include "weblib/l_ftp/l_ftp_server.h"
      #include "weblib/l_ftp/l_ftp_download.h"
      #include "weblib/l_file/l_file_download.h"
      #include "weblib/l_nntp/l_nntp_server.h"
      #include "weblib/l_nntp/l_nntp_download.h"
      #include "weblib/l_pop3/l_pop3_server.h"
      #include "weblib/l_pop3/l_pop3_download.h"
      #include "weblib/l_finger/l_finger_server.h"
      #include "weblib/l_finger/l_finger_download.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
          t_httpCfg    webCfg ;
          t_ftpCfg     ftpCfg ;
          t_fileCfg    fileCfg ;
          t_nntpCfg    nntpCfg ;
          t_pop3Cfg    pop3Cfg ;
          t_fingerCfg  fingerCfg ;
      } t_siteCfg ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_VP_SERVER_InitSite      ( OUT    t_siteCfg      *siteCfg ) ;
      /* - */
      /* - */

      T_BOOL  L_VP_SERVER_FinalizeSite  ( OUT    t_siteCfg      *siteCfg ) ;
      /* - */
      /* - */

      T_BOOL  L_VP_SERVER_SetupSite     ( INOUT  t_downLoadWS   *dlws,
                                          INOUT  t_siteCfg      *siteCfg,
                                          IN     t_url          *purl ) ;
      /* - */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

