

 #ifndef X_PRINT_H
 #define X_PRINT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Functions / Funciones ......................................... */

      void   X_PRINT_setPrintWrapper (
                                       IN  T_INT  (*f_int__string__valist)
                                                  (
                                                    const T_CHAR *,
                                                    va_list
                                                  )
                                     ) ;
      /* - Set function to use when 'X_PRINT_*' are called. 
           NULL means no print. */
      /* - Activa la funcion a usar al imprimir. 
           NULL significa no imprimir. */

      void   X_PRINT_write    ( IN    T_CHAR  *msg ) ;
      /* - Write a debug string using X_PRINT_PrintMsg,
           if this var. is NOT null. */
      /* - Escribe una tira de caracteres usando 
           X_PRINT_PrintMsg, si no es null. */

      void   X_PRINT_vprintf  ( IN    T_CHAR  *fto,
                                IN    va_list  vl ) ;
      /* - */
      /* - Escribe un mensaje, usando formato y lista
           de argumentos variables. */

      void   X_PRINT_printf   ( IN    T_CHAR  *fto, 
                                ... ) ;
      /* - */
      /* - Escribe una tira CON FORMATO usando PrintMsg. */


   /* ................................................................... */

 #ifdef  __cplusplus
    }
 #endif


 #endif

