

 #ifndef X_THREAD_H
 #define X_THREAD_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


  /* ... Includes / Inclusiones ...............................*/

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_thread/v_thread.h"


  /* ... Functions / Funciones ................................*/

     /*  Thread  *
      * -------- */
     T_BOOL   X_THREAD_createDetached  ( OUT  pthread_t    *thid,
                                         IN   t_thcode     thcode,
                                         IN   void         *tharg ) ;
     T_BOOL   X_THREAD_createJoinable  ( OUT  pthread_t   *thid,
                                         IN   t_thcode     thcode,
                                         IN   void        *tharg ) ;
     T_BOOL   X_THREAD_join            ( IN   pthread_t    thid,
                                         OUT  void       **thret ) ;

     /*  Condition  *
      * ----------- */
     void     X_THREAD_init            ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_destroy         ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_lock            ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_unlock          ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_setReady        ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_setNotReady     ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_signalReady     ( IN   t_mtsda      *mtsda ) ;
     void     X_THREAD_waitReady       ( IN   t_mtsda      *mtsda ) ;
     T_CHAR  *X_THREAD_mtsdaToString   ( IN   t_mtsda      *mtsda ) ;
     T_CHAR  *X_THREAD_mtsdaToXML      ( IN   t_mtsda      *mtsda ) ;


  /* ... Inline / Macros ......................................*/

      #include "corelib/l_thread/x_thread.m"


  /* ..........................................................*/


 #ifdef  __cplusplus
    }
 #endif

#endif  /* X_THREAD_H */

