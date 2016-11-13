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

      #include "weblib/l_finger/l_finger_command.h"


   /* ... Function / Funciones .......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_FINGER_COMMAND_Connect      ( INOUT  t_sock          *sd,
                                                IN     T_CHAR          *host,
                                                IN     T_INT            port,
                                                INOUT  t_finger_response  *fingerr )
      {
        T_BOOL   ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(host) ;
        NULL__SET_ERROR__RET_FALSE(fingerr) ;

        ok = L_FINGER_RESPONSE_MakeEmpty(fingerr) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Connect(sd,host,port) ;
        return ok ;
      }
  
      T_BOOL    L_FINGER_COMMAND_Close       ( INOUT  t_sock          *sd,
                                               INOUT  t_finger_response  *fingerr )
      {
        T_BOOL   ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(fingerr) ;

        ok = L_FINGER_RESPONSE_MakeEmpty(fingerr) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Close(sd) ;
        return ok ;
      }
  
  
      /*  FINGER Commands  *
       * -------------- */
      T_BOOL    L_FINGER_COMMAND_Request     ( INOUT  t_sock          *sd,
                                               IN     T_CHAR          *request,
                                               INOUT  t_finger_response  *fingerr )
      {
        T_BOOL ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL_RET_FALSE(request) ;
        NULL__SET_ERROR__RET_FALSE(fingerr) ;

        ok = L_FINGER_COMMAND_WriteString(sd,request) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_FINGER_RESPONSE_Read(sd,fingerr) ;
        return ok ;
      } 
  
      T_BOOL    L_FINGER_COMMAND_finger      ( INOUT  t_sock          *sd,
                                               IN     T_CHAR          *user,
                                               INOUT  t_finger_response  *fingerr )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(user) ;
        NULL__SET_ERROR__RET_FALSE(fingerr) ;

        reqstr = X_STRING_Dsprintf("%s\n",user) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FINGER_COMMAND_Request(sd,reqstr,fingerr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  

  /* ................................................................... */

