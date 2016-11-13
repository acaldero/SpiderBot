

 #ifndef L_BUFFW_H
 #define L_BUFFW_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Window Buffering .............................................. */
 
      T_BOOL L_BUFFW_CatOneByteToBuffEnd ( INOUT  T_CHAR  **b,
                                           IN     T_U_INT  *c,
 					   IN     T_CHAR    ch ) ;
      /* - */
      /* - Se le pasa un buffer, su taman~o y un caracter.
           Lo que hara es concatenar el caracter al final del buffer */
 
      T_BOOL L_BUFFW_CatNBytesToBuffEnd  ( INOUT  T_CHAR  **b,
 					   IN     T_U_INT  *cb,
  					   IN     T_CHAR   *s,
                                           IN     T_U_INT   cs ) ;
      /* - */
      /* - Lo que hara es concatenar el buffer 's' de taman~o 'cs'
           al final del buffer */
 
      T_BOOL L_BUFFW_AddBytesToBuffEnd   ( INOUT  T_CHAR   **b, 
 				 	   IN     T_U_INT    oldcb,  
                                           IN     T_U_INT    newcb,
 					   IN     T_U_INT    setval ) ; 
      /* - */
      /* - */

      T_BOOL L_BUFFW_AddBytesToBuffBegin ( INOUT  T_CHAR   **b, 
 					   IN     T_U_INT    oldcb,  
                                           IN     T_U_INT    newcb,
 					   IN     T_U_INT    setval ) ; 
      /* - */
      /* - */

 
   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

