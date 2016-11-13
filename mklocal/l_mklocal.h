

 #ifndef L_MKLOCAL_H
 #define L_MKLOCAL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_dir/x_dir.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_dir/x_dir.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlxml.h"
      #include "mklocal/l_mkopt.h"
      #include "mklocal/l_mkmsg.h"
      #include "mklocal/l_mkcl.h"
      #include "c_mklocal.h"


   /* ... Global Vars / Variables Globales .............................. */

      extern t_mkOptions  mk_opt ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_MKLOCAL_rewriteUrls ( T_CHAR *path, T_CHAR *fname ) ;
      /* - rewrite Urls to local browsing. */
      /* - */

      T_INT    L_MKLOCAL_main        ( T_INT argc, T_CHAR *argv[] ) ;
      /* - rewrite Urls to local browsing. */
      /* - */


   /* ................................................................... */


#endif

