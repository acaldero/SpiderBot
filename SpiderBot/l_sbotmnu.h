

 #ifndef L_SBOTMNU_H
 #define L_SBOTMNU_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_file/x_print.h"
      #include "uilib/l_apps/l_info.h"
#if defined(__UILIB__)
      #include "uilib/l_wterm/l_win.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_browse/l_htxt.h"
      #include "uilib/l_apps/l_uirc.h"
      #include "uilib/l_gadget/l_edtbox.h"
#endif
      #include "SpiderBot/c_spiderbot.h"
      #include "SpiderBot/l_sbotcl.h"
      #include "SpiderBot/l_sbotdl.h"
      #include "SpiderBot/l_sbotmsg.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_SBOTMNU_setupOptions ( IN    int           *chosen,
                                        INOUT t_wppOptions  *spiderOpt ) ;
      /* - */
      /* - */

      T_BOOL   L_SBOTMNU_setupFlags   ( IN    int           *chosen,
                                        INOUT t_wppOptions  *spiderOpt ) ;
      /* - */
      /* - */

      /*  Menu  *
       * ------ */
      t_menu   L_SBOTMNU_OpenPresent  ( INOUT   t_DiNode *g, 
                                        IN      T_INT     x,
                                        IN      T_INT     y ) ;
      /* - */
      /* - */

      T_INT   *L_SBOTMNU_Select       ( INOUT   t_menu   *mnu ) ;
      /* - */
      /* - */

      T_BOOL   L_SBOTMNU_ClosePresent ( INOUT   t_menu   *mnu ) ;
      /* - */
      /* - */


   /* ................................................................... */


#endif

