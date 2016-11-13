

 #ifndef L_SBOTMSG_H
 #define L_SBOTMSG_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "wpplib/l_cl_wpp/l_wpp_opt.h"
      #include "wpplib/l_cl_wpp/l_wpp_msg.h"
      #include "SpiderBot/c_spiderbot.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_SBOTMSG_presentation  ( void ) ;
      /* - Hello. */
      /* - Bienvenidos */

      T_BOOL   L_SBOTMSG_listOptions   ( void ) ;
      /* - Print at stdout how to use options. */
      /* - */


   /* ... Inline / Macros ............................................... */

      #define L_SBOTMSG_presentation() \
              L_WPP_MSG_presentation("SpiderBot",c_SPIDERBOT_VER)


   /* ................................................................... */


#endif

