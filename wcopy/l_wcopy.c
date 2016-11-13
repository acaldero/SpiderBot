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

      #include "wcopy/l_wcopy.h"


   /* ... Functions / Funciones ......................................... */
  
      T_INT L_WCOPY_main ( T_INT argc, T_CHAR *argv[] )
      {
        T_BOOL           ok ;
        t_wppOptions     wcOpt ;

        setbuf(stdin,NULL) ;
        L_WCPMSG_presentation(&wcOpt) ;

        ok = L_WPP_CL_ParseCommandLine(&wcOpt,argc,argv,"WebCopy") ;
        if (ok == FALSE)
           {
             X_PRINT_printf("\n\n") ;
             return TRUE ;
           }
        if (wcOpt.help_f == ON)
           {
             ok = L_WCPMSG_help(&wcOpt) ;
           }
        if (wcOpt.help_f == OFF)
           {
             ok = L_WPP_OPT_activeOptToFile(stdout,&wcOpt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_WPP_OPT_CheckValid(stdout,&wcOpt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_WCPDL_DownLoad(&wcOpt) ;
           }
        X_PRINT_printf("\n") ;
        return ok ;
      }


   /* ................................................................... */

