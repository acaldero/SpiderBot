

 #ifndef L_NNTP_RESPONSE_H
 #define L_NNTP_RESPONSE_H

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
      } t_nntp_response ;


   /* ... Const / Constantes ............................................ */

      #define  c_NNTP_RESPONSE   sizeof(t_nntp_response)


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_NNTP_RESPONSE_Skip      ( INOUT  t_sock      *sd ) ;
      /* - Skip response to a nntp command. */
      /* - Lee la respuesta y la descarta. */

      T_BOOL    L_NNTP_RESPONSE_Read      ( INOUT  t_sock           *sd,
                                            INOUT  t_nntp_response  *nntpr ) ;
      /* - Read response to a nntp command. */
      /* - Lee la respuesta a un comando nntp. */

      T_BOOL    L_NNTP_RESPONSE_MakeEmpty ( INOUT  t_nntp_response   *nntpr ) ;
      /* - Fill with null/neutral values. */
      /* - Inicializa con valores nulos/neutrales. */

      T_BOOL    L_NNTP_RESPONSE_Empty     ( INOUT  t_nntp_response   *nntpr ) ;
      /* - Free componets and MakeEmpty. */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL    L_NNTP_RESPONSE_Destroy   ( INOUT  t_nntp_response  **nntpr ) ;
      /* - Free componets and Free nntpr. */
      /* - Libera los componentes asi como nntpr. */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

