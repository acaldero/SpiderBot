

 #ifndef I_INT86_H
 #define I_INT86_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Const / Constantes ............................................ */

      /* 
         el orden de colores es :
             [0]  Black,      [1]  Blue,          [2]  Green,
             [3]  Cyan,       [4]  Red,           [5]  Magneta,
             [6]  Brown,      [7]  LightGray,     [8]  DarkGray,
             [9]  LightBlue,  [10] LightGreen,    [11] LightCyan,
             [12] LightRed,   [13] LightMagneta,
             [14] Yellow,     [15] White
      */
      #define c_intx_Text16Color { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 }
        /* usados en msdos, si no se usa caracteres de escape
           8-15 -> NO permitidos como Background, parpadean !
           al ser el que se toma como referencia, no hace falta
           traducirlo! */


    /* ... Functions / Funciones ......................................... */

       void   I_INT86_set_modo_video ( T_INT modo_video ) ;                   
       void   I_INT86_cgotoxy   ( T_INT x, T_INT y ) ;                          
       void   I_INT86_cwherexy  ( INOUT T_INT *x, INOUT T_INT *y ) ;            
       void   I_INT86_clrscr    ( T_INT x, T_INT y ) ;                          
       T_BOOL I_INT86_cdump     ( T_CHAR *scr, T_CHAR *attr,  
                                  T_INT ncolores, 
                                  T_INT width, T_INT tall, 
                                  T_INT rx1, T_INT ry1, 
                                  T_INT rx2, T_INT ry2 ) ;      
       void   I_INT86_cursor_off ( void ) ;                                 
       void   I_INT86_cursor_on  ( void ) ;                                 
       void   I_INT86_set_cursor ( T_INT lini, T_INT lfin ) ;                   
       void   I_INT86_AutoDetect ( INOUT T_INT *currmode,  
                                   INOUT T_INT *cfilas, 
     			           INOUT T_INT *ccolumnas, 
                                   INOUT T_INT *ncolores ) ;
       T_BOOL I_INT86_Begin      ( void ) ;                                 
       void   I_INT86_End        ( void ) ;                                 


/* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

