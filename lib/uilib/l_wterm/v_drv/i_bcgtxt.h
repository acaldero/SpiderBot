

 #ifndef I_BCGTXT_H
 #define I_BCGTXT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"


   /* ... Const / Constantes ............................................ */

      /* 
         color number is :
             [0]  Black,      [1]  Blue,          [2]  Green,
             [3]  Cyan,       [4]  Red,           [5]  Magneta,
             [6]  Brown,      [7]  LightGray,     [8]  DarkGray,
             [9]  LightBlue,  [10] LightGreen,    [11] LightCyan,
             [12] LightRed,   [13] LightMagneta,
             [14] Yellow,     [15] White
      */

      #define c_bcgtxt_Text16Color { 0,1,2,3,4,5,20,7,56,57,58,59,60,61,62,63 }
      /* in DOS VGA mode */

      /* ... ctes modos graficos ... */
      #define c_MCGA     0x13
      #define c_DTXT     0x03

      /* ... menssages ... */
      #define IBCGTXT_INITMSG           "Espere por favor..."
      #define IBCGTXT_BAD_DIMENSIONS    "Incoherencia entre coordenadas-taman~o terminal"
      #define IBCGTXT_NO_MEMORY         "V_TERM: NOT enough memory."


    /* ... Glob. var / Var. global ....................................... */

       extern T_CHAR *gObuff ;
       extern long gObuffsize ;


    /* ... Functions / Funciones ......................................... */

       T_BOOL I_BCGTXT_Begin      ( INOUT T_INT *currmode ) ;
       void   I_BCGTXT_End        ( void ) ;
       void   I_BCGTXT_set_modo_video ( T_INT modo_video ) ;
       void   I_BCGTXT_cgotoxy    ( IN    T_INT  x, IN    T_INT  y ) ;
       void   I_BCGTXT_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) ;
       T_BOOL I_BCGTXT_cdump      ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                                    T_INT width, T_INT tall, T_INT charw,
                                    T_INT charh, T_INT rx1, T_INT ry1,
                                    T_INT rx2, T_INT ry2 ) ;
       void   I_BCGTXT_cursor_off ( void ) ;                                  
       void   I_BCGTXT_cursor_on  ( void ) ;                                  
       void   I_BCGTXT_set_cursor ( T_INT lini, T_INT lfin ) ;
       void   I_BCGTXT_AutoDetect ( INOUT T_INT *currmode, 
                                    INOUT T_INT *cfilas,   
                                    INOUT T_INT *ccolumnas, 
                                    INOUT T_INT *rvertical,    
                                    INOUT T_INT *rhorizontal, 
                                    INOUT T_INT *charheight, 
                                    INOUT T_INT *charwidth, 
                                    INOUT T_INT *ncolores ) ;
       void   I_BCGTXT_set_modo_video ( T_INT modo_video ) ;                    
       void   I_BCGTXT_clrscr     ( void ) ;                                  


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

