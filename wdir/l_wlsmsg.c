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

      #include "wdir/l_wlsmsg.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_WLSMSG_help        ( OUT   t_wppOptions   *wcOpt )
      {
        L_WPP_MSG_common_command_line(c_WDIR_VER,"wdir",1,5) ;
        X_PRINT_printf("    Press ENTER to continue...\n") ;
        fgetc(stdin) ;

        L_WPP_MSG_options(c_WDIR_VER,2,5) ;
        X_PRINT_printf("    Press ENTER to continue...\n") ;
        fgetc(stdin) ;

        L_WPP_MSG_flags(c_WDIR_VER,3,5) ;
        X_PRINT_printf("    Press ENTER to continue...\n") ;
        fgetc(stdin) ;

        L_WPP_MSG_advanced(c_WDIR_VER,4,5) ;
        X_PRINT_printf("    Press ENTER to continue...\n") ;
        fgetc(stdin) ;

        L_WPP_MSG_thanks_1(c_WDIR_VER,5,5) ;
        return TRUE ;
      }


   /* ................................................................... */

