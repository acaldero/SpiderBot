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

      #include "weblib/l_ftp/l_ftp_download/l_ftp_file.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_FTP_FILE_rwfile       ( INOUT  t_downLoadWS   *dlws,
                                        INOUT  T_LONG          total_to_read,
                                        INOUT  int             infile,
                                        INOUT  FILE          **fpage )
      {
        T_LONG    leidos ;
        T_INT     result, size_buff ;
        T_LONG    number_urls ;

          #define c_FTP_BSIZE (8*1024)
          char    ftp_buff[c_FTP_BSIZE] ;

        leidos       = 0L ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), sizeof(ftp_buff) ) ;
        number_urls = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        /* ... first read is out of while ... */
        result = read(infile,ftp_buff,size_buff) ;
        while ( result > 0 )
        {
          L_FILE_COMMAND_Write(ftp_buff,result,(*fpage)) ;
          leidos = leidos + result ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_to_read) ;
          result = read(infile,ftp_buff,size_buff) ;
        }
        dlws->currentBytes += leidos ;
        if ( result < 0 )
             return FALSE ;
        return TRUE ;
      }

      T_BOOL  L_FTP_FILE_OpenFileToRead  ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_ftpCfg       *ftpCfg,
                                           IN     t_url          *url,
                                           INOUT  T_LONG         *total_to_read,
                                           INOUT  int            *fpage )
      {
        T_BOOL ok ;
        struct sockaddr faddr ;
        t_ftp_response  ftpr ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(ftpCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(fpage) ;

        if (ftpCfg->connected == FALSE)
           {
             ok = L_FTP_SERVER_GetConnection(ftpCfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... get server sock ... */
        ok = L_FTP_COMMAND_pasv( &(ftpCfg->sd),
                                 &(ftpr),
                                 &(faddr) ) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... connect server sock ... */
        ok = L_SOCKET_connect(fpage,(struct sockaddr_in *)&faddr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... retr ... */
        ok = L_FTP_COMMAND_retr( &(ftpCfg->sd),
                                 url->file,
                                 total_to_read,
                                 &(ftpr) ) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;
        if (ok == FALSE)
           {
             close((*fpage)) ;
             return FALSE ;
           }

        return TRUE ;
      }

      T_BOOL  L_FTP_FILE_CloseFileToRead  ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_ftpCfg       *ftpCfg,
                                            INOUT  int            *fpage )
      {
        T_BOOL   ok ;
        t_ftp_response   ftpr ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(ftpCfg) ;
        NULL__SET_ERROR__RET_FALSE(fpage) ;

        ok = L_FTP_RESPONSE_Read(&(ftpCfg->sd),&ftpr) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;

        close((*fpage)) ;
        return ok ;
      }

      T_BOOL  L_FTP_FILE_DownLoadFile ( INOUT  t_downLoadWS   *dlws,
                                        IN     t_ftpCfg       *ftpCfg,
                                        INOUT  FILE          **fpage,
                                        IN     t_url          *url )
      {
        T_BOOL   ok ;
        int      fsock ;
        T_LONG   total_to_read ;

        /* ... request ... */
        ok = L_FTP_FILE_OpenFileToRead(dlws,ftpCfg,url,
                                       &total_to_read,&fsock) ;
        FALSE_RET_FALSE(ok) ;
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "retr...",
                                      total_to_read,
                                      url) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_FTP_FILE_rwfile(dlws,total_to_read,fsock,fpage) ;

        /* ... finalize ... */
        ok = L_FTP_FILE_CloseFileToRead(dlws,ftpCfg,&fsock) ;
        return ok ;
      }


   /* ................................................................... */

