

 #ifndef L_INFO_H
 #define L_INFO_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "uilib/l_wterm/l_win.h"


   /* ... Functions / Funciones ......................................... */

      T_INT  L_INFO_wprintf  ( IN     T_CHAR   *format,
                               IN     va_list   arg ) ;
      /* - */
      /* - */

      void   L_INFO_MakingOf ( IN     T_BOOL inWterm, 
                               IN     T_CHAR *version ) ;
      /* - Print where program was make, and version. */
      /* - Imprime donde el programa se hizo, y la version. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

