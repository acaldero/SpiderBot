

 #ifndef X_ALLOC_H
 #define X_ALLOC_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/v_alloc.h"


   /* ... Functions / Funciones ......................................... */

      /*  Standard Memory Functions  *
       * --------------------------- */
      T_POINTER  X_ALLOC_Malloc    ( IN     T_U_INT     size ) ;
      /* - totalmemo-=size, ret 'size' bytes */

      void       X_ALLOC_Free      ( INOUT  T_POINTER  *ptr ) ;
      /* - totalmemo+=size (**ptr), (*ptr)=NULL */

      T_POINTER  X_ALLOC_Realloc   ( IN     T_POINTER   block, 
                                     IN     T_U_INT     size ) ;
      /* - Change 'block' memory size into 'size' bytes. */
      /* - Cambia el taman~o del bloque 'block' a 'size' bytes */
      

      /*  Advanced Memory Functions  *
       * --------------------------- */
      void       X_ALLOC_MemMove   ( IN     T_POINTER   dest,
                                     IN     T_POINTER   src,
                                     IN     T_U_INT     count ) ;   
      /* - Copy from 'src' to 'dest' 'count' bytes */
      /* - Copia en 'dest' los 'count' primeros bytes de 'src' */

      void       X_ALLOC_MemSet    ( IN     T_POINTER   dest,
                                     IN     T_BYTE      byte,
                                     IN     T_U_INT     count ) ;   
      /* - Fill 'count' first bytes of 'dest' with 'byte'
           value */
      /* - Rellena los 'count' primeros bytes de 'dest' con 
           el byte 'byte'. */

      T_POINTER  X_ALLOC_MemDup    ( IN     T_POINTER   b, 
                                     IN     T_U_INT     bsize ) ;
      /* - Retorna zona de memoria de memoria de 'bsize' bytes    
           cuyo contenido es una copia de los 'bsize' primeros 
           bytes de 'b' */

      T_POINTER  X_ALLOC_AllocAndSet ( IN     T_U_INT  bsize, 
                                       IN     T_CHAR   setval ) ;
      /* - Request 'bsize' free space, and return this space
           filled with 'setval'. 
           Return NULL if someth was wrong */
      /* - Retorna zona de memoria de 'bsize' bytes cuyo valor 
           se ha fijado a setval */


      /*  Control Memory Functions  *
       * -------------------------- */
      T_U_LONG   X_ALLOC_Available ( void ) ;
      /* - Return total memory available.
           In Unix, this is no very important */
      /* - Retorna totalmemo, salvo en unix, pues es ampliable hasta
           el valor definido por el comando 'limit' */

      T_POINTER  X_ALLOC_ChkPtr    ( IN     T_POINTER   b,
                                     IN     T_CHAR     *file,
                                     IN     T_INT       line ) ;
      /* - Explore if 'b' is a valid memory block.
           If any error, print a message.
           Any way, return 'b'. */
      /* - Explora que 'b' sea la referencia valida a un bloque
           de memoria, retornando ese mismo 'b'.
           Ante errores, informa con un mensaje */


   /* ... Inline / Expansiones .......................................... */

      #include "corelib/l_alloc/x_alloc.m"


   /* ................................................................... */

 #ifdef  __cplusplus
    }
 #endif


 #endif 

