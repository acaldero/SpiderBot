

 #ifndef I_CURMAP_H
 #define I_CURMAP_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_wterm/v_term.h"
      #if defined(__SUNOS__)
          #include <sys/ttold.h>
      #endif
      #if defined(__LCURSES__)
          #include "curses.h"
      #endif
      #if defined(__LNCURSES__)
          #include "ncurses.h"
      #endif


   /* ... Functions / Funciones ......................................... */

      T_INT I_CURMAP_getkey ( void ) ;
      /* - */
      /* - Le del teclado una 'tecla', no el byte
           que genera el teclado. */


/* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

