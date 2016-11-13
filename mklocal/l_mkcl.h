

 #ifndef L_MKCL_H
 #define L_MKCL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_cl/l_cl.h"
      #include "corelib/l_file/l_file.h"
      #include "mklocal/l_mkopt.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_MKCL_ParseCommandLine   ( OUT   t_mkOptions    *mkOpt,
                                           IN    int             argc,
                                           IN    char           *argv[] ) ;
      /* - it will setup 'mkOpt' from command line. */
      /* - */


   /* ................................................................... */


#endif

