

 #ifndef L_STTBOX_H
 #define L_STTBOX_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_wterm/l_win.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_browse/l_htxt.h"


   /* ... Functions / Funciones .................................. */

      t_win      L_STTBOX_Open           ( IN    T_INT    x1,
                                           IN    T_INT    y1,
                                           IN    T_INT    x2,
                                           IN    T_INT    y2 ) ;
      /* - */
      /* - */

      T_INT      L_STTBOX_KeyProcessing  ( IN    t_win    w,
                                           IN    T_INT    tecla ) ;
      /* - */
      /* - */

      T_BOOL     L_STTBOX_Show           ( IN    t_win    wwin ) ;
      /* - */
      /* - */



   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

