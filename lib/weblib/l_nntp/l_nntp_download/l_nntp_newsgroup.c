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

      #include "weblib/l_nntp/l_nntp_download/l_nntp_newsgroup.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_NNTP_NEWSGROUP_ParserGroups ( IN     T_CHAR  *machine,
                                             INOUT  t_sock  *fdin,
                                             INOUT  FILE    *dpage )
      {
        T_BOOL   ret ;
        T_CHAR   gname[1024] ;
        T_CHAR  *pch ;
   
        fprintf( dpage,
                 "<HTML>\n"
                 "<CENTER><H1><U>NewsGroup's Directory</U></H1></CENTER>\n"
                 "<P>\n"
                 "<UL>\n") ;
        ret = L_NNTP_COMMAND_ReadLine(fdin,gname,sizeof(gname)) ;
        while (
                ( ret == FALSE )
                       &&
                ( L_LINE_dot_enter(gname) == FALSE )
              )
        {
          pch = strchr(gname,' ') ;
          if (pch != NULL)
              pch[0] = '\0' ;
          fprintf( dpage,
                   "<LI>"
                   "<A HREF=\"nntp://%s/%s/\"> nntp://%s/%s </A>"
                   "</LI>\n",
                   machine,gname,
                   machine,gname) ;
          ret = L_NNTP_COMMAND_ReadLine(fdin,gname,sizeof(gname)) ;
        }
        fprintf( dpage,
                 "</UL>\n"
                 "<P>\n"
                 "</HTML>\n") ;
        return TRUE ;
      }

      T_BOOL  L_NNTP_NEWSGROUP_DownLoad  ( INOUT  t_downLoadWS   *dlws,
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

        /* ... list ... */
        ok = L_NNTP_COMMAND_list(&(nntpCfg->sd),
                                 &nntpr) ;
        L_NNTP_LOG_PrintResponse(dlws->finfo,&nntpr) ;
        L_NNTP_RESPONSE_Empty(&nntpr) ;
        FALSE_RET_FALSE(ok) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_NNTP_NEWSGROUP_ParserGroups(url->machine,
                                      &(nntpCfg->sd),
                                      (*fpage)) ;

        /* ... finalize ... */
        return ok ;
      }


   /* ................................................................... */

