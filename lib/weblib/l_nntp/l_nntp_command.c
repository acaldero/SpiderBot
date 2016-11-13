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

      #include "weblib/l_nntp/l_nntp_command.h"


   /* ... Function / Funciones .......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_NNTP_COMMAND_Connect      ( INOUT  t_sock           *sd,
                                              IN     T_CHAR           *host,
                                              IN     T_INT             port,
                                              INOUT  t_nntp_response  *nntpr )
      {
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(host) ;
        NULL__SET_ERROR__RET_FALSE(nntpr) ;

        ok = L_NNTP_RESPONSE_MakeEmpty(nntpr) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Connect(sd,host,port) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_NNTP_RESPONSE_Read(sd,nntpr) ;
        return ok ;
      }

      T_BOOL    L_NNTP_COMMAND_Close       ( INOUT  t_sock            *sd,
                                             INOUT  t_nntp_response   *nntpr )
      {
        NULL_RET_FALSE(sd) ;
        L_NNTP_COMMAND_Request(sd,"QUIT\n",nntpr) ;
        return X_SOCKET_Close(sd) ;
      }
  
  
      /*  NNTP Commands  *
       * --------------- */
      T_BOOL    L_NNTP_COMMAND_Request     ( INOUT  t_sock            *sd,
                                             IN     T_CHAR            *request,
                                             INOUT  t_nntp_response   *nntpr )
      {
        T_BOOL   ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL_RET_FALSE(request) ;
        NULL__SET_ERROR__RET_FALSE(nntpr) ;

        ok = L_NNTP_COMMAND_WriteString(sd,request) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_NNTP_RESPONSE_Read(sd,nntpr) ;
        return ok ;
      }

      T_BOOL    L_NNTP_COMMAND_group       ( INOUT  t_sock            *sd,
                                             IN     T_CHAR            *group,
                                             INOUT  t_nntp_response   *nntpr )
      {
        T_CHAR  *reqstr ;
        T_BOOL   ok ;
  
        reqstr = X_STRING_Dsprintf("GROUP %s\n",
                                   group) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_NNTP_COMMAND_Request(sd,reqstr,nntpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      }

      T_BOOL    L_NNTP_COMMAND_article     ( INOUT  t_sock            *sd,
                                             IN     T_CHAR            *article,
                                             INOUT  t_nntp_response   *nntpr )
      {
        T_CHAR  *reqstr ;
        T_BOOL   ok ;
  
        reqstr = X_STRING_Dsprintf("ARTICLE %s\n",
                                   article) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_NNTP_COMMAND_Request(sd,reqstr,nntpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      }

      T_BOOL    L_NNTP_COMMAND_stat        ( INOUT  t_sock            *sd,
                                             IN     T_CHAR            *article,
                                             INOUT  t_nntp_response   *nntpr )
      {
        T_CHAR  *reqstr ;
        T_BOOL   ok ;
  
        reqstr = X_STRING_Dsprintf("STAT %s\n",
                                article) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_NNTP_COMMAND_Request(sd,reqstr,nntpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      }


  /* ................................................................... */

