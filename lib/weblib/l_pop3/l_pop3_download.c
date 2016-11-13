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

      #include "weblib/l_pop3/l_pop3_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_POP3_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_pop3Cfg      *pop3Cfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url )
      {
        T_BOOL   ok ;

        /* ... init ... */
        if (dlws->finfo != NULL)
           {
             L_POP3_LOG_PrintUrl(dlws->finfo,url) ;
           }
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "retr...",
                                      0,
                                      url) ;

        /* ... download box list or mail ... */
        if ( 
             ((url->file)    == NULL) 
                       || 
             ((url->file)[0] == '\0') 
                       || 
             (X_STRING_Equal((url->file),"/") == TRUE)
           )
           {
             ok = L_URLFILE_MakeIndexUrl(url) ;
             FALSE_RET_FALSE(ok) ;
             ok = L_POP3_BOX_DownLoadBox(dlws,pop3Cfg,
                                         fpage,url) ;
           }
        else 
           {
             ok = L_POP3_MAIL_DownLoadMail(dlws,pop3Cfg,
                                           fpage,url) ;
           }

        return ok ;
      }


   /* ................................................................... */

