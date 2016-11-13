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

      #include "weblib/l_finger/l_finger_response.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_FINGER_RESPONSE_Skip      ( INOUT  t_sock     *sd )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
  
        return TRUE ;
      }

      T_BOOL    L_FINGER_RESPONSE_Read   ( INOUT  t_sock          *sd,
                                           INOUT  t_finger_response  *fingerr )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(fingerr) ;
  
        /* ... initialize ... */
        L_FINGER_RESPONSE_MakeEmpty(fingerr) ;
        fingerr->ok = TRUE ;

        return (fingerr->ok) ;
      }

      T_BOOL    L_FINGER_RESPONSE_Destroy ( INOUT  t_finger_response  **fingerr )
      {
        NULL_RET_TRUE(fingerr) ;
        NULL_RET_TRUE((*fingerr)) ;

        X_ALLOC_Free( (void **) &( (*fingerr)->msg ) ) ;
        X_ALLOC_Free( (void **) fingerr ) ;

        return TRUE ;
      }

      T_BOOL    L_FINGER_RESPONSE_MakeEmpty ( INOUT  t_finger_response   *fingerr )
      {
        NULL_RET_TRUE(fingerr) ;

        fingerr->ok   = FALSE ;
        fingerr->msg  = NULL ;

        return TRUE ;
      }

      T_BOOL    L_FINGER_RESPONSE_Empty  ( INOUT  t_finger_response   *fingerr )
      {
        NULL_RET_TRUE(fingerr) ;

        X_ALLOC_Free( (void **) &(fingerr->msg) ) ;
        fingerr->ok   = FALSE ;
        fingerr->msg  = NULL ;

        return TRUE ;
      }


  /* ................................................................... */

