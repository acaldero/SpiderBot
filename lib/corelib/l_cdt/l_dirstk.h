

 #ifndef L_DIRSTK_H
 #define L_DIRSTK_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_dir/v_dir.h"


   /* ... Types / Tipos ................................................. */

      typedef struct eslabon *t_di_stack ;
      struct  eslabon
              {
                t_dirinfo elto ;
                t_di_stack anterior ;
              } ;


   /* ... Const / Constantes ............................................ */

      #define c_DIRINFO        sizeof(t_dirinfo)
      #define c_DISTACK        sizeof(struct eslabon)


   /* .............................................. "dirinfo's" stack ... */

    T_BOOL *L_DIRSTK_IsEmpty ( IN t_di_stack p ) ;
    /* - Ret TRUE si la pila NO tiene elementos, FALSE e.o.c. */

    t_di_stack *L_DIRSTK_Pop ( INOUT t_di_stack *p,
                               INOUT t_dirinfo  *e ) ;
    /* - Si la pila esta vacia, retorna NULL.
         si no vacia, quita la cima de la pila y la coloca en 'e',
         retornando esta vez la pila que queda */

    t_di_stack L_DIRSTK_Push ( INOUT t_di_stack *p,
                               IN    t_dirinfo *e   ) ;
    /* - Inserta el elemento 'e' en la pila 'p'. Ret la pila con el
         elemento insertado o NULL si no pudo */

    void L_DIRSTK_Empty ( INOUT t_di_stack *p ) ;
    /* - Vacia la pila de todo elemento, liberando la memoria
         ocupada por cada elemento (y campo path de cada elto) */


   /* ... Inline / Codigo en linea ...................................... */

      #define L_DIRSTK_IsEmpty(p)         (((p)==NULL) ? TRUE : FALSE)


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

