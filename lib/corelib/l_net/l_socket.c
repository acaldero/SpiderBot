/* ....................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 * See documentation for more information.
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * .................................................................... */



   /* ... Includes .................................................... */

      #include "corelib/l_net/l_socket.h"


   /* ... Funciones ................................................... */

      /*  Address management *
       * ------------------- */
      T_BOOL   L_SOCKET_getSockAddr      ( IN    struct sockaddr_in  *sa,
                                           OUT   int                 *sd )
      {
        #define MACHINENAME_SIZE 1024

        char  *machineName ;
        int    resultado ;
        int    salen ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sa) ;
        NULL__SET_ERROR__RET_FALSE(sd) ;

        salen = c_SOCKADDR_IN ;
        machineName = X_ALLOC_Malloc(MACHINENAME_SIZE) ;
        NULL_RET_FALSE(machineName) ;
        resultado = getsockname((*sd),(struct sockaddr *)(sa),&salen) ;
        if (resultado < 0)
           {
             close((*sd)) ;
             perror("At getsockname...") ;
             X_ALLOC_Free( (void **) &(machineName) ) ;
             return FALSE ;
           }
        resultado = gethostname(machineName,MACHINENAME_SIZE) ;
        if (resultado < 0)
           {
             close((*sd)) ;
             perror("At gethostname...") ;
             X_ALLOC_Free( (void **) &(machineName) ) ;
             return FALSE ;
           }
        L_SOCKET_ln2address(sa,
                            machineName,
                            sa->sin_port) ;
        X_ALLOC_Free( (void **) &(machineName) ) ;
        return TRUE ;
      }

      T_BOOL   L_SOCKET_local2address    ( IN    struct sockaddr_in  *sa,
                                           IN    T_INT                port )
      {
        NULL__SET_ERROR__RET_FALSE(sa) ;
        sa->sin_family      = AF_INET ;
        sa->sin_port        = port ;
        sa->sin_addr.s_addr = INADDR_ANY ;
        return TRUE ;
      }

      T_BOOL   L_SOCKET_ln2address       ( IN    struct sockaddr_in  *sa,
                                           IN    T_CHAR              *hostName,
                                           IN    T_INT                port )
      {
        struct hostent     *hostInfo ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sa) ;
        NULL__SET_ERROR__RET_FALSE(hostName) ;

        hostInfo = gethostbyname(hostName);
        if (hostInfo == NULL)
           {
             X_PRINT_printf( "Sorry, I can not find host called '%s'\n", 
                             hostName) ;
             return FALSE ;
           }
        sa->sin_family  = AF_INET ;
        sa->sin_port    = port ;
        memcpy(&(sa->sin_addr), 
               (hostInfo->h_addr_list[0]), 
                hostInfo->h_length) ;
        return TRUE ;
      }

      T_BOOL   L_SOCKET_env2address      ( IN    struct sockaddr_in  *sa,
                                           IN    T_CHAR              *hostName,
                                           IN    T_CHAR              *port )
      {
        T_INT   aux_port ;
        T_CHAR *aux_host ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(hostName) ;
        NULL__SET_ERROR__RET_FALSE(port) ;

        if (getenv(hostName) == NULL)
           {
             X_PRINT_printf( "%s must be in enviroment\n",
                             hostName) ;
             return FALSE ;
           }
        if (getenv(port) == NULL)
           {
             X_PRINT_printf( "%s must be in enviroment\n",
                             port ) ;
             return FALSE ;
           }
        aux_port = atoi(getenv(port)) ;
        aux_host = getenv(hostName) ;
        return L_SOCKET_ln2address(sa,aux_host,aux_port) ;
      }

      T_BOOL   L_SOCKET_cmpHostName      ( IN    T_CHAR              *ha1,
                                           IN    T_CHAR              *ha2,
                                           IN    T_INT                level,
                                           OUT   T_BOOL              *equals )
      {
        T_CHAR  *pcha1, *pcha2 ;
        T_CHAR  *pch1, *pch2 ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(ha1) ;
        NULL__SET_ERROR__RET_FALSE(ha2) ;
        NULL__SET_ERROR__RET_FALSE(equals) ;

        /* ... same address ... */
        if (X_STRING_Equal(ha1,ha2) == TRUE)
           {
             (*equals) = TRUE ;
             return TRUE ;
           }

        /* ... check address ... */
        (*equals) = TRUE ;
        pcha1 = ha1 + strlen(ha1) ;
        pcha2 = ha2 + strlen(ha2) ;
        pch1 = strrchr(ha1,'.') ;
        pch2 = strrchr(ha2,'.') ;
        if ( (level & c_CMPA_COUNTRY)  != 0)
           {
             if ( (pch1 == NULL) || (pch2 == NULL))
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
             if (strncmp(pch1,pch2,abs(pch1-pcha1)) != 0)
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
           }

        pcha1 = pch1 ;
        pcha2 = pch2 ;
        if (pch1 != NULL)
           {
             pcha1[0] = '\0' ;
             pch1 = strrchr(ha1,'.') ;
             pcha1[0] = '.' ;
           }
        if (pch2 != NULL)
           {
             pcha2[0] = '\0' ;
             pch2 = strrchr(ha2,'.') ;
             pcha2[0] = '.' ;
           }
        if ( (level & c_CMPA_ORG)  != 0)
           {
             if ( (pch1 == NULL) || (pch2 == NULL))
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
             if (strncmp(pch1,pch2,abs(pch1-pcha1)) != 0)
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
           }

        pcha1 = pch1 ;
        pcha2 = pch2 ;
        if (pch1 != NULL)
           {
             pcha1[0] = '\0' ;
             pch1 = strrchr(ha1,'.') ;
             pcha1[0] = '.' ;
           }
        if (pch2 != NULL)
           {
             pcha2[0] = '\0' ;
             pch2 = strrchr(ha2,'.') ;
             pcha2[0] = '.' ;
           }
        if ( (level & c_CMPA_DPT)  != 0)
           {
             if ( (pch1 == NULL) || (pch2 == NULL))
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
             if (strncmp(pch1,pch2,abs(pch1-pcha1)) != 0)
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
           }

        pcha1 = pch1 ;
        pcha2 = pch2 ;
        if (pch1 != NULL)
           {
             pcha1[0] = '\0' ;
             pch1 = strrchr(ha1,'.') ;
             pcha1[0] = '.' ;
           }
        if (pch2 != NULL)
           {
             pcha2[0] = '\0' ;
             pch2 = strrchr(ha2,'.') ;
             pcha2[0] = '.' ;
           }
        if ( (level & c_CMPA_HOST) != 0)
           {
             if ( (pch1 == NULL) || (pch2 == NULL))
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
             if (strncmp(pch1,pch2,abs(pch1-pcha1)) != 0)
                {
                  (*equals) = FALSE ;
                  return TRUE ;
                }
           }

        return TRUE ;
      }

      T_BOOL   L_SOCKET_cmpAddr          ( IN    T_CHAR              *ha1,
                                           IN    T_CHAR              *ha2,
                                           IN    T_INT                level,
                                           OUT   T_BOOL              *equals )
      {
        struct hostent   *hostInfo1, *hostInfo2 ;
        struct sockaddr   sa1, sa2 ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(ha1) ;
        NULL__SET_ERROR__RET_FALSE(ha2) ;
        NULL__SET_ERROR__RET_FALSE(equals) ;

        /* ... same address ... */
        if (X_STRING_Equal(ha1,ha2) == TRUE)
           {
             (*equals) = TRUE ;
             return TRUE ;
           }

        /* ... translate address ... */
        (*equals) = FALSE ;
        hostInfo1 = gethostbyname(ha1) ;
        if (hostInfo1 == NULL)
           {
             X_PRINT_printf( "Sorry, I can not find host called '%s'\n", 
                             ha1 ) ;
             return FALSE ;
           }
        memcpy( &(((struct sockaddr_in *)&sa1)->sin_addr), 
                (hostInfo1->h_addr_list[0]), 
                 hostInfo1->h_length ) ;
        hostInfo2 = gethostbyname(ha2) ;
        if (hostInfo2 == NULL)
           {
             X_PRINT_printf( "Sorry, I can not find host called '%s'\n", 
                             ha2 ) ;
             return FALSE ;
           }
        memcpy( &(((struct sockaddr_in *)&sa2)->sin_addr), 
                (hostInfo2->h_addr_list[0]), 
                 hostInfo2->h_length ) ;

        /* ... check address ... */
        (*equals) = TRUE ;
        if ( (level & c_CMPA_HOST) != 0)
           {
             if (sa1.sa_data[5] != sa2.sa_data[5])
                 (*equals) = FALSE ;
           }
        if ( (level & c_CMPA_DPT)  != 0)
           {
             if (sa1.sa_data[4] != sa2.sa_data[4])
                 (*equals) = FALSE ;
           }
        if ( (level & c_CMPA_ORG)  != 0)
           {
             if (sa1.sa_data[3] != sa2.sa_data[3])
                 (*equals) = FALSE ;
           }
        if ( (level & c_CMPA_COUNTRY)  != 0)
           {
             if (sa1.sa_data[2] != sa2.sa_data[2])
                 (*equals) = FALSE ;
           }

        return TRUE ;
      }


      /*  Live Cycle Connection Oriented Socket  *
       * --------------------------------------- */
      T_BOOL   L_SOCKET_setDefaultOptForStream  ( INOUT    int  socket )
      {
        int  val ;
        int  ret ;
        long int_size ;

        val      = 1 ;
        int_size = c_INT ;
        /* ... IPPROTO_TCP/TCP_NODELAY ... */
        ret = setsockopt(socket,
                         IPPROTO_TCP,
                         TCP_NODELAY,
                         (char *)&val,
                         c_INT) ;
        if (ret < 0)
           {
             perror("At setsockopt...") ;
             return FALSE ;
           }
        /* ... SOL_SOCKET/SO_REUSEADDR ... */
        ret = setsockopt(socket,
                         SOL_SOCKET,
                         SO_REUSEADDR,
                         (char *)&val,
                         c_INT) ;
        if (ret < 0)
           {
             perror("At setsockopt...") ;
             return FALSE ;
           }
#if (0)
        /* ... IPPROTO_TCP/TCP_MAXSEG ... */
        ret = getsockopt(socket,
                         IPPROTO_TCP,
                         TCP_MAXSEG,
                         (char *)&val, 
                         &int_size);
        if (ret < 0)
           {
             perror("At getsockopt...") ;
             return FALSE ;
           }
        /* ... SOL_SOCKET/SO_RCVBUF ... */
        val = (128 * 1024);
        ret =  setsockopt(socket, 
                          SOL_SOCKET, 
                          SO_RCVBUF,
                          (char *)&val,
                          c_INT ) ;
        if (ret < 0)
           {
             perror("At setsockopt...") ;
             return FALSE ;
           }
        /* ... SOL_SOCKET/SO_SNDBUF ... */
        val = (128* 1024) ;
        ret =  setsockopt(socket, 
                          SOL_SOCKET, 
                          SO_SNDBUF, 
                          (char *)&val,
                          c_INT) ;
        if (ret < 0)
           {
             perror("At setsockopt...") ;
             return FALSE ;
           }
        L_DEBUG_MSG_printf(INFO,TRUE,
                           "MAX_SEG FOR %d = %d\n", 
                           socket, (128* 1024)) ;
#endif
        return TRUE ;
      }

        
      T_BOOL   L_SOCKET_socketBindTo     ( OUT   int                 *sd,
                                           IN    struct sockaddr_in  *sa )
      {
        int resultado ;

        (*sd) =  socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) ;
        if ((*sd) < 0)
           {
             perror("At socket...") ;
             return FALSE ;
           }
        L_SOCKET_setDefaultOptForStream((*sd)) ;
        resultado = bind( (*sd),
                          (struct sockaddr *)(sa),
                          c_SOCKADDR_IN ) ;
        if (resultado < 0)
           {
             close((*sd)) ;
             perror("At bind...") ;
             return FALSE ;
           }
        return TRUE ;
      }

      T_BOOL   L_SOCKET_beeper           ( OUT   int                 *sd,
                                           IN    struct sockaddr_in  *sa )
      {
        int    resultado ;
        T_BOOL ok ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(sa) ;

        ok = L_SOCKET_socketBindTo(sd,sa) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_SOCKET_getSockAddr(sa,sd) ;
        FALSE_RET_FALSE(ok) ;
        resultado = listen((*sd),SOMAXCONN) ;
        if (resultado < 0)
           {
             close((*sd));
             perror("At listen...") ;
             return FALSE ;
           }
        return TRUE ;
      }

      T_BOOL   L_SOCKET_connect          ( OUT   int                 *sd,
                                           IN    struct sockaddr_in  *sa )
      {
        int ret ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(sa) ;

        (*sd) = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) ;
        if ((*sd) < 0)
           {
             perror("At socket...") ;
             return FALSE ;
           }
        ret = connect((*sd),(struct sockaddr *)sa,c_SOCKADDR_IN) ;
        if (ret < 0)
           {
             close((*sd));
             perror("At connect...") ;
             return FALSE ;
           }
        return L_SOCKET_setDefaultOptForStream((*sd)) ;
      }

      T_BOOL   L_SOCKET_accept           ( OUT    int                 *sd,
                                           OUT    struct sockaddr_in  *sa,
                                           IN     int                  beeper )
      {
        int   size ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(sa) ;

        size  = c_SOCKADDR_IN ;
        (*sd) = accept(beeper,
                       (struct sockaddr *)(sa),
                       &size ) ;
        if ((*sd) < 0)
           {
             perror ("At accept...") ;
             return FALSE ;
           }
        return L_SOCKET_setDefaultOptForStream((*sd)) ;
      }

      T_BOOL   L_SOCKET_unplug           ( INOUT    int  socket )
      {
        shutdown(socket,2) ;
        close(socket) ;
        return TRUE ;
      }


      /*  Connection Oriented Socket Data Movement  *
       * ------------------------------------------ */
      T_INT    L_SOCKET_fullRead         ( INOUT    int      socket,
                                           INOUT    T_CHAR  *buffer,
                                           INOUT    T_INT    size )
      {
        int  ret ;
        int  size_aux ;

        ret = read(socket,buffer,size) ;
        size_aux = size - ret ;
        while (size_aux > 0)
        {
          if (ret < 0)
             {
               perror("At read...") ;
               return ret ;
             }
          if (ret == 0)
              return ret ;
          buffer   += ret ;
          ret = read(socket,buffer,size_aux) ;
          size_aux -= ret ;
        }
        return size ;
      }

      T_INT    L_SOCKET_write            ( INOUT    int      socket,
                                           INOUT    T_CHAR  *buffer,
                                           INOUT    T_INT    size )
      {
        int ret ;
        int size_aux ;

        ret = write(socket,buffer,size) ;
        size_aux = size - ret ;
        while (size_aux > 0)
        {
          if (ret < 0)
             {
               perror("At write...") ;
               return FALSE ;
             }
          buffer   += ret ;
          ret = write(socket,buffer,size_aux) ;
          size_aux -= ret ;
        }
        return size ;
      }

      T_INT    L_SOCKET_read             ( INOUT    int      socket,
                                           INOUT    T_CHAR  *buffer,
                                           INOUT    T_INT    size )
      {
        int ret, size2, i ;
        int chunk, chunkMod ;

        chunk    = size / SSIZE_MAX ;
        chunkMod = size % SSIZE_MAX ;
        if (chunkMod != 0)
           {
             ret = L_SOCKET_fullRead(socket,buffer,chunkMod) ;
             if (ret < 0)
                {
                  perror("At read...") ;
                  return ret ;
                }
             if (ret == 0)
                 return ret ;
           }
        size2 = ret ;
        for (i=0; i<chunk; i++)
           {
             ret = L_SOCKET_fullRead(socket,buffer,(int)SSIZE_MAX) ;
             if (ret < 0)
                {
                  perror("At read...") ;
                  return ret ;
                }
             if (ret == 0)
                 return ret ;
             size2 = size2 + ret ;
           }
        return size2 ;
      }

      T_INT    L_SOCKET_writeRead        ( INOUT    int      socket,
                                           INOUT    T_CHAR  *buffer,
                                           INOUT    T_INT    size )
      {
        T_INT  ret ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(buffer) ;
        ret = L_SOCKET_write(socket,buffer,size) ;
        if (ret < 0)
            return FALSE ;
        ret = L_SOCKET_read(socket,buffer,size) ;
        return ret ;
      }


      /*  Live Cycle NOT Connection Oriented Socket  *
       * ------------------------------------------- */
      T_BOOL   L_SOCKET_setDefaultOptForDgram   ( INOUT    int  socket )
      {
        int val ;
        int ret ;
        int int_size ;

        int_size = c_INT ;
        /* ... SOL_SOCKET/SO_RCVBUF ... */
        val = (128 * 1024);
        ret =  setsockopt(socket, 
                          SOL_SOCKET, 
                          SO_RCVBUF,
                          (char *)&val,
                          c_INT ) ;
        if (ret < 0)
           {
             perror("At setsockopt...") ;
             return FALSE ;
           }
        /* ... SOL_SOCKET/SO_SNDBUF ... */
        val = (128* 1024) ;
        ret =  setsockopt(socket, 
                          SOL_SOCKET, 
                          SO_SNDBUF, 
                          (char *)&val,
                          c_INT) ;
        if (ret < 0)
           {
             perror("At setsockopt...") ;
             return FALSE ;
           }
        return TRUE ;
      }

      T_BOOL   L_SOCKET_creatSocket      ( INOUT  int   *sockout )
      {
        (*sockout) = socket( PF_INET,
                             SOCK_DGRAM,
                             0 ) ;
        if ((*sockout) < 0)
           {
             perror("At socket...") ;
             return FALSE ;
           }
        return L_SOCKET_setDefaultOptForDgram((*sockout)) ;
      }

      T_BOOL   L_SOCKET_close            ( INOUT    int  socket )
      {
        close(socket) ;
        return TRUE ;
      }


      /*  NOT Connection Oriented Socket Data Movement  *
       * ---------------------------------------------- */
      T_BOOL  L_SOCKET_sendMsg        ( INOUT int                  sockdest,
                                        IN    void                *msg,
                                        IN    T_INT                msgLen,
                                        IN    struct sockaddr_in  *raddr )
      {
        T_INT resultado ;
   
        resultado = sendto ( sockdest,
                             msg, 
  			     msgLen,
                             0,
                             (struct sockaddr *)(raddr),
                             sizeof(struct sockaddr_in) ) ;
        if (resultado < 0)
           {
             perror("At sendto...") ;
             return FALSE ;
           }
        return TRUE ;
      }
  
      T_BOOL  L_SOCKET_recvMsg        ( INOUT int                  sockorig,
                                        IN    void                *msg,
                                        IN    T_INT                msgLen,
                                        IN    struct sockaddr_in  *raddr )
      {
        int   resultado ;
        int   longitud ;
   
        longitud = sizeof(struct sockaddr_in) ;
        resultado = recvfrom ( sockorig,
                               msg, 
  			       msgLen, 
  			       0,
                               (struct sockaddr *)(raddr),
                               &(longitud) ) ;
        if (resultado < 0)
           {
             perror("At receive...") ;
             return FALSE ;
           }
        return TRUE ;
      }


  /* .................................................................... */

