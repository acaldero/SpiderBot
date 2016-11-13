

 #ifndef L_BASE64_H
 #define L_BASE64_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_BASE64_encode     ( IN   unsigned char  *instr,
                                      IN   unsigned int    inlen,
                                      OUT  unsigned char **outstr,
                                      OUT  unsigned int   *outlen ) ;
      /* - */
      /* - */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

