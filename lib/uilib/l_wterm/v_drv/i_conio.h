

 #ifndef I_CONIO_H
 #define I_CONIO_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL I_CONIO_Begin      ( void ) ;
      void   I_CONIO_End        ( void ) ;
      void   I_CONIO_set_modo_video ( T_INT modo_video ) ;
      void   I_CONIO_cgotoxy    ( T_INT x, T_INT y ) ;                     
      void   I_CONIO_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) ;       
      void   I_CONIO_clrscr     ( void ) ;                                 
      void   I_CONIO_cursor_off ( void ) ;                                 
      void   I_CONIO_cursor_on  ( void ) ;                                 
      void   I_CONIO_set_cursor ( T_INT lini, T_INT lfin ) ;
      void   I_CONIO_AutoDetect ( INOUT T_INT *currmode,                   
                                  INOUT T_INT *cfilas,                     
      	  		          INOUT T_INT *ccolumnas,                  
 			       	  INOUT T_INT *ncolores ) ;                
      T_BOOL I_CONIO_cdump      ( T_CHAR *scr, T_CHAR *attr,
                                  T_INT ncolores,
                                  T_INT width, T_INT tall,
                                  T_INT rx1, T_INT ry1,
                                  T_INT rx2, T_INT ry2 ) ;


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

