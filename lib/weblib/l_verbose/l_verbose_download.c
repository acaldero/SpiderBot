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

      #include "weblib/l_verbose/l_verbose_download.h"


   /* ... Functions / Funciones ......................................... */

      void   L_VERBOSE_DOWNLOAD_currentReaded ( INOUT  t_downLoadWS     *dlws,
                                                IN     T_LONG            readed,
                                                IN     T_LONG            total )
      {
        if ( 
             (dlws->verbose == ON)
                    && 
             (readed > 0) 
           )
           {
             if (total == 0)
                      X_PRINT_printf("\r[url %li/%li] [bytes %li/unknow]",
                                     (dlws->i),
                                     (T_LONG)L_URLLI_NumberUrls(dlws->urllist),
                                     readed) ;
                 else X_PRINT_printf("\r[url %li/%li] [bytes %li/%li]",
                                     (dlws->i),
                                     (T_LONG)L_URLLI_NumberUrls(dlws->urllist),
                                     readed,
                                     total) ;
             fflush(stdout) ;
           }
      }

      void   L_VERBOSE_DOWNLOAD_currentChunked ( INOUT  t_downLoadWS  *dlws,
                                                 IN     T_LONG         creaded,
                                                 IN     T_LONG         ctotal,
                                                 IN     T_LONG         freaded,
                                                 IN     T_LONG         ftotal )
      {
        if ( 
             (dlws->verbose == ON)
           )
           {
             X_PRINT_printf("\r[url %li/%li] ",
                            (dlws->i),
                            (T_LONG)L_URLLI_NumberUrls(dlws->urllist)) ;
             if (freaded != 0)
                {
                  if (ftotal == 0)
                           X_PRINT_printf("[bytes %li/unknow] ",
                                          freaded) ;
                      else X_PRINT_printf("[bytes %li/%li] ",
                                          freaded,
                                          ftotal) ;
                }
             if (creaded != 0)
                {
                  if (ctotal == 0)
                           X_PRINT_printf("[chunk %li/unknow] ",
                                          creaded) ;
                      else X_PRINT_printf("[chunk %li/%li] ",
                                          creaded,
                                          ctotal) ;
                }
             fflush(stdout) ;
           }
      }

      void   L_VERBOSE_DOWNLOAD_currentUrl  ( INOUT  t_downLoadWS   *dlws,
                                              IN     T_CHAR         *codigo,
                                              IN     T_LONG          size,
                                              IN     t_url          *url )
      {
        if (dlws->verbose == ON)
           {
             X_PRINT_printf("\r%-15s %-10li %s%-40s\n"
                            "[url %li/%li] [waiting...]",
                            (codigo == NULL) ? "unknow" : codigo,
                            size,
                            (url->params == NULL) ? "" : "?...",
                            url->file,
                            (dlws->i),
                            (T_LONG)L_URLLI_NumberUrls(dlws->urllist)) ;
           }
        else
           {
             T_INT lenstr ;

             lenstr = X_STRING_StrLen(url->file) ;
             if ( lenstr < 35 )
                {
                   X_PRINT_printf("\r%-15s %-10li "
                                  "%-35s "
                                  "[%-6li/%-6li]", 
                                  (codigo == NULL) ? "unknow" : codigo,
                                  size,
                                  url->file,
                                  (dlws->i),
                                  (T_LONG)L_URLLI_NumberUrls(dlws->urllist)) ;
                }
             else 
                {
                   X_PRINT_printf("\r%-15s %-10li "
                                  "...%-32s "
                                  "[%-6li/%-6li]", 
                                  (codigo == NULL) ? "unknow" : codigo,
                                  size,
                                  ((url->file) + lenstr - 30),
                                  (dlws->i),
                                  (T_LONG)L_URLLI_NumberUrls(dlws->urllist)) ;
                }
           }
      }

      void   L_VERBOSE_DOWNLOAD_currentPage ( INOUT  t_downLoadWS     *dlws,
                                              IN     t_http_response *httpr,
                                              IN     t_url            *url )
      {
        T_LONG   number_urls ;
        T_CHAR  *httph ;
        T_CHAR  *codigo ;
        T_LONG   size ;

        number_urls = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;
        httph       = L_HTTP_RESPONSE_getField(httpr,"Content-Length") ;
        if (httph == NULL)
                 size = 0L ;
            else size = atoi(httph) ;
        codigo      = L_HTTP_RESPONSE_getField(httpr,"Codigo") ;
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      codigo,
                                      size,
                                      url) ;
      }

      void   L_VERBOSE_DOWNLOAD_TimeOut ( void )
      {
        X_PRINT_printf( "\n"
                        "HTTP Server give a conection TimeOut.\n"
                        "please, use '-resume' option to continue :\n"
                        "(see help for more information)\n"
                        "\n" ) ;
      }


   /* ................................................................... */

