

 #ifndef V_TIME_M
 #define V_TIME_M

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Inline / Macros ............................................... */


  #if defined(__MSDOS__)

      #define  V_TIME_GetTime(ins)                      \
               I_TIME_HS_GetTime((ins))

      #define  V_TIME_DiffTime(fin,ini)                 \
               1000*I_TIME_HS_DiffTime((fin),(ini))

      #define  V_TIME_timeToString(t)                   \
               I_TIME_HS_timeToString((t))

      #define  V_TIME_CurrCTime()                       \
               I_TIME_HS_CurrCTime()

      #define  V_TIME_acctimeToString(t)                \
               I_TIME_HS_acctimeToString((t))

  #endif


  #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))

      #define  V_TIME_GetTime(ins)                      \
               I_TIME_MS_GetTime((ins))

      #define  V_TIME_DiffTime(fin,ini)                 \
               I_TIME_MS_DiffTime((fin),(ini))

      #define  V_TIME_timeToString(t)                   \
               I_TIME_MS_timeToString((t))

      #define  V_TIME_CurrCTime()                       \
               I_TIME_MS_CurrCTime()

      #define  V_TIME_acctimeToString(t)                \
               I_TIME_MS_acctimeToString((t))

  #endif


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif 

