

 #ifndef L_FTP_COMMAND_H
 #define L_FTP_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_ftp/l_ftp_log.h"


   /* ... Functions / Funciones ......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_FTP_COMMAND_Connect      ( INOUT  t_sock          *sd,
                                             IN     T_CHAR          *host,
                                             IN     T_INT            port,
                                             INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */

      T_BOOL    L_FTP_COMMAND_Close       ( INOUT  t_sock          *sd,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */
  
  
      /*  FTP Commands  *
       * -------------- */
      T_BOOL    L_FTP_COMMAND_Request     ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *request,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */
  
      T_BOOL    L_FTP_COMMAND_user        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *user,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */
  
      T_BOOL    L_FTP_COMMAND_pass        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *pass,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */
  
      T_BOOL    L_FTP_COMMAND_bin          ( INOUT  t_sock          *sd,
                                             INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */

      T_BOOL    L_FTP_COMMAND_asc          ( INOUT  t_sock          *sd,
                                             INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */

      T_BOOL    L_FTP_COMMAND_cwd         ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *setcwd,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */
  
      T_BOOL    L_FTP_COMMAND_port        ( INOUT  t_sock          *sd,
                                            INOUT  t_ftp_response  *ftpr,
                                            IN     t_sock          *insock ) ;
      /* - */
      /* - */
  
      T_BOOL    L_FTP_COMMAND_retr        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *file,
                                            INOUT  T_LONG          *total_to_read,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */

      T_BOOL    L_FTP_COMMAND_nlst        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *path,
                                            INOUT  t_ftp_response  *ftpr ) ;
      /* - */
      /* - */

      T_BOOL    L_FTP_COMMAND_pasv        ( INOUT  t_sock           *sd,
                                            INOUT  t_ftp_response   *ftpr,
                                            INOUT  struct sockaddr  *faddr ) ;
      /* - */
      /* - */


  /* ... Inline / Macros ............................................... */

      #define  L_FTP_COMMAND_Read(sd,buff,buffLen)              \
               X_SOCKET_Read((sd),(buff),(buffLen))

      #define  L_FTP_COMMAND_WriteString(sd,reqString)          \
               X_SOCKET_Write((sd),(reqString),strlen((reqString)))


      /*  FTP Commands  *
       * -------------- */
      #define  L_FTP_COMMAND_bin(sd,ftpr)                       \
               L_FTP_COMMAND_Request(sd,"TYPE I\n",ftpr)

      #define  L_FTP_COMMAND_asc(sd,ftpr)                       \
               L_FTP_COMMAND_Request(sd,"TYPE A\n",ftpr)


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

