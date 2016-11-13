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

      #include "corelib/l_dir/i_fffn.h"


   /* ... Functions / Funciones ......................................... */


#if defined(__MSDOS__)

   /* Funciones uso directorios ... *
    * ----------------------------- */
    T_BOOL I_FFFN_FindFirstEntry ( OUT   struct ffblk *ff,
				   IN    T_CHAR       *path,
				   IN    T_CHAR       *filtro,
				   OUT   T_CHAR       **name )
    {
      T_INT result ;
      T_CHAR *auxpath ;

      auxpath=X_STRING_ConcatInStr(path,c_DOS_DIR_SEP,filtro) ;
      NULL_RET_FALSE(auxpath) ;
      result=findfirst(auxpath,ff,0x7fff) ;
      X_ALLOC_Free((void **)&(auxpath)) ;
      if (result==-1)
          return FALSE ; /*V_DIR_ErrorInfo(errno) ;*/
      (*name)=X_STRING_StrDup(ff->ff_name) ;
      return TRUE ;
    }

    T_BOOL I_FFFN_FindNextEntry  ( OUT    struct ffblk *ff,
				   OUT    T_CHAR       **name )
    {
      T_INT result ;

      result=findnext(ff) ;
      if (result==-1)
          return FALSE ; /*V_DIR_ErrorInfo(errno) ;*/
      (*name)=X_STRING_StrDup(ff->ff_name) ;
      return TRUE ;
    }

    T_BOOL  I_FFFN_GetEntryInfo ( IN     T_CHAR  *path,
				  IN     T_CHAR  *name,
				  OUT    long    *size,
				  OUT    long    *ctime,
				  OUT    T_INT   *attrib )
    {
      /* TIP :
         stat parece NO funcionar con las entradas de directorio
         de Windows95, con lo que deberia usarse exclusivamente
         findfirst & findnext 
      */
      T_INT result ;
      T_CHAR *auxpath ;
      struct ffblk ff ;

      auxpath=X_STRING_ConcatInStr(path,c_DOS_DIR_SEP,name) ;
      NULL_RET_FALSE(auxpath) ;
      result=findfirst(auxpath,&ff,0x7fff) ;
      X_ALLOC_Free((void **)&(auxpath)) ;
      if (result==-1)
          return FALSE ; /*V_DIR_ErrorInfo(errno) ;*/
      (*attrib)=(unsigned short)ff.ff_attrib ;
      (*size)=ff.ff_fsize ;
      (*ctime)=((long)ff.ff_fdate * 100000L) + (long)ff.ff_ftime ;
      return TRUE ;
    }


   /* Funciones tratamiento Atributos ... *
    * ----------------------------------- */
    T_BOOL I_FFFN_IsAttr ( IN     T_INT fattrib,
			   IN     T_INT patron )
    {
      switch (patron)
      {
        case  FA_DIREC  :
        case  FA_ARCH   :
        case  FA_RDONLY :
        case  FA_HIDDEN :
        case  FA_SYSTEM :
        case  FA_LABEL  :
              return ((fattrib & patron)==patron) ;
      }
      return FALSE ;
    }

    T_CHAR *I_FFFN_AttrToStr ( IN     T_INT  attr )
    {
      static T_CHAR attrstr[7] ;

      attrstr[0]= (attr & FA_ARCH)   ? 'a' : '-' ;
      attrstr[0]= (attr & FA_DIREC)  ? 'd' : attrstr[0] ;
      attrstr[1]= (attr & FA_RDONLY) ? 'r' : '-' ;
      attrstr[2]= (attr & FA_HIDDEN) ? 'h' : '-' ;
      attrstr[3]= (attr & FA_SYSTEM) ? 's' : '-' ;
      attrstr[4]= (attr & FA_LABEL)  ? 'l' : '-' ;
      attrstr[5]= '\0' ;
      return attrstr ;
    }


 /* ...................................................................... */

#endif

