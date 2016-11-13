

 #ifndef L_CL_H
 #define L_CL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/x_print.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
        T_CHAR   *switch_name ;
        T_CHAR   *switch_help ;
        T_BOOL    alone  ;
        T_BOOL    active ;
        T_CHAR   *value  ;
        T_INT     position ;
      } t_cl_option ;

      typedef
      struct
      {
        T_U_LONG       nopt ; 
        t_cl_option  **lopt ;
      } t_listOptions ;


   /* ... Const / Constantes ............................................ */

      #define  c_CL_OPTION      sizeof(t_cl_option)
      #define  c_LISTOPTIONS    sizeof(t_listOptions)


   /* ... Functions / Funciones ......................................... */

      /* Option Management *
       * ----------------- */
      t_cl_option    *L_CL_CrearOption  ( void ) ;
      void            L_CL_FreeOption   ( INOUT  t_cl_option  *elto_opt ) ;


      /* List Management *
       * --------------- */
      t_listOptions  *L_CL_Crear       ( void ) ;
      T_BOOL          L_CL_Copia       ( INOUT t_listOptions   *opt_liDest,
                                         IN    t_listOptions   *opt_liOrig ) ;
      T_BOOL          L_CL_Destruir    ( INOUT t_listOptions  **opt_li ) ;
      T_BOOL          L_CL_Insertar    ( INOUT t_listOptions   *opt_li,
                                         IN    t_cl_option     *elto ) ;
      T_BOOL          L_CL_Vaciar      ( INOUT t_listOptions   *opt_li ) ;
      T_BOOL          L_CL_PonerVacia  ( INOUT t_listOptions   *opt_li ) ;
      t_cl_option    *L_CL_ArgIn       ( IN    t_listOptions   *cl_opt,  
				         IN    T_U_LONG         index ) ;

 
      /* Arg processing *
       * -------------- */
      void   L_CL_ArgInfo       ( IN     t_listOptions   *cl_opt ) ;
      /* - Print info associated with each cl_option. */
      /* - Informa de la linea de comandos asociada a cada opcion. */

      T_BOOL L_CL_ArgInvalid    ( IN     T_INT            argc,
                                  IN     T_CHAR         **argv,
                                  INOUT  t_listOptions   *cl_opt ) ;
      /* - Return TRUE if any 'switch' is bad */
      /* - Retorna TRUE si hay alguna opcion extranya */

      T_BOOL L_CL_ArgProcess    ( IN     T_INT            argc, 
                                  IN     T_CHAR         **argv,
                                  INOUT  t_listOptions   *cl_opt ) ;
      /* - Preprocess arguments in command line. */
      /* - Preprocesa los argumentos de la linea de comandos. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

