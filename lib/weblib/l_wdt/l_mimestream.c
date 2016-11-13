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

      #include "weblib/l_wdt/l_mimestream.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL      L_MIME_mimeToFile    ( INOUT  FILE       *fout,
                                         INOUT  t_mime     *mimeh )
      {
        T_U_LONG     i ;
        t_kv_field  *kv_field ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(mimeh,"NULL mime header") ;

        /* ... to file ... */
        for (i=0; i<(*mimeh).neltos; i++)
            {
              kv_field = &( (*((*mimeh).table[i])).entry ) ;
              if (kv_field != NULL)
                  fprintf(fout,
                          "\t%s: %s\n",
                          kv_field->key,
                          kv_field->value) ;
            }

        return TRUE ;
      }


  /* ................................................................... */

