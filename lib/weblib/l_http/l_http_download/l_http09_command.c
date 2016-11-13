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

      #include "weblib/l_http/l_http_download/l_http09_command.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_HTTP09_COMMAND_GET   ( INOUT  t_sock     *sd,
                                         IN     T_CHAR     *url,
                                         IN     T_CHAR     *HttpVer,
                                         IN     T_CHAR     *clientName )
      {
        T_CHAR  *reqstr ;
        T_BOOL   ok ;
  
        reqstr = X_STRING_Dsprintf("GET %s %s\n"
                                   "User-Agent: %s\n"
                                   "Accept: */*\n"
                                   "\n",
                                   url,HttpVer,clientName) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_HTTP09_COMMAND_Request(sd,reqstr) ;
        X_ALLOC_Free((void **)&reqstr) ;
        return ok ;
      } 
  

/* ...................................................................... */

