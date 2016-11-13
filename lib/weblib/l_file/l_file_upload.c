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

      #include "weblib/l_file/l_file_upload.h"


   /* ... Functions / Funciones ......................................... */

      FILE   *L_FILE_UPLOAD_OpenUrlToWrite   ( INOUT  t_downLoadWS   *dlws,
                                               IN     t_url          *url )
      {
        FILE    *fpage ;
        T_CHAR  *fname ;

        /* ... check params ... */
        NULL_RET_FALSE(dlws) ;
        NULL_RET_FALSE(url) ;

        /* ... open file ... */
        fname = L_URLFILE_MirrorUrlName(url,dlws->mirrorSelection) ;
        fpage = L_FILE_UPLOAD_OpenUrlToWrite_2(dlws,fname) ;
        X_ALLOC_Free((void **)&fname) ;

        /* ... return ... */
        return fpage ;
      }

      FILE   *L_FILE_UPLOAD_OpenUrlToWrite_2 ( INOUT  t_downLoadWS   *dlws,
                                               IN     T_CHAR         *uname )
      {
        FILE    *fpage ;
        T_CHAR  *buf ;

        /* ... check params ... */
        NULL_RET_FALSE(dlws) ;
        NULL_RET_FALSE(uname) ;

        /* ... open file ... */
        fpage = L_FILE_FullPathOpen(uname,"w+",0770) ;
        NULL_RET_NULL(fpage) ;
        buf = X_ALLOC_Malloc( 16 * 1024 ) ;
        setbuf(fpage,buf) ;

        /* ... return ... */
        return fpage ;
      }


   /* ................................................................... */

