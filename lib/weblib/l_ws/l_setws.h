

 #ifndef L_SETWS_H
 #define L_SETWS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "weblib/l_ws/l_ws.h"
      #include "weblib/l_ws/l_wsstream.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_wdt/l_urllistream.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_SETWS_WorkSpaceSetup (    IN     t_downLoadWS *dlws,
                                          IN     FILE         *finfo,
                                          IN     FILE         *fresume,
                                          IN     T_CHAR       *clientNameReal,
                                          IN     T_CHAR       *clientNameToSend,
                                          IN     T_CHAR       *identification,
                                          IN     T_CHAR       *proxy,
                                          IN     T_INT         rewriteSelection,   
                                          IN     T_INT         scanSelection,   
                                          IN     T_INT         protocolSelection,
                                          IN     T_INT         mirrorSelection,
                                          IN     T_FLAG        detectHttp,
                                          IN     T_FLAG        verbose,
                                          IN     T_FLAG        fromSamePath,   
                                          IN     T_FLAG        skipBin,
                                          IN     T_FLAG        skipEL,
                                          IN     T_FLAG        rentry,
                                          IN     T_FLAG        makeQuery,
                                          IN     T_LONG        maxBytes,
                                          IN     T_LONG        maxUrls,
                                          IN     T_LONG        delay,
                                          IN     T_LONG        bufSize,
                                          IN     T_LONG        timeLimit,
                                          IN     T_LONG        resumeFrec ) ;
      /* - Setup initial values for this workspace. */
      /* - */

      void    L_SETWS_WorkSpaceResume   ( IN     t_downLoadWS *dlws ) ;
      /* - Save a workspace in a file. */
      /* - */

      T_BOOL  L_SETWS_WorkSpaceRecover  ( IN     FILE         *frecov,
                                          OUT    t_downLoadWS *dlws ) ;
      /* - Recover a previously saved workspace. */
      /* - */



  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

