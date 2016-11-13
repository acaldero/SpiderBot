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

      #include "corelib/l_thread/x_thread.h"


   /* ... Functions / Funciones ......................................... */

      /*  thread  *
       * -------- */
      T_BOOL   I_THREAD_SHADOW_createDetached  ( OUT  pthread_t       *thid,
                                                 IN   t_shadow_thcode  thcode,
                                                 IN   void            *tharg )
      {
        NULL_RET_FALSE(thid) ;
        (*thid) = (pthread_t)(*thcode)(tharg) ;
        return TRUE ;
      }

      T_BOOL   I_THREAD_SHADOW_createJoinable  ( OUT  pthread_t       *thid,
                                                 IN   t_shadow_thcode  thcode,
                                                 IN   void            *tharg )
      {
        NULL_RET_FALSE(thid) ;
        (*thid) = (pthread_t)(*thcode)(tharg) ;
        return TRUE ;
      }

      T_BOOL   I_THREAD_SHADOW_join            ( IN   pthread_t        thid,
                                                 OUT  void           **thret )
      {
        ((*thret) = (void *)thid) ;
        return TRUE ;
      }


      /*  mtsdaToXZY  *
       * ------------ */
      T_CHAR  *I_THREAD_SHADOW_mtsdaToString   ( IN   t_shadow_mtsda  *mtsda )
      {
        T_CHAR  *pstr ;

        if (mtsda == NULL)
           {
             pstr = X_STRING_StrDup("mtsda(NULL)") ;
           }
        else 
           {
             pstr = X_STRING_Dsprintf( "mtsda(ready(%i))",
                                       (mtsda)->ready ) ;
           }
        return pstr ;
      }

      T_CHAR  *I_THREAD_SHADOW_mtsdaToXML      ( IN   t_shadow_mtsda  *mtsda )
      {
        T_CHAR  *pstr ;

        if (mtsda == NULL)
           {
             pstr = X_STRING_StrDup("<mtsda>\n"
                                    "</mtsda>\n") ;
           }
        else 
           {
             pstr = X_STRING_Dsprintf( "<mtsda>\n"
                                      " <ready value=\"%i\">\n"
                                      "</mtsda>\n",
                                      (mtsda)->ready ) ;
           }
        return pstr ;
      }


   /* ................................................................... */

