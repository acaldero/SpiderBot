

 #ifndef L_TRANS_H
 #define L_TRANS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_math/x_math.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Functions / Funciones ......................................... */
   
      /* Funciones conversion de strings ... *
       * ----------------------------------- */
      T_INT  L_TRANS_BinToCard    ( IN    T_CHAR *Bin ) ;
      /* - */
      /* - Pasa un numero en binario codificado como 
           una secuencia de caracteres '0', '1' a 
           su valor en decimal */
   
      T_INT  L_TRANS_SubBinToCard ( IN    const T_CHAR *l ,
                                    IN    T_INT chi ,
                                    IN    T_INT num ) ;
      /* - */
      /* - Dado el string 'l' que representa un numero 
           binario (ej '100110') la funcion pasa de binario 
           a entero. Pero no todo 'l', sino el substring 
           que comienza en 'chi' y con 'num' de cararcteres
           Retorna el entero resultante */
   
      void L_TRANS_StrSwitch      ( IN    T_INT b,
                                    IN    T_INT limit,
                                    OUT    T_CHAR *l, ... ) ;
      /* - */
      /* - 'b' es un numero de 0..'limit'-1, y es el indice 
           del string que se concatenara a 'l'. Ejemplo, 
           si b es 2, el segundo parametro despues de 'l' se 
           interpreta como string, y se concatena a 'l' */
   
   
   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

