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

      #include "weblib/l_nntp/l_nntp_response.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_NNTP_RESPONSE_Skip      ( INOUT  t_sock     *sd )
      {
        T_BOOL           eof ;
        T_CHAR           lineBuff[1024] ;
        t_nntp_response  nntpr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;

        /* ... initialize ... */
        L_NNTP_RESPONSE_MakeEmpty(&nntpr) ;

        /* ... read first line ... */
        eof = X_SOCKET_ReadLine( sd,
                                 lineBuff,
                                 sizeof(lineBuff) ) ;
        TRUE_RET_FALSE(eof) ;
        nntpr.ok   = TRUE ;
        if (lineBuff[0] == '-')
            nntpr.ok = FALSE ;
        if (lineBuff[0] == '+')
            nntpr.ok = TRUE ;

        return (nntpr.ok) ;
      }

      T_BOOL    L_NNTP_RESPONSE_Read      ( INOUT  t_sock           *sd,
                                            INOUT  t_nntp_response  *nntpr )
      {
        T_BOOL   eof ;
        T_INT    code ;
        T_CHAR   lineBuff[1024] ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(nntpr) ;

        /* ... initialize ... */
        L_NNTP_RESPONSE_MakeEmpty(nntpr) ;

        /* ... read response line ... */
        eof = X_SOCKET_ReadLine( sd,
                                 lineBuff,
                                 sizeof(lineBuff) ) ;
        TRUE_RET_FALSE(eof) ;

        /* ... setup response struct ... */
        nntpr->msg  = X_STRING_StrDup(lineBuff) ;
        nntpr->ok   = TRUE ;
        sscanf(lineBuff,"%i",&code) ;
        if (code >= 400)   /* unperformed */
            nntpr->ok = FALSE ;
        if (code >= 500)   /* unimplemented */
            nntpr->ok = FALSE ;

        return (nntpr->ok) ;
      }

      T_BOOL    L_NNTP_RESPONSE_Destroy   ( INOUT  t_nntp_response  **nntpr )
      {
        NULL_RET_TRUE(nntpr) ;
        NULL_RET_TRUE((*nntpr)) ;

        X_ALLOC_Free( (void **) &( (*nntpr)->msg ) ) ;
        X_ALLOC_Free( (void **) nntpr ) ;

        return TRUE ;
      }

      T_BOOL    L_NNTP_RESPONSE_MakeEmpty   ( INOUT  t_nntp_response   *nntpr )
      {
        NULL_RET_TRUE(nntpr) ;

        nntpr->ok   = FALSE ;
        nntpr->msg  = NULL ;

        return TRUE ;
      }

      T_BOOL    L_NNTP_RESPONSE_Empty       ( INOUT  t_nntp_response   *nntpr )
      {
        NULL_RET_TRUE(nntpr) ;

        X_ALLOC_Free( (void **) &(nntpr->msg) ) ;
        nntpr->ok   = FALSE ;
        nntpr->msg  = NULL ;

        return TRUE ;
      }


  /* ................................................................... */

