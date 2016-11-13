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

      #include "weblib/l_pop3/l_pop3_response.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_POP3_RESPONSE_Skip      ( INOUT  t_sock     *sd,
                                            IN     T_BOOL      isMultiLine )
      {
        T_BOOL           eof ;
        T_CHAR           lineBuff[1024] ;
        t_pop3_response  pop3r ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;

        /* ... initialize ... */
        L_POP3_RESPONSE_MakeEmpty(&pop3r) ;

        /* ... read first line ... */
        eof = X_SOCKET_ReadLine( sd,
                                 lineBuff,
                                 sizeof(lineBuff) ) ;
        TRUE_RET_FALSE(eof) ;
        pop3r.ok   = TRUE ;
        if (lineBuff[0] == '-')
            pop3r.ok = FALSE ;
        if (lineBuff[0] == '+')
            pop3r.ok = TRUE ;

        /* ... read rest lines ... */
        if (isMultiLine == TRUE)
           {
             while ( L_LINE_dot_enter(lineBuff) == FALSE )
             {
               eof = X_SOCKET_ReadLine( sd,
                                        lineBuff,
                                        sizeof(lineBuff) ) ;
               if (eof == TRUE)
                   return (pop3r.ok) ;
             }
           }

        return (pop3r.ok) ;
      }

      T_BOOL    L_POP3_RESPONSE_Read      ( INOUT  t_sock           *sd,
                                            INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL   eof ;
        T_CHAR   lineBuff[1024] ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        /* ... initialize ... */
        L_POP3_RESPONSE_MakeEmpty(pop3r) ;

        /* ... read response line ... */
        eof = X_SOCKET_ReadLine( sd,
                                 lineBuff,
                                 sizeof(lineBuff) ) ;
        TRUE_RET_FALSE(eof) ;

        /* ... setup response struct ... */
        pop3r->msg  = X_STRING_StrDup(lineBuff) ;
        pop3r->ok   = TRUE ;
        if (lineBuff[0] == '-')
            pop3r->ok = FALSE ;
        if (lineBuff[0] == '+')
            pop3r->ok = TRUE ;

        return (pop3r->ok) ;
      }

      T_BOOL    L_POP3_RESPONSE_Destroy   ( INOUT  t_pop3_response  **pop3r )
      {
        NULL_RET_TRUE(pop3r) ;
        NULL_RET_TRUE((*pop3r)) ;

        X_ALLOC_Free( (void **) &( (*pop3r)->msg ) ) ;
        X_ALLOC_Free( (void **) pop3r ) ;

        return TRUE ;
      }

      T_BOOL    L_POP3_RESPONSE_MakeEmpty   ( INOUT  t_pop3_response   *pop3r )
      {
        NULL_RET_TRUE(pop3r) ;

        pop3r->ok   = FALSE ;
        pop3r->msg  = NULL ;

        return TRUE ;
      }

      T_BOOL    L_POP3_RESPONSE_Empty       ( INOUT  t_pop3_response   *pop3r )
      {
        NULL_RET_TRUE(pop3r) ;

        X_ALLOC_Free( (void **) &(pop3r->msg) ) ;
        pop3r->ok   = FALSE ;
        pop3r->msg  = NULL ;

        return TRUE ;
      }


  /* ................................................................... */

