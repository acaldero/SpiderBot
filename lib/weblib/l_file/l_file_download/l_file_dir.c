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

      #include "weblib/l_file/l_file_download/l_file_dir.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL L_FILE_DIR_OperOverDirEntrys ( IN     T_CHAR  *path,
                                            INOUT  FILE    *fpage )
      {
        T_BOOL      ok ;
        t_dirinfo   wdi ;
        T_CHAR      *wpath, *fname, *SelFilter ;
        T_INT       fattrib ;
        T_LONG      fsize, fctime ;
   
        wpath     = X_STRING_StrDup(path) ;
        SelFilter = L_FILE_COMMAND_AllDirEntry() ;
        ok        = L_FILE_COMMAND_FindFirstEntry(&wdi,wpath,SelFilter,&fname) ;
        while (ok == TRUE)
        {
          ok = L_FILE_COMMAND_GetEntryInfo(wpath,fname,
                                           &fsize,&fctime,&fattrib) ;
          if (ok == TRUE)
             {
               if ( (X_STRING_Equal(fname,".") == FALSE)
                                &&
                    (X_STRING_Equal(fname,"..") == FALSE) )
                  {
                    fprintf( fpage,
                             "<LI>"
                             "<A HREF=\"file://localhost%s%s\"> /%s%s </A>"
                             "</LI>\n",
                             wpath,fname,
                             wpath,fname) ;
                  }
             }
          X_ALLOC_Free((void **)&(fname)) ;
          ok = L_FILE_COMMAND_FindNextEntry(&wdi,&fname) ;
        }
        X_ALLOC_Free((void **)&(wpath)) ;
        return TRUE ;
      }

      T_BOOL  L_FILE_DIR_DownLoadDir     ( INOUT  t_downLoadWS   *dlws,
                                           IN     t_fileCfg      *fileCfg,
                                           INOUT  FILE          **fpage,
                                           INOUT  t_url          *url )
      {
        T_BOOL ok ;

        NULL_RET_FALSE( dlws ) ;
        NULL_RET_FALSE( fileCfg ) ;
        NULL_RET_FALSE( (*fpage) ) ;
        NULL_RET_FALSE( url ) ;
        fprintf( (*fpage),
                 "<HTML>\n"
                 "<CENTER><H1><U>Directory Contents</U></H1></CENTER>\n"
                 "<P>\n"
                 "<UL>\n") ;
        ok = L_FILE_DIR_OperOverDirEntrys(url->file,(*fpage)) ;
        fprintf( (*fpage),
                 "</UL>\n"
                 "<P>\n"
                 "</HTML>\n") ;
        return ok ;
      }


   /* ................................................................... */

