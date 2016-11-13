

 #ifndef I_THREAD_POSIX_M
 #define I_THREAD_POSIX_M

 #ifdef  __cplusplus
    extern "C" {
 #endif


  /* ... Includes / Inclusiones ...............................*/

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/x_print.h"


  /* ... Inline / Macros ......................................*/

#if defined(HAVE_PTHREAD_H)

     #define  I_THREAD_POSIX_init(mtsda)                           \
              {                                                    \
                (mtsda)->ready = FALSE ;                           \
                pthread_mutex_init(&((mtsda)->mutex),NULL) ;       \
                pthread_cond_init(&((mtsda)->cond),NULL) ;         \
              }

     #define  I_THREAD_POSIX_destroy(mtsda)                        \
              {                                                    \
                int ret ;                                          \
                                                                   \
                (mtsda)->ready = FALSE ;                           \
                ret = pthread_mutex_destroy(&((mtsda)->mutex)) ;   \
                if (ret == EINVAL)                                 \
                    X_PRINT_printf("Bad mutex\n") ;                \
                if (ret == EBUSY)                                  \
                    X_PRINT_printf("locked mutex\n") ;             \
                ret = pthread_cond_destroy(&((mtsda)->cond)) ;     \
                if (ret == EBUSY)                                  \
                    X_PRINT_printf("locked condition\n") ;         \
              }

     #define  I_THREAD_POSIX_lock(mtsda)                           \
              {                                                    \
                int ret ;                                          \
                                                                   \
                ret = pthread_mutex_lock(&((mtsda)->mutex)) ;      \
                if (ret == EINVAL)                                 \
                    X_PRINT_printf("Bad mutex\n") ;                \
              }

     #define  I_THREAD_POSIX_unlock(mtsda)                         \
              {                                                    \
                int ret ;                                          \
                                                                   \
                ret = pthread_mutex_unlock(&((mtsda)->mutex)) ;    \
                if (ret == EINVAL)                                 \
                    X_PRINT_printf("Bad mutex\n") ;                \
              }

     #define  I_THREAD_POSIX_setNotReady(mtsda)                    \
              (mtsda)->ready = FALSE ;

     #define  I_THREAD_POSIX_setReady(mtsda)                       \
              (mtsda)->ready = TRUE ;

     #define  I_THREAD_POSIX_signalReady(mtsda)                    \
              {                                                    \
                (mtsda)->ready = TRUE ;                            \
                pthread_cond_signal  ( &((mtsda)->cond) ) ;        \
              }

     #define  I_THREAD_POSIX_waitReady(mtsda)                      \
              {                                                    \
                while ((mtsda)->ready == FALSE)                    \
                {                                                  \
                  pthread_cond_wait( &((mtsda)->cond),             \
                                     &((mtsda)->mutex) ) ;         \
                }                                                  \
              }


  /* ..........................................................*/


#endif


 #ifdef  __cplusplus
    }
 #endif

#endif  /* I_THREAD_POSIX_M */

