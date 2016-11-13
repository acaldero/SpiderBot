

 #ifndef I_THREAD_SHADOW_M
 #define I_THREAD_SHADOW_M

 #ifdef  __cplusplus
    extern "C" {
 #endif



  /* ... Includes / Inclusiones ...............................*/

      #include "corelib/l_basic/c_basic.h"


  /* ... Inline / Macros ......................................*/

#if ( ! defined(HAVE_PTHREAD_H) )

     #define  I_THREAD_SHADOW_init(mtsda)                    \
              (mtsda)->ready = FALSE ;

     #define  I_THREAD_SHADOW_destroy(mtsda)                 \
              (mtsda)->ready = FALSE ;

     #define  I_THREAD_SHADOW_lock(mtsda)

     #define  I_THREAD_SHADOW_unlock(mtsda)

     #define  I_THREAD_SHADOW_setNotReady(mtsda)             \
              (mtsda)->ready = FALSE ;

     #define  I_THREAD_SHADOW_setReady(mtsda)                \
              (mtsda)->ready = TRUE ;

     #define  I_THREAD_SHADOW_signalReady(mtsda)             \
              (mtsda)->ready = TRUE ;

     #define  I_THREAD_SHADOW_waitReady(mtsda)


  /* ..........................................................*/

#endif


 #ifdef  __cplusplus
    }
 #endif

#endif  /* I_THREAD_SHADOW_M */

