

 #ifndef L_FINGER_RESPONSE_H
 #define L_FINGER_RESPONSE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"


   /* ... Type / Tipos .................................................. */

      typedef
      struct
      {
        T_BOOL   ok ;
        T_CHAR  *msg ;
      } t_finger_response ;


   /* ... Const / Constantes ............................................ */

      #define  c_FINGER_RESPONSE   sizeof(t_finger_response)


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_FINGER_RESPONSE_Read  ( INOUT  t_sock          *sd,
                                          INOUT  t_finger_response  *fingerr ) ;
      /* - Read response to a finger command. */
      /* - Lee la respuesta a un comando finger. */

      T_BOOL    L_FINGER_RESPONSE_Skip  ( INOUT  t_sock     *sd ) ;
      /* - Skip response to a finger command. */
      /* - Lee la respuesta y la descarta. */
 
      T_BOOL    L_FINGER_RESPONSE_MakeEmpty ( INOUT  t_finger_response   *fingerr ) ;
      /* - Fill with null/neutral values. */
      /* - Inicializa con valores nulos/neutrales. */

      T_BOOL    L_FINGER_RESPONSE_Empty ( INOUT  t_finger_response  *fingerr ) ;
      /* - Free componets and MakeEmpty. */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL    L_FINGER_RESPONSE_Destroy ( INOUT  t_finger_response  **fingerr ) ;
      /* - Free componets and Free fingerr. */
      /* - Libera los componentes asi como fingerr. */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

