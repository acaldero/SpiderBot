

 #ifndef C_SYSTEM_H
 #define C_SYSTEM_H


  /* ... Includes .............................................*/


         #include <stdio.h>
         #include <errno.h>
         #include <ctype.h>
         #include <string.h>
         #include <stdarg.h>
         #include <stdlib.h>
         #include <dirent.h>
         #include <signal.h>
         #include <limits.h>
         #include <fcntl.h>
         #include <pwd.h>
         #include <math.h>
         #include <sys/types.h>
         #include <sys/wait.h>

         #include <netdb.h>
         #include <sys/socket.h>
         #include <netinet/in.h>


     #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
         #include <unistd.h>
         #include <malloc.h>
         #include <strings.h>
         #include <fcntl.h>
         #include <termio.h>
         #include <sys/stat.h>
         #include <sys/resource.h>
         #include <sys/time.h>
         #include <sys/ioctl.h>
      #endif
      #if defined(__MSDOS__)
          #include <graphics.h>
          #include <conio.h>
          #include <io.h>
          #include <dos.h>
          #include <alloc.h>
          #include <process.h>
          #include <sys\stat.h>
          #include <time.h>
      #endif

      #if defined(HAVE_PTHREAD_H)
          #include <pthread.h>
      #endif

      #if defined(HAVE_SYS_TTOLD_H)
          #include <sys/ttold.h>
      #endif

      #if defined(HAVE_VALUES_H)
          #include <values.h>
      #endif

      #if defined(HAVE_INET_TCP_H)
          #include <inet/tcp.h>
      #endif

      #if defined(HAVE_NETINET_TCP_H)
          #include <netinet/tcp.h>
      #endif


  /* .......................................................... */


#endif

