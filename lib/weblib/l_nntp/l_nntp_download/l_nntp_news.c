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

      #include "weblib/l_nntp/l_nntp_download/l_nntp_news.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_NNTP_NEWS_rwfile     ( INOUT  t_downLoadWS   *dlws,
                                       INOUT  t_sock         *insock,
                                       INOUT  FILE          **fpage )
      {
        T_LONG    total_a_leer, leidos ;
        T_INT     result, size_buff ;
        T_LONG    number_urls ;

          #define c_NNTP_BSIZE (8*1024)
          char    nntp_buff[c_NNTP_BSIZE] ;

        leidos       = 0L ;
        total_a_leer = 0 ;
        size_buff    = (8*1024) ;
        if (dlws->bufSize != LONG_MAX)
            size_buff = MIN( (dlws->bufSize), sizeof(nntp_buff) ) ;
        number_urls = (T_LONG)L_URLLI_NumberUrls(dlws->urllist) ;

        result = L_NNTP_COMMAND_ReadLine(insock,nntp_buff,size_buff) ;
        while (
                ( result == FALSE )
                       &&
                ( L_LINE_dot_enter(nntp_buff) == FALSE )
              )
        {
          L_FILE_COMMAND_Write(nntp_buff,X_STRING_StrLen(nntp_buff),(*fpage)) ;
          leidos = leidos + X_STRING_StrLen(nntp_buff) ;
          L_VERBOSE_DOWNLOAD_currentReaded(dlws,leidos,total_a_leer) ;
          result = L_NNTP_COMMAND_ReadLine(insock,nntp_buff,size_buff) ;
        }
        dlws->currentBytes += leidos ;
        return result ; /* eof */
      }

      T_BOOL  L_NNTP_NEWS_DownLoad    ( INOUT  t_downLoadWS   *dlws,
                                        IN     t_nntpCfg      *nntpCfg,
                                        INOUT  FILE          **fpage,
                                        IN     t_url          *url )
      {
        T_BOOL    ok ;
        T_CHAR    chSave ;
        T_CHAR   *pch ;
        t_nntp_response nntpr ;

        if (nntpCfg->connected == FALSE)
           {
             ok = L_NNTP_SERVER_GetConnection(nntpCfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... ptr to group/news ... */
        pch = L_LINE_skipRoot(url->file) ;
        pch = strchr(pch,'/') ;
        if (pch == NULL)
            pch = strchr(pch,'\\') ;
        if (pch == NULL)
            return FALSE ;

        /* ... group ... */
        chSave = pch[0] ;
        pch[0] = '\0' ;
        ok = L_NNTP_COMMAND_group( &(nntpCfg->sd),
                                    L_LINE_skipRoot(url->file),
                                   &nntpr ) ;
        pch[0] = chSave ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... stat ... */
        ok = L_NNTP_COMMAND_stat( &(nntpCfg->sd),
                                  L_LINE_skipRoot(pch),
                                  &nntpr) ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... body ... */
        ok = L_NNTP_COMMAND_body(&(nntpCfg->sd),
                                 &nntpr) ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_NNTP_NEWS_rwfile(dlws,&(nntpCfg->sd),fpage) ;

        /* ... finalize ... */
        return ok ;
      }


   /* ................................................................... */

