

 #ifndef L_LINE_H
 #define L_LINE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_string/x_string.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_LINE_enter           ( IN     T_CHAR         *line ) ;
      /* - */
      /* - */

      T_BOOL  L_LINE_dot_enter       ( IN     T_CHAR         *line ) ;
      /* - */
      /* - */

      T_CHAR   *L_LINE_skipRoot      ( IN     T_CHAR         *line ) ;
      /* - */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

