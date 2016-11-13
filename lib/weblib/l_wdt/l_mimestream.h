

 #ifndef L_MIMESTREAM_H
 #define L_MIMESTREAM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "weblib/l_wdt/l_mime.h"


   /* ... Functions / Funciones ......................................... */
 
      T_BOOL      L_MIME_mimeToFile    ( INOUT  FILE       *fout,
                                         INOUT  t_mime     *mimeh ) ;
      /*   - */
      /*   - */

 
   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif


