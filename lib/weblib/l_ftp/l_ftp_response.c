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

      #include "weblib/l_ftp/l_ftp_response.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_FTP_RESPONSE_Skip      ( INOUT  t_sock     *sd )
      {
        T_BOOL          eof ;
        T_CHAR          lineBuff[1024] ;
        t_ftp_response  ftpr ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
  
        /* ... initialize ... */
        L_FTP_RESPONSE_MakeEmpty(&ftpr) ;

        /* ... read first line ... */
        eof = X_SOCKET_ReadLine( sd,
                                 lineBuff,
                                 sizeof(lineBuff) ) ;
        TRUE_RET_FALSE(eof) ;
        ftpr.code = atoi(lineBuff) ;
        ftpr.ok   = TRUE ;
        if (abs(ftpr.code) < 100)
            ftpr.ok = FALSE ;
        if (abs(ftpr.code) > 500)
            ftpr.ok = FALSE ;

        /* ... read rest lines ... */
        while (
                 (X_STRING_StrLen(lineBuff) >= 3) 
                           && 
                 ((lineBuff)[3] == '-')
              )
        {
          eof = X_SOCKET_ReadLine( sd,
                                   lineBuff,
                                   sizeof(lineBuff) ) ;
          if (eof == TRUE)
              return (ftpr.ok) ;
        }

        return (ftpr.ok) ;
      }

      T_BOOL    L_FTP_RESPONSE_Read      ( INOUT  t_sock          *sd,
                                           INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL    eof, ok ;
        T_U_INT   msgSize ;
        T_CHAR    lineBuff[1024] ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;
  
        /* ... initialize ... */
        L_FTP_RESPONSE_MakeEmpty(ftpr) ;
        msgSize = 0 ;

        /* ... read first line ... */
        eof = X_SOCKET_ReadLine( sd,
                                 lineBuff,
                                 sizeof(lineBuff) ) ;
        TRUE_RET_FALSE(eof) ;
        ok = L_BUFFA_CatNBytesToCache( &(ftpr->msg),
                                       &(msgSize),
                                       lineBuff,
                                       X_STRING_StrLen(lineBuff) ) ;
        FALSE_RET_FALSE(ok) ;
        ftpr->code = atoi(lineBuff) ;
        ftpr->ok   = TRUE ;
        if (abs(ftpr->code) < 100)
            ftpr->ok = FALSE ;
        if (abs(ftpr->code) > 500)
            ftpr->ok = FALSE ;

        /* ... read rest lines ... */
        while (
                 (X_STRING_StrLen(lineBuff) >= 3) 
                           && 
                 ((lineBuff)[3] == '-')
              )
        {
          eof = X_SOCKET_ReadLine( sd,
                                   lineBuff,
                                   sizeof(lineBuff) ) ;
          if (eof == TRUE)
              break ;
          ok = L_BUFFA_CatNBytesToCache( &(ftpr->msg),
                                         &(msgSize),
                                         lineBuff,
                                         X_STRING_StrLen(lineBuff) ) ;
          if (ok == FALSE)
              break ;
        }

        ok = L_BUFFA_CatOneByteToCache( &(ftpr->msg),
                                        &(msgSize),
                                        '\0' ) ;
        return (ftpr->ok) ;
      }

      T_BOOL    L_FTP_RESPONSE_Destroy   ( INOUT  t_ftp_response  **ftpr )
      {
        NULL_RET_TRUE(ftpr) ;
        NULL_RET_TRUE((*ftpr)) ;

        X_ALLOC_Free( (void **) &( (*ftpr)->msg ) ) ;
        X_ALLOC_Free( (void **) ftpr ) ;

        return TRUE ;
      }

      T_BOOL    L_FTP_RESPONSE_MakeEmpty   ( INOUT  t_ftp_response   *ftpr )
      {
        NULL_RET_TRUE(ftpr) ;

        ftpr->ok   = FALSE ;
        ftpr->code = 0 ;
        ftpr->msg  = NULL ;

        return TRUE ;
      }

      T_BOOL    L_FTP_RESPONSE_Empty       ( INOUT  t_ftp_response   *ftpr )
      {
        NULL_RET_TRUE(ftpr) ;

        X_ALLOC_Free( (void **) &(ftpr->msg) ) ;
        ftpr->ok   = FALSE ;
        ftpr->code = 0 ;
        ftpr->msg  = NULL ;

        return TRUE ;
      }


  /* ................................................................... */

