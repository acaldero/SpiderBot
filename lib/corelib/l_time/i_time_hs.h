

 #ifndef I_TIME_HS_H
 #define I_TIME_HS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"


   /* ... Types / Tipos ................................................. */

 #if defined(__MSDOS__)
      #define  T_TIMEHS       struct time
      #define  T_ACCTIMEHS    double
 #else
      #define  T_TIMEHS       int
      #define  T_ACCTIMEHS    double
 #endif


   /* ... Const / Constantes ............................................ */

      #define  c_TIMEHS          sizeof(T_TIMEHS)
      #define  c_ACCTIMEHS       sizeof(T_ACCTIMEHS)

      #define  ACCTIMEHS_MAX       MAXDOUBLE
      #define  ACCTIMEHS_MIN       ((double)0)


   /* ... Functions / Funciones ......................................... */

      void         I_TIME_HS_GetTime          ( IN  T_TIMEHS     *ins ) ;
      T_ACCTIMEHS  I_TIME_HS_DiffTime         ( IN  T_TIMEHS     *fin, 
                                                IN  T_TIMEHS     *ini ) ;
      T_CHAR      *I_TIME_HS_CurrCTime        ( void ) ;
      T_CHAR      *I_TIME_HS_timeToString     ( IN  T_TIMEHS     *t ) ;
      T_CHAR      *I_TIME_HS_acctimeToString  ( IN  T_ACCTIMEHS  *t ) ;


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

