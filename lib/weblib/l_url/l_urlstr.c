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

      #include "weblib/l_url/l_urlstr.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_URLSTR_Empareja_protocol    ( OUT   t_url    *url,
                                                IN    T_CHAR  **str )
      {
        static T_CHAR *L_URLSTR_protocols[] = 
               {
                 "http",
                 "ftp",
                 "file",
                 "news",
                 "nntp",
                 "pop3",
                 "mailto",
                 "gopher",
                 "telnet",
                 "finger",
                 NULL
               } ;
        T_INT i, ret ;

        for (i=0; L_URLSTR_protocols[i] != NULL; i++)
            {
              ret = strncmp( (*str),
                             L_URLSTR_protocols[i],
                             strlen(L_URLSTR_protocols[i]) ) ;
              if (ret == 0)
                 {
                   if (strcmp("news",L_URLSTR_protocols[i]) == 0)
                            url->protocol = X_STRING_StrDup("nntp") ;
                       else url->protocol = X_STRING_StrDup(L_URLSTR_protocols[i]) ;

                   (*str) = (*str) + X_STRING_StrLen(L_URLSTR_protocols[i]) ;
                   if ( (**str) == ':' )
                        (*str) ++ ;
                   if ( (**str) == '/' )
                        (*str) ++ ;
                   if ( (**str) == '/' )
                        (*str) ++ ;
                   return TRUE ;
                 }
            }
        url->protocol = X_STRING_StrDup("http") ;
        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_user     ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_CHAR  *pch ;

        pch = X_STRING_StrChr((*str),'@') ;
        if (pch == NULL)
           {
             return TRUE ;
           }
        (*str) = pch + 1 ;
        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_machine  ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_CHAR  *pch1, *pch2 ;

        url->machine = NULL ;

        /* 
           file
        */
        if ( X_STRING_Equal(url->protocol,"file") == TRUE )
           {
             int ret ;

             url->machine = X_STRING_StrDup("localhost") ;
             ret = strncmp((*str),"localhost",strlen("localhost")) ;
             if (ret == 0)
                 (*str) = (*str) + strlen("localhost") ;
             return TRUE ;
           }

        /* 
           http || ftp 
        */
        pch1 = strchr((*str),'/') ;
        pch2 = strchr((*str),':') ;
        if (pch2 == NULL)
           {
             if (pch1 == NULL)
                {
                  url->machine = X_STRING_StrDup((*str)) ;
                  (*str) = (*str) + X_STRING_StrLen((*str)) ;
                  return TRUE ;
                }
             if (pch1 != NULL)
                {
                  pch1[0] = '\0' ;
                  url->machine = X_STRING_StrDup((*str)) ;
                  (*str) = pch1 ;
                  pch1[0] = '/' ;
                  return TRUE ;
                }
           }
        if (pch2 != NULL)
           {
             pch2[0] = '\0' ;
             url->machine = X_STRING_StrDup((*str)) ;
             pch2[0] = ':' ;
             (*str) = pch2 ;
             return TRUE ;
           }
        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_port     ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_CHAR  *pch1, *pch2 ;

        /* ... default port ... */
        url->port = htons(80) ;
        if (X_STRING_Equal(url->protocol,"http") == TRUE)
            url->port = htons(80) ;
        if (X_STRING_Equal(url->protocol,"ftp") == TRUE)
            url->port = htons(21) ;
        if (X_STRING_Equal(url->protocol,"file") == TRUE)
            url->port = htons(0) ;
        if (X_STRING_Equal(url->protocol,"nntp") == TRUE)
            url->port = htons(119) ;
        if (X_STRING_Equal(url->protocol,"news") == TRUE)
            url->port = htons(119) ;
        if (X_STRING_Equal(url->protocol,"pop3") == TRUE)
            url->port = htons(110) ;
        if (X_STRING_Equal(url->protocol,"finger") == TRUE)
            url->port = htons(79) ;

        /* ... scanning port ... */
        /* 
           file
        */
        if (X_STRING_Equal(url->protocol,"file") == TRUE)
            return TRUE ;

        /* 
           http || ftp 
        */
        pch1 = X_STRING_StrChr((*str),':') ;
        if (pch1 == NULL)
           {
             return TRUE ;
           }
        pch1 ++ ; /* skip ':' */
        pch2 = strchr(pch1,'/') ;
        if (pch2 == NULL)
           {
             url->port = htons(atoi(pch1)) ;
             (*str) = (*str) + X_STRING_StrLen((*str)) ;
             return TRUE ;
           }
        if (pch2 != NULL)
           {
             pch2[0] = '\0' ;
             url->port = htons(atoi(pch1)) ;
             pch2[0] = '/' ;
             (*str) = pch2 ;
             return TRUE ;
           }
        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_file     ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_CHAR  *pch1 ;

        pch1 = X_STRING_StrChr((*str),'#') ;
        if (pch1 != NULL)
           {
             pch1[0] = '\0' ;
             url->file = X_STRING_StrDup((*str)) ;
             (*str) = (*str) + X_STRING_StrLen(pch1) ;
             pch1[0] = '#' ;
             return TRUE ;
           }
        pch1 = X_STRING_StrChr((*str),'?') ;
        if (pch1 != NULL)
           {
             pch1[0] = '\0' ;
             url->file = X_STRING_StrDup((*str)) ;
             pch1[0] = '?' ;
             (*str) = pch1 ;
             return TRUE ;
           }

        /* ... all is file ... */
        if ((*str)[0] != '\0')
           {
             url->file = X_STRING_StrDup((*str)) ;
             (*str) = (*str) + X_STRING_StrLen((*str)) ;
             return TRUE ;
           }
        url->file = X_STRING_StrDup("/") ;
        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_relative ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_CHAR  *pch1, *pch2 ;

        url->relative = NULL ;
        pch1 = X_STRING_StrChr((*str),'#') ;
        if (pch1 == NULL)
           {
             return TRUE ;
           }
        pch1 ++ ; /* skip '#' */
        pch2 = strchr(pch1,'?') ;
        if (pch2 == NULL)
           {
             url->relative = X_STRING_StrDup((*str)) ;
             (*str) = (*str) + X_STRING_StrLen((*str)) ;
             return TRUE ;
           }
        if (pch2 != NULL)
           {
             pch2[0] = '\0' ;
             url->relative = X_STRING_StrDup(pch1) ;
             (*str) = pch2 ;
             pch2[0] = '?' ;
             return TRUE ;
           }

        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_params   ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_CHAR  *pch1 ;

        url->params = NULL ;
        pch1 = X_STRING_StrChr((*str),'?') ;
        if (pch1 == NULL)
           {
             return TRUE ;
           }
        pch1 ++ ; /* skip '?' */
        url->params = X_STRING_StrDup(pch1) ;
        (*str) = (*str) + X_STRING_StrLen((*str)) ;
        return TRUE ;
      }

      T_BOOL    L_URLSTR_Empareja_url      ( OUT   t_url    *url,
                                             IN    T_CHAR  **str )
      {
        T_BOOL ok ;

        ok = L_URLSTR_Empareja_protocol(url,str) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_URLSTR_Empareja_user(url,str) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_URLSTR_Empareja_machine(url,str) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_URLSTR_Empareja_port(url,str) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_URLSTR_Empareja_file(url,str) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_URLSTR_Empareja_relative(url,str) ;
        FALSE_RET_FALSE(ok) ;
        ok = L_URLSTR_Empareja_params(url,str) ;
        FALSE_RET_FALSE(ok) ;
        return TRUE ;
      }

      T_BOOL    L_URLSTR_StringToUrl  ( OUT   t_url    *url,
                                        IN    T_CHAR   *str )
      {
        T_CHAR  *pch, *fch ;
        T_BOOL   ok ;

        fch = pch = X_STRING_StrDup(str) ;
        NULL_RET_FALSE(pch) ;
        ok  = L_URLSTR_Empareja_url(url,&pch) ;
        X_ALLOC_Free( (void **)&(fch) ) ;
        return ok ;
      }

      T_BOOL    L_URLSTR_UrlToString  ( IN     t_url    *url,
                                        OUT    T_CHAR  **str )
      {
        T_BOOL ok ;

        /* ... check ... */
        NULL_RET_FALSE(url) ;
        NULL_RET_FALSE(str) ;

        /* ... base request ... */
        /* 
           file
        */
        if ( X_STRING_Equal(url->protocol,"file") == TRUE )
           {
             (*str) = X_STRING_Dsprintf("file://%s%s",
                                     url->machine, 
                                     url->file) ;
             NULL_RET_FALSE((*str)) ;
             return TRUE ;
           }

        /* 
           http || ftp 
        */
        (*str) = X_STRING_Dsprintf("%s://%s:%i%s",
                                url->protocol, 
                                url->machine, 
                                ntohs(url->port), /*check*/
                                url->file) ;
        NULL_RET_FALSE((*str)) ;

        /* ... relative && params ... */
        ok = TRUE ;
        if ( url->relative != NULL )
             ok = X_STRING_Add2StrToStr(str,"#",url->relative) ;
        FALSE_RET_FALSE(ok) ;
        if ( url->params != NULL )
             ok = X_STRING_Add2StrToStr(str,"?",url->params) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }

      T_BOOL    L_URLSTR_GlobalUrlToRequest   ( IN     t_url    *url,
                                                OUT    T_CHAR  **str )
      {
        T_BOOL ok ;

        /* ... check ... */
        NULL_RET_FALSE(url) ;
        NULL_RET_FALSE(str) ;

        /* ... file ... */
        if ( (url->file)[0] != '/' )
             (*str) = X_STRING_Dsprintf("%s://%s:%i/%s",
                                     url->protocol, 
                                     url->machine, 
                                     ntohs(url->port), /*check*/
                                     url->file) ;
        if ( (url->file)[0] == '/' )
             (*str) = X_STRING_Dsprintf("%s://%s:%i%s",
                                     url->protocol, 
                                     url->machine, 
                                     ntohs(url->port), /*check*/
                                     url->file) ;
        NULL_RET_FALSE((*str)) ;

        /* ... params ... */
        ok = TRUE ;
        if ( url->params != NULL )
             ok = X_STRING_Add2StrToStr(str,"?",url->params) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }

      T_BOOL    L_URLSTR_LocalUrlToRequest    ( IN     t_url    *url,
                                                OUT    T_CHAR  **str )
      {
        T_BOOL ok ;

        /* ... check ... */
        NULL_RET_FALSE(url) ;
        NULL_RET_FALSE(str) ;

        /* ... file ... */
        if ( (url->file)[0] == '/' )
             (*str) = X_STRING_StrDup(url->file) ;
        if ( (url->file)[0] != '/' )
             (*str) = X_STRING_ConcatInStr("/",url->file,"") ;
        NULL_RET_FALSE((*str)) ;

        /* ... params ... */
        ok = TRUE ;
        if ( url->params != NULL )
             ok = X_STRING_Add2StrToStr(str,"?",url->params) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }


  /* ...................................................................... */

