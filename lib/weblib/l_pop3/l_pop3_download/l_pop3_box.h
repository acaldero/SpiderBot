

 #ifndef L_POP3_BOX_H
 #define L_POP3_BOX_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/l_line.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_pop3/l_pop3_log.h"
      #include "weblib/l_pop3/l_pop3_server.h"
      #include "weblib/l_pop3/l_pop3_response.h"
      #include "weblib/l_pop3/l_pop3_command.h"
      #include "weblib/l_file/l_file_upload.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_POP3_BOX_OpenBox       ( INOUT  t_downLoadWS    *dlws,
                                         IN     t_pop3Cfg       *pop3Cfg,
                                         IN     t_url           *url,
                                         INOUT  t_pop3_response *pop3r ) ;
      /* - */
      /* - */

      T_BOOL  L_POP3_BOX_CloseBox      ( INOUT  t_downLoadWS    *dlws,
                                         IN     t_pop3Cfg       *pop3Cfg ) ;
      /* - */
      /* - */

      T_BOOL  L_POP3_BOX_DownLoadBox     ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_pop3Cfg      *pop3Cfg,
                                           INOUT  FILE          **fpage,
                                           IN     t_url          *url ) ;
      /* - download ONLY box entrys. */
      /* - */


   /* ... Inline / Macros ............................................... */

      #define  L_POP3_BOX_CloseBox(dlws,pop3Cfg)       \
               /* ---> L_POP3_BOX_CloseBox do nothing ! <--- */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

