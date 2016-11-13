

 #ifndef L_URLLISTREAM_H
 #define L_URLLISTREAM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/x_string.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlfile.h"
      #include "weblib/l_url/l_urlstream.h"
      #include "weblib/l_url/l_urlstr.h"
      #include "weblib/l_wdt/l_urlli.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL      L_URLLI_UrlLiToFile    ( INOUT t_urlLi      *listr,
                                           INOUT FILE         *fout ) ;
      /*   - */
      /*   - Escribe en fichero una lista de url. */

      T_BOOL      L_URLLI_FileToUrlLi    ( INOUT t_urlLi      *listr,
                                           INOUT FILE         *fin ) ;
      /*   - */
      /*   - Lee de fichero una lista de url. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif


