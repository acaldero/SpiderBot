

 #ifndef L_FINGER_COMMAND_H
 #define L_FINGER_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_finger/l_finger_log.h"


   /* ... Functions / Funciones ......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_FINGER_COMMAND_Connect      ( INOUT  t_sock          *sd,
                                                IN     T_CHAR          *host,
                                                IN     T_INT            port,
                                                INOUT  t_finger_response  *fingerr ) ;
      /* - */
      /* - */

      T_BOOL    L_FINGER_COMMAND_Close       ( INOUT  t_sock          *sd,
                                               INOUT  t_finger_response  *fingerr ) ;
      /* - */
      /* - */
  
  
      /*  FINGER Commands  *
       * -------------- */
      T_BOOL    L_FINGER_COMMAND_Request     ( INOUT  t_sock          *sd,
                                               IN     T_CHAR          *request,
                                               INOUT  t_finger_response  *fingerr ) ;
      /* - */
      /* - */
  
      T_BOOL    L_FINGER_COMMAND_finger      ( INOUT  t_sock          *sd,
                                               IN     T_CHAR          *user,
                                               INOUT  t_finger_response  *fingerr ) ;
      /* - */
      /* - */
  

  /* ... Inline / Macros ............................................... */

      #define  L_FINGER_COMMAND_Read(sd,buff,buffLen)              \
               X_SOCKET_Read((sd),(buff),(buffLen))

      #define  L_FINGER_COMMAND_ReadLine(sd,buff,buffLen)          \
               X_SOCKET_ReadLine((sd),(buff),(buffLen))

      #define  L_FINGER_COMMAND_WriteString(sd,reqString)          \
               X_SOCKET_Write((sd),(reqString),strlen((reqString)))


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

