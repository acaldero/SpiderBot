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

      #include "weblib/l_ftp/l_ftp_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FTP_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_ftpCfg       *ftpCfg,
                                           INOUT  FILE          **fpage,
                                           IN     t_url          *url )
      {
        T_BOOL   ok ;

        /* ... init ... */
        if (dlws->finfo != NULL)
           {
             L_FTP_LOG_PrintUrl(dlws->finfo,url) ;
           }

        /* ... try first as file, else is directory ... */
        ok = L_FTP_FILE_DownLoadFile(dlws,ftpCfg,fpage,url) ;
        if (ok == FALSE)
           {
             ok = L_URLFILE_MakeIndexUrl(url) ;
             FALSE_RET_FALSE(ok) ;
             ok = L_FTP_DIR_DownLoadDir(dlws,ftpCfg,fpage,url) ;
           }
        if (ok == FALSE)
           {
             L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                           "empty...",
                                           0,
                                           url) ;
           }

        return ok ;
      }


   /* ................................................................... */

