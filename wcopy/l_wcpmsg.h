

 #ifndef L_WCPMSG_H
 #define L_WCPMSG_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "wpplib/l_cl_wpp/l_wpp_msg.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wcopy/c_wcopy.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_WCPMSG_presentation  ( OUT   t_wppOptions    *wOpt ) ;
      /* - Print at stdout our presentation. */
      /* - */

      T_BOOL   L_WCPMSG_help          ( OUT   t_wppOptions    *wOpt ) ;
      /* - Print at stdout how to use options. */
      /* - */


   /* ... Inline / Macros ............................................... */

      #define L_WCPMSG_presentation(wcOpt) \
              L_WPP_MSG_presentation("WebCopy",c_WCOPY_VER)


   /* ................................................................... */


#endif

