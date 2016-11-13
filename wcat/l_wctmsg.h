

 #ifndef L_WCTMSG_H
 #define L_WCTMSG_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wpplib/l_cl_wpp/l_wpp_msg.h"
      #include "wcat/c_wcat.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_WCTMSG_presentation  ( OUT   t_wppOptions    *wcOpt ) ;
      /* - Print at stdout our presentation. */
      /* - */

      T_BOOL   L_WCTMSG_help          ( OUT   t_wppOptions    *wcOpt ) ;
      /* - Print at stdout how to use options. */
      /* - */


   /* ... Inline / Macros ............................................... */

      #define L_WCTMSG_presentation(wcOpt) \
              L_WPP_MSG_presentation("WebCat",c_WCAT_VER)


   /* ................................................................... */


#endif

