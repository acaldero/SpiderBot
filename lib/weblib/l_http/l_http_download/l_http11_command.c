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

      #include "weblib/l_http/l_http_download/l_http11_command.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_HTTP11_COMMAND_GET   ( INOUT  t_sock     *sd,
                                         IN     t_url      *url,
                                         IN     T_CHAR     *clientName,
                                         IN     T_CHAR     *ident,
                                         IN     T_BOOL      acceptFullUrl,
                                         IN     T_BOOL      acceptHost )
      {
        T_BOOL   ok ;
        T_CHAR  *fullUrl ;
        T_CHAR  *hostField ;
        T_CHAR  *reqstr ;
  
        /* ... url to string ... */
        if (acceptFullUrl == FALSE)
                 ok = L_URLSTR_LocalUrlToRequest(url,&fullUrl) ;
            else ok = L_URLSTR_GlobalUrlToRequest(url,&fullUrl) ;
        FALSE_RET_FALSE(ok) ;

        /* ... url to string ... */
        if (acceptHost == FALSE)
                 hostField = X_STRING_StrDup("") ;
            else hostField = X_STRING_Dsprintf("Host: %s\n",url->machine) ;
        NULL_RET_FALSE(hostField) ;

        /* ... request ... */
        if (ident == NULL)
           {
             reqstr = X_STRING_Dsprintf("GET %s HTTP/1.1\n"
                                        "User-Agent: %s\n"
                                        "Accept: */*\n"
                                        "%s"
                                        "\n",
                                        fullUrl,
                                        clientName,
                                        hostField) ;
           }
        else
           {
             unsigned char *encodeId ;
             unsigned int   encodeIdLen ;
  
             ok = L_BASE64_encode((unsigned char  *)ident,
                                  (unsigned int    )X_STRING_StrLen(ident),
                                  (unsigned char **)&encodeId,
                                  (unsigned int   *)&encodeIdLen) ;
             FALSE_RET_FALSE(ok) ;
             reqstr = X_STRING_Dsprintf("GET %s HTTP/1.1\n"
                                        "User-Agent: %s\n"
                                        "Accept: */*\n"
                                        "%s"
                                        "Authorization: Basic %s\n"
                                        "\n",
                                        url,
                                        clientName,
                                        hostField,
                                        encodeId) ;
             X_ALLOC_Free((void **)&encodeId) ;
           }
        NULL_RET_FALSE(reqstr) ;
        ok = L_HTTP11_COMMAND_Request(sd,reqstr) ;

        /* ... free ... */
        X_ALLOC_Free((void **)&fullUrl) ;
        X_ALLOC_Free((void **)&hostField) ;
        X_ALLOC_Free((void **)&reqstr) ;

        return ok ;
      } 

      T_BOOL    L_HTTP11_COMMAND_HEAD  ( INOUT  t_sock     *sd,
                                         IN     t_url      *url,
                                         IN     T_CHAR     *clientName,
                                         IN     T_BOOL      acceptFullUrl,
                                         IN     T_BOOL      acceptHost )
      {
        T_BOOL   ok ;
        T_CHAR  *fullUrl ;
        T_CHAR  *hostField ;
        T_CHAR  *reqstr ;
  
        /* ... url to string ... */
        if (acceptFullUrl == FALSE)
                 ok = L_URLSTR_LocalUrlToRequest(url,&fullUrl) ;
            else ok = L_URLSTR_GlobalUrlToRequest(url,&fullUrl) ;
        FALSE_RET_FALSE(ok) ;

        /* ... url to string ... */
        if (acceptHost == FALSE)
                 hostField = X_STRING_StrDup("") ;
            else hostField = X_STRING_Dsprintf("Host: %s\n",fullUrl) ;
        NULL_RET_FALSE(hostField) ;

        /* ... request ... */
        reqstr = X_STRING_Dsprintf("HEAD %s HTTP/1.1\n"
                                   "User-Agent: %s\n"
                                   "Accept: */*\n"
                                   "%s"
                                   "\n",
                                   fullUrl,
                                   clientName,
                                   hostField) ;
        NULL_RET_FALSE(reqstr) ;
        ok = L_HTTP11_COMMAND_Request(sd,reqstr) ;

        /* ... free ... */
        X_ALLOC_Free((void **)&fullUrl) ;
        X_ALLOC_Free((void **)&hostField) ;
        X_ALLOC_Free((void **)&reqstr) ;

        return ok ;
      } 
  

/* ...................................................................... */

