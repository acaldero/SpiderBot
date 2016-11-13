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

      #include "weblib/l_ftp/l_ftp_log.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_FTP_LOG_PrintUrl         ( INOUT  FILE    *flog,
                                            IN     t_url   *url )
      {
        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        fprintf(flog,
                "\n"
                "\n"
                "\tREQUEST\n") ;
        fprintf(flog,
                "%s://%s:%i%s\n\n",
                url->protocol, 
                url->machine, 
                ntohs(url->port), 
                url->file) ;
        fprintf(flog,
                "\tDIALOG\n") ;
        return TRUE ;
      }
  
      T_BOOL   L_FTP_LOG_PrintResponse    ( INOUT  FILE            *flog,
                                            IN     t_ftp_response  *ftpr )
      {
        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(ftpr) ;
        fprintf(flog,
                "%s",
                ftpr->msg) ; 
        return TRUE ;
      }
  

   /* ................................................................... */

