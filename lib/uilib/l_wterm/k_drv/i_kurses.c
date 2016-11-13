/* ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "uilib/l_wterm/k_drv/i_kurses.h"


   /* ... Global Vars / Vars. Globales .................................. */

      extern T_BOOL I_CURSES_isInit ;


   /* ... Funtions / Funciones .......................................... */


#if (defined(__LCURSES__) || defined(__LNCURSES__))

    /* ... Keybd en i_curses ... */
    T_CHAR I_CURSES_getch ( void )
    {
      T_CHAR ch ;

      cbreak() ;
      noecho() ;
      do
      {
        ch = getch() ;
      } while (ch == ERR) ;
      echo() ;
      nocbreak() ;
      return ch ;
    }

    T_BOOL I_CURSES_nbgetch ( INOUT T_CHAR *ch )
    {
      cbreak() ;
      noecho() ;
      nodelay(stdscr,TRUE) ;
      (*ch) = getch() ;
      nodelay(stdscr,FALSE) ;
      echo() ;
      nocbreak() ;
      return ((*ch)!=ERR) ;
    }

#endif


#if ( !defined(__LCURSES__) && !defined(__LNCURSES__) )

    /* ... Keybd en i_curses ... */
    T_CHAR I_CURSES_getch ( void )
    {
      return (0) ;
    }

    T_BOOL I_CURSES_nbgetch ( INOUT T_CHAR *ch )
    {
      (*ch) = '\0' ;
      return FALSE ;
    }

#endif


/* ....................................................................... */

