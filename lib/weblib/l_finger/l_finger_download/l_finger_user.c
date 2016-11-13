/* ........................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "weblib/l_finger/l_finger_download/l_finger_user.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FINGER_USER_rwfile      ( INOUT  t_downLoadWS   *dlws,
                                          INOUT  t_sock         *fingerSd,
                                          INOUT  FILE          **fpage )
      {
        T_LONG    total_a_leer, leidos ;
        T_INT     result, size_buff ;
        T_LONG    number_urls ;

          #define c_FINGER_BSIZE (8*1024)
          char    finger_buff[c_FINGER_BSIZE] ;

        leidos       = 0L ;
        total_a_leer = 0 ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), sizeof(finger_buff) ) ;
        number_urls = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        /* ... first read is out of while ... */
        result = L_FINGER_COMMAND_ReadLine(fingerSd,finger_buff,size_buff) ;
        while ( result == FALSE )
        {
          L_FILE_COMMAND_Write(finger_buff,X_STRING_StrLen(finger_buff),(*fpage)) ;
          leidos = leidos + X_STRING_StrLen(finger_buff) ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_a_leer) ;
          result = L_FINGER_COMMAND_ReadLine(fingerSd,finger_buff,size_buff) ;
        }
        dlws->currentBytes += leidos ;
        return result ; /* eof */
      }

      T_BOOL  L_FINGER_USER_Open          ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg,
                                            IN     t_url          *url )
      {
        T_BOOL    ok ;
        T_CHAR   *user, *puser ;
        T_INT     puserlen ;
        t_finger_response  fingerr ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        if (fingerCfg->connected == FALSE)
           {
             ok = L_FINGER_SERVER_GetConnection(fingerCfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... get user only ... */
        user     = url->file ;
        puser    = "%7e" ;
        puserlen = X_STRING_StrLen(puser) ;
        if (X_STRING_CaseNEqual(user,puser,puserlen,FALSE) == TRUE)
            user = user + puserlen ;
        puser    = "/" ;
        puserlen = X_STRING_StrLen(puser) ;
        if (X_STRING_CaseNEqual(user,puser,puserlen,FALSE) == TRUE)
            user = user + puserlen ;

        /* ... finger ... */
        ok = L_FINGER_COMMAND_finger(&(fingerCfg->sd),user,&fingerr) ;
        L_FINGER_LOG_PrintResponse(dlws->finfo,&fingerr) ;
        L_FINGER_RESPONSE_Empty(&fingerr) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }

      T_BOOL  L_FINGER_USER_Close         ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg )
      {
        T_BOOL    ok ;
        t_finger_response  fingerr ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;

        L_FINGER_RESPONSE_Empty(&fingerr) ;
        fingerCfg->connected = FALSE ;

        return ok ;
      }

      T_BOOL  L_FINGER_USER_DownLoad      ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url )
      {
        T_BOOL   ok ;

        ok = L_FINGER_USER_Open(dlws,fingerCfg,url) ;
        FALSE_RET_FALSE(ok) ;
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "user...",
                                      0,
                                      url) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        ok = L_FINGER_USER_rwfile(dlws,&(fingerCfg->sd),fpage) ;

        /* ... finalize ... */
        ok = L_FINGER_USER_Close(dlws,fingerCfg) ;
        return ok ;
      }


   /* ................................................................... */

