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

      #include "weblib/l_url/l_urlstream.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_URLSTREAM_UrlToFile         ( IN     t_url    *url,
                                                OUT    FILE     *fout )
      {
        NULL_RET_FALSE(url) ;
        NULL_RET_FALSE(fout) ;

        /*
           file
        */
        if (X_STRING_Equal(url->protocol,"file") == TRUE)
           {
             fprintf(fout,"file://%s%s",
                          url->machine,
                          url->file) ;
             fprintf(fout,"\n") ;
             return TRUE ;
           }

        /*
           http || ftp
        */
        fprintf(fout,"%s://%s:%i%s",
                     url->protocol,
                     url->machine,
                     ntohs(url->port),
                     url->file) ;
        if (url->relative != NULL)
            fprintf(fout,"#%s",
                         url->relative) ;
        if (url->params != NULL)
            fprintf(fout,"?%s",
                         url->params) ;
        fprintf(fout,"\n") ;
        return TRUE ;
      }

      T_BOOL    L_URLSTREAM_FileToUrl          ( IN     t_url    *url,
                                                 OUT    FILE     *fin ) 
      {
        #define  IOBUFF_SIZE  4*1024

        T_CHAR   iobuff[IOBUFF_SIZE] ;
        T_U_INT  last ;

        NULL_RET_FALSE(url) ;
        NULL_RET_FALSE(fin) ;
        if (feof(fin))
            return FALSE ;
        if (fgets(iobuff,sizeof(iobuff),fin) == NULL) 
            return FALSE ;
        last = X_STRING_StrLen(iobuff) ;
	if (last > 0)
	    last -- ;
        iobuff[last] = '\0' ;
        if (last == 0)
            return FALSE ;
        return L_URLSTR_StringToUrl(url,iobuff) ;
      }


  /* ...................................................................... */

