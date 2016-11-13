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

      #include "weblib/l_ftp/l_ftp_download/l_ftp_dir.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FTP_DIR_ParserDirEntrys    ( IN     T_CHAR  *machine,
                                            INOUT  FILE    *fin,
                                            INOUT  FILE    *dpage )
      {
        T_CHAR   *ret ;
        T_CHAR    fname[1024] ;
   
        fprintf( dpage,
                 "<HTML>\n"
                 "<CENTER><H1><U>Directory Contents</U></H1></CENTER>\n"
                 "<P></P>\n"
                 "<UL>\n") ;
        ret = fgets(fname,sizeof(fname),fin) ;
        while (ret != NULL)
        {
          fname[strlen(fname)-1] = '\0' ;
          if ( (X_STRING_Equal(fname,".") == FALSE)
                           &&
               (X_STRING_Equal(fname,"..") == FALSE) )
             {
               fprintf( dpage,
                        "<LI>"
                        "<A HREF=\"ftp://%s%s\"> ftp://%s%s </A>"
                        "</LI>\n",
                        machine,fname,
                        machine,fname) ;
             }
          ret = fgets(fname,sizeof(fname),fin) ;
        }
        fprintf( dpage,
                 "</UL>\n"
                 "<P></P>\n"
                 "</HTML>\n") ;
        return TRUE ;
      }

      T_BOOL  L_FTP_DIR_OpenDir       ( INOUT  t_downLoadWS   *dlws,
                                        IN     t_ftpCfg       *ftpCfg,
                                        IN     t_url          *url,
                                        INOUT  int            *fpage )
      {
        T_BOOL    ok ;
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
        ok = L_FTP_COMMAND_nlst(&(ftpCfg->sd),url->file,&ftpr) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;
        if (ok == FALSE)
           {
             close((*fpage)) ;
             return FALSE ;
           }

        return TRUE ;
      }

      T_BOOL  L_FTP_DIR_CloseDir      ( INOUT  t_downLoadWS   *dlws,
                                        IN     t_ftpCfg       *ftpCfg,
                                        INOUT  int            *fpage )
      {
        T_BOOL    ok ;
        t_ftp_response  ftpr ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(ftpCfg) ;
        NULL__SET_ERROR__RET_FALSE(fpage) ;

        ok = L_FTP_RESPONSE_Read(&(ftpCfg->sd),&ftpr) ;
        L_FTP_LOG_PrintResponse(dlws->finfo,&ftpr) ;
        L_FTP_RESPONSE_Empty(&ftpr) ;

        close((*fpage)) ;
        return ok ;
      }

      T_BOOL  L_FTP_DIR_DownLoadDir   ( INOUT  t_downLoadWS   *dlws,
                                        IN     t_ftpCfg       *ftpCfg,
                                        INOUT  FILE          **fpage,
                                        IN     t_url          *url )
      {
        T_BOOL   ok ;
        FILE    *ffsock ;
        int      fsock ;

        ok = L_FTP_DIR_OpenDir(dlws,ftpCfg,url,&fsock) ;
        FALSE_RET_FALSE(ok) ;
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "nlst...",
                                      0,
                                      url) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        ffsock = fdopen(fsock,"r") ;
        NULL_RET_FALSE(ffsock) ;
        L_FTP_DIR_ParserDirEntrys(url->machine,ffsock,(*fpage)) ;

        /* ... finalize ... */
        ok = L_FTP_DIR_CloseDir(dlws,ftpCfg,&fsock) ;
        return ok ;
      }


   /* ................................................................... */

