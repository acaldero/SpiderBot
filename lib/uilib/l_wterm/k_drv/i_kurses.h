

 #ifndef I_CURSES_H
 #define I_CURSES_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #if defined(__SUNOS__)
          #include <sys/ttold.h>
      #endif
      #if defined(__LCURSES__)
          #include "curses.h"
      #endif
      #if defined(__LNCURSES__)
          #include "ncurses.h"
      #endif


    /* ... Functions / Funciones ......................................... */

       /* --- Keybd en x_curses --- */
       T_CHAR I_CURSES_getch   ( void ) ;                                   
       T_BOOL I_CURSES_nbgetch ( INOUT T_CHAR *ch ) ;                       


    /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif
