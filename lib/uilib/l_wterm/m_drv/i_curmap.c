/* ....................................................................... */



   /* ... Includes / Inclusiones ......................................... */

      #include "uilib/l_wterm/m_drv/i_curmap.h"


   /* ... Global Vars / Vars. Globales .................................. */

      extern T_BOOL I_CURSES_isInit ;


   /* ... Functions / Funciones ......................................... */
  
      T_INT I_CURMAP_getkey ( void )
      {
#if (defined(__LCURSES__) || defined(__LNCURSES__))
        T_INT ch ;

        keypad(stdscr,TRUE) ;
        ch = wgetch(stdscr) ;
        switch(ch)
        {
          case KEY_UP           : return c_UP ;
          case KEY_DOWN         : return c_DOWN ;
          case KEY_RIGHT        : return c_RIGHT ;
          case KEY_LEFT         : return c_LEFT ;
          case KEY_NPAGE        : return c_AVPAG ;
          case KEY_PPAGE        : return c_REPAG ;
          case KEY_F(2)         : return c_F2 ;
          case KEY_F(3)         : return c_F3 ;
          case KEY_HOME         : return c_BEGIN ;
          case KEY_END          : return c_END ;
          case KEY_ENTER        : return c_ENTER ;
          case '\n'             : return c_ENTER ; /*deb*/
        }
        return (T_INT) ch ;
#else
        return 0 ;
#endif
      }


 /* ..................................................................... */

