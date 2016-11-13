

 #ifndef I_PCMAP_H
 #define I_PCMAP_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_wterm/v_term.h"


   /* ... Const / Constantes ............................................ */

       #define c_ENTER_PC     '\r'
       #define c_BEGIN_PC     71
       #define c_END_PC       79
       #define c_UP_PC        72
       #define c_REPAG_PC     73
       #define c_LEFT_PC      75
       #define c_RIGHT_PC     77
       #define c_DOWN_PC      80
       #define c_AVPAG_PC     81
       #define c_F2_PC        60
       #define c_F3_PC        61


   /* ... Functions / Funciones ......................................... */

      T_INT I_PCMAP_getkey ( void ) ;
      /* - */
      /* - Le del teclado una 'tecla', no el byte
           que genera el teclado. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

