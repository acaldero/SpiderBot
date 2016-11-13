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

      #include "weblib/l_pop3/l_pop3_download/l_pop3_box.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_POP3_BOX_ParserBoxEntrys    ( IN     T_CHAR  *machine,
                                             INOUT  t_sock  *fdin,
                                             INOUT  FILE    *dpage )
      {
        T_BOOL   ret ;
        T_CHAR   fname[1024] ;
        T_CHAR  *pch ;
   
        fprintf( dpage,
                 "<HTML>\n"
                 "<CENTER><H1><U>MailBox Contents</U></H1></CENTER>\n"
                 "<P></P>\n"
                 "<UL>\n") ;
        ret = L_POP3_COMMAND_ReadLine(fdin,fname,sizeof(fname)) ;
        while (
                (ret == FALSE)
                     &&
                (L_LINE_dot_enter(fname) == FALSE)
              )
        {
          pch = strchr(fname,' ') ;
          if (pch != NULL)
              pch[0] = '\0' ;
          fprintf( dpage,
                   "<LI>"
                   "<A HREF=\"pop3://%s/%s\"> pop3://%s/%s </A>"
                   "</LI>\n",
                   machine,fname,
                   machine,fname) ;
          ret = L_POP3_COMMAND_ReadLine(fdin,fname,sizeof(fname)) ;
        }
        fprintf( dpage,
                 "</UL>\n"
                 "<P></P>\n"
                 "</HTML>\n") ;
        return TRUE ;
      }

      T_BOOL  L_POP3_BOX_OpenBox       ( INOUT  t_downLoadWS    *dlws,
                                         IN     t_pop3Cfg       *pop3Cfg,
                                         IN     t_url           *url,
                                         INOUT  t_pop3_response *pop3r )
      {
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        if (pop3Cfg->connected == FALSE)
           {
             ok = L_POP3_SERVER_GetConnection(pop3Cfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... list ... */
        ok = L_POP3_COMMAND_list(&(pop3Cfg->sd),pop3r) ;
        L_POP3_LOG_PrintResponse(dlws->finfo,pop3r) ;

        return ok ;
      }

      T_BOOL  L_POP3_BOX_DownLoadBox   ( INOUT  t_downLoadWS   *dlws,
                                         IN     t_pop3Cfg      *pop3Cfg,
                                         INOUT  FILE          **fpage,
                                         IN     t_url          *url )
      {
        T_BOOL           ok ;
        t_pop3_response  pop3r ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(pop3Cfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;
        NULL__SET_ERROR__RET_FALSE(fpage) ;

        ok = L_POP3_BOX_OpenBox(dlws,pop3Cfg,url,&pop3r) ;
        FALSE_RET_FALSE(ok) ;
        L_POP3_RESPONSE_Empty(&pop3r) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_POP3_BOX_ParserBoxEntrys(url->machine,
                                   &(pop3Cfg->sd),
                                   (*fpage)) ;

        return ok ;
      }


   /* ................................................................... */

