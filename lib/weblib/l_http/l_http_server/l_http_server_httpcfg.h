

 #ifndef L_HTTP_SERVER_HTTPCFG_H
 #define L_HTTP_SERVER_HTTPCFG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_cdt/l_strli.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_wdt/l_disallowli.h"
      #include "weblib/l_url/l_url.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        t_url          *host ;
        t_disallowLi    disallowList ;
        t_http_ver      httpVer ;
        t_sock          sd ;
        T_BOOL          connected ;
        T_BOOL          acceptFullUrl ;
        T_BOOL          acceptHost ;
      } t_httpCfg ;


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

