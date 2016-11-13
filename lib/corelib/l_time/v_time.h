

 #ifndef V_TIME_H
 #define V_TIME_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
 #if defined(__MSDOS__)
      #include "corelib/l_time/i_time_hs.h"
 #endif
 #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
      #include "corelib/l_time/i_time_ms.h"
 #endif


   /* ... Types / Tipos ................................................. */

 #if defined(__MSDOS__)
      #define  T_TIME       T_TIMEHS
      #define  T_ACCTIME    T_ACCTIMEHS
 #endif
 #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
      #define  T_TIME       T_TIMEMS 
      #define  T_ACCTIME    T_ACCTIMEMS
 #endif


   /* ... Const / Constantes ............................................ */

      #define  c_TIME            sizeof(T_TIME)
      #define  c_ACCTIME         sizeof(T_ACCTIME)

      #define  ACCTIME_MAX       MAXDOUBLE
      #define  ACCTIME_MIN       ((double)0)


   /* ... Functions / Funciones ......................................... */

      void         V_TIME_GetTime     ( IN  T_TIME  *ins ) ;
      /* - If 'ins' is no NULL, put in current time. */
      /* - Si ins es NO NULL, introduce el instante actual
           de tiempo */

      T_ACCTIME    V_TIME_DiffTime    ( IN  T_TIME  *fin, 
                                        IN  T_TIME  *ini ) ;
      /* - Return miliseq. between 'ini' and 'fin' */
      /* - Retorna la diferencia de tiempo en  
           milisegundos, que separa los instantes 
           'ini' y 'fin' */

      T_CHAR      *V_TIME_CurrCTime   ( void ) ;
      /* - Return a string with day, month, year, hour,
           minutes and seconds at instant where is called
           Return a NO malloc string. */
      /* - Retorna un string que informa del dia, mes, a~o,
           hora, minuto y segundo del instante en que es
           llamado. 
           Retorna un string ESTATICO. */

      T_CHAR      *V_TIME_timeToString     ( IN  T_TIME  *t ) ;
      /* - Return a string with "(seq,useq)" format */
      /* - Retorna un string con el formato "(seg,useg)" */

      T_CHAR      *V_TIME_acctimeToString  ( IN  T_ACCTIME  *t ) ;
      /* - Return a string with "(miliseq)" format */
      /* - Retorna un string con el formato "(miliseg)" */


   /* ... Inline / Macros ............................................... */

      #include "corelib/l_time/v_time.m"


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

