

 #ifndef L_MKOPT_H
 #define L_MKOPT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        T_FLAG   help_f ;
        T_FLAG   allSites_f ;
        T_FLAG   skipBin_f ;
        T_FLAG   makeQuery_f ;
        T_FLAG   verbose_f ;
        T_CHAR  *webdir ;
      } t_mkOptions ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_MKOPT_DupWebDir           ( INOUT  t_mkOptions    *mkOpt,
                                             IN     T_CHAR         *webdir ) ;
      /* - Dup memory in 'webdir' and copy this dup
           into 'mkOpt'. */
      /* - */

      T_BOOL   L_MKOPT_MakeEmpty           ( INOUT  t_mkOptions   *mkOpt ) ;
      /* - Free memory in 'mkOpt' componets */
      /* - */

      T_BOOL   L_MKOPT_activeOptToFile     ( OUT   FILE           *fout,
                                             IN    t_mkOptions    *mkOpt ) ;
      /* - like L_MKOPT_mkOptToFile, but only 
           print option that are ON */
      /* - */

      T_BOOL   L_MKOPT_mkOptToFile         ( OUT   FILE            *fout,
                                             IN    t_mkOptions     *mkOpt ) ;
      /* - Print at 'fout', a human readable 
           representacion of 'mkOpt'. */
      /* - */

      T_BOOL   L_MKOPT_CheckValid          ( OUT   FILE            *fout,
                                             IN    t_mkOptions     *mkOpt ) ;
      /* - Check if values of 'mkOpt' are valid. */
      /* - */


   /* ................................................................... */


 #endif

