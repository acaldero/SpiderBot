

 #ifndef L_FTP_DIR_H
 #define L_FTP_DIR_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_ftp/l_ftp_log.h"
      #include "weblib/l_ftp/l_ftp_server.h"
      #include "weblib/l_ftp/l_ftp_response.h"
      #include "weblib/l_ftp/l_ftp_command.h"
      #include "weblib/l_file/l_file_upload.h"
      #include "weblib/l_verbose/l_verbose_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FTP_DIR_OpenDir         ( INOUT  t_downLoadWS   *dlws,
                                          IN     t_ftpCfg       *ftpCfg,
                                          IN     t_url          *url,
                                          INOUT  int            *fpage ) ;
      /* - */
      /* - */

      T_BOOL  L_FTP_DIR_CloseDir        ( INOUT  t_downLoadWS   *dlws,
                                          IN     t_ftpCfg       *ftpCfg,
                                          INOUT  int            *fpage ) ;
      /* - */
      /* - */

      T_BOOL  L_FTP_DIR_DownLoadDir     ( INOUT  t_downLoadWS   *dlws,
                                          IN     t_ftpCfg       *ftpCfg,
                                          INOUT  FILE          **fpage,
                                          IN     t_url          *url ) ;
      /* - Download ONLY directory entrys. */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

