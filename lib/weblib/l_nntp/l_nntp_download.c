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

      #include "weblib/l_nntp/l_nntp_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_NNTP_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_nntpCfg       *nntpCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url )
      {
        T_BOOL   ok ;

        /* ... init ... */
        if (dlws->finfo != NULL)
           {
             L_NNTP_LOG_PrintUrl(dlws->finfo,url) ;
           }
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "retr...",
                                      0,
                                      url) ;

        /* ... newsgroup, group, news ... */
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
             /* newsgroup */
             ok = L_NNTP_NEWSGROUP_DownLoad(dlws,nntpCfg,fpage,url) ;
             FALSE_RET_FALSE(ok) ;
           }
        else if (
                  (
                    (strchr((url->file)+1,'/') == NULL)
                                  &&
                    (strchr((url->file)+1,'\\') == NULL)
                  )
                                ||
                  (
                    (strchr((url->file)+1,'/') != NULL)
                                  &&
                    (strchr((url->file)+1,'/')[1] == '\0')
                  )
                                ||
                  (
                    (strchr((url->file)+1,'\\') != NULL)
                                  &&
                    (strchr((url->file)+1,'\\')[1] == '\0')
                  )
                )
           {
             T_CHAR  *pch ;

             /* group */
             pch = strchr((url->file)+1,'/') ;
             if ( pch == NULL )
                  pch = strchr((url->file)+1,'\\') ;
             if ( pch != NULL )
                  (*pch) = '\0' ;
             ok = L_NNTP_GROUP_DownLoad(dlws,nntpCfg,fpage,url) ;
             FALSE_RET_FALSE(ok) ;
           }
        else
           {
             /* news */
             ok = L_NNTP_NEWS_DownLoad(dlws,nntpCfg,fpage,url) ;
             FALSE_RET_FALSE(ok) ;
           }

        return ok ;
      }


   /* ................................................................... */

