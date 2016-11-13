

 #ifndef I_CURSES_H
 #define I_CURSES_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #if defined(__SUNOS__)
          #include <sys/ttold.h>
      #endif
      #if defined(__LCURSES__)
          #include "curses.h"
      #endif
      #if defined(__LNCURSES__)
          #include "ncurses.h"
      #endif


   /* ... Const / Constantes ............................................ */

      /* el orden de colores es :
             [0]  Black,      [1]  Blue,          [2]  Green,
             [3]  Cyan,       [4]  Red,           [5]  Magneta,
             [6]  Brown,      [7]  LightGray,     [8]  DarkGray,
             [9]  LightBlue,  [10] LightGreen,    [11] LightCyan,
             [12] LightRed,   [13] LightMagneta,
             [14] Yellow,     [15] White           */
      #define c_curses_Text16Color { 0,4,2,6,1,5,3,7,0,4,2,6,1,5,3,7 }

      /* ... mensajes constantes ... */
      #define ICURSES_BAD_DIMENSIONS    "Incoherencia entre coordenadas-taman~o terminal"


    /* ... Glob. var / Var. global ....................................... */

      extern T_CHAR *gObuff ;
      extern long gObuffsize ;


    /* ... Functions / Funciones ......................................... */

     /* --- Text Video en x_curses --- */
       void   I_CURSES_cgotoxy    ( T_INT x, T_INT y ) ;                      
       void   I_CURSES_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) ;        
       void   I_CURSES_clrscr     ( void ) ;                                  
       void   I_CURSES_cursor_off ( void ) ;                                  
       void   I_CURSES_cursor_on  ( void ) ;                                  
       void   I_CURSES_set_cursor ( T_INT lini, T_INT lfin ) ;
       void   I_CURSES_AutoDetect ( INOUT T_INT *currmode,  
                                    INOUT T_INT *cfilas,  
                                    INOUT T_INT *ccolumnas,                   
                                    INOUT T_INT *ncolores ) ;
       T_BOOL I_CURSES_Begin      ( void ) ;                                  
       void   I_CURSES_End        ( void ) ;                                  
       T_BOOL I_CURSES_cdump      ( T_CHAR *scr, T_CHAR *attr, 
                                    T_INT ncolores,      
                                    T_INT width, T_INT tall,
                                    T_INT rx1, T_INT ry1, 
                                    T_INT rx2, T_INT ry2 ) ;    


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif
