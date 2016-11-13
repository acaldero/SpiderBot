

 #ifndef L_FILE_UPLOAD_H
 #define L_FILE_UPLOAD_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_verbose/l_verbose_download.h"
      #include "weblib/l_file/l_file_command.h"
      #include "weblib/l_file/l_file_log.h"


   /* ... Functions / Funciones ......................................... */

      FILE   *L_FILE_UPLOAD_OpenUrlToWrite   ( INOUT  t_downLoadWS   *dlws,
                                               IN     t_url          *url ) ;
      /* - Open a local file where we can store a 
           mirror of url's contents. File name will
           be the name return by L_URLFILE_MirrorUrlName. */
      /* - Abre un fichero en el cual almacenar el 
           contenido del url 'url'. El nombre del fichero
           sera el nombre que L_URLFILE_MirrorUrlName retorne. */

      FILE   *L_FILE_UPLOAD_OpenUrlToWrite_2 ( INOUT  t_downLoadWS   *dlws,
                                               IN     T_CHAR         *uname ) ;
      /* - Open a local file named 'uname' where we can store a 
           mirror of url's contents. */
      /* - Abre un fichero llamado 'uname' en el cual almacenar el 
           contenido del url 'url'. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

