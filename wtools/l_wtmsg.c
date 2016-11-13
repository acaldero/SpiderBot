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



   /* ... Include / Inclusion ........................................... */

      #include "wtools/l_wtmsg.h"


   /* ... Functions / Funciones ......................................... */
  
      /* ... wtools ....................................................... */
      T_INT    L_WTMSG_N_wtools = 2 ;

      T_CHAR  *L_WTMSG_wtools_1_N = 
"\n" 
"                                                                %s\n" 
"                                                                (1/%i)\n" 
"\n" 
"\n" 
"    WebTools\n"
"   ----------\n"
"\n"
"    Copyright (C) 1997/1999 Alejandro Calderon Mateos\n"
"    WebCopy comes with ABSOLUTELY NO WARRANTY;\n"
"    This is free software, and you are welcome to redistribute\n"
"    it under certain conditions.\n"
"    (See GNU Library General Public License).\n"
"\n" 
"\n" 
"        WebTools can not be used directly.\n"
"        Please, make symbolic links like :\n"
"\n" 
"        #ln -s   wtools.exe   <web command>.exe\n" 
"\n" 
"        where <web command> are wcopy, wdir, wcat and mklocal.\n" 
"\n" 
"    Press ENTER to continue...\n"  ;

      T_CHAR  *L_WTMSG_wtools_2_N = 
"\n"
"\n"
"                                                                %s\n"
"                                                                (2/%i)\n"
"\n"
"\n"
"               x                                             \n"
"             x           x     x   x  x   x  xxx             \n"
"         x x            x  x   xx  x  x  x  x                \n"
"       x    x     x  x  x  x   x x x  x x    x x             \n" 
"            x     x  x  xxxxx  x  xx  xx        x       x x  \n"
"             x    xxxx  x   x  x   x  x x    x   x         x \n"
"             x    x  x  x   x  x   x  x   x   xxx         x  \n"
"             x    x  x  x                                x   \n"
"             x    x                                     x    \n"
"             x                      x x x x x x x x x x      \n"
"                                                             \n"
"                                                             \n"
"    Thanks to all people that wtools me in many things...\n"
"    ... people of D.A.T.S.I department, at Facultad de Informatica (U.P.M)\n"
"    ... Juan Jose Amor, Vicente Luque, Guillermo Bautista, Antonio Diaz,...\n"
"    ... and my parents too, too much ;->.\n"
"\n" ;

  
      T_BOOL   L_WTMSG_wtools   ( void )
      {
        X_PRINT_printf(L_WTMSG_wtools_1_N,
                       c_WTOOLS_VER,
                       L_WTMSG_N_wtools) ;
        fgetc(stdin) ;
        X_PRINT_printf(L_WTMSG_wtools_2_N,
                       c_WTOOLS_VER,
                       L_WTMSG_N_wtools) ;
        return TRUE ;
      }


   /* ................................................................... */

