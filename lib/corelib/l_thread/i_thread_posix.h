

 #ifndef I_THREAD_POSIX_H
 #define I_THREAD_POSIX_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


  /* ... Includes / Inclusiones ...............................*/

      #include "corelib/l_basic/c_basic.h"


#if defined(HAVE_PTHREAD_H)

  /* ... Types / Tipos ........................................*/

     typedef
     struct
     {
       pthread_mutex_t mutex ;
       pthread_cond_t  cond ;
       T_BOOL          ready ;
     } t_posix_mtsda ;

     typedef
     void *(*t_posix_thcode)(void *) ;


  /* ... Const / Constantes ...................................*/

#if defined(PTHREAD_CREATE_UNDETACHED)
      #define PTHREAD_CREATE_JOINABLE  PTHREAD_CREATE_UNDETACHED
#endif


  /* ... Functions / Funciones ................................*/

     /*  Thread  *
      * -------- */
     T_BOOL   I_THREAD_POSIX_createDetached  ( OUT  pthread_t      *thid,
                                               IN   t_posix_thcode  thcode,
                                               IN   void           *tharg ) ;
     T_BOOL   I_THREAD_POSIX_createJoinable  ( OUT  pthread_t      *thid,
                                               IN   t_posix_thcode  thcode,
                                               IN   void           *tharg ) ;
     T_BOOL   I_THREAD_POSIX_join            ( IN   pthread_t       thid,
                                               OUT  void          **thret ) ;

     /*  Condition  *
      * ----------- */
     void     I_THREAD_POSIX_init            ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_destroy         ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_lock            ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_unlock          ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_setReady        ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_setNotReady     ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_signalReady     ( IN   t_posix_mtsda  *mtsda ) ;
     void     I_THREAD_POSIX_waitReady       ( IN   t_posix_mtsda  *mtsda ) ;
     T_CHAR  *I_THREAD_POSIX_mtsdaToString   ( IN   t_posix_mtsda  *mtsda ) ;
     T_CHAR  *I_THREAD_POSIX_mtsdaToXML      ( IN   t_posix_mtsda  *mtsda ) ;


  /* ... Inline / Macros ......................................*/

      #include "corelib/l_thread/i_thread_posix.m"


  /* ..........................................................*/

#endif


 #ifdef  __cplusplus
    }
 #endif

#endif  /* I_THREAD_POSIX_H */

