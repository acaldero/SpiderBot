

 #ifndef X_SOCKET_H
 #define X_SOCKET_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_net/l_socket.h"


   /* ... Types / Tipos ................................................. */

      typedef struct
      {
        T_INT                 socket ;
        FILE                 *fsocket ;
        struct sockaddr_in    addr ;
        T_INT                 type ;
        T_INT                 protocolo ;
      } t_sock ;


   /* ... Consts / Constantes ........................................... */

      #define  c_SOCK   sizeof(t_sock)


   /* ... Functions / Funciones ......................................... */

      /*  Socket  *
       * -------- */
      T_BOOL  X_SOCKET_CreatSocket          ( INOUT  t_sock    *sockout,
                                              IN     T_CHAR    *computer,
                                              IN     T_U_SHORT  port ) ;
      T_BOOL  X_SOCKET_CreatSocketBinded    ( INOUT  t_sock    *sockin ) ;
      T_BOOL  X_SOCKET_Close                ( INOUT  t_sock    *s_in ) ;
      T_BOOL  X_SOCKET_Connect              ( INOUT  t_sock    *sd,
                                              IN     T_CHAR    *maquina, 
                                              IN     T_INT      puerto ) ;

      /*  Read/Write  *
       * ------------ */
      T_BOOL  X_SOCKET_Write                ( INOUT  t_sock    *sd,
                                              IN     T_CHAR    *buff,
                                              IN     T_INT      buffLen ) ;
      T_INT   X_SOCKET_Read                 ( INOUT  t_sock    *sd,
                                              IN     T_CHAR    *buff,
                                              IN     T_INT      buffLen ) ;
      T_INT   X_SOCKET_TryRead              ( INOUT  t_sock    *sd,
                                              IN     T_CHAR    *buff,
                                              IN     T_INT      buffLen,
                                              IN     T_U_LONG   seconds ) ;
      T_BOOL  X_SOCKET_ReadLine             ( INOUT  t_sock     *sd,
                                              IN     T_CHAR     *buff,
                                              IN     T_INT       buffLen ) ;


   /* ... Inline / Macros ...................................... */

      #define  X_SOCKET_CreatSocketBinded(sd)     \
               L_SOCKET_beeper( &((sd)->socket),&((sd)->addr) )

      #define  X_SOCKET_Close(sd)                 \
               close( (sd)->socket )

  
   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

