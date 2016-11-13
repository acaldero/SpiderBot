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

      #include "wdir/l_wdir.h"


   /* ... Functions / Funciones ......................................... */
  
      T_INT L_WDIR_main ( T_INT argc, T_CHAR *argv[] )
      {
        T_BOOL         ok ;
        t_wppOptions   wls_opt ;
      
        setbuf(stdin,NULL) ;
        L_WLSMSG_presentation(&wls_opt) ;

        ok = L_WPP_CL_ParseCommandLine(&wls_opt,argc,argv,"WebDir") ;
        if (ok == FALSE)
           {
             X_PRINT_printf("\n\n") ;
             return TRUE ;
           }
        if (wls_opt.help_f == ON)
           {
             ok = L_WLSMSG_help(&wls_opt) ;
           }
        if (wls_opt.help_f == OFF)
           {
             ok = L_WPP_OPT_activeOptToFile(stdout,&wls_opt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_WPP_OPT_CheckValid(stdout,&wls_opt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_WLSDL_DownLoad(&wls_opt) ;
           }
        X_PRINT_printf("\n") ;
        return ok ;
      }


   /* ................................................................... */

