

 #ifndef I_ESCMAP_H
 #define I_ESCMAP_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_wterm/v_term.h"


   /* ... Const / Constantes ............................................ */

       #define c_ENTER_ESC   '\n'
       #define c_DEL_ESC     '\177'
       #define c_BEGIN_ESC   '1'
       #define c_END_ESC     '4'
       #define c_UP_ESC      'A'
       #define c_DOWN_ESC    'B'
       #define c_RIGHT_ESC   'C'
       #define c_LEFT_ESC    'D'
       #define c_REPAG_ESC   '5'
       #define c_AVPAG_ESC   '6'
       #define c_F2_ESC      'B'
       #define c_F3_ESC      'C'


   /* ... Functions / Funciones ......................................... */

      T_INT I_ESCMAP_getkey ( void ) ;
      /* - Read from keyboad a 'key', but
           it can envolve reads some bytes. */
      /* - Le del teclado una 'tecla', no el byte
           que genera el teclado. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

