

 #ifndef L_HTTP11_COMMAND_H
 #define L_HTTP11_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlstr.h"
      #include "weblib/l_encode/l_base64.h"
      #include "weblib/l_http/l_http_response.h"


   /* ... Functions / Funciones ......................................... */

      /*  conection  *
       * ----------- */
      T_BOOL    L_HTTP11_COMMAND_Connect ( INOUT  t_sock         *sd,
                                           IN     T_CHAR         *machine, 
                                           IN     T_INT           port ) ;
      /* - */
      /* - */
 
      T_BOOL    L_HTTP11_COMMAND_Close   ( INOUT  t_sock         *sd ) ;
      /* - */
      /* - */
 

      /*  commands  *
       * ---------- */
      T_BOOL    L_HTTP11_COMMAND_HEAD    ( INOUT  t_sock     *sd,
                                           IN     t_url      *url,
                                           IN     T_CHAR     *clientName,
                                           IN     T_BOOL      acceptFullUrl,
                                           IN     T_BOOL      acceptHost ) ;
      /* - */
      /* - */
 
      T_BOOL    L_HTTP11_COMMAND_GET     ( INOUT  t_sock     *sd,
                                           IN     t_url      *url,
                                           IN     T_CHAR     *clientName,
                                           IN     T_CHAR     *ident,
                                           IN     T_BOOL      acceptFullUrl,
                                           IN     T_BOOL      acceptHost ) ;
      /* - */
      /* - */
 
      T_BOOL    L_HTTP11_COMMAND_Request ( INOUT  t_sock         *sd,
                                           IN     T_CHAR         *reqString ) ;
      /* - */
      /* - */
 
      T_INT     L_HTTP11_COMMAND_Read    ( INOUT  t_sock         *sd,
                                           IN     T_CHAR         *buff,
                                           IN     T_INT           buffLen ) ;
      /* - */
      /* - */
 
      T_INT     L_HTTP11_COMMAND_TryRead ( INOUT  t_sock         *sd,
                                           IN     T_CHAR         *buff,
                                           IN     T_INT           buffLen,
                                           IN     T_U_LONG        seconds ) ;
      /* - */
      /* - */
 


   /* ... Inline / Macros ............................................... */

      #define  L_HTTP11_COMMAND_Connect(sd,machine,port)           \
               X_SOCKET_Connect((sd),(machine),(port))

      #define  L_HTTP11_COMMAND_Request(sd,reqString)              \
               X_SOCKET_Write((sd),(reqString),strlen((reqString)))

      #define  L_HTTP11_COMMAND_Close(sd)                          \
               X_SOCKET_Close((sd))

      #define  L_HTTP11_COMMAND_Read(sd,buff,buffLen)              \
               X_SOCKET_Read((sd),(buff),(buffLen))

      #define  L_HTTP11_COMMAND_TryRead(sd,buff,buffLen,seconds)   \
               X_SOCKET_TryRead((sd),(buff),(buffLen),(seconds))


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

