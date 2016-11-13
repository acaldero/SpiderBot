

 #ifndef L_BUFFA_H
 #define L_BUFFA_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"


   /* ... Consts / Constantes ........................................... */

      #define c_BUFFSIZE   (32*1024)


   /* ... Ahead Buffering ............................................... */
   
      T_BOOL  L_BUFFA_CatOneByteToCache   ( INOUT  T_CHAR   **b, 
   					    INOUT  T_U_INT   *cb,
   					    IN     T_CHAR     ch ) ;
      /* - Will catenate 'ch' at end of '(*b)' buffer, and
           also will increment '(*cb)' in one. */
      /* - Se le pasa un buffer, su taman~o y un caracter.
           Lo que hara es concatenar el caracter al final del buffer,
           y si es necesario, amplia el taman~o del buffer en 
           'c_BUFFSIZE' para que quepa */
   
      T_BOOL  L_BUFFA_CatNBytesToCache    ( INOUT  T_CHAR   **b,
   				            INOUT  T_U_INT   *cb,
   					    IN     T_CHAR    *s, 
                                            IN     T_U_INT    cs ) ;
      /* - Will catenate 'cs' first char of string 's' 
           at end of '(*b)' buffer, and also will 
           increment '(*cb)' in one. */
      /* - Lo que hara es concatenar el string de taman~o indicado,
           al final del buffer, y si es necesario, amplia el taman~o
           del buffer de 'c_BUFFSIZE' en 'c_BUFFSIZE' hasta que quepa */
   
      T_BOOL  L_BUFFA_AjustCache          ( INOUT  T_CHAR   **b,
                                            IN     T_U_INT    cb ) ;
      /* - Cambia el taman~o del buffer 'b' a 'cb' */
   

   /* ... Inline / Macros ............................................... */

      T_BOOL  L_BUFFA_F_CatOneByteToCache   ( INOUT  T_CHAR   **b, 
   		          		      INOUT  T_U_INT   *cb,
   					      IN     T_CHAR     ch ) ;

      #define L_BUFFA_CatOneByteToCache(b,cb,ch)                \
              (                                                 \
                ( ((*cb) % c_BUFFSIZE) == 0 ) ?                 \
                  (L_BUFFA_F_CatOneByteToCache((b),(cb),(ch)))  \
                  :                                             \
                  (((*(b))[(*(cb))++]=(ch)),TRUE)               \
              )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

