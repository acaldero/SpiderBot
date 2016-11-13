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

      #include "weblib/l_url/l_url.h"


   /* ... Functions / Funciones ......................................... */

      t_url    *L_URL_CreatEmpty   ( void )
      {
        t_url *urlret ;

        urlret = X_ALLOC_Malloc(c_URL) ;
        NULL_RET_NULL(urlret) ;
        urlret->protocol = NULL ;
        urlret->machine  = NULL ;
        urlret->file     = NULL ;
        urlret->relative = NULL ;
        urlret->params   = NULL ;
        urlret->port     = 0 ;
        return urlret ;
      }

      t_url    *L_URL_Creat        ( IN     T_CHAR    *protocol,
                                     IN     T_CHAR    *machine,
                                     IN     T_CHAR    *file,
                                     IN     T_CHAR    *relative,
                                     IN     T_CHAR    *params,
                                     IN     T_INT      port )
      {
        t_url *urlret ;

        urlret = X_ALLOC_Malloc(c_URL) ;
        NULL_RET_FALSE(urlret) ;
        urlret->protocol = X_STRING_StrDup(protocol) ;
        urlret->machine  = X_STRING_StrDup(machine ) ;
        urlret->file     = X_STRING_StrDup(file    ) ;
        urlret->relative = X_STRING_StrDup(relative) ;
        urlret->params   = X_STRING_StrDup(params  ) ;
        urlret->port     = port ;
        return urlret ;
      }

      t_url    *L_URL_CreatFrom    ( IN     T_CHAR    *protocol,
                                     IN     T_CHAR    *machine,
                                     IN     T_CHAR    *file,
                                     IN     T_CHAR    *relative,
                                     IN     T_CHAR    *params,
                                     IN     T_INT      port )
      {
        t_url *urlret ;

        urlret = X_ALLOC_Malloc(c_URL) ;
        NULL_RET_FALSE(urlret) ;
        urlret->protocol = protocol ;
        urlret->machine  = machine  ;
        urlret->file     = file     ;
        urlret->relative = relative ;
        urlret->params   = params ;
        urlret->port     = port ;
        return urlret ;
      }

      T_BOOL    L_URL_FillFrom     ( OUT    t_url     *url,
                                     IN     T_CHAR    *protocol,
                                     IN     T_CHAR    *machine,
                                     IN     T_CHAR    *file,
                                     IN     T_CHAR    *relative,
                                     IN     T_CHAR    *params,
                                     IN     T_INT      port )
      {
        NULL_RET_FALSE(url) ;
        url->protocol = protocol ;
        url->machine  = machine  ;
        url->file     = file     ;
        url->relative = relative ;
        url->params   = params ;
        url->port     = port ;
        return TRUE ;
      }

      t_url    *L_URL_UrlDup       ( IN     t_url    *url )
      {
        t_url *urlret ;

        NULL_RET_NULL(url) ;
        urlret = X_ALLOC_Malloc(c_URL) ;
        NULL_RET_NULL(urlret) ;
        urlret->protocol = X_STRING_StrDup(url->protocol) ;
        urlret->machine  = X_STRING_StrDup(url->machine ) ;
        urlret->file     = X_STRING_StrDup(url->file    ) ;
        urlret->relative = X_STRING_StrDup(url->relative) ;
        urlret->params   = X_STRING_StrDup(url->params  ) ;
        urlret->port     = url->port ;
        return urlret ;
      }

      T_BOOL    L_URL_Destroy      ( INOUT  t_url    **url )
      {
        NULL_RET_TRUE((*url)) ;
        X_ALLOC_Free( (void **)&((*url)->protocol) ) ;
        X_ALLOC_Free( (void **)&((*url)->machine ) ) ;
        X_ALLOC_Free( (void **)&((*url)->file    ) ) ;
        X_ALLOC_Free( (void **)&((*url)->relative) ) ;
        X_ALLOC_Free( (void **)&((*url)->params  ) ) ;
        X_ALLOC_Free( (void **)(url) ) ;
        return TRUE ;
      }

      T_BOOL    L_URL_Empty        ( INOUT  t_url     *url )
      {
        NULL_RET_TRUE(url) ;
        X_ALLOC_Free( (void **)&(url->protocol) ) ;
        X_ALLOC_Free( (void **)&(url->machine ) ) ;
        X_ALLOC_Free( (void **)&(url->file    ) ) ;
        X_ALLOC_Free( (void **)&(url->relative) ) ;
        X_ALLOC_Free( (void **)&(url->params  ) ) ;
        return TRUE ;
      }

      T_BOOL    L_URL_Equal        ( IN     t_url    *url1,
                                     IN     t_url    *url2 )
      {
        if (url1 == url2)
            return TRUE ;
        NULL_RET_FALSE(url1) ;
        NULL_RET_FALSE(url2) ;

        return ( 
                 (X_STRING_Equal(url1->protocol,url2->protocol) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->machine,url2->machine) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->file,url2->file) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->relative,url2->relative) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->params,url2->params) == TRUE)
                                   &&
                       (url1->port == url2->port) 
               ) ;
      }

      T_BOOL    L_URL_EqualBase    ( IN     t_url    *url1,
                                     IN     t_url    *url2 )
      {
        if (url1 == url2)
            return TRUE ;
        return ( 
                 (X_STRING_Equal(url1->protocol,url2->protocol) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->machine,url2->machine) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->file,url2->file) == TRUE)
                                   &&
                 (X_STRING_Equal(url1->params,url2->params) == TRUE)
                                   &&
                       (url1->port == url2->port) 
               ) ;
      }

      T_INT     L_URL_UrlCmp        ( IN     t_url     *url1,
                                      IN     t_url     *url2 )
      {
        T_INT result ;

        if (url1 == url2)
            return 0 ;

        /* ... protocol ... */
        result = X_STRING_StrCmp(url1->protocol,url2->protocol) ;
        if (result != 0)
            return result ;

        /* ... machine ... */
        result = X_STRING_StrCmp(url1->machine,url2->machine) ;
        if (result != 0)
            return result ;

        /* ... file ... */
        result = X_STRING_StrCmp(url1->file,url2->file) ;
        if (result != 0)
            return result ;

        /* ... params ... */
        result = X_STRING_StrCmp(url1->params,url2->params) ;
        if (result != 0)
            return result ;

        /* ... relative ... */
        result = X_STRING_StrCmp(url1->relative,url2->relative) ;
        if (result != 0)
            return result ;

        /* ... port ... */
        if (url1->port < url2->port)
            return -1 ;
        if (url1->port > url2->port)
            return  1 ;
        return  0 ;
      }

      T_INT     L_URL_UrlBinCmp     ( IN     t_url     *url1,
                                      IN     t_url     *url2 )
      {
        T_INT result ;

        /* ... file ... */
        result = X_STRING_StrCmp(url1->file,url2->file) ;
        if (result != 0)
            return result ;

        /* ... protocol ... */
        result = X_STRING_StrCmp(url1->protocol,url2->protocol) ;
        if (result != 0)
            return result ;

        /* ... machine ... */
        result = X_STRING_StrCmp(url1->machine,url2->machine) ;
        if (result != 0)
            return result ;

        /* ... params ... */
        result = X_STRING_StrCmp(url1->params,url2->params) ;
        if (result != 0)
            return result ;

        /* ... port ... */
        if (url1->port < url2->port)
            return -1 ;
        if (url1->port > url2->port)
            return  1 ;
        return  0 ;
      }


  /* ...................................................................... */

