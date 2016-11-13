/* ........................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * ........................................................................ */



   /* ... Includes / Inclusiones ......................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "uilib/l_wterm/c_wterm.h"
      #if defined(__SUNOS__)
          #include <sys/ttold.h>
      #endif
      #if defined(__LCURSES__)
          #include "curses.h"
      #endif
      #if defined(__LNCURSES__)
          #include "ncurses.h"
      #endif


   /* ... Global vars / Vars. globales ................................... */

      T_CHAR  *simple_frame1 ( void )
      {
#if ( (0) && ((defined(__LCURSES__) || defined(__LNCURSES__))) )
        static T_CHAR coolframe1[9] ;

        coolframe1[0] = ACS_ULCORNER ;
        coolframe1[1] = ACS_HLINE ;
        coolframe1[2] = ACS_URCORNER ;
        coolframe1[3] = ACS_VLINE ;
        coolframe1[4] = ACS_VLINE ;
        coolframe1[5] = ACS_LLCORNER ;
        coolframe1[6] = ACS_HLINE ;
        coolframe1[7] = ACS_LRCORNER ;
        coolframe1[8] = '\0'      ;
        return coolframe1 ;
#else
        return "|^.><.v|" ;
#endif
      }

      T_CHAR  *simple_frame2 ( void )
      {
        return "|\"||||_|" ;
      }


   /* .................................................................. */
