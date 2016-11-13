

 #ifndef L_FILTER_H
 #define L_FILTER_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_cl/l_cl.h"
      #include "uilib/l_apps/l_info.h"


   /* ... Const / Constantes ............................................ */

      #define  c_STR_PIPE        "-p"
      #define  c_STR_HELP        "-h"
      #define  c_STR_VERBOSE     "-v"
      #define  c_STR_INPUT       "-fi"
      #define  c_STR_OUTPUT      "-fo"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FILTER_FilterOptions ( INOUT t_listOptions  *cl_opt ) ;
      /* - Build in 'cl_opt' a tipical filter options. */
      /* - Preprocesa los argumentos de la linea de comandos. */

      T_BOOL L_FILTER_ArgProcess ( IN     t_listOptions  *cl_opt,
                                   IN     T_INT           argc,
                                   IN     T_CHAR        **argv,
                                   IN     void          (*intro)(void),
                                   OUT    FILE          **fdinput,
                                   OUT    FILE          **fdoutput,
                                   OUT    T_CHAR        **filename,
                                   OUT    T_FLAG         *verboseflag,
                                   OUT    T_FLAG         *pipeflag ) ;
      /* - Preprocess arguments in command line. */
      /* - Preprocesa los argumentos de la linea de comandos. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

