

 #ifndef L_FTP_RESPONSE_H
 #define L_FTP_RESPONSE_H

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
        int      code ;
        T_CHAR  *msg ;
      } t_ftp_response ;


   /* ... Const / Constantes ............................................ */

      #define  c_FTP_RESPONSE   sizeof(t_ftp_response)


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_FTP_RESPONSE_Read      ( INOUT  t_sock          *sd,
                                           INOUT  t_ftp_response  *ftpr ) ;
      /* - Read response to a ftp command. */
      /* - Lee la respuesta a un comando ftp. */

      T_BOOL    L_FTP_RESPONSE_Skip      ( INOUT  t_sock     *sd ) ;
      /* - Skip response to a ftp command. */
      /* - Lee la respuesta y la descarta. */
 
      T_BOOL    L_FTP_RESPONSE_MakeEmpty ( INOUT  t_ftp_response   *ftpr ) ;
      /* - Fill with null/neutral values. */
      /* - Inicializa con valores nulos/neutrales. */

      T_BOOL    L_FTP_RESPONSE_Empty     ( INOUT  t_ftp_response   *ftpr ) ;
      /* - Free componets and MakeEmpty. */
      /* - Borra todos los strings de la tabla y la inicializa. */

      T_BOOL    L_FTP_RESPONSE_Destroy   ( INOUT  t_ftp_response  **ftpr ) ;
      /* - Free componets and Free ftpr. */
      /* - Libera los componentes asi como ftpr. */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

