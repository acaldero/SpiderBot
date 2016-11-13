/* ........................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * ........................................................................ */



   /* ... Includes .................................................... */

      #include "corelib/l_net/x_socket.h"


   /* ... Funciones ................................................... */

      T_BOOL   X_SOCKET_CreatSocket      ( INOUT  t_sock    *sockout,
                                           IN     T_CHAR    *computer,
                                           IN     T_U_SHORT  port )       
      {
        T_BOOL ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sockout) ;
        NULL__SET_ERROR__RET_FALSE(computer) ;

        ok = L_SOCKET_ln2address(&(sockout->addr),computer,port) ;
        FALSE_RET_FALSE(ok) ;
        sockout->socket = socket( PF_INET,
                                  (sockout->type),
                                  (sockout->protocolo) ) ;
        if (sockout->socket < 0)
           {
             perror("At socket...") ;
             return FALSE ;
           }
        sockout->fsocket = fdopen(sockout->socket,"r") ;
        NULL_RET_FALSE(sockout->fsocket) ;
        setbuf(sockout->fsocket,NULL) ;
        return TRUE ;
      }

      T_BOOL    X_SOCKET_Connect     ( INOUT  t_sock     *sd,
                                       IN     T_CHAR     *maquina, 
                                       IN     T_INT       puerto )
      {
        size_t  longitud ;
        T_INT   status ;
        T_BOOL  ok ;
       
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(maquina) ;

        sd->socket    = -1 ; 
        sd->type      = SOCK_STREAM ;
        sd->protocolo = 0 ; 
        ok = X_SOCKET_CreatSocket(sd,maquina,puerto) ;
        FALSE_RET_FALSE(ok) ;
        longitud = sizeof(sd->addr) ;
        do
        {
          status = connect( (sd->socket),
                            (struct sockaddr *)&(sd->addr),
                            longitud ) ;
        }
        while ( (status<0) && (errno==EINTR) ) ;
        if (status < 0)
           {
             perror("At connect...");
             return FALSE ;
           }
        return TRUE ;
      }
  
      T_BOOL    X_SOCKET_Write       ( INOUT  t_sock       *sd,
                                       IN     T_CHAR       *buff,
                                       IN     T_INT         buffLen )
      {
        T_INT  result ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(buff) ;

        do
        {
          result = write(sd->socket,buff,buffLen) ;
        }
        while ( (result<0) && (errno==EINTR) ) ;
        if (result < 0) 
           {
             perror("At write...");
             return FALSE ;
           }
        return TRUE ;
      }
  
      T_INT     X_SOCKET_Read        ( INOUT  t_sock     *sd,
                                       IN     T_CHAR     *buff,
                                       IN     T_INT       buffLen )
      {
        T_INT  result ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(buff) ;

        do
        {
          result = read(sd->socket,buff,buffLen) ;
        }
        while ( (result<0) && (errno==EINTR) ) ;
        if (result < 0) 
           {
             perror("At read...") ;
           }
        return result ;
      }
  
      T_INT     X_SOCKET_TryRead     ( INOUT  t_sock     *sd,
                                       IN     T_CHAR     *buff,
                                       IN     T_INT       buffLen,
                                       IN     T_U_LONG    seconds )
      {
        struct timeval tv ;
        time_t   ti, tf ;
        fd_set   rfds ;
        T_INT    result ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(buff) ;

        FD_ZERO(&rfds);
        FD_SET(sd->socket, &rfds);
        tv.tv_sec  = seconds ;
        tv.tv_usec = 10 ;
        time(&ti) ;
        do
        {
          result = select(1, &rfds, NULL, NULL, &tv) ;
          time(&tf) ;
          if (result == 0) 
             {
               if ( difftime(tf,ti) > (double)seconds )
                    return -1 ;
             }
        }
        while ( (result<0) && (errno==EINTR) ) ;
        if (result < 0) 
           {
             perror("At select...") ;
             return result ;
           }
        return X_SOCKET_Read(sd,buff,buffLen) ;
      }
  
      T_BOOL    X_SOCKET_ReadLine    ( INOUT  t_sock     *sd,
                                       IN     T_CHAR     *buff,
                                       IN     T_INT       buffLen )
      {
        T_INT  i ;
        T_INT  result ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(buff) ;

        X_ALLOC_MemSet(buff,0,buffLen) ;
        i = 0 ;
        do
        {
          result = read(sd->socket,&(buff[i]),1) ;
          i++ ;
        } while (
                  (i < buffLen)
                        &&
                  (buff[i-1] != '\n')
                        &&
                  (buff[i-1] != EOF)
                        &&
                  (result > 0)
                ) ;
        return (result <= 0) ;
      }


  /* .................................................................... */

