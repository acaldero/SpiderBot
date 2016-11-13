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

      #include "weblib/l_ftp/l_ftp_command.h"


   /* ... Function / Funciones .......................................... */

      /*  Conection  *
       * ----------- */
      T_BOOL    L_FTP_COMMAND_Connect      ( INOUT  t_sock          *sd,
                                             IN     T_CHAR          *host,
                                             IN     T_INT            port,
                                             INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(host) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        ok = L_FTP_RESPONSE_MakeEmpty(ftpr) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Connect(sd,host,port) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_FTP_RESPONSE_Read(sd,ftpr) ;
        return ok ;
      }
  
      T_BOOL    L_FTP_COMMAND_Close       ( INOUT  t_sock          *sd,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        L_FTP_COMMAND_WriteString(sd,"QUIT\n") ;
        ok = L_FTP_RESPONSE_Read(sd,ftpr) ;
        FALSE_RET_FALSE(ok) ;
        ok = X_SOCKET_Close(sd) ;
        return ok ;
      }
  
  
      /*  FTP Commands  *
       * -------------- */
      T_BOOL    L_FTP_COMMAND_Request     ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *request,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL ok ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL_RET_FALSE(request) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        ok = L_FTP_COMMAND_WriteString(sd,request) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_FTP_RESPONSE_Read(sd,ftpr) ;
        return ok ;
      } 
  
      T_BOOL    L_FTP_COMMAND_user        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *user,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(user) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        reqstr = X_STRING_Dsprintf("USER %s\n",user) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FTP_COMMAND_Request(sd,reqstr,ftpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  
      T_BOOL    L_FTP_COMMAND_pass        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *pass,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(pass) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        reqstr = X_STRING_Dsprintf("PASS %s\n",pass) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FTP_COMMAND_Request(sd,reqstr,ftpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  
      T_BOOL    L_FTP_COMMAND_cwd         ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *setcwd,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(setcwd) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        reqstr = X_STRING_Dsprintf("CWD %s\n",setcwd) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FTP_COMMAND_Request(sd,reqstr,ftpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  
      T_BOOL    L_FTP_COMMAND_port        ( INOUT  t_sock          *sd,
                                            INOUT  t_ftp_response  *ftpr,
                                            IN     t_sock          *insock )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
        long     addr ;
        int      port ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(insock) ;

        addr = (insock->addr).sin_addr.s_addr ;
        port = (insock->addr).sin_port ;
        reqstr = X_STRING_Dsprintf("PORT %i,%i,%i,%i,%i,%i\n",
                                   LOWB(LOWDB(addr)),
                                   HIGHB(LOWDB(addr)),
                                   LOWB(HIGHDB(addr)),
                                   HIGHB(HIGHDB(addr)),
                                   LOWB(port),
                                   HIGHB(port)
                                  ) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FTP_COMMAND_Request(sd,reqstr,ftpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  
      T_BOOL    L_FTP_COMMAND_retr        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *file,
                                            INOUT  T_LONG          *total_to_read,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
        T_CHAR  *pch ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(file) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        reqstr = X_STRING_Dsprintf("RETR %s\n",file) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FTP_COMMAND_Request(sd,reqstr,ftpr) ;
        X_ALLOC_Free((void **)&reqstr) ;

        /* ... read file size ... */
        pch = X_STRING_StrChr(ftpr->msg,'(') ;
        if (pch != NULL)
                 (*total_to_read) = (T_LONG)atoi(pch + 1) ;
            else (*total_to_read) = 0L ;

        return ok ;
      } 
  
      T_BOOL    L_FTP_COMMAND_nlst        ( INOUT  t_sock          *sd,
                                            IN     T_CHAR          *path,
                                            INOUT  t_ftp_response  *ftpr )
      {
        T_BOOL   ok ;
        T_CHAR  *reqstr ;
  
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(path) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;

        reqstr = X_STRING_Dsprintf("NLST %s\n",path) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_FTP_COMMAND_Request(sd,reqstr,ftpr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 

      T_BOOL    L_FTP_COMMAND_pasv        ( INOUT  t_sock           *sd,
                                            INOUT  t_ftp_response   *ftpr,
                                            INOUT  struct sockaddr  *faddr )
      {
        T_BOOL          ok ;
        T_CHAR         *pch ;
        unsigned int    bv[6] ;
 
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;
        NULL__SET_ERROR__RET_FALSE(faddr) ;

        ok = L_FTP_COMMAND_Request(sd,"PASV\n",ftpr) ;
        FALSE_RET_FALSE(ok) ;

        pch = strchr(ftpr->msg,'(') ;
        NULL_RET_FALSE(pch) ;
        pch++ ; /* skip '(' */
        faddr->sa_family = AF_INET ;
        sscanf(pch,
               "%u,%u,%u,%u,%u,%u",
               &bv[2],
               &bv[3],
               &bv[4],
               &bv[5],
               &bv[0],
               &bv[1]) ;
        faddr->sa_data[2] = bv[2] ;
        faddr->sa_data[3] = bv[3] ;
        faddr->sa_data[4] = bv[4] ;
        faddr->sa_data[5] = bv[5] ;
        faddr->sa_data[0] = bv[0] ;
        faddr->sa_data[1] = bv[1] ;

        return TRUE ;
      } 


  /* ................................................................... */

