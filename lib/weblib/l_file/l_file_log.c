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

      #include "weblib/l_file/l_file_log.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_FILE_LOG_PrintUrl      ( INOUT  FILE   *flog,
                                          IN     t_url  *url )
      {
        T_CHAR  *urlstr ;
        T_BOOL   ok ;

        NULL_RET_FALSE(url) ;
        NULL_RET_FALSE(flog) ;
        fprintf(flog,
                "\n"
                " REQUEST\n") ;
        ok = L_URLSTR_GlobalUrlToRequest(url,&urlstr) ;
        FALSE_RET_FALSE(ok) ;
        fprintf(flog,
                "\t%s\n",
                urlstr) ;
        X_ALLOC_Free( (void **)&(urlstr) ) ;
        return TRUE ;
      }
  
      T_BOOL   L_FILE_LOG_PrintHeader   ( INOUT  FILE              *flog,
                                          INOUT  struct stat       *stath )
      {
        NULL_RET_FALSE(flog) ;
        NULL_RET_FALSE(stath) ;
        fprintf(flog,
                "\n"
                " ANSWER\n") ;
        fprintf(flog,
                "\tsize = %li\n",
                (T_U_LONG)(stath->st_size)) ;
        fprintf(flog,
                "\tinode = %li\n",
                (T_LONG)stath->st_ino) ;
        fprintf(flog,
                "\tprotection mask = %li\n",
                (T_U_LONG)(stath->st_mode)) ;
        return TRUE ;
      }

      T_BOOL   L_FILE_LOG_PrintNotFound ( INOUT  FILE          *flog )
      {
        NULL_RET_FALSE(flog) ;
        fprintf(flog,
                "\n"
                " ANSWER\n") ;
        fprintf(flog,
                "\tFile NOT found\n") ;
        return TRUE ;
      }


   /* ................................................................... */

