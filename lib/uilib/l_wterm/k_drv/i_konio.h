

 #ifndef I_CONIO_H
 #define I_CONIO_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


    /* ... Include / Inclusion .......................................... */

       #include "corelib/l_basic/c_basic.h"


    /* ... Functions / Funciones ........................................ */

       /* --- Keybd en x_conio --- */
       T_CHAR I_CONIO_getch   ( void ) ;                                  
       T_BOOL I_CONIO_nbgetch ( INOUT T_CHAR *ch ) ;                      
                                                                        

    /* .................................................................. */


 #ifdef  __cplusplus
    }
 #endif

#endif

