

 #ifndef L_DIALOG_H
 #define L_DIALOG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "uilib/l_wterm/l_win.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_browse/l_htxt.h"


   /* ... Functions / Funciones .................................. */

       T_CHAR   *L_DIALOG_SelectString    ( IN t_DiNode *g ) ;
       /* - Present as a dialog box, a hipertext node,
            and options are see as butons. */
       /* - Presenta como cuadro de dialogo, un nodo de hipertexto,
            siendo las opciones los botones. */
      

   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

