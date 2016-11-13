

 #ifndef L_UIRC_H
 #define L_UIRC_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_apps/l_info.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_adt/l_dnodo.h"
      #include "corelib/l_file/x_print.h"
      #include "uilib/l_wterm/l_win.h"
      #include "uilib/l_browse/l_fs.h"
      #include "uilib/l_browse/l_menu.h"
      #include "uilib/l_browse/l_htxt.h"
      #include "uilib/l_browse/l_wcon.h"


   /* ... Functions / Funciones ......................................... */

      FILE      *L_UIRC_OpenFile      ( IN     T_CHAR *progname ) ;
      /* - */
      /* - */

      t_DiNode  *L_UIRC_ReadMenu      ( INOUT  FILE   *fin ) ;
      /* - */
      /* - */

      t_DiNode  *L_UIRC_ReadDialog    ( INOUT  FILE   *fin ) ;
      /* - */
      /* - */

      t_DiNode  *L_UIRC_ReadHtxt      ( INOUT  FILE   *fin ) ;
      /* - */
      /* - */

      t_DiNode  *L_UIRC_ReadAssistant ( INOUT  FILE   *fin ) ;
      /* - */
      /* - */



   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

