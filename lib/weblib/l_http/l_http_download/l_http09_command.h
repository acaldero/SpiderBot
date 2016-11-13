

 #ifndef L_HTTP09_COMMAND_H
 #define L_HTTP09_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_http/l_http_response.h"


   /* ... Functions / Funciones ......................................... */

      /*  conection  *
       * ----------- */
      T_BOOL    L_HTTP09_COMMAND_Connect ( INOUT  t_sock       *sd,
                                           IN     T_CHAR       *host, 
                                           IN     T_INT         port ) ;
      /* - */
      /* - */
 
      T_BOOL    L_HTTP09_COMMAND_Close   ( INOUT  t_sock       *sd ) ;
      /* - */
      /* - */
 

      /*  commands  *
       * ---------- */
      T_BOOL    L_HTTP09_COMMAND_Request ( INOUT  t_sock       *sd,
                                           IN     T_CHAR       *reqString ) ;
      /* - */
      /* - */
 
      T_INT     L_HTTP09_COMMAND_Read    ( INOUT  t_sock       *sd,
                                           IN     T_CHAR       *buff,
                                           IN     T_INT         buffLen ) ;
      /* - */
      /* - */
 
      T_INT     L_HTTP09_COMMAND_TryRead ( INOUT  t_sock       *sd,
                                           IN     T_CHAR       *buff,
                                           IN     T_INT         buffLen,
                                           IN     T_U_LONG      seconds ) ;
      /* - */
      /* - */
 
      T_BOOL    L_HTTP09_COMMAND_GET     ( INOUT  t_sock       *sd,
                                           IN     T_CHAR       *url,
                                           IN     T_CHAR       *HttpVer,
                                           IN     T_CHAR       *clientName ) ;
      /* - */
      /* - */
 


   /* ... Inline / Macros ............................................... */

      #define  L_HTTP09_COMMAND_Connect(sd,machine,port)           \
               X_SOCKET_Connect((sd),(machine),(port))

      #define  L_HTTP09_COMMAND_Close(sd)                          \
               X_SOCKET_Close((sd))

      #define  L_HTTP09_COMMAND_Request(sd,reqString)              \
               X_SOCKET_Write((sd),(reqString),strlen((reqString)))

      #define  L_HTTP09_COMMAND_Read(sd,buff,buffLen)              \
               X_SOCKET_Read((sd),(buff),(buffLen))

      #define  L_HTTP09_COMMAND_TryRead(sd,buff,buffLen,seconds)   \
               X_SOCKET_TryRead((sd),(buff),(buffLen),(seconds))


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

