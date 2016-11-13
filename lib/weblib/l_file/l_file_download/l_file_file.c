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

      #include "weblib/l_file/l_file_download/l_file_file.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FILE_FILE_rwfile         ( INOUT  t_downLoadWS     *dlws,
                                           IN     T_LONG            fsize,
                                           IN     t_fileCfg        *fileCfg,
                                           INOUT  FILE            **fpage )
      {
        #define c_RNSACK_BSIZE (32*1024)
 
        T_CHAR   *buff ;
        T_LONG    total_a_leer, leidos ;
        T_INT     result, size_buff ;
        T_LONG           number_urls ;

        buff = X_ALLOC_Malloc(c_RNSACK_BSIZE) ;
        NULL_RET_FALSE(buff) ;
        leidos       = 0L ;
        total_a_leer = fsize ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), sizeof(buff) ) ;
        number_urls  = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        /* ... first read is out of while ... */
        result = L_FILE_COMMAND_Read(buff,size_buff,(fileCfg->sd)) ;
        while ( result > 0 )
        {
          fwrite(buff,result,1,(*fpage)) ;
          leidos = leidos + result ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_a_leer) ;
          result = L_FILE_COMMAND_Read(buff,size_buff,(fileCfg->sd)) ;
        }
        dlws->currentBytes += leidos ;
        X_ALLOC_Free( (void **)&buff ) ;
        if ( result < 0 )
             return FALSE ;
        return TRUE ;
      }

      T_BOOL  L_FILE_FILE_DownLoadFile   ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_fileCfg      *fileCfg,
                                           INOUT  FILE          **fpage,
                                           INOUT  t_url          *url,
                                           IN     T_LONG          fsize )
      {
        T_BOOL  ok ;

        fileCfg->sd  = L_FILE_COMMAND_Open(url->file,"rb") ;
        NULL_RET_FALSE(fileCfg->sd) ;
        ok           = L_FILE_FILE_rwfile(dlws,fsize,fileCfg,fpage) ;
        L_FILE_COMMAND_Close(fileCfg->sd) ;
        return ok ;
      }


   /* ................................................................... */

