

 #ifndef L_DSTACK_H
 #define L_DSTACK_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Types / Tipos .................................................. */

      typedef struct deslabon *t_pointerDStack ;
      struct  deslabon
      {
	T_POINTER elemento ;
	t_pointerDStack anterior ;
      } ;


   /* ... Consts / Constantes ............................................ */

      /* data size */
      #define c_POINTERPILA    sizeof(struct deslabon)


   /* ... Functions / Funciones .......................................... */

      t_pointerDStack   L_DSTACK_CreatEmpty ( void ) ;
      /* - Return the (t_pointerDStack)NULL */
      /* - Retorna la (t_pointerDStack)NULL */

      T_BOOL          L_DSTACK_IsEmpty    ( t_pointerDStack p ) ;
      /* - Check if stack is empty. */
      /* - Comprueba si la pila es (t_pointerDStack)NULL */
 
      T_POINTER       L_DSTACK_Pop        ( INOUT t_pointerDStack *p ) ;
      /* - */
      /* - Saca el ultimo elemento insertado en 'p',
           y retorna dicho elemento */
 
      t_pointerDStack   L_DSTACK_Push     ( INOUT t_pointerDStack *p,
   				            IN    T_POINTER e ) ;
      /* - */
      /* - Inserta en la pila 'p' el elemento 'e' */
 
      t_pointerDStack   L_DSTACK_PushNew  ( INOUT t_pointerDStack *p,
 		  		   	    IN    T_POINTER e ) ;
      /* - */
      /* - Inserta el la pila 'p' el elemento 'e' SOLO si NO
           esta ya en la pila */
 
      void            L_DSTACK_Empty      ( INOUT t_pointerDStack *p ) ;
      /* - */
      /* - Libera la memoria ocupada por la pila.
           NO libera el espacio de cada elemento */
 

   /* ... Inline / Expansiones ........................................... */

      #define L_DSTACK_CreatEmpty() \
              (t_pointerDStack)NULL

      #define L_DSTACK_IsEmpty(p)   \
              ((p)==(t_pointerDStack)NULL)


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

