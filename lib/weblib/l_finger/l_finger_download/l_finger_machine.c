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

      #include "weblib/l_finger/l_finger_download/l_finger_machine.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FINGER_MACHINE_ParserEntrys  ( IN     T_CHAR  *machine,
                                              INOUT  t_sock  *sd,
                                              INOUT  FILE    *dpage )
      {
        T_BOOL    err ;
        T_CHAR    fname[1024] ;
        T_CHAR   *pch ;
   
        fprintf( dpage,
                 "<HTML>\n"
                 "<CENTER><H1><U>Users Connected</U></H1></CENTER>\n"
                 "<P></P>\n"
                 "<UL>\n") ;
        err = X_SOCKET_ReadLine(sd,fname,sizeof(fname)) ;
        while (
                (err == FALSE)
                      &&
                (fname[0] != '\0')
              )
        {
          fname[strlen(fname)-1] = '\0' ;
          pch = strchr(fname,' ') ;
          if (pch != NULL)
                   *pch = '\0' ;
              else pch = "" ;

          if (X_STRING_Equal(fname,"") == FALSE)
             {
               if (X_STRING_Equal(fname,"Login") == FALSE)
                  {
                    fprintf( dpage,
                             "<LI>"
                             "<A HREF=\"finger://%s/%s\"> finger://%s/%s </A>"
                             "</LI>\n",
                             machine,fname,
                             machine,fname) ;
                  }
               else 
                  {
                    fprintf( dpage,
                             "<B>"
                             "%s"
                             "</B>\n",
                             fname) ;
                  }
             }
          err = X_SOCKET_ReadLine(sd,fname,sizeof(fname)) ;
        }
        fprintf( dpage,
                 "</UL>\n"
                 "<P></P>\n"
                 "</HTML>\n") ;
        return TRUE ;
      }

      T_BOOL  L_FINGER_MACHINE_Open       ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg,
                                            IN     t_url          *url )
      {
        T_BOOL    ok ;
        t_finger_response  fingerr ;

        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;
        NULL__SET_ERROR__RET_FALSE(url) ;

        if (fingerCfg->connected == FALSE)
           {
             ok = L_FINGER_SERVER_GetConnection(fingerCfg,url,dlws) ;
             FALSE_RET_FALSE(ok) ;
           }

        /* ... retr ... */
        ok = L_FINGER_COMMAND_finger(&(fingerCfg->sd),"",&fingerr) ;
        L_FINGER_LOG_PrintResponse(dlws->finfo,&fingerr) ;
        L_FINGER_RESPONSE_Empty(&fingerr) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }

      T_BOOL  L_FINGER_MACHINE_Close      ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg )
      {
        NULL__SET_ERROR__RET_FALSE(dlws) ;
        NULL__SET_ERROR__RET_FALSE(fingerCfg) ;

        fingerCfg->connected = FALSE ;

        return TRUE ;
      }

      T_BOOL  L_FINGER_MACHINE_DownLoad   ( INOUT  t_downLoadWS   *dlws,
                                            IN     t_fingerCfg    *fingerCfg,
                                            INOUT  FILE          **fpage,
                                            IN     t_url          *url )
      {
        T_BOOL   ok ;

        ok = L_FINGER_MACHINE_Open(dlws,fingerCfg,url) ;
        FALSE_RET_FALSE(ok) ;
        L_VERBOSE_DOWNLOAD_currentUrl(dlws,
                                      "host...",
                                      0,
                                      url) ;

        /* ... mirror ... */
        if ((*fpage) == NULL)
            (*fpage) = L_FILE_UPLOAD_OpenUrlToWrite(dlws,url) ;
        L_FINGER_MACHINE_ParserEntrys(url->machine,&(fingerCfg->sd),(*fpage)) ;

        /* ... finalize ... */
        ok = L_FINGER_MACHINE_Close(dlws,fingerCfg) ;
        return ok ;
      }


   /* ................................................................... */

