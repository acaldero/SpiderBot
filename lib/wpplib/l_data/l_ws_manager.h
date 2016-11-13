

 #ifndef L_WS_MANAGER_H
 #define L_WS_MANAGER_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_thread/x_thread.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_setws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlfile.h"
      #include "weblib/l_url/l_urlxml.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_vp/l_vp_server.h"
      #include "weblib/l_vp/l_vp_download.h"


   /* ... Functions / Funciones ......................................... */

      /* ... Work space ... */
      T_BOOL  L_WS_MANAGER_ResumeWS      ( IN     t_downLoadWS   *dlws ) ;
      /* - */
      /* - */

      /* ... Url list ... */
      T_BOOL  L_WS_MANAGER_initUrlList   ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_url          *url ) ;
      /* - */
      /* - */

      T_BOOL  L_WS_MANAGER_SkipParser    ( IN     t_url          *purl ) ;
      /* - */
      /* - */

      T_BOOL  L_WS_MANAGER_AddPageUrls   ( INOUT  t_downLoadWS   *dlws,
                                           INOUT  t_url          *purl,
                                           INOUT  FILE           *fpage ) ;
      /* - Add more url to dlws`s url list (dlws->urlli),
           that are inside 'fpage' file. */
      /* - */

      T_BOOL  L_WS_MANAGER_getNextUrl    ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_url         **purl ) ;
      /* - Get url from list and point to next url.
           Is was used to concurrent acces to dlws->urlli. */
      /* - */


      /* ... Url list Access ... */
      T_BOOL  L_WS_MANAGER_initUrlListAccess   ( IN     T_INT    nThreads ) ;
      /* - */
      /* - */

      T_BOOL  L_WS_MANAGER_finalizeUrlListAccess ( void ) ;
      /* - */
      /* - */


   /* ... Inline / Macro ................................................ */

      /*  Equals  *
       * -------- */
     #define    L_WS_MANAGER_SkipParser(purl)                \
                (                                            \
                  ((purl) != NULL) ?                         \
                    (L_URLFILE_IsBin((purl)->file))          \
                    :                                        \
                    TRUE                                     \
                )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

