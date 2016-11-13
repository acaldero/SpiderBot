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

      #include "weblib/l_nntp/l_nntp_download/l_nntp_group.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_NNTP_GROUP_ParserNews       ( IN     T_CHAR          *machine,
                                             IN     T_CHAR          *group,
                                             IN     t_nntp_response *nntpr,
                                             INOUT  t_sock          *fdin,
                                             INOUT  FILE            *dpage )
      {
        T_INT    code, nestimated, first, last ;
        T_CHAR   gname[1024] ;
   
        /* ... read group info ... */
        sscanf(nntpr->msg,
               "%i %i %i %i %s",
               &code,&nestimated,&first,&last,gname) ;

        /* ... write html page ... */
        if (code == 411)
           {
             fprintf( dpage,
                      "<HTML>\n"
                      "<P>\n"
                      "<CENTER><H1><U>NO such news group</U></H1></CENTER>\n"
                      "<P>\n"
                      "</HTML>\n") ;
             return FALSE ;
           }
        if (
              (code == 211)
                    &&
             (first == last)
           )
           {
             fprintf( dpage,
                      "<HTML>\n"
                      "<CENTER><H1><U>Empty Group</U></H1></CENTER>\n"
                      "<P>\n"
                      "</HTML>\n") ;
             return TRUE ;
           }
        if (code == 211)
           {
             T_INT  i ;

             fprintf( dpage,
                      "<HTML>\n"
                      "<CENTER><H1><U>Group's News</U></H1></CENTER>\n"
                      "<P>\n"
                      "<UL>\n") ;
             for (i=first; i<=last; i++)
             {
               fprintf( dpage,
                        "<LI>"
                        "<A HREF=\"nntp://%s%s%i\"> nntp://%s%s%i </A>"
                        "</LI>\n",
                        machine,group,i,
                        machine,group,i) ;
             }
             fprintf( dpage,
                      "</UL>\n"
                      "<P>\n"
                      "</HTML>\n") ;

             return TRUE ;
           }
        if (
             (code != 411)
                   &&
             (code != 211)
           )
           {
             fprintf( dpage,
                      "<HTML>\n"
                      "<P>\n"
                      "<CENTER><H1><U>NO such news group</U></H1></CENTER>\n"
                      "<P>\n"
                      "</HTML>\n") ;
             return FALSE ;
           }

        return FALSE ;
      }

      T_BOOL  L_NNTP_GROUP_DownLoad      ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_nntpCfg      *nntpCfg,
                                           INOUT  FILE          **fpage,
                                           IN     t_url          *url )
      {
        T_BOOL           ok ;
        t_nntp_response  nntpr ;

        if (nntpCfg->connected == FALSE)
           {
             ok = L_NNTP_SERVER_GetConnection(nntpCfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... group ... */
        ok = L_NNTP_COMMAND_group( &(nntpCfg->sd),
                                     L_LINE_skipRoot(url->file),
                                   &nntpr ) ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        if (ok == FALSE)
           {
             L_NNTP_RESPONSE_Empty(&nntpr) ;
             return FALSE ;
           }

        /* ... add last '/' ... */
        ok = L_URLFILE_MakeIndexUrl(url) ;
        if (ok == FALSE)
           {
             L_NNTP_RESPONSE_Empty(&nntpr) ;
             return FALSE ;
           }

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_NNTP_GROUP_ParserNews(url->machine,
                                url->file,
                                &nntpr,
                                &(nntpCfg->sd),
                                (*fpage)) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;

        /* ... finalize ... */
        return ok ;
      }


   /* ................................................................... */

