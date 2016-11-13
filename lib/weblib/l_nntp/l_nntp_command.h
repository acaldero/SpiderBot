

 #ifndef L_NNTP_COMMAND_H
 #define L_NNTP_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_nntp/l_nntp_log.h"


   /* ... Functions / Funciones ......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_NNTP_COMMAND_Connect      ( INOUT  t_sock     *sd,
                                              IN     T_CHAR     *host, 
                                              IN     T_INT       port,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_Close        ( INOUT  t_sock     *sd,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */



      /*  NNTP Commands  *
       * --------------- */
      T_BOOL    L_NNTP_COMMAND_Request      ( INOUT  t_sock            *sd,
                                              IN     T_CHAR            *request,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_list         ( INOUT  t_sock     *sd,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_group        ( INOUT  t_sock     *sd,
                                              IN     T_CHAR     *group,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_listgroup    ( INOUT  t_sock     *sd,
                                              IN     T_CHAR            *group,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_article      ( INOUT  t_sock     *sd,
                                              IN     T_CHAR     *article,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_stat         ( INOUT  t_sock     *sd,
                                              IN     T_CHAR     *article,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_head         ( INOUT  t_sock     *sd,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_body         ( INOUT  t_sock     *sd,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_mode_reader  ( INOUT  t_sock     *sd,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */

      T_BOOL    L_NNTP_COMMAND_quit         ( INOUT  t_sock     *sd,
                                              INOUT  t_nntp_response   *nntpr ) ;
      /* - */
      /* - */



  /* ... Inline / Macros ............................................... */

      #define  L_NNTP_COMMAND_WriteString(sd,reqString)          \
               X_SOCKET_Write((sd),(reqString),strlen((reqString)))

      #define  L_NNTP_COMMAND_Read(sd,buff,buffLen)              \
               X_SOCKET_Read((sd),(buff),(buffLen))

      #define  L_NNTP_COMMAND_ReadLine(sd,buff,buffLen)          \
               X_SOCKET_ReadLine((sd),(buff),(buffLen))

      /*  NNTP Commands  *
       * --------------- */
      #define  L_NNTP_COMMAND_list(sd,nntpr)                     \
               L_NNTP_COMMAND_Request(sd,"LIST\n",nntpr)

      #define  L_NNTP_COMMAND_head(sd,nntpr)                     \
               L_NNTP_COMMAND_Request(sd,"HEAD\n",nntpr)

      #define  L_NNTP_COMMAND_body(sd,nntpr)                     \
               L_NNTP_COMMAND_Request(sd,"BODY\n",nntpr)

      #define  L_NNTP_COMMAND_mode_reader(sd,nntpr)              \
               L_NNTP_COMMAND_Request(sd,"MODE READER\r\n",nntpr)

      #define  L_NNTP_COMMAND_quit(sd,nntpr)                     \
               L_NNTP_COMMAND_Request(sd,"QUIT\n",nntpr)


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

