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

      #include "weblib/l_pop3/l_pop3_log.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_POP3_LOG_PrintUrl       ( INOUT  FILE    *flog,
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
  
      T_BOOL   L_POP3_LOG_PrintResponse  ( INOUT  FILE             *flog,
                                           IN     t_pop3_response  *pop3r )
      {
        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        fprintf(flog,
                "\n"
                "\tRESPONSE\n") ;
        fprintf(flog,
                "%s",
                pop3r->msg) ;
        return TRUE ;
      }
  

   /* ................................................................... */

