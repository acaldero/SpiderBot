

 #ifndef L_STRLI_H
 #define L_STRLI_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_string/x_string.h"


   /* ... Types / Tipos ................................................. */

      typedef 
      struct 
      {
	T_CHAR     **list ;
	T_U_LONG     neltos ;
      } t_strLi ;


   /* ... Const / Constantes ............................................ */

      #define  c_STRLI       (sizeof(t_strLi))


   /* ... Functions / Funciones ......................................... */

      t_strLi    *L_STRLI_Creat ( void ) ;
      /* - */
      /* - Retorna puntero a una lista de strings, 
           usando 'malloc' */

      T_BOOL      L_STRLI_Copy  ( INOUT t_strLi      *listrDest,
                                  IN    t_strLi      *listrOrig ) ;
      /* - */
      /* - Almacena en 'listrDest' los valores de
           'listrOrig' SIN duplicar memoria */

      T_BOOL     L_STRLI_Destroy         ( INOUT t_strLi    **listr ) ;
      /* - */
      /* - Borra todos los strings de la tabla y 
           despues la tabla */

      T_BOOL     L_STRLI_Insert          ( INOUT t_strLi      *listr, 
                                           IN    T_CHAR       *elto ) ;
      /* - */
      /* - Anade un strings a la lista. */

      T_BOOL     L_STRLI_Empty           ( INOUT t_strLi      *listr ) ;
      /* - */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL     L_STRLI_MakeEmpty       ( INOUT t_strLi      *listr ) ;
      /* - */
      /* - Inicializa con valores nulos */

      T_U_LONG   L_STRLI_NumberStrings   ( IN    t_strLi      *listr ) ;
      /* - */
      /* - Retorna el numero de strings almacenados en la lista */

      T_CHAR     *L_STRLI_StringIn        ( IN    t_strLi      *listr, 
                                            IN    T_U_LONG     index  ) ;
      /* - */
      /* - Retorna el simbolo que se encuentre en la posicion `index`. */

      T_BOOL       L_STRLI_IsPresent       ( IN    t_strLi   *listr,
                                             IN    T_CHAR    *elto ) ;
      /* - */
      /* - Retorna TRUE si 'elto' esta en la tabla */

      T_BOOL       L_STRLI_Delete          ( INOUT t_strLi   *listr,
                                             IN    T_CHAR    *elto ) ;
      /* - */
      /* - Retorna TRUE si 'elto' esta en la tabla y,
           ha logrado borrarlo de la tabla sin problemas.
           Borra el primer elemento que se encuentre con 
           igual contenido que 'elto'. */


   /* ... Inline / Expansiones .......................................... */

      #define L_STRLI_NumberStrings(LS) \
              ( ((LS) == NULL) ? \
                 (0L) : ((LS)->neltos) )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif


