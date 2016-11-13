

 #ifndef L_MKMSG_H
 #define L_MKMSG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "mklocal/c_mklocal.h"
      #include "mklocal/l_mkopt.h"
      #include "wpplib/l_cl_wpp/l_wpp_msg.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_MKMSG_presentation  ( OUT   t_mkOptions    *mkOpt ) ;
      /* - Print at stdout our presentation. */
      /* - */

      T_BOOL   L_MKMSG_help          ( OUT   t_mkOptions    *mkOpt ) ;
      /* - Print at stdout how to use options. */
      /* - */


   /* ... Inline / Macros ............................................... */

      #define L_MKMSG_presentation(mkOpt) \
              L_WPP_MSG_presentation("mklocal",c_MKLOCAL_VERSION)


   /* ................................................................... */


#endif

