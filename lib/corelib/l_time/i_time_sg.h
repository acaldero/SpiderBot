

 #ifndef I_TIME_SG_H
 #define I_TIME_SG_H


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Types / Tipos ................................................. */

      #define  T_TIMESG       time_t
      #define  T_ACCTIMESG    double


   /* ... Const / Constantes ............................................ */

      #define  c_TIMESG       sizeof(T_TIMESG)
      #define  c_ACCTIMESG    sizeof(T_ACCTIMESG)


   /* ... Functions / Funciones ......................................... */

      T_TIMESG      *I_TIME_SG_GetTime        ( void ) ;
      T_ACCTIMESG    I_TIME_SG_DiffTime       ( IN  T_TIMESG  fin, 
                                                IN  T_TIMESG  ini ) ;
      T_CHAR      *I_TIME_SG_CurrCTime        ( void ) ;
      T_CHAR      *I_TIME_SG_timeToString     ( IN  T_TIMESG     *t ) ;
      T_CHAR      *I_TIME_SG_acctimeToString  ( IN  T_ACCTIMESG  *t ) ;


   /* ... Inline / Codigo en linea ...................................... */

      #define  I_TIME_SG_GetTime() \
	       time(NULL)

      #define  I_TIME_SG_DiffTime(fin,ini) \
	       difftime((fin),(ini))


   /* ................................................................... */


 #endif

