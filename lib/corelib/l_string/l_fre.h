

 #ifndef L_FRE_H
 #define L_FRE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fchset.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FRE_RWTillRE        ( IN     FILE     *fin,
                                     OUT    FILE     *fout,
                                     IN     T_CHAR  **toklist,
                                     INOUT  T_INT    *tokfound,
                                     IN     T_CHAR   *delimitadores,
                                     IN     T_BOOL    casesense ) ;
      /* - */
      /* - */

      T_BOOL L_FRE_ReadTillRE       ( IN     FILE     *f,
                                      IN     T_CHAR  **toklist,
                                      INOUT  T_CHAR  **buff,
                                      INOUT  T_U_INT  *buffsize,
                                      INOUT  T_INT    *tokfound,
                                      IN     T_CHAR   *delimitadores,
                                      IN     T_BOOL    casesense ) ;
      /* - */
      /* - */

      T_BOOL L_FRE_SkipTillRE       ( IN     FILE     *fin,
                                      IN     T_CHAR  **toklist,
                                      INOUT  T_INT    *tokfound,
                                      IN     T_CHAR   *delimitadores,
                                      IN     T_BOOL    casesense ) ;
      /* - */
      /* - */


   /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

