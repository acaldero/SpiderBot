

 #ifndef L_WPP_CL_H
 #define L_WPP_CL_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_cl/l_cl.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_file/l_file.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_WPP_CL_ParseCommandLine  ( OUT   t_wppOptions   *wcOpt,
                                            IN    int             argc,
                                            IN    char           *argv[],
                                            IN    T_CHAR         *wpp_name ) ;
      /* - it will setup 'wcOpt' from command line. */
      /* - */


   /* ................................................................... */


#endif

