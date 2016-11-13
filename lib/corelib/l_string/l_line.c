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

      #include "corelib/l_string/l_line.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_LINE_enter           ( IN     T_CHAR         *line )
      {
        return
        (
          (X_STRING_Equal(line,"\n") == TRUE)
                         ||
          (X_STRING_Equal(line,"\r\n") == TRUE)
                         ||
          (X_STRING_Equal(line,"\n\r") == TRUE)
        ) ;
      }

      T_BOOL  L_LINE_dot_enter       ( IN     T_CHAR         *line )
      {
        return
        (
          (X_STRING_Equal(line,".") == TRUE)
                         ||
          (X_STRING_Equal(line,".\r\n") == TRUE)
                         ||
          (X_STRING_Equal(line,".\n\r") == TRUE)
        ) ;
      }

      T_CHAR   *L_LINE_skipRoot      ( IN     T_CHAR         *line )
      {
        register int i ;
        register int lenstr ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_NULL(line) ;

        lenstr = X_STRING_StrLen(line) ;
        for (i=0; i<lenstr; i++)
            {
              if (
                   (line[i] != '/')
                          &&
                   (line[i] != '\\')
                 )
                 {
                   return &(line[i]) ;
                 }
            }
        return &(line[lenstr]) ;
      }


   /* ................................................................... */

