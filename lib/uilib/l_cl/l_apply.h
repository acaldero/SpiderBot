

 #ifndef L_APPLY_H
 #define L_APPLY_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_cl/l_cl.h"
      #include "uilib/l_apps/l_info.h"


   /* ... Const / Constantes ............................................ */

      /* ... switches ... */
      #define  c_STR_RECURSIVE   "-r"
      #define  c_STR_HELP        "-h"
      #define  c_STR_VERBOSE     "-v"
      #define  c_STR_DIRBASE     "-d"

      /* ... verbose modes ... */
      #define   c_VERBOSE_NO       100
      #define   c_VERBOSE_LINE     101
      #define   c_VERBOSE_LIST     102


   /* ... Functions / Funciones ......................................... */


      T_BOOL L_APPLY_ApplyOptions ( INOUT t_listOptions  *cl_opt ) ;
      /* - Setup 'apply' command line. */
      /* - Construye las opciones de linea de comando */

      T_BOOL L_APPLY_ArgProcess ( IN     t_listOptions  *cl_opt,
                                  IN     T_INT           argc,
                                  IN     T_CHAR         **argv,
                                  IN     void            (*intro)(void),
                                  INOUT  T_INT          *verbosemode,
                                  INOUT  T_FLAG         *recurseflag,
                                  INOUT  T_INT          *dirpos ) ;
      /* - Preprocess arguments in command line. */
      /* - Preprocesa los argumentos de la linea de comandos. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

