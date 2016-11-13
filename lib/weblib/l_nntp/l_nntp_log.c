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

      #include "weblib/l_nntp/l_nntp_log.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_NNTP_LOG_PrintUrl       ( INOUT  FILE    *flog,
                                           IN     t_url   *url )
      {
        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        fprintf(flog,
                "\n"
                "\tREQUEST\n") ;
        fprintf(flog,
                "\t%s://%s:%i%s\n"
                "\n",
                url->protocol, 
                url->machine, 
                ntohs(url->port), 
                url->file) ;
        return TRUE ;
      }
  
      T_BOOL   L_NNTP_LOG_PrintResponse  ( INOUT  FILE             *flog,
                                           IN     t_nntp_response  *nntpr )
      {
        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(nntpr) ;

        fprintf(flog,
                "\n"
                "\tRESPONSE\n") ;
        fprintf(flog,
                "%s",
                nntpr->msg) ;
        return TRUE ;
      }
  

   /* ................................................................... */

