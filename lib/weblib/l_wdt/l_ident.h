

 #ifndef L_IDENT_H
 #define L_IDENT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/x_string.h"


   /* ... Type / Tipos .................................................. */

      typedef
      struct
      {
        T_CHAR  *user ;
        T_CHAR  *pass ;
      } t_ident ;


   /* ... Const / Constantes ............................................ */

      #define  c_IDENT   sizeof(t_ident)


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_IDENT_ParseFromString   ( INOUT  t_ident  *ident,
                                            IN     T_CHAR   *str ) ;
      /* - Duplicate user and pass from 'str'.
           'str' has a format like "<user>:<pass>". */
      /* - Duplica el usuario y password procedente de 'str'.
           'str' tiene el formato "<usuario>:<password>". */

      T_BOOL    L_IDENT_MakeEmpty ( INOUT  t_ident   *ident ) ;
      /* - Fill with null/neutral values. */
      /* - Inicializa con valores nulos/neutrales. */

      T_BOOL    L_IDENT_Empty     ( INOUT  t_ident   *ident ) ;
      /* - Free componets and MakeEmpty. */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL    L_IDENT_Destroy   ( INOUT  t_ident  **ident ) ;
      /* - Free componets and Free ident. */
      /* - Libera los componentes asi como ident. */

      T_CHAR   *L_IDENT_getUser   ( INOUT  t_ident   *ident ) ;
      /* - Return a 'mallocated' string with user. */
      /* - Retorna un string dinamico con el usuario. */

      T_CHAR   *L_IDENT_getPass   ( INOUT  t_ident   *ident ) ;
      /* - Return a 'mallocated' string with password. */
      /* - Retorna un string dinamico con el contrasena. */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

