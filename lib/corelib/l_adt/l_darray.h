

 #ifndef L_DARRAY_H
 #define L_DARRAY_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"


   /* ... Consts / Constantes ............................................ */

      /* ... type sizes ... */
      #define c_POINTERTABLA   sizeof(t_pointerDArray)


   /* ... Types / Tipos .................................................. */

      typedef 
      T_POINTER  *t_pointerDArray ;
      /* Dinamic array, NULL end */


   /* ... Functions / Funciones .......................................... */

      T_BOOL       L_DARRAY_InsEndDarray ( INOUT t_pointerDArray *t,
                                           INOUT T_U_LONG        *n,
                                           IN    T_POINTER        gptr ) ;
      /* - Insert 'gptr' at end of 't', with '(*n)' eltos and
           add one more ( (*n) = (*n) + 1 ) */
      /* - Inserta el puntero 'gptr' al final de la tabla 't'
           que tiene ya 'n' punteros. En la funcion se incrementa
           en uno 'n', pues al final, tendra un elemento mas : 'gptr' */

      T_BOOL       L_DARRAY_DelEndDarray ( INOUT t_pointerDArray *t,
                                           INOUT T_U_LONG        *n,
                                           INOUT T_POINTER       *delGPtr ) ;
      /* - Del las elto of 't' and subtract one elto
           ( (*n) = (*n) - 1 ) */
      /* - Borra el ultimo elemento de la tabla 't', decrementa el
           numero de elementos en tabla ('n') y coloca en el parametro
           delGPtr el elemento borrado, por si nos interesa */

      T_BOOL       L_DARRAY_DelBeginDarray ( INOUT t_pointerDArray *t,
                                             INOUT T_U_LONG        *n,
                                             INOUT T_POINTER       *delGPtr ) ;
      /* - */
      /* - Borra el primer elemento de la tabla 't', decrementa el
           numero de elementos en tabla ('n') y coloca en el parametro
           delGPtr el elemento borrado, por si nos interesa */

      T_BOOL       L_DARRAY_DelNFromDarray ( IN    t_pointerDArray *t,
                                             INOUT T_U_LONG        *n,
                                             IN    T_U_LONG         orden,
                                             INOUT T_POINTER       *delGPtr ) ;
      /* - */
      /* - Borra el elemento de posicion 'orden' de la tabla 't', decrementa
           el numero de elementos en tabla ('n') y coloca en el parametro
           delGPtr el elemento borrado, por si nos interesa */

      T_BOOL       L_DARRAY_ChangeNFromDarray ( IN    t_pointerDArray *t,
                                                INOUT T_U_LONG        *n,
                                                IN    T_U_LONG         orden,
                                                INOUT T_POINTER        nPtr ) ;
      /* - */
      /* - Cambia Darray[orden] a 'nPtr' */

      T_BOOL       L_DARRAY_FreeEltosDarray ( INOUT t_pointerDArray *t,
                                              INOUT T_U_LONG        *n,
                                              IN    void (*freef)(T_POINTER) ) ;
      /* - */
      /* - Se recorre la tabla, del 0..N aplicando la funcion 'freef'
           sobre cada elemento. Cuando ha terminado, hace un 'free(t)' */

      T_POINTER  L_DARRAY_GetNFromDarray ( IN t_pointerDArray t,
                                           IN T_U_LONG orden ) ;
      /* - */
      /* - Retorna el elemento que ocupa la posicion 'orden' en la tabla.
           OJO, si orden es 3, retorna t[3] (es decir, el cuarto) 
           NO comprueba que se salga de los limites del array. */

      T_POINTER  L_DARRAY_FindEltoDarray ( IN     t_pointerDArray  t,
                                           INOUT  T_U_LONG         n,
                                           IN     T_POINTER        gptr,
                                           IN     T_BOOL (*findf)(T_POINTER,T_POINTER) ) ;
      /* - */
      /* - Busca el array dinamico, el primer elemento que haga que,
           (*findf)(gptr,<elemento darray) == TRUE. */
 

      /*  using NULL elto is end  *
       * ------------------------ */
      T_U_LONG     L_DARRAY_GetNDarray ( IN t_pointerDArray t ) ;
      /* - */
      /* - Retorna el numero de elementos de la tabla 't' */

      T_BOOL       L_DARRAY_FreeEltosDarray2 ( INOUT t_pointerDArray *t,
                                               IN    void (*freef)(T_POINTER) ) ;
      /* - */
      /* - Se recorre la tabla, del 0..N aplicando la funcion 'freef'
           sobre cada elemento. Cuando ha terminado, hace un 'free(t)' */

      T_BOOL       L_DARRAY_DelEltoDarray ( INOUT t_pointerDArray *t,
                                            IN    T_POINTER elto ) ;
      /* - */
      /* - Intenta borra el elemento 'elto' de la tabla 't'. Lo busca
           y si no lo encuentra retorna FALSE. Si lo encuentra lo borra
           y ajusta la tabla. No necesita el dato 'numero de elementos'
           pues en la busqueda ya recorre la tabla */

      T_BOOL       L_DARRAY_InsEndDarray2 ( INOUT t_pointerDArray *t,
                                            IN    T_POINTER gptr ) ; 
      /* - */
      /* - Inserta el puntero 'gptr' al final de la tabla 't'.
           La diferencia con la anterior funcion es que, al no
           conocerse el numero de elementos, 'los cuenta', algo que
           es ineficiente. Recuerdo, la tabla de punteros termina
           con el puntero NULL */

      T_BOOL       L_DARRAY_DelEndDarray2 ( INOUT t_pointerDArray *t,
                                            INOUT T_POINTER *delGPtr ) ; 
      /* - */
      /* - Borra el ultimo elemento de la tabla 't' y coloca en el 
           parametro 'delGPtr' el elemento borrado, por si nos interesa.
           La diferencia con la anterior funcion es que, al no
           conocerse el numero de elementos, 'los cuenta', algo que
           es terriblemente ineficiente. */


   /* ................................................................... */

      #define    L_DARRAY_GetNFromDarray(t,orden)    \
                 ( ((t)==(t_pointerDArray)NULL) ? NULL : t[(orden)] ) 


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

