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

      #include "weblib/l_file/l_file_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FILE_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fileCfg      *fileCfg,
                                            INOUT  FILE          **fpage,
                                            INOUT  t_url          *url )
      {
        T_BOOL           ok ;
        struct stat      statHeader ;
        int              ret ;

        /* ... init ... */
        ret  = L_FILE_COMMAND_stat(url->file,&statHeader) ;
        if (ret == -1)
           {
             L_FILE_LOG_PrintUrl(dlws->finfo,url) ;
             L_FILE_LOG_PrintNotFound(dlws->finfo) ;
             L_VERBOSE_LOG_applyTo(dlws,"(e) file not found") ;
             return FALSE ;
           }
        else /* (ret != -1) */
           {
             L_FILE_LOG_PrintUrl(dlws->finfo,url) ;
             L_FILE_LOG_PrintHeader(dlws->finfo,&statHeader) ;
           }
        if (L_FILE_COMMAND_isDir( &(statHeader) ) )
             L_URLFILE_MakeIndexUrl(url) ;
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "200",
                                      (T_U_LONG)(statHeader.st_size),
                                      url) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;

	NULL_RET_FALSE((*fpage)) ;
        if (L_FILE_COMMAND_isDir( &(statHeader) ) )
                  ok = L_FILE_DIR_DownLoadDir   (dlws,fileCfg,fpage,url) ;
             else ok = L_FILE_FILE_DownLoadFile (dlws,fileCfg,fpage,url,
                                                (T_LONG)(statHeader.st_size)) ;

        return ok ;
      }


   /* ................................................................... */

