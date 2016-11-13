

 #ifndef I_IOCTL_H
 #define I_IOCTL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


    /* ... Functions / Funciones ......................................... */

      /* --- Keybd con ioctl --- */
      T_CHAR I_IOCTL_getch   ( void ) ;
      T_BOOL I_IOCTL_nbgetch ( INOUT T_CHAR *ch ) ;


  /* ..................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

