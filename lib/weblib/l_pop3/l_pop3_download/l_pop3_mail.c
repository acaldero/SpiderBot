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

      #include "weblib/l_pop3/l_pop3_download/l_pop3_mail.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_POP3_MAIL_rwfile      ( INOUT  t_downLoadWS   *dlws,
                                        INOUT  t_sock         *pop3sd,
                                        INOUT  FILE          **fpage )
      {
        T_LONG    total_a_leer, leidos ;
        T_INT     result, size_buff ;
        T_LONG    number_urls ;

          #define c_POP3_BSIZE (8*1024)
          char    pop3_buff[c_POP3_BSIZE] ;

        leidos       = 0L ;
        total_a_leer = 0 ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), sizeof(pop3_buff) ) ;
        number_urls = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        /* ... first read is out of while ... */
        result = L_POP3_COMMAND_ReadLine(pop3sd,pop3_buff,size_buff) ;
        while (
                ( result == FALSE )
                       &&
                ( L_LINE_dot_enter(pop3_buff) == FALSE )
              )
        {
          L_FILE_COMMAND_Write(pop3_buff,X_STRING_StrLen(pop3_buff),(*fpage)) ;
          leidos = leidos + X_STRING_StrLen(pop3_buff) ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_a_leer) ;
          result = L_POP3_COMMAND_ReadLine(pop3sd,pop3_buff,size_buff) ;
        }
        dlws->currentBytes += leidos ;
        return result ; /* eof */
      }

      T_BOOL  L_POP3_MAIL_OpenMailToRead   ( INOUT  t_downLoadWS    *dlws,
                                             IN     t_pop3Cfg       *pop3Cfg,
                                             IN     t_url           *url,
                                             INOUT  t_pop3_response *pop3r )
      {
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(pop3r) ;

        if (pop3Cfg->connected == FALSE)
           {
             ok = L_POP3_SERVER_GetConnection(pop3Cfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... retr ... */
        ok = L_POP3_COMMAND_retr( &(pop3Cfg->sd),
                                  L_LINE_skipRoot(url->file),
                                  pop3r ) ;
        L_POP3_LOG_PrintResponse(dlws->finfo,pop3r) ;

        return ok ;
      }

      T_BOOL  L_POP3_MAIL_DownLoadMail ( INOUT  t_downLoadWS   *dlws,
                                         IN     t_pop3Cfg      *pop3Cfg,
                                         INOUT  FILE          **fpage,
                                         IN     t_url          *url )
      {
        T_BOOL           ok ;
        t_pop3_response  pop3r ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;
        NULL__SET_ERROR__RET_FALSE(fpage) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... request ... */
        ok = L_POP3_MAIL_OpenMailToRead(dlws,pop3Cfg,url,&pop3r) ;
        FALSE_RET_FALSE(ok) ;
        L_POP3_RESPONSE_Empty(&pop3r) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_POP3_MAIL_rwfile(dlws,&(pop3Cfg->sd),fpage) ;

        return ok ;
      }


   /* ................................................................... */

