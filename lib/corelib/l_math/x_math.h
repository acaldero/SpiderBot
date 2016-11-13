

 #ifndef X_MATH_H
 #define X_MATH_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_time/v_time.h"


   /* ... Inline / Macros ............................................... */

      /* ... Incremento Circular de Radianes ... */
      #define  RAD_INC(a,i)    (a)=(((a)+(i) > 2*M_PI) ? 0.0    : (a)+(i))
      #define  RAD_DEC(a,i)    (a)=(((a)-(i) <    0.0) ? 2*M_PI : (a)-(i))

      /* ... Paso entre grados y radianes ... */
      #define  GRAD_RAD(a)     (a*M_PI  / 180.0)
      #define  RAD_GRAD(a)     (a*180.0 /  M_PI)


   /* ... Funtions / Funciones .......................................... */

      T_INT   X_MATH_Ipow ( IN     T_INT  base,
                            IN     T_INT  expo ) ;
      /* - Return 'base' ^ 'expo'. */
      /* - Retorna el numero 'base' elevado a 'expo' */

      void  X_MATH_Randomize ( T_U_INT base ) ;
      /* - Start random generator. */
      /* - Arranque generador numeros aleatorios. */

      T_INT X_MATH_Random    ( T_U_INT limit ) ;
      /* - */
      /* - Numero aleatorio desde 0 hasta 'limit'. */


   /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

