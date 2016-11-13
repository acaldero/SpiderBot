

 #ifndef V_KEYMAP_H
 #define V_KEYMAP_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */
 
      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_wterm/v_term.h"


   /* ... Const / Constantes ............................................ */
    
      /* msgs *
       * ---- */
       #define VKEYMAP_BAD_KEY      "NO valid method for get a key."
   
      /* keyboard mapper *
       * --------------- */
       #define c_PC          200
       #define c_ESCAPE      210
       #define c_CURSES      220
   
      /* keys *
       * ---- */
       #define c_NINGUNA     256
       #define c_ENTER       258
       #define c_UP          259
       #define c_DOWN        260
       #define c_RIGHT       261
       #define c_LEFT        262
       #define c_AVPAG       263
       #define c_REPAG       264
       #define c_F2          265
       #define c_F3          266
       #define c_BEGIN       267
       #define c_END         268
       #define c_TAB         '\t'
       #define c_DEL         '\10'
       #define c_BLACK       ' '
       #define c_ESC 	     '\33'
   
       /* TABs * 
        * ---- */
       #define c_TABHITS "        "
   

   /* ... Functions / Funciones ......................................... */

      T_INT V_KEYMAP_Configur ( T_INT newkm ) ;
      /* - Change keyboard manager */
      /* - Cambia de gestor de teclado */

      T_INT V_KEYMAP_getkey ( void ) ;
      /* - Return key code, not bytes readed */
      /* - Retorna el codigo de una tecla 
           (no los bytes que genera) */

   
   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

