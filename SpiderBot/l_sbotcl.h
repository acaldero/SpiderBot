

 #ifndef L_SBOTCL_H
 #define L_SBOTCL_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_cl/l_cl.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_file/x_print.h"
      #include "SpiderBot/l_sbotopt.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_SBOTCL_ParseCommandLine  ( OUT   t_wppOptions   *wOpt,
                                            IN    int             argc,
                                            IN    char           *argv[] ) ;
      /* - it will setup 'wcOpt' from command line. */
      /* - */


   /* ................................................................... */


#endif

