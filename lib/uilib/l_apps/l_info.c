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

      #include "uilib/l_apps/l_info.h"


   /* ... Functions / Funciones ......................................... */
   
      T_INT  L_INFO_wprintf  ( IN     T_CHAR   *format,
                               IN     va_list   arg )
      {
        T_INT  ret ;

        ret = L_WIN_Vprintf(MainWin,format,arg) ;
        L_WIN_Flush() ;
        return ret ;
      }

      void   L_INFO_PrintF   ( IN     T_BOOL inWterm,
                               IN     T_CHAR *format, ... )
      {
        va_list arg ;

        va_start(arg,format) ;
        if (inWterm == TRUE)
                 L_INFO_wprintf(format,arg) ;
            else vfprintf(stderr,format,arg) ;
        va_end(arg) ;  
      }

      void   L_INFO_MakingOf ( IN     T_BOOL inWterm,
                               IN     T_CHAR *version )
      {
        L_INFO_PrintF(inWterm,
          "    Copyright (C) 1997/1999 Alejandro Calderon Mateos\n") ;
        L_INFO_PrintF(inWterm,
          "    this software comes with ABSOLUTELY NO WARRANTY;\n") ;
        L_INFO_PrintF(inWterm,
          "    This is free software, and you are welcome to redistribute\n") ;
        L_INFO_PrintF(inWterm,
          "    it under certain conditions.\n") ;
        L_INFO_PrintF(inWterm,
          "    (See GNU Library General Public License).\n") ;
        L_INFO_PrintF(inWterm,
          "    version %s\n\n",version) ;
      }


   /* ................................................................... */

