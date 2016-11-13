

 #ifndef L_EDTBOX_H
 #define L_EDTBOX_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "uilib/l_wterm/l_win.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_browse/l_htxt.h"


   /* ... Functions / Funciones .................................. */

      T_CHAR    *L_EDTBOX_WriteString    ( IN    T_INT    x1,
                                           IN    T_INT    y1,
                                           IN    T_INT    x2,
                                           IN    T_INT    y2,
                                           IN    T_CHAR  *title,
                                           IN    T_INT    maxStringLeng ) ;
       /* - Let user write text into a window,
            and return this string (it will be
            less than 'maxStringLeng' chars */
       /* - Permite escribir en una ventana texto, de 
            'maxStringLeng' caracteres como maximo, y retorna 
            dicha tira de caracteres */

       T_CHAR *L_EDTBOX_WritePasswd    ( IN    T_INT    x1,
                                         IN    T_INT    y1,
                                         IN    T_INT    x2,
                                         IN    T_INT    y2,
                                         IN    T_CHAR  *title ) ;
       /* - Same as 'L_EDTBOX_WriteString' but
            no echo. */
       /* - Equivalente a 'L_EDTBOX_WriteString' pero
            sin verse lo que se escribe. */


   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

