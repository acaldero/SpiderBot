

 #ifndef L_URLSTREAM_H
 #define L_URLSTREAM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlstr.h"


   /* ... Functions / Funciones ......................................... */

     T_BOOL    L_URLSTREAM_UrlToFile   ( IN     t_url    *url,
                                         OUT    FILE     *fout ) ;
     /* - */
     /* - Escribe la representacion en "string" de
          'url' en el fichero 'fout'. */

     T_BOOL    L_URLSTREAM_FileToUrl   ( IN     t_url    *url,
                                         OUT    FILE     *fin ) ;
     /* - */
     /* - */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

