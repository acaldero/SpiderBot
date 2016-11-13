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

      #include "weblib/l_url/l_urlxml.h"


   /* ... Const / Constantes ............................................ */

      /* ... PageUrlParsing ... */
      static T_CHAR *L_URLXML_str_arr[] =
                     { 
                         /* ... Url ... */
                         "HREF", "SRC", "URL",
                         "CODE", "LOCATION", "ACTION",
                         "BACKGROUND", "VALUE",
                         "XML-XPTR",

                         /* ... tag to delete ... */
                         "<BASE",

                         /* ... tag to skip ... */
                         "<!",

                         /* ... block to delete ... */

                         /* ... block to skip ... */
                         "<SCRIPT",

                         NULL 
                     } ;
      static T_CHAR *L_URLXML_str_espaciadores1 = " \t\r\n\">=" ;
      static T_CHAR *L_URLXML_str_espaciadores2 = " \t\r\n\">" ;
      static T_CHAR *L_URLXML_str_espaciadores3 = ">" ;
      static T_CHAR *L_URLXML_str_end4 = "</SCRIPT>" ;


   /* ... Inline / Macros ............................................... */

      /* ... Is tag X... */
      #define IS_URLSCAN(tid)       ( (tid >= 0) && (tid < 9) )
      #define IS_URLDEL(tid)        ( (tid == 9) )
      #define IS_URLSKIP(tid)       ( (tid == 10) )
      #define IS_URLSCRIPT(tid)     ( (tid >= 11) && (tid < 12) )


      /* ... Write ... */
      #define  L_URLXML_fWriteString(str,fout)  \
               fwrite((str),1,X_STRING_StrLen((str)),(fout)) ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_URLXML_WriteUrls  ( IN     t_url     *url,
                                    INOUT  FILE      *fout,
                                    IN     T_CHAR    *strurl,
                                    IN     T_INT      mkls,
                                    IN     T_INT      muns )
      {
        if (mkls == c_RS_NONE)
           {
             /* ... if no mklselection, skip ... */
             L_URLXML_fWriteString(strurl,fout) ;
             return TRUE ;
           }

        if (mkls != c_RS_NONE)
           {
             T_BOOL   ok ;
             T_CHAR  *mirrorName ;
	     t_url   *purlaux ;
     
	     /* ... see like url ... */
             mirrorName = NULL ;
             purlaux    = L_URL_CreatEmpty() ;
             NULL_RET_FALSE(purlaux) ;
             ok = L_URLFILE_OpenInsideUrl(purlaux,url,strurl) ;
             if (ok == FALSE)
                {
                  ok = L_URLSTR_StringToUrl(purlaux,strurl) ;
                  if (ok == FALSE)
                     {
                       L_URLXML_fWriteString(strurl,fout) ;
                       return FALSE ;
                     }
                }

             /* ... if strulr is relative to page, skip ... */
             if (X_STRING_FirstChar(strurl) == '#')
		{
                  L_URLXML_fWriteString(strurl,fout) ;
                  L_URL_Destroy(&purlaux) ;
                  return TRUE ;
		}

	     /* ... if url can not be mirrored, skip ... */
             if (
                  (X_STRING_CaseEqual(purlaux->protocol,"http",FALSE) == FALSE)
                                          &&
                  (X_STRING_CaseEqual(purlaux->protocol,"ftp",FALSE) == FALSE)
                                          &&
                  (X_STRING_CaseEqual(purlaux->protocol,"file",FALSE) == FALSE)
                                          &&
                  (X_STRING_CaseEqual(purlaux->protocol,"nntp",FALSE) == FALSE)
                                          &&
                  (X_STRING_CaseEqual(purlaux->protocol,"pop3",FALSE) == FALSE)
                                          &&
                  (X_STRING_CaseEqual(purlaux->protocol,"finger",FALSE) == FALSE)
                )
		{
                  L_URLXML_fWriteString(strurl,fout) ;
                  L_URL_Destroy(&purlaux) ;
                  return TRUE ;
		}

             /* ... if url from other website, no translation => skip ... */
             if (
                  (mkls != c_RS_ALL_SITE)
                          &&
                  (X_STRING_Equal(url->machine,purlaux->machine) == FALSE)
                )
		{
                  L_URLXML_fWriteString(strurl,fout) ;
                  L_URL_Destroy(&purlaux) ;
                  return TRUE ;
		}

	     /* ... rewritting ... */
             mirrorName = L_URLFILE_MirrorUrlNameFrom(purlaux,url,muns) ;
             L_URLXML_fWriteString(mirrorName,fout) ;
             X_ALLOC_Free( (void **)&(mirrorName) ) ;
             L_URL_Destroy(&purlaux) ;
             return TRUE ;
           }

        return TRUE ;
      }

      T_BOOL  L_URLXML_UpdateUrlList   ( IN     T_CHAR    *urlstr,
                                         INOUT  t_urlLi   *urlli,
                                         IN     t_url     *url,
                                         IN     T_INT      place,
                                         IN     T_FLAG     skipBin,
                                         IN     T_FLAG     fromSamePath,
                                         IN     T_FLAG     makeQuery )
      {
        t_url *zurl ;

        zurl = L_URLLI_UrlIn(urlli,0) ;
        NULL_RET_FALSE(zurl) ;
        if (
             (
                (skipBin == OFF)
                       ||
                (L_URLFILE_IsBin(urlstr) == FALSE)
             )
                       &&
             (
                (fromSamePath == OFF)
                       ||
                (L_URLFILE_FromSamePath(zurl,urlstr) == TRUE)
             )
           )
           {
             T_BOOL   ok ;
             t_url    urlaux ;
     
             /* ... build url ... */
             ok = L_URLFILE_OpenInsideUrl(&urlaux,url,urlstr) ;
             FALSE_RET_FALSE(ok) ;

             /* ... query ? ... */
             if (
                  (makeQuery == OFF)
                         &&
                  (urlaux.params != NULL)
                )
                {
                  L_URL_Empty(&urlaux) ;
                  return TRUE ;
                }

             /* ... update ... */
             if (place == c_SS_GLOBAL)
                {
                  if (L_URLLI_IsPresent(urlli,&urlaux) == FALSE)
                     {
                       ok = L_URLLI_Insert(urlli,&urlaux) ;
                     }
                }
             if (place == c_SS_LOCAL)
                {
                  if (
                        (L_URL_EqualMachine(&urlaux,url) == TRUE)
                                           &&
                        (L_URLLI_IsPresent(urlli,&urlaux) == FALSE)
                     )
                     {
                       ok = L_URLLI_Insert(urlli,&urlaux) ;
                     }
                }
             if (place == c_SS_COUNTRY)
                {
                  T_BOOL  ok, equal ;

                  ok = L_SOCKET_cmpHostName( urlaux.machine,
                                             url->machine,
                                             c_CMPA_COUNTRY,
                                             &equal ) ;
                  if (
                        (equal == TRUE)
                               &&
                        (L_URLLI_IsPresent(urlli,&urlaux) == FALSE)
                     )
                     {
                       ok = L_URLLI_Insert(urlli,&urlaux) ;
                     }
                }
             L_URL_Empty(&urlaux) ;
             return ok ;
           }
        return TRUE ;
      }

      T_BOOL  L_URLXML_AjustPageUrls   ( INOUT  FILE          *fin,
                                         INOUT  FILE          *fout,
                                         INOUT  T_BOOL        *updated,
                                         INOUT  t_downLoadWS  *dlws,
                                         IN     t_url         *url )
      {
        T_BOOL   ok ;
        T_INT    tid ;
        T_CHAR  *saux ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(fout) ;
        NULL__SET_ERROR__RET_FALSE(updated) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... rewritting links ... */
        (*updated) = FALSE ;
        L_VERBOSE_LOG_applyTo(dlws,
                              "rewritting links...") ;
        while (TRUE)
        {
          ok = L_FTOKEN_RWTillToken(fin,fout,
                                    L_URLXML_str_arr,&tid,
                                    L_URLXML_str_espaciadores1,FALSE) ;
          if (ok == FALSE)
             {
               if (feof(fin) == 0)
                   return FALSE ;
               return TRUE ;
             }
          if ( IS_URLSCAN(tid) )
             {
               /* Url to scan ... */
               saux = L_FSTR_GetItemValue(fin,"=",FALSE,
                                          L_URLXML_str_espaciadores2) ;
               if (saux == NULL)
                  {
                    L_URLXML_fWriteString(" ",fout) ;
                  }
               if (saux != NULL)
                  {
                    (*updated) = TRUE ;
                    L_URLXML_UpdateUrlList( saux,
                                            (dlws->urllist),
                                            (url),
                                            (dlws->scanSelection),
                                            (dlws->skipBin),
                                            (dlws->fromSamePath),
                                            (dlws->makeQuery) ) ;
                    L_URLXML_fWriteString("=\"",fout) ;
                    L_URLXML_WriteUrls( url,
                                        fout,
                                        saux,
                                        (dlws->rewriteSelection),
                                        (dlws->mirrorSelection) ) ;
                    L_URLXML_fWriteString("\"",fout) ;
                    L_FCHSET_SkipCharSet(fin,"\"") ;
                    X_ALLOC_Free((void **)&saux) ;
                  }
             }
          if ( IS_URLDEL(tid) )
             {
               /* html TAG to delete ... */
               fseek(fout,
                     - X_STRING_StrLen(L_URLXML_str_arr[tid]),
                     SEEK_CUR) ;
               L_FSTR_SkipTillStr(fin,L_URLXML_str_espaciadores3,FALSE) ;
             }
          if ( IS_URLSKIP(tid) )
             {
               /* html TAG to skip ... */
               L_FSTR_RWTillStr(fin,fout,L_URLXML_str_espaciadores3,FALSE) ;
               L_FSTR_AcceptStr(fin,L_URLXML_str_espaciadores3,FALSE) ;
               L_URLXML_fWriteString(L_URLXML_str_espaciadores3,fout) ;
             }
          if ( IS_URLSCRIPT(tid) )
             {
               /* html SCRIPT to skip ... */
               L_FSTR_RWTillStr(fin,fout,L_URLXML_str_end4,FALSE) ;
               L_FSTR_AcceptStr(fin,L_URLXML_str_end4,FALSE) ;
               L_URLXML_fWriteString(L_URLXML_str_end4,fout) ;
             }
        } /* while(TRUE) */
      }

      T_BOOL  L_URLXML_GetPageUrls     ( IN     FILE          *fin,
                                         INOUT  t_downLoadWS  *dlws,
                                         IN     t_url         *url )
      {
        T_BOOL   ok ;
        T_INT    tid ;
        T_CHAR  *saux ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        /* ... scannig ... */
        L_VERBOSE_LOG_applyTo(dlws,
                              "scanning links...") ;
        while (TRUE)
        {
          ok = L_FTOKEN_SkipTillToken(fin,
                                      L_URLXML_str_arr,
                                      &tid,
                                      L_URLXML_str_espaciadores1,
                                      FALSE) ;
          if (ok == FALSE)
             {
               if (feof(fin) == 0)
                   return FALSE ;
               return TRUE ;
             }
          if ( IS_URLSCAN(tid) )
             {
               /* Url to scan ... */
               saux = L_FSTR_GetItemValue(fin,
                                          "=",
                                          FALSE,
                                          L_URLXML_str_espaciadores2) ;
               if (saux != NULL)
                  {
                    L_URLXML_UpdateUrlList( saux,
                                            (dlws->urllist),
                                            (url),
                                            (dlws->scanSelection),
                                            (dlws->skipBin),
                                            (dlws->fromSamePath),
                                            (dlws->makeQuery) ) ;
                    L_FCHSET_SkipCharSet(fin,"\"") ;
                    X_ALLOC_Free((void **)&saux) ;
                  }
             }
          if ( IS_URLDEL(tid) )
             {
               /* html TAG to delete or skip ... */
               L_FSTR_SkipTillStr(fin,L_URLXML_str_espaciadores3,FALSE) ;
             }
          if ( IS_URLSCRIPT(tid) )
             {
               /* 
                  <SCRIPT> is NOT skiped ...
                  When looking for urls, scan whole page all
               */
             }
        } /* while(TRUE) */
      }

      T_BOOL  L_URLXML_mkLocal         ( INOUT  FILE          *fin,
                                         INOUT  FILE          *fout,
                                         INOUT  T_BOOL        *updated,
                                         INOUT  t_downLoadWS  *dlws,
                                         IN     t_url         *url )
      {
        T_BOOL   ok ;
        T_INT    tid ;
        T_CHAR  *saux ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fin) ;
        NULL__SET_ERROR__RET_FALSE(fout) ;
        NULL__SET_ERROR__RET_FALSE(updated) ;
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        (*updated) = FALSE ;
        while (TRUE)
        {
          ok = L_FTOKEN_RWTillToken( fin,fout,
                                     L_URLXML_str_arr,
                                     &(tid),
                                     L_URLXML_str_espaciadores1,
                                     FALSE ) ;
          if (ok == FALSE)
             {
               if (feof(fin) == 0)
                   return FALSE ;
               return TRUE ;
             }
          if ( IS_URLSCAN(tid) )
             {
               /* Url to scan ... */
               saux = L_FSTR_GetItemValue(fin,"=",FALSE,
                                          L_URLXML_str_espaciadores2) ;
               if (saux == NULL)
                  {
                    L_URLXML_fWriteString(" ",fout) ;
                  }
               if (saux != NULL)
                  {
                    (*updated) = TRUE ;
                    L_URLXML_fWriteString("=\"",fout) ;
                    L_URLXML_WriteUrls( url,
                                        fout,
                                        saux,
                                        (dlws->rewriteSelection),
                                        (dlws->mirrorSelection) ) ;
                    L_URLXML_fWriteString("\"",fout) ;
                    L_FCHSET_SkipCharSet(fin,"\"") ;
                    X_ALLOC_Free((void **)&saux) ;
                  }
             }
          if ( IS_URLDEL(tid) )
             {
               /* html TAG to delete ... */
               fseek(fout,
                     - X_STRING_StrLen(L_URLXML_str_arr[tid]),
                     SEEK_CUR) ;
               L_FSTR_SkipTillStr(fin,L_URLXML_str_espaciadores3,FALSE) ;
             }
          if ( IS_URLSKIP(tid) )
             {
               /* html TAG to skip ... */
               L_FSTR_RWTillStr(fin,fout,L_URLXML_str_espaciadores3,FALSE) ;
               L_FSTR_AcceptStr(fin,L_URLXML_str_espaciadores3,FALSE) ;
               L_URLXML_fWriteString(L_URLXML_str_espaciadores3,fout) ;
             }
          if ( IS_URLSCRIPT(tid) )
             {
               /* html SCRIPT to skip ... */
               L_FSTR_RWTillStr(fin,fout,L_URLXML_str_end4,FALSE) ;
               L_FSTR_AcceptStr(fin,L_URLXML_str_end4,FALSE) ;
               L_URLXML_fWriteString(L_URLXML_str_end4,fout) ;
             }
        } /* while(TRUE) */
      }


   /* ................................................................... */

