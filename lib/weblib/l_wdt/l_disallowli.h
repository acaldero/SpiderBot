

 #ifndef L_DISALLOWLI_H
 #define L_DISALLOWLI_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_cdt/l_strli.h"
      #include "weblib/l_url/l_url.h"


   /* ... Types / Tipos ................................................. */

      typedef
      t_strLi  t_disallowLi ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_DISALLOWLI_MakeEmpty       ( INOUT t_disallowLi *disli ) ;
      /* - Fill with null/neutral values. */
      /* - Inicializa con valores nulos/neutrales. */

      T_BOOL   L_DISALLOWLI_Empty           ( INOUT t_disallowLi *disli ) ;
      /* - Free componets and MakeEmpty. */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL   L_DISALLOWLI_IsDisallow      ( IN    t_disallowLi *disli,
                                              IN    t_url        *url ) ;
      /* - Return TRUE if 'url' is forbidden. */
      /* - TRUE si 'url' esta prohibido. */

      T_BOOL   L_DISALLOWLI_ReadDisallow    ( INOUT t_disallowLi *disli,
                                              INOUT FILE         *fbot ) ;
      /* - Read Disallow path from file 'fbot'.
           Return FALSE if problem ocurrs. */
      /* - Lee los path a excluir, indicando
           con FALSE que no pudo leer bien la lista. */


   /* ... Inline / Expansiones .......................................... */

      #define L_DISALLOWLI_MakeEmpty(disli)  \
              L_STRLI_MakeEmpty((t_strLi *)disli)

      #define L_DISALLOWLI_Empty(disli)  \
              L_STRLI_Empty((t_strLi *)disli)


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

