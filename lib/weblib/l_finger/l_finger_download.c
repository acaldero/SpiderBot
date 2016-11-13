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

      #include "weblib/l_finger/l_finger_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FINGER_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                              IN     t_fingerCfg    *fingerCfg,
                                              INOUT  FILE          **fpage,
                                              IN     t_url          *url )
      {
        T_BOOL   ok ;

        /* ... init ... */
        if (dlws->finfo != NULL)
           {
             L_FINGER_LOG_PrintUrl(dlws->finfo,url) ;
           }

        /* ... user or machine ... */
        if (
             ((url->file)    == NULL)
                       ||
             ((url->file)[0] == '\0')
                       ||
             (X_STRING_Equal((url->file),"/") == TRUE)
                       ||
             (X_STRING_Equal((url->file),"\\") == TRUE)
           )
           {
             /* ... machine ... */
             ok = L_FINGER_MACHINE_DownLoad(dlws,fingerCfg,fpage,url) ;
             if (ok == FALSE)
                {
                  L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                                "empty...",
                                                0,
                                                url) ;
                }
           }
           else
           {
             /* ... user ... */
             ok = L_FINGER_USER_DownLoad(dlws,fingerCfg,fpage,url) ;
             if (ok == FALSE)
                {
                  L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                                "empty...",
                                                0,
                                                url) ;
                }
           }

        return ok ;
      }


   /* ................................................................... */

