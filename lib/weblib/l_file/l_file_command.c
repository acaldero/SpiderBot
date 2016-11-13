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

      #include "weblib/l_file/l_file_command.h"


   /* ... Function / Funciones .......................................... */

      /*  DIR Commands  *
       * -------------- */
      T_BOOL    L_FILE_COMMAND_FindFirstEntry  ( OUT   t_dirinfo  *d,
                                                 IN    T_CHAR     *path,
                                                 IN    T_CHAR     *filtro,
                                                 OUT   T_CHAR     **name )
      {
        return V_DIR_FindFirstEntry(d,path,filtro,name) ;
      }

      T_BOOL    L_FILE_COMMAND_FindNextEntry   ( OUT   t_dirinfo  *d,
                                                 OUT   T_CHAR     **name )
      {
        return V_DIR_FindNextEntry(d,name) ;
      }

      T_BOOL    L_FILE_COMMAND_GetEntryInfo    ( IN    T_CHAR     *path,
                                                 IN    T_CHAR     *name,
                                                 OUT   T_LONG     *size,
                                                 OUT   T_LONG     *ctime,
                                                 OUT   T_INT      *attrib )
      {
        return V_DIR_GetEntryInfo(path,name,size,ctime,attrib) ;
      }


  /* ................................................................... */

