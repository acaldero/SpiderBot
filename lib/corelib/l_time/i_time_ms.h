

 #ifndef I_TIME_MS_H
 #define I_TIME_MS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"


   /* ... Types / Tipos ................................................. */

 #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
      #define  T_TIMEMS       struct timeval
      #define  T_ACCTIMEMS    double
 #else
      #define  T_TIMEMS       int
      #define  T_ACCTIMEMS    double
 #endif


   /* ... Const / Constantes ............................................ */

      #define  c_TIMEMS          sizeof(T_TIMEMS)
      #define  c_ACCTIMEMS       sizeof(T_ACCTIMEMS)

      #define  ACCTIMEMS_MAX       MAXDOUBLE
      #define  ACCTIMEMS_MIN       ((double)0)


   /* ... Functions / Funciones ......................................... */

      void         I_TIME_MS_GetTime          ( IN  T_TIMEMS  *ins ) ;
      T_ACCTIMEMS  I_TIME_MS_DiffTime         ( IN  T_TIMEMS  *fin, 
                                                IN  T_TIMEMS  *ini ) ;
      T_CHAR      *I_TIME_MS_CurrCTime        ( void ) ;
      T_CHAR      *I_TIME_MS_timeToString     ( IN  T_TIMEMS  *t ) ;
      T_CHAR      *I_TIME_MS_acctimeToString  ( IN  T_ACCTIMEMS  *t ) ;


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

