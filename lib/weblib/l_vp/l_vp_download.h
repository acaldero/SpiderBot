

 #ifndef L_VP_DOWNLOAD_H
 #define L_VP_DOWNLOAD_H

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
      #include "weblib/l_ftp/l_ftp_download.h"
      #include "weblib/l_http/l_http_download.h"
      #include "weblib/l_file/l_file_download.h"
      #include "weblib/l_nntp/l_nntp_download.h"
      #include "weblib/l_pop3/l_pop3_download.h"
      #include "weblib/l_vp/l_vp_server.h"


   /* ... Const / Constantes ............................................ */

      #define VP_NONE       0
      #define VP_FILE       1
      #define VP_HTTP       2
      #define VP_FTP        3
      #define VP_POP3       4
      #define VP_NNTP       5
      #define VP_FINGER     6


   /* ... Functions / Funciones ......................................... */

      /*  main functions  *
       * ---------------- */
      T_BOOL  L_VP_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                          INOUT  t_siteCfg      *siteCfg,
                                          INOUT  t_url          *purl,
                                          INOUT  FILE          **fpage,
                                          OUT    T_BOOL         *skip ) ;
      /* - */
      /* - */


      T_BOOL  L_VP_DOWNLOAD_CopyUrlToUrl ( INOUT  t_downLoadWS   *dlws,
                                           INOUT  t_siteCfg      *siteCfg,
                                           INOUT  t_url          *urlOrig,
                                           INOUT  t_url          *urlDest,
                                           OUT    T_BOOL         *skip ) ;
      /* - */
      /* - */


      /*  misc functions  *
       * ---------------- */
      T_BOOL  L_VP_SelectProtocol      ( INOUT  t_downLoadWS   *dlws,
                                         INOUT  t_siteCfg      *siteCfg,
                                         IN     t_url          *url,
                                         INOUT  int            *selp ) ;
      /* - */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

