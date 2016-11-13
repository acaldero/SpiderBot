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

      #include "weblib/l_http/l_http_log.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_HTTP_LOG_PrintUrl      ( INOUT  FILE   *flog,
                                          IN     t_url  *url )
      {
        T_CHAR  *urlstr ;
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        fprintf(flog,
                "\n"
                " REQUEST\n") ;
        ok = L_URLSTR_GlobalUrlToRequest(url,&urlstr) ;
        FALSE_RET_FALSE(ok) ;
        fprintf(flog,
                "\t%s\n",
                urlstr) ;
        X_ALLOC_Free( (void **)&(urlstr) ) ;
        return TRUE ;
      }
  
      T_BOOL   L_HTTP_LOG_PrintHeader   ( INOUT  FILE              *flog,
                                          INOUT  t_http_response  *httpr )
      {
        T_BOOL ok ;

        NULL__SET_ERROR__RET_FALSE(flog) ;
        NULL__SET_ERROR__RET_FALSE(httpr) ;
        fprintf(flog,
                "\n"
                " ANSWER\n") ;
        ok = L_HTTP_RESPONSE_ResponseToFile(flog,httpr) ;
        return ok ;
      }


   /* ................................................................... */

