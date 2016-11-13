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

      #include "weblib/l_verbose/l_verbose_log.h"


   /* ... Functions / Funciones ......................................... */

      void   L_VERBOSE_LOG_applyTo  ( IN     t_downLoadWS     *dlws,
                                      IN     T_CHAR           *msg )
      {
        if (dlws->verbose == ON)
           {
             X_PRINT_printf("\r[url %li/%li]  %s %.*s",
                            (dlws->i),
                            (T_LONG)L_URLLI_NumberUrls(dlws->urllist),
                            msg,
                            (70 - strlen(msg)),
                            "                                            " ) ;
             fflush(stdout) ;
           }
      }

      void   L_VERBOSE_LOG_newMsg      ( IN     t_downLoadWS     *dlws,
                                         IN     T_CHAR           *msgFto,
                                         IN     ...                       )
      {
        va_list varg ;

        va_start(varg,msgFto) ;
        if (dlws->verbose == ON)
           {
             X_PRINT_printf("\n\t") ;
             X_PRINT_vprintf(msgFto,varg) ;
             fflush(stdout) ;
           }
        va_end(varg) ;
      }

      void   L_VERBOSE_LOG_appendMsg   ( IN     t_downLoadWS     *dlws,
                                         IN     T_CHAR           *msgFto,
                                         IN     ...                       )
      {
        va_list varg ;

        va_start(varg,msgFto) ;
        if (dlws->verbose == ON)
           {
             X_PRINT_vprintf(msgFto,varg) ;
             fflush(stdout) ;
           }
        va_end(varg) ;
      }


   /* ................................................................... */

