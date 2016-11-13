

 #ifndef I_ALLOC_FINAL_H
 #define I_ALLOC_FINAL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Functions / Funciones ......................................... */

      /*  Standard Memory Functions  *
       * --------------------------- */
      T_POINTER  I_ALLOC_FINAL_Malloc    ( IN     T_U_INT    size ) ;
      /* - totalmemo-=size, return 'size' bytes */

      void       I_ALLOC_FINAL_Free      ( INOUT  T_POINTER *ptr ) ;
      /* - totalmemo+=size (**ptr), (*ptr)=NULL */

      T_POINTER  I_ALLOC_FINAL_Realloc   ( IN     T_POINTER  block, 
                                           IN     T_U_INT    size ) ;
      /* - Change 'block' memory size into 'size' bytes. */
      /* - Cambia el taman~o del bloque 'block' a 'size' bytes */
      

      /*  Advanced Memory Functions  *
       * --------------------------- */
      T_POINTER  I_ALLOC_FINAL_MemMove   ( IN     T_POINTER  dest,
                                           IN     T_POINTER  src,
                                           IN     T_U_INT    count ) ;   
      /* - Copy from 'src' to 'dest' 'count' bytes */
      /* - Copia en 'dest' los 'count' primeros bytes de 'src' */

      T_POINTER  I_ALLOC_FINAL_MemSet    ( IN     T_POINTER  dest,
                                           IN     T_BYTE     byte,
                                           IN     T_U_INT    count ) ;   
      /* - Fill 'count' first bytes of 'dest' with 
          'byte' value */
      /* - Rellena los 'count' primeros bytes de 'dest' con 
           el byte 'byte'. */


      /*  Control Memory Functions  *
       * -------------------------- */
      T_U_LONG   I_ALLOC_FINAL_Available ( void ) ;
      /* - Return total memory available.
           In Unix, can be changes using 'limit' */
      /* - Retorna totalmemo, salvo en unix, pues es
           ampliable hasta el valor definido por el
           comando 'limit' */

      T_POINTER  I_ALLOC_FINAL_ChkPtr    ( IN     T_POINTER   b ) ;
      /* - Explore if 'b' is a valid memory block.
           If any error, print a message.
           Any way, return 'b'. */
      /* - Explora que 'b' sea la referencia valida a un bloque
           de memoria, retornando ese mismo 'b'.
           Ante errores, informa con un mensaje */


   /* ... Inline / Macros ............................................... */

      #include "corelib/l_alloc/i_alloc_final.m"


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif 

