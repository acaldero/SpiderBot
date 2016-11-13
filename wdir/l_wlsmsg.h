

 #ifndef L_WLSMSG_H
 #define L_WLSMSG_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wpplib/l_cl_wpp/l_wpp_msg.h"
      #include "wdir/c_wdir.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_WLSMSG_presentation  ( OUT   t_wppOptions    *wlsOpt ) ;
      /* - Print at stdout out presentation. */
      /* - */

      T_BOOL   L_WLSMSG_help          ( OUT   t_wppOptions    *wlsOpt ) ;
      /* - Print at stdout how to use options. */
      /* - */


   /* ... Inline / Macros ............................................... */

      #define L_WLSMSG_presentation(wlsOpt) \
              L_WPP_MSG_presentation("WebDir",c_WDIR_VER)


   /* ................................................................... */


#endif

