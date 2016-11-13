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

      #include "weblib/l_file/l_file_server.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_FILE_SERVER_Empty        ( INOUT  t_fileCfg   *fileCfg )
      {
        /* ... check params ... */
        L_DEBUG_NULL_E_F(fileCfg,"NULL fileCfg") ;

        if (fileCfg->connected == TRUE)
           {
             fclose((fileCfg->sd)) ;
           }
        return TRUE ;
      }

      T_BOOL   L_FILE_SERVER_Setup        ( OUT     t_fileCfg      *fileCfg,
                                            IN      t_url          *urlHost,
                                            INOUT   t_downLoadWS   *dlws )
      {
        T_BOOL  ok ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(fileCfg,"NULL fileCfg") ;
        L_DEBUG_NULL_E_F(urlHost,"NULL urlHost") ;
        L_DEBUG_NULL_E_F(dlws,"NULL dlws") ;

        ok = TRUE ;
        fileCfg->connected = FALSE ;
        if (dlws->verbose == ON)
           {
             fprintf(dlws->finfo,
                     "\t\"%s\"' file system setup\n",
                     (urlHost->file)) ;
           }

	return ok ;
      }


   /* ................................................................... */

