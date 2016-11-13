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

      #include "weblib/l_http/l_http_response.h"


   /* ... Function / Funciones .......................................... */

      T_BOOL    L_HTTP_RESPONSE_Read    ( INOUT  t_sock            *sd,
                                          OUT    t_http_response   *httpr )
      {
        T_BOOL  ok, eof ;
        T_INT   result ;
        T_CHAR  key[1024] ;
        T_CHAR  value[1024] ;
        T_CHAR  line[1024] ;
  

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(sd) ;
        NULL__SET_ERROR__RET_FALSE(httpr) ;

        eof    = X_SOCKET_ReadLine(sd,line,sizeof(line)) ;
        result = sscanf(line,"%[^ ]%*[ ]%[^\n\r]\n",key,value) ;
        if ( result == -1 ) 
             return FALSE ;
        if ( (eof == TRUE) && (result <= 0) )
             return FALSE ;

        /* ... version ... */
        ok = L_MIME_Insert(httpr,"HttpVersion",key) ;
        if (ok == FALSE) 
            return FALSE ;

        /* ... codigo ... */
        ok = L_MIME_Insert(httpr,"Codigo",value) ;
        if (ok == FALSE) 
            return FALSE ;

        /* ... resto ... */
        X_SOCKET_ReadLine(sd,line,sizeof(line)) ;
        result = sscanf(line,"%[^:\n\r]: %[^\n\r]",key,value) ;
        while (result > 1) 
        {
          ok = L_MIME_Insert(httpr,key,value) ;
          if (ok == FALSE) 
              return FALSE ;

          X_SOCKET_ReadLine(sd,line,sizeof(line)) ;
          result = sscanf(line,"%[^:\n\r]: %[^\n\r]",key,value) ;
        } 

        return TRUE ;
      }

      T_INT   L_HTTP_RESPONSE_readChuckSize    ( INOUT  t_sock         *sd )
      {
        T_INT   value ;
        T_CHAR  buff[1024] ;

        NULL__SET_ERROR__RET_FALSE(sd) ;
        do 
        {
          X_SOCKET_ReadLine(sd,
                            buff,
                            sizeof(buff)) ;
        } while (L_LINE_enter(buff) == TRUE) ;
        value = L_HEX_HexToDec(buff) ;
        return value ;
      }


  /* .................................................................... */

