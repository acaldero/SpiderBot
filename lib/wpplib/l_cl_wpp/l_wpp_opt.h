

 #ifndef L_WPP_OPT_H
 #define L_WPP_OPT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        T_FLAG   help_f ;
        T_FLAG   makeRelative_f ;
        T_FLAG   scanGlobal_f ;
        T_FLAG   fromSamePath_f ;
        T_FLAG   skipBin_f ;
        T_FLAG   skipEL_f ;
        T_FLAG   rentry_f ;
        T_FLAG   detectHttp_f ;
        T_FLAG   verbose_f ;
        T_FLAG   onlyHttp_f ;
        T_FLAG   makeQuery_f ;
        T_FLAG   in1Page_f ;
        T_CHAR  *href ;
        T_CHAR  *proxy ;
        T_CHAR  *recoverFile ;
        T_CHAR  *identification ;
        T_U_LONG   maxBytes ;
        T_U_LONG   maxUrls ;
        T_U_LONG   delay ;
        T_U_LONG   timeLimit ;
        T_U_LONG   bufSize ;
        T_U_LONG   resumeFrec ;
      } t_wppOptions ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_WPP_OPT_DupHref         ( INOUT  t_wppOptions  *wppOpt,
                                           IN     T_CHAR        *href ) ;
      /* - Dup memory in 'href' and copy this dup
           into 'wppOpt'. */
      /* - */

      T_BOOL   L_WPP_OPT_DupProxy        ( INOUT  t_wppOptions  *wppOpt,
                                           IN     T_CHAR        *proxy ) ;
      /* - Dup memory in 'proxy' and copy this dup
           into 'wppOpt'. */
      /* - */

      T_BOOL   L_WPP_OPT_DupRecoverFile  ( INOUT  t_wppOptions  *wppOpt,
                                           IN     T_CHAR        *recoverFile ) ;
      /* - Dup memory in 'recoverFile' and copy this dup
           into 'wppOpt'. */
      /* - */

      T_BOOL   L_WPP_OPT_DupIdentification ( INOUT  t_wppOptions  *wppOpt,
                                             IN     T_CHAR        *id ) ;
      /* - Dup memory in 'identification' and copy this dup
           into 'wppOpt'. */
      /* - */

      T_BOOL   L_WPP_OPT_MakeEmpty       ( INOUT  t_wppOptions  *wppOpt ) ;
      /* - Free memory in 'wppOpt' componets */
      /* - */

      T_BOOL   L_WPP_OPT_activeOptToFile  ( OUT   FILE          *fout,
                                            IN    t_wppOptions  *wppOpt ) ;
      /* - like L_WPP_OPT_wppOptToFile, but only 
           print option that are ON */
      /* - */

      T_BOOL   L_WPP_OPT_wppOptToFile     ( OUT   FILE           *fout,
                                            IN    t_wppOptions   *wppOpt ) ;
      /* - Print at 'fout', a human readable 
           representacion of 'wppOpt'. */
      /* - */

      T_BOOL   L_WPP_OPT_CheckValid      ( OUT   FILE           *fout,
                                           IN    t_wppOptions   *wppOpt ) ;
      /* - Check if values of 'wppOpt' are valid. */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

