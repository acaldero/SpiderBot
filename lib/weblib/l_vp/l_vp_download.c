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

      #include "weblib/l_vp/l_vp_download.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_VP_SelectProtocol      ( INOUT  t_downLoadWS   *dlws,
                                         INOUT  t_siteCfg      *siteCfg,
                                         IN     t_url          *url,
                                         INOUT  int            *selp )
      {
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(selp) ;

        /* ... forbidden ... */
        if (
             (dlws->protocolSelection == c_PS_HTTP)
                      &&
             (X_STRING_Match(url->protocol,"http",FALSE) == FALSE)
           )
           {
             L_VERBOSE_LOG_applyTo(dlws,"(w) using only http protocol") ;
             (*selp) = VP_NONE ;
             return TRUE ;
           }

        if (
             (X_STRING_Match(url->protocol,"http",FALSE) == TRUE)
                          &&
             (L_HTTP_SERVER_IsDisallow(&(siteCfg->webCfg),url) == TRUE)
           )
           {
             L_VERBOSE_LOG_applyTo(dlws,"(w) disallow path") ;
             (*selp) = VP_NONE ;
             return TRUE ;
           }

        /* ... allowed ... */
        if (X_STRING_Match(url->protocol,"http",FALSE) == TRUE)
           {
             (*selp) = VP_HTTP ;
             return TRUE ;
           }

        else 
        if (X_STRING_Match(url->protocol,"ftp",FALSE) == TRUE)
           {
             if (dlws->proxy != NULL)
                  (*selp) = VP_HTTP ;
             else (*selp) = VP_FTP ;
             return TRUE ;
           }

        else 
        if (X_STRING_Match(url->protocol,"file",FALSE) == TRUE)
           {
             (*selp) = VP_FILE ;
             return TRUE ;
           }

        else 
        if (
             (X_STRING_Match(url->protocol,"nntp",FALSE) == TRUE)
                                   ||
             (X_STRING_Match(url->protocol,"news",FALSE) == TRUE)
           )
           {
             if (dlws->proxy != NULL)
                  (*selp) = VP_HTTP ;
             else (*selp) = VP_NNTP ;
             return TRUE ;
           }

        else 
        if (X_STRING_Match(url->protocol,"pop3",FALSE) == TRUE)
           {
             (*selp) = VP_POP3 ;
             return TRUE ;
           }

        else 
        if (X_STRING_Match(url->protocol,"finger",FALSE) == TRUE)
           {
             (*selp) = VP_FINGER ;
             return TRUE ;
           }

        else /* unknow protocol */
           {
             if (dlws->proxy != NULL)
                 (*selp) = VP_HTTP ;
             return TRUE ;
           }

        return TRUE ;
      }

      T_BOOL  L_VP_DOWNLOAD_DownLoadUrl ( INOUT  t_downLoadWS   *dlws,
                                          INOUT  t_siteCfg      *siteCfg,
                                          INOUT  t_url          *purl,
                                          INOUT  FILE          **fpage,
                                          OUT    T_BOOL         *skip )
      {
        T_BOOL  ok ;
        int     selecOrigProto ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(siteCfg) ;
        NULL__SET_ERROR__RET_FALSE(purl) ;
        NULL__SET_ERROR__RET_FALSE(fpage) ;
        NULL__SET_ERROR__RET_FALSE(skip) ;

        (*skip) = FALSE ;
        ok = L_VP_SelectProtocol(dlws,siteCfg,purl,&selecOrigProto) ;
        FALSE_RET_FALSE(ok) ;
        switch (selecOrigProto)
        {
          case VP_FILE :
               ok = L_FILE_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->fileCfg),
                                                fpage,
                                                purl) ;
               break ;
          case VP_HTTP : 
               ok = L_HTTP_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->webCfg),
                                                fpage,
                                                purl) ;
               break ;
          case VP_FTP  : 
               ok = L_FTP_DOWNLOAD_DownLoadUrl(dlws,
                                               &(siteCfg->ftpCfg),
                                               fpage,
                                               purl) ;
               break ;
          case VP_POP3 : 
               ok = L_POP3_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->pop3Cfg),
                                                fpage,
                                                purl) ;
               break ;
          case VP_NNTP : 
               ok = L_NNTP_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->nntpCfg),
                                                fpage,
                                                purl) ;
               break ;
          case VP_FINGER :
               ok = L_FINGER_DOWNLOAD_DownLoadUrl(dlws,
                                                  &(siteCfg->fingerCfg),
                                                  fpage,
                                                  purl) ;
               break ;
          case VP_NONE :
               (*skip) = TRUE ;
               return TRUE ;
               break ;
          default :
               (*skip) = TRUE ;
               return TRUE ;
        }

        return ok ;
      }


      T_BOOL  L_VP_DOWNLOAD_CopyUrlToUrl ( INOUT  t_downLoadWS   *dlws,
                                           INOUT  t_siteCfg      *siteCfg,
                                           INOUT  t_url          *urlOrig,
                                           INOUT  t_url          *urlDest,
                                           OUT    T_BOOL         *skip )
      {
        T_BOOL   ok ;
        FILE    *fpage ;
        int      selecOrigProto, selecDestProto ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(siteCfg) ;
        NULL__SET_ERROR__RET_FALSE(urlOrig) ;
        NULL__SET_ERROR__RET_FALSE(urlDest) ;
        NULL__SET_ERROR__RET_FALSE(skip) ;

        /* ... apply Dest. protocol ... */
        ok = L_VP_SelectProtocol(dlws,siteCfg,urlOrig,&selecDestProto) ;
        FALSE_RET_FALSE(ok) ;
        switch (selecDestProto)
        {
          case VP_FILE :
               {
                 T_CHAR  *fname, *uname ;

                 /* ... get fname ... */
                 fname = X_STRING_StrDup(urlDest->file) ;
                 uname = L_URLFILE_MirrorUrlName(urlDest,
                                                 dlws->mirrorSelection) ;
                 X_STRING_AddStrToStr(&(fname),uname) ;
                 X_ALLOC_Free((void **)&uname) ;
                 fpage = L_FILE_UPLOAD_OpenUrlToWrite_2(dlws,fname) ;
               }
               break ;
          case VP_HTTP : 
          case VP_FTP  : 
          case VP_POP3 : 
          case VP_NNTP : 
          case VP_FINGER :
               L_VERBOSE_LOG_applyTo(dlws,
                                     "(w) dest. \"read only\" protocol") ;
               (*skip) = TRUE ;
               return TRUE ;
               break ;
          case VP_NONE :
               (*skip) = TRUE ;
               return TRUE ;
               break ;
          default :
               (*skip) = TRUE ;
               return TRUE ;
        }

        /* ... apply Orig. protocol ... */
        ok = L_VP_SelectProtocol(dlws,siteCfg,urlOrig,&selecOrigProto) ;
        FALSE_RET_FALSE(ok) ;
        switch (selecOrigProto)
        {
          case VP_FILE :
               ok = L_FILE_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->fileCfg),
                                                &(fpage),
                                                urlOrig) ;
               break ;
          case VP_HTTP : 
               ok = L_HTTP_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->webCfg),
                                                &(fpage),
                                                urlOrig) ;
               break ;
          case VP_FTP  : 
               ok = L_FTP_DOWNLOAD_DownLoadUrl(dlws,
                                               &(siteCfg->ftpCfg),
                                               &(fpage),
                                               urlOrig) ;
               break ;
          case VP_POP3 : 
               ok = L_POP3_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->pop3Cfg),
                                                &(fpage),
                                                urlOrig) ;
               break ;
          case VP_NNTP : 
               ok = L_NNTP_DOWNLOAD_DownLoadUrl(dlws,
                                                &(siteCfg->nntpCfg),
                                                &(fpage),
                                                urlOrig) ;
               break ;
          case VP_FINGER :
               ok = L_FINGER_DOWNLOAD_DownLoadUrl(dlws,
                                                  &(siteCfg->fingerCfg),
                                                  &(fpage),
                                                  urlOrig) ;
               break ;
          case VP_NONE :
               fclose(fpage) ;
               (*skip) = TRUE ;
               return TRUE ;
               break ;
          default :
               fclose(fpage) ;
               (*skip) = TRUE ;
               return TRUE ;
        }

        fclose(fpage) ;
        (*skip) = FALSE ;
        return ok ;
      }


   /* ................................................................... */

