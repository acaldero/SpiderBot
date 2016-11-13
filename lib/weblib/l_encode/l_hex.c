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

      #include "weblib/l_encode/l_hex.h"


   /* ... Function / Funciones .......................................... */

      T_INT   L_HEX_HexToDec         ( IN     T_CHAR      *str_hex )
      {
        T_INT   str_len, i, dig, acc ;
        T_CHAR  ch ;

        acc = 0 ;
        str_len = X_STRING_StrLen(str_hex) ;
        for (i=0; i<str_len; i++)
            {
              ch  = str_hex[i] ;
              dig = 0 ;
              if ( (ch >= 'a') && (ch <= 'f') )
                 {
                    dig = (ch - 'a') + 10 ;
                 }
              if ( (ch >= '0') && (ch <= '9') )
                 {
                    dig = (ch - '0') ;
                 }
              if ( !
                   (
                     ( (ch >= 'a') && (ch <= 'f') )
                                   ||
                     ( (ch >= '0') && (ch <= '9') )
                   )
                 )
                 {
                   break ;
                 }
              acc = 16*acc + dig ;
            }
        return acc ;
      }


  /* .................................................................... */

