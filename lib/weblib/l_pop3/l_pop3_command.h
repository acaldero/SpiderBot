

 #ifndef L_POP3_COMMAND_H
 #define L_POP3_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_pop3/l_pop3_log.h"


   /* ... Functions / Funciones ......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_POP3_COMMAND_Connect     ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *host, 
                                             IN     T_INT             port,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_Close       ( INOUT  t_sock           *sd,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */


      /*  POP3 Commands  *
       * --------------- */
      T_BOOL    L_POP3_COMMAND_Request     ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *request,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_user        ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *user,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_pass        ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *pass,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_stat        ( INOUT  t_sock           *sd,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_list        ( INOUT  t_sock           *sd,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_noop        ( INOUT  t_sock           *sd,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_retr        ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *msgid,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */

      T_BOOL    L_POP3_COMMAND_quit        ( INOUT  t_sock           *sd,
                                             INOUT  t_pop3_response  *pop3r ) ;
      /* - */
      /* - */



  /* ... Inline / Macros ............................................... */

      #define  L_POP3_COMMAND_WriteString(sd,reqString)              \
               X_SOCKET_Write((sd),(reqString),strlen((reqString)))

      #define  L_POP3_COMMAND_Read(sd,buff,buffLen)              \
               X_SOCKET_Read((sd),(buff),(buffLen))

      #define  L_POP3_COMMAND_ReadLine(sd,buff,buffLen)          \
               X_SOCKET_ReadLine((sd),(buff),(buffLen))


      /*  POP3 Commands  *
       * --------------- */
      #define  L_POP3_COMMAND_stat(sd,pop3r)                     \
               L_POP3_COMMAND_Request(sd,"STAT\n",pop3r)

      #define  L_POP3_COMMAND_list(sd,pop3r)                     \
               L_POP3_COMMAND_Request(sd,"LIST\n",pop3r)

      #define  L_POP3_COMMAND_noop(sd,pop3r)                     \
               L_POP3_COMMAND_Request(sd,"NOOP\n",pop3r)

      #define  L_POP3_COMMAND_quit(sd,pop3r)                     \
               L_POP3_COMMAND_Request(sd,"QUIT\n",pop3r)


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

