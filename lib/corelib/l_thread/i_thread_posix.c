/* ....................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 * See documentation for more information.
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * .................................................................... */



   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_thread/i_thread_posix.h"


   /* ... Functions / Funciones ......................................... */


#if defined(HAVE_PTHREAD_H)

      /*  thread  *
       * -------- */
      T_BOOL   I_THREAD_POSIX_createDetached  ( OUT  pthread_t      *thid,
                                                IN   t_posix_thcode  thcode,
                                                IN   void           *tharg )
      {
   	pthread_attr_t attr ;
        int ret ;

        NULL_RET_FALSE(thid) ;
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM) ;
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) ;
        ret = pthread_create( thid, &attr, thcode, tharg ) ;
        if (ret < 0)
           {
             perror("pthread_create:") ;
             return FALSE ;
           }
        return TRUE ;
      }

      T_BOOL   I_THREAD_POSIX_createJoinable  ( OUT  pthread_t      *thid,
                                                IN   t_posix_thcode  thcode,
                                                IN   void           *tharg )
      {
   	pthread_attr_t attr ;
        int ret ;

        NULL_RET_FALSE(thid) ;
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM) ;
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE) ;
        ret = pthread_create( thid, &attr, thcode, tharg ) ;
        if (ret < 0)
           {
             perror("pthread_create:") ;
             return FALSE ;
           }
        return TRUE ;
      }

      T_BOOL   I_THREAD_POSIX_join            ( IN   pthread_t       thid,
                                                OUT  void          **thret )
      {
        int ret ;

        ret = pthread_join(thid,thret) ;
        if (ret < 0)
           {
             perror("pthread_join:") ;
             return FALSE ;
           }
        return TRUE ;
      }


      /*  mtsdaToXZY  *
       * ------------ */
      T_CHAR  *I_THREAD_POSIX_mtsdaToString   ( IN   t_posix_mtsda  *mtsda )
      {
        T_BOOL   ret ;
        T_CHAR  *pstr ;

        if (mtsda == NULL)
           {
             pstr = X_STRING_StrDup("mtsda(NULL)") ;
             return pstr ;
           }

        ret = pthread_mutex_trylock( &((mtsda)->mutex) ) ;
        pthread_mutex_unlock( &((mtsda)->mutex) ) ;
        switch (ret)
        {
          case EBUSY :
               pstr = X_STRING_Dsprintf( "mtsda(ready(%i),mutex(lock),cond(%p))",
                                      (mtsda)->ready,
                                      (void *)&((mtsda)->cond) ) ;
               break ;
          case EINVAL :
               pstr = X_STRING_Dsprintf( "mtsda(ready(%i),mutex(NOT init),cond(%p))",
                                      (mtsda)->ready,
                                      (void *)&((mtsda)->cond) ) ;
               break ;
          default : ; 
               pstr = X_STRING_Dsprintf( "mtsda(ready(%i),mutex(unlock),cond(%p))",
                                      (mtsda)->ready,
                                      (void *)&((mtsda)->cond) ) ;
               break ;
        }
        return pstr ;
      }

      T_CHAR  *I_THREAD_POSIX_mtsdaToXML      ( IN   t_posix_mtsda  *mtsda )
      {
        T_BOOL   ret ;
        T_CHAR  *pstr ;

        if (mtsda == NULL)
           {
             pstr = X_STRING_StrDup("<mtsda>\n"
                                 "</mtsda>\n") ;
             return pstr ;
           }

        ret = pthread_mutex_trylock( &((mtsda)->mutex) ) ;
        pthread_mutex_unlock( &((mtsda)->mutex) ) ;
        switch (ret)
        {
          case EBUSY :
               pstr = X_STRING_Dsprintf( "<mtsda>\n"
                                      " <ready value=\"%i\">\n"
                                      " <mutex value=\"lock\">\n"
                                      " <cond  value=\"%p\">\n"
                                      "</mtsda>\n",
                                      (mtsda)->ready,
                                      (void *)&((mtsda)->cond) ) ;
               break ;
          case EINVAL :
               pstr = X_STRING_Dsprintf( "<mtsda>\n"
                                      " <ready value=\"%i\">\n"
                                      " <mutex value=\"NOT INIT\">\n"
                                      " <cond  value=\"%p\">\n"
                                      "</mtsda>\n",
                                      (mtsda)->ready,
                                      (void *)&((mtsda)->cond) ) ;
               break ;
          default : ; 
               pstr = X_STRING_Dsprintf( "<mtsda>\n"
                                      " <ready value=\"%i\">\n"
                                      " <mutex value=\"unlock\">\n"
                                      " <cond  value=\"%p\">\n"
                                      "</mtsda>\n",
                                      (mtsda)->ready,
                                      (void *)&((mtsda)->cond) ) ;
               break ;
        }
        return pstr ;
      }

#endif


/* ...................................................................... */

