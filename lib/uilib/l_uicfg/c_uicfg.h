

 #ifndef  C_UICFG_H
 #define  C_UICFG_H


   /* ... XY-DOS .................................................... */

      #if defined(__MSDOS__)
         #define __BCC__
         #define __MVIDEO__     c_BC_INT10
	 #define __MGRPH__      c_BCGRAPH
	 #define __MTECLADO__   c_PCKB
	 #define __KEYMAPPING__ c_PC
      #endif

/*
      #if defined(__MSDOS__)
         #define __TCC__
	 #define __MVIDEO__     c_BC_INT10
 	 #define __MGRPH__      c_BCGRAPH
	 #define __MTECLADO__   c_PCKB
	 #define __KEYMAPPING__ c_PC
      #endif
*/


   /* ... Unix ...................................................... */

      #if defined(HAVE_CURSES_H)

	 #define __MTECLADO__   c_CURSESKB
	 #define __KEYMAPPING__ c_CURSES
	 #define __MVIDEO__     c_xCURSES
	 #define __LCURSES__    "/usr/include/curses.h"

      #elsif defined(HAVE_NCURSES_H)

	 #define __MTECLADO__   c_CURSESKB
	 #define __KEYMAPPING__ c_CURSES
	 #define __MVIDEO__     c_xCURSES
	 #define __LNCURSES__   "/usr/include/ncurses.h"

      #else 

         #if defined(__LINUX__)
   	    #define __MTECLADO__   c_VTKB
   	    #define __KEYMAPPING__ c_ESCAPE
	    #define __MVIDEO__     c_ESC_CMD
         #endif

         #if defined(__SUNOS__)
	    #define __MTECLADO__   c_VTKB
	    #define __KEYMAPPING__ c_ESCAPE
            #define __MVIDEO__     c_ESC_CMD
         #endif

         #if defined(__AIX__)
	    #define __MTECLADO__   c_VTKB
	    #define __KEYMAPPING__ c_ESCAPE
	    #define __MVIDEO__     c_ESC_CMD
         #endif

      #endif

   /* ............................................................... */


 #endif


