

#ifndef L_SOCKET_H
#define L_SOCKET_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


  /* ... Includes / Inclusiones ...............................*/

     #include "corelib/l_basic/c_basic.h"
     #include "corelib/l_debug/l_debug.h"
     #include "corelib/l_alloc/x_alloc.h"
     #include "corelib/l_string/x_string.h"
     #include "corelib/l_file/x_print.h"


  /* ... Const / Constantes ...................................*/
 
     /* ... data size ... */
     #define c_SOCKADDR_IN    (sizeof(struct sockaddr_in))


     /* ... address check level ... */
     #define c_CMPA_ALL         (1 || 2 || 4 || 8)

     #define c_CMPA_HOST        (1)
     #define c_CMPA_DPT         (2)
     #define c_CMPA_ORG         (4)
     #define c_CMPA_COUNTRY     (8)


  /* ... Functions / Funciones ................................*/

      /*  Address Management  *
       * -------------------- */
      T_BOOL   L_SOCKET_local2address    ( OUT   struct sockaddr_in  *sa,
                                           IN    T_INT                port ) ;
      T_BOOL   L_SOCKET_ln2address       ( OUT   struct sockaddr_in  *sa,
                                           IN    T_CHAR              *hostName,
                                           IN    T_INT                port ) ;
      T_BOOL   L_SOCKET_env2address      ( OUT   struct sockaddr_in  *sa,
                                           IN    T_CHAR              *hostName,
                                           IN    T_CHAR              *port ) ;
      T_BOOL   L_SOCKET_getSockAddr      ( IN    struct sockaddr_in  *sa,
                                           OUT   int                 *sd ) ;
      T_BOOL   L_SOCKET_cmpHostName      ( IN    T_CHAR              *sa1,
                                           IN    T_CHAR              *sa2,
                                           IN    T_INT                level,
                                           OUT   T_BOOL              *equals ) ;
      T_BOOL   L_SOCKET_cmpAddr          ( IN    T_CHAR              *sa1,
                                           IN    T_CHAR              *sa2,
                                           IN    T_INT                level,
                                           OUT   T_BOOL              *equals ) ;


      /*  Socket Connection Oriented  *
       * ---------------------------- */

      /* ... socket live ... */
      T_BOOL   L_SOCKET_beeper          ( OUT    int                 *sd,
                                          IN     struct sockaddr_in  *sa ) ;
      T_BOOL   L_SOCKET_connect         ( OUT    int                 *sd,
                                          IN     struct sockaddr_in  *sa ) ;
      T_BOOL   L_SOCKET_accept          ( OUT    int                 *sd,
                                          OUT    struct sockaddr_in  *sa,
                                          IN     int                  beeper ) ;
      T_BOOL   L_SOCKET_unplug          ( INOUT  int                  socket ) ;
      T_BOOL   L_SOCKET_socketBindTo    ( OUT    int                 *sd,
                                          IN     struct sockaddr_in  *sa ) ;


      /* ... data movement ... */
      T_INT    L_SOCKET_read             ( INOUT    int      socket,
                                           OUT      T_CHAR  *buffer,
                                           IN       T_INT    size ) ;
      T_INT    L_SOCKET_write            ( INOUT    int      socket,
                                           IN       T_CHAR  *buffer,
                                           IN       T_INT    size ) ;
      T_INT    L_SOCKET_writeRead        ( INOUT    int      socket,
                                           INOUT    T_CHAR  *buffer,
                                           INOUT    T_INT    size ) ;
      T_INT    L_SOCKET_fullRead         ( INOUT    int      socket,
                                           INOUT    T_CHAR  *buffer,
                                           INOUT    T_INT    size ) ;


      /*  Socket NOT Connection Oriented  *
       * -------------------------------- */

      /* ... socket live ... */
      T_BOOL   L_SOCKET_creatSocket      ( INOUT  int     *sockout ) ;
      T_BOOL   L_SOCKET_close            ( INOUT  int      socket ) ;

      /* ... data movement ... */
      T_BOOL   L_SOCKET_sendMsg          ( INOUT  int                 sockdest,
                                           IN     void               *msg,
                                           IN     T_INT               msgLen,
                                           IN     struct sockaddr_in *raddr ) ;
      T_BOOL   L_SOCKET_recvMsg          ( INOUT  int                 sockorig,
                                           IN     void               *msg,
                                           IN     T_INT               msgLen,
                                           IN     struct sockaddr_in *raddr ) ;
      /* - Rellena los 'msgLen' primeros caracteres de 'msg',
           leyendo del socket 'sockorig'. Ademas, en 'raddr'
           se rellena con la direccion de quien nos han mandado
           el mensaje. Importante recordar que si hay mas bytes
           que no caben en 'msg', estos se perderan. */
      /* - Fill first 'msgLen' characters that are reading, 
           from socket 'sockorig'. In 'raddr' we will found
           origin's address. Remember that if there are more
           bytes to read, these will be delete.  */


  /* ... Inline / Macros ...................................... */

     #define  L_SOCKET_readAvailable(socket,buffer,size)           \
              read((socket),(buffer),(size))

     #define  L_SOCKET_MAC_writeRead(socket,buffer,size)           \
              (                                                    \
                (L_SOCKET_write((socket),(buffer),(size)) < 0) ?   \
                (-1)                                               \
                :                                                  \
                (L_SOCKET_read((socket),(buffer),(size)))          \
              )


  /* ..........................................................*/


 #ifdef  __cplusplus
    }
 #endif

#endif  /* L_SOCKET_H */

