     

 #ifndef L_WCON_H
 #define L_WCON_H
     
 #ifdef  __cplusplus
    extern "C" {
 #endif

     
   /* ... Include / Inclusion ........................................... */
     
      #include "corelib/l_basic/c_basic.h"   
      #include "uilib/l_browse/l_brws1.h"
      #include "corelib/l_adt/l_dnodo.h" 
     
     
   /* ... Const / Constantes ............................................ */
    
      #define c_WCON_MSGSX1              1
      #define c_WCON_MSGSY1              1
      #define c_WCON_MSGSX2              (V_TERM_cmaxX())
      #define c_WCON_MSGSY2              (V_TERM_cmaxY())
      #define c_WCON_VERX1               1
      #define c_WCON_VERY1               (V_TERM_cmaxY() / 2)+1
      #define c_WCON_VERX2               (V_TERM_cmaxX())
      #define c_WCON_VERY2               (V_TERM_cmaxY())

      #define c_WCON_ERRTITLE           " Report Console "
      #define c_WCON_VERTITLE           " Version Console "


   /* ... Functions / Funciones ......................................... */
                      
      void L_WCON_On ( void ) ;
      /* - */
      /* - */

      void L_WCON_Off  ( void ) ;
      /* - */
      /* - */

      void L_WCON_Hidden ( void ) ;
      /* - */
      /* - */

      void L_WCON_UnHidden ( void ) ;
      /* - */
      /* - */


   /* ................................................................... */
   

 #ifdef  __cplusplus
    }
 #endif

#endif


