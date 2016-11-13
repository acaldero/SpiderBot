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

      #include "corelib/l_file/x_print.h"


   /* ... Globla var. / Variables glob. ................................. */

      T_INT  (*X_PRINT_PrintMsg)(const T_CHAR *, va_list) = vprintf ;


   /* ... Functions / Funciones ......................................... */

      void   X_PRINT_setPrintWrapper (
                                       IN  T_INT  (*f_int__string__valist)
                                                  (
                                                    const T_CHAR *,
                                                    va_list
                                                  )
                                     )
      {
        X_PRINT_PrintMsg = f_int__string__valist ;
      }

      void   X_PRINT_write    ( IN    T_CHAR  *msg )
      {
        X_PRINT_printf(msg) ;
      }

      void   X_PRINT_vprintf  ( IN    T_CHAR  *fto,
                                IN    va_list  vl )
      {
        if (X_PRINT_PrintMsg != NULL)
           {
             (*X_PRINT_PrintMsg)(fto,vl) ; 
           }
      }

      void   X_PRINT_printf   ( IN    T_CHAR  *fto, 
                                ... )
      {
        if (X_PRINT_PrintMsg != NULL)
           {
             va_list vl ;

             va_start(vl,fto) ;
             (*X_PRINT_PrintMsg)(fto,vl) ; 
       	     va_end(vl) ;
           }
      }


   /* ................................................................... */

