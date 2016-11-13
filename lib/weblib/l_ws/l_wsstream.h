

 #ifndef L_WSSTREAM_H
 #define L_WSSTREAM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_wdt/l_urllistream.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_WSSTREAM_WSToFile      ( IN     t_downLoadWS  *dlws,
                                           OUT    FILE          *fout ) ;
      /* - Save a workspace in a file. */
      /* - */

      T_BOOL    L_WSSTREAM_FileToWS      ( OUT     t_downLoadWS  *dlws,
                                           INOUT   FILE          *fin ) ;
      /* - Read a workspace from file. */
      /* - */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

