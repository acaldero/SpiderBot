

 #ifndef L_FILE_DOWNLOAD_H
 #define L_FILE_DOWNLOAD_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_verbose/l_verbose_download.h"
      #include "weblib/l_file/l_file_log.h"
      #include "weblib/l_file/l_file_upload.h"
      #include "weblib/l_file/l_file_download/l_file_dir.h"
      #include "weblib/l_file/l_file_download/l_file_file.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FILE_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fileCfg      *fileCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url ) ;
      /* - Use 'fileCfg' file system and download 'url'
           that is present in it name space */
      /* - Transfiere el fichero referenciado por 'url'
           a '*fpage', desde el sistema de fichero
           'fileCfg'. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

