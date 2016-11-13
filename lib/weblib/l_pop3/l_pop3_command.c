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

      #include "weblib/l_pop3/l_pop3_command.h"


   /* ... Function / Funciones .......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_POP3_COMMAND_Connect      ( INOUT  t_sock           *sd,
                                              IN     T_CHAR           *host,
                                              IN     T_INT             port,
                                              INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(host) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        ok = L_POP3_RESPONSE_MakeEmpty(pop3r) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Connect(sd,host,port) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_POP3_RESPONSE_Read(sd,pop3r) ;
        return ok ;
      }

      T_BOOL    L_POP3_COMMAND_Close       ( INOUT  t_sock           *sd,
                                             INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        L_POP3_COMMAND_WriteString(sd,"QUIT\n") ;
        ok = L_POP3_RESPONSE_Read(sd,pop3r) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Close(sd) ;
        return ok ;
      }
  
  
      /*  POP3 Commands  *
       * --------------- */
      T_BOOL    L_POP3_COMMAND_Request     ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *request,
                                             INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL ok ;

        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL_RET_FALSE(request) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        ok = L_POP3_COMMAND_WriteString(sd,request) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_POP3_RESPONSE_Read(sd,pop3r) ;
        return ok ;
      }

      T_BOOL    L_POP3_COMMAND_user        ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *user,
                                             INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(user) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        reqstr = X_STRING_Dsprintf("USER %s\n",user) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_POP3_COMMAND_Request(sd,reqstr,pop3r) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  
      T_BOOL    L_POP3_COMMAND_pass        ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *pass,
                                             INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(pass) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        reqstr = X_STRING_Dsprintf("PASS %s\n",pass) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_POP3_COMMAND_Request(sd,reqstr,pop3r) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  
      T_BOOL    L_POP3_COMMAND_retr        ( INOUT  t_sock           *sd,
                                             IN     T_CHAR           *msgid,
                                             INOUT  t_pop3_response  *pop3r )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(msgid) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        reqstr = X_STRING_Dsprintf("RETR %s\n",msgid) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_POP3_COMMAND_Request(sd,reqstr,pop3r) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  

  /* ................................................................... */

