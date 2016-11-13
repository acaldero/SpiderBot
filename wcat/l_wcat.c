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

      #include "wcat/l_wcat.h"


   /* ... Functions / Funciones ......................................... */
  
      T_INT   L_WCAT_Print           ( IN     const T_CHAR   *fto,
                                       IN     va_list         va )
      {
        return vfprintf(stderr,fto,va) ;
      }

      T_INT L_WCAT_main ( T_INT argc, T_CHAR *argv[] )
      {
        T_BOOL          ok ;
        t_wppOptions    spi_opt ;
      
        setbuf(stdin,NULL) ;
        setbuf(stderr,NULL) ;
        X_PRINT_setPrintWrapper(L_WCAT_Print) ;
        L_WCTMSG_presentation(&spi_opt) ;

        ok = L_WPP_CL_ParseCommandLine(&spi_opt,argc,argv,"WebCat") ;
        if (ok == FALSE)
           {
             X_PRINT_printf("\n\n") ;
             return TRUE ;
           }
        if (spi_opt.help_f == ON)
           {
             ok = L_WCTMSG_help(&spi_opt) ;
           }
        if (spi_opt.help_f == OFF)
           {
             ok = L_WPP_OPT_activeOptToFile(stderr,&spi_opt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_WPP_OPT_CheckValid(stderr,&spi_opt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_WCTDL_DownLoad(&spi_opt) ;
           }
        X_PRINT_printf("\n") ;
        return ok ;
      }


   /* ................................................................... */

