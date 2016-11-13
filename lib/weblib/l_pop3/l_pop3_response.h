

 #ifndef L_POP3_RESPONSE_H
 #define L_POP3_RESPONSE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/l_line.h"
      #include "corelib/l_net/x_socket.h"


   /* ... Type / Tipos .................................................. */

      typedef
      struct
      {
        T_BOOL   ok ;
        T_CHAR  *msg ;
      } t_pop3_response ;


   /* ... Const / Constantes ............................................ */

      #define  c_POP3_RESPONSE   sizeof(t_pop3_response)


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_POP3_RESPONSE_Read      ( INOUT  t_sock           *sd,
                                            INOUT  t_pop3_response  *pop3r ) ;
      /* - Read response to a pop3 command. */
      /* - Lee la respuesta a un comando pop3. */

      T_BOOL    L_POP3_RESPONSE_Skip      ( INOUT  t_sock      *sd,
                                            IN     T_BOOL       isMultiLine ) ;
      /* - Skip response to a pop3 command. */
      /* - Lee la respuesta y la descarta. */

      T_BOOL    L_POP3_RESPONSE_MakeEmpty ( INOUT  t_pop3_response   *pop3r ) ;
      /* - Fill with null/neutral values. */
      /* - Inicializa con valores nulos/neutrales. */

      T_BOOL    L_POP3_RESPONSE_Empty     ( INOUT  t_pop3_response   *pop3r ) ;
      /* - Free componets and MakeEmpty. */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL    L_POP3_RESPONSE_Destroy   ( INOUT  t_pop3_response  **pop3r ) ;
      /* - Free componets and Free pop3r. */
      /* - Libera los componentes asi como pop3r. */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

