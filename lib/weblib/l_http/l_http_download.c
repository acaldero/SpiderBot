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

      #include "weblib/l_http/l_http_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_HTTP_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_httpCfg      *webCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url )
      {
	switch (webCfg->httpVer)
        {
          case v_0_9 :
	       return L_HTTP09_PAGE_DownLoadPage(dlws,webCfg,fpage,url) ;
          case v_1_0 :
	       return L_HTTP10_PAGE_DownLoadPage(dlws,webCfg,fpage,url) ;
          case v_1_1 :
	       return L_HTTP11_PAGE_DownLoadPage(dlws,webCfg,fpage,url) ;
        }

        return FALSE ;
      }


   /* ................................................................... */

