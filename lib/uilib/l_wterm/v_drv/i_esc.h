

 #ifndef I_ESC_H
 #define I_ESC_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"


   /* ... Const / Constantes ............................................ */

      /*
         identificacion de colores :
             [0]  Black,      [1]  Blue,          [2]  Green,
             [3]  Cyan,       [4]  Red,           [5]  Magneta,
             [6]  Brown,      [7]  LightGray,     [8]  DarkGray,
             [9]  LightBlue,  [10] LightGreen,    [11] LightCyan,
             [12] LightRed,   [13] LightMagneta,
             [14] Yellow,     [15] White
      */
      #define c_esc_Text16Color { 0,4,2,6,1,5,3,7,0,4,2,6,1,5,3,7 }

      /* ... menssages ... */
      #define IESC_BAD_DIMENSIONS    "Incoherencia entre coordenadas-taman~o terminal"


    /* ... Glob. var / Var. global ....................................... */

       extern T_CHAR *gObuff ;
       extern long gObuffsize ;


    /* ... Functions / Funciones ......................................... */

       T_BOOL I_ESC_Begin   ( void ) ;                                       
       void   I_ESC_End     ( void ) ;                                       
       void   I_ESC_set_modo_video ( T_INT modo_video ) ;
       T_BOOL I_ESC_cdump   ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,   
                              T_INT width, T_INT tall,                      
                              T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 ) ;    
       void   I_ESC_cgotoxy ( T_INT x, T_INT y ) ;                           
       void   I_ESC_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) ;
       void   I_ESC_cursor_off ( void ) ;
       void   I_ESC_cursor_on  ( void ) ;
       void   I_ESC_set_cursor ( T_INT lini, T_INT lfin ) ;
       void   I_ESC_clrscr  ( void ) ;                                       
       void   I_ESC_AutoDetect ( INOUT T_INT *currmode,
                                 INOUT T_INT *cfilas,
                                 INOUT T_INT *ccolumnas,
                                 INOUT T_INT *rvertical,
                                 INOUT T_INT *rhorizontal,
                                 INOUT T_INT *charheight,
                                 INOUT T_INT *charwidth,
                                 INOUT T_INT *ncolores ) ;


  /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

