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

      #include "corelib/l_dir/v_dir.h"
      #include "corelib/l_dir/i_fffn.c"
      #include "corelib/l_dir/i_dirent.c"


   /* ... glob var / variable global ......................................*/

      T_INT FST=__FSTYPE__ ;
      T_INT FSL=__FSLIB__ ;


   /* ... Functions / Funciones ......................................... */

    /* Funciones Auxiliares ... *
     * ------------------------ */
    T_BOOL V_DIR_ErrorInfo ( IN  T_INT  errniao )
    {
      switch (errniao)
      {
	case ENOENT :
             /*
                L_DEBUG_MSG_Write(WARNING,TRUE,"NO more dir entrys") ;
                NO es error, sino algo natural, se acaban
                las entradas en el directorio.
                No suele ser necesario informar.
             */
	     return FALSE ;
        case EBADF  :
             L_DEBUG_MSG_Write(ERROR,TRUE,"BAD file descriptor") ;
	     return FALSE ;
        case EACCES :
             L_DEBUG_MSG_Write(ERROR,TRUE,"Permission denied") ;
	     return FALSE ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,"Unknow fail reading entrys") ;
             return FALSE ;
      }
    }

    /* Funciones Independientes *
     * ------------------------ */
    T_INT  V_DIR_Configur ( IN  T_INT  cfgnew )
    {
      T_INT oldcfg ;

      switch (cfgnew)
      {
        case c_LDOS :
        case c_LDIRENT :
             oldcfg=FSL ;
             FSL=cfgnew ;
             return oldcfg ;
        case c_FAT  :
        case c_XFS  :
             oldcfg=FST ;
             FST=cfgnew ;
             return oldcfg ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,"Invalid configuration.") ;
      }
      return -1 ;
    }

    T_BOOL V_DIR_FindFirstEntry ( OUT  t_dirinfo  *d,
  			          IN   T_CHAR     *path,
                                  IN   T_CHAR     *filtro,
                                  OUT  T_CHAR    **name )
    {
      T_BOOL ok ;

      d->path=path ;
      d->filtro=filtro ;
      switch (FSL)
      {
        case c_LDOS :
             ok=I_FFFN_FindFirstEntry(&(d->ff),path,filtro,name) ;
             break ;
        case c_LDIRENT : 
             ok=I_DIRENT_FindFirstEntry(&(d->d),path,filtro,name) ;
             break ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFSL) ;
             return FALSE ;
      }
      if (ok==FALSE)
          return V_DIR_ErrorInfo(errno) ;
      return TRUE ;
    }

    T_BOOL V_DIR_FindNextEntry ( OUT  t_dirinfo  *d,
		                 OUT  T_CHAR    **name )
    {
      T_BOOL ok ;

      switch (FSL)
      {
        case c_LDOS : 
             ok=I_FFFN_FindNextEntry(&(d->ff),name) ;
             break ;
        case c_LDIRENT :
             ok=I_DIRENT_FindNextEntry(&(d->d),d->filtro,name) ;
             break ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFSL) ;
             return FALSE ;
      }
      if (ok==FALSE)
          return V_DIR_ErrorInfo(errno) ;
      return TRUE ;
    }

    T_BOOL  V_DIR_GetEntryInfo ( IN  T_CHAR  *path,  
			         IN  T_CHAR  *name,
                                 OUT T_LONG  *size, 
			         OUT T_LONG  *ctime,
                                 OUT T_INT   *attrib )
    {
      T_BOOL ok ;

      switch (FSL)
      {
        case c_LDOS : 
             ok=I_FFFN_GetEntryInfo(path,name, size,ctime,attrib) ;
             break ;
        case c_LDIRENT : 
             ok=I_DIRENT_GetEntryInfo(path,name,V_DIR_DirSep(),
                                      size,ctime,attrib) ;
             break ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFSL) ;
             return FALSE ;
      }
      if (ok==FALSE)
          return V_DIR_ErrorInfo(errno) ;
      return TRUE ;
    }

    T_CHAR *V_DIR_DirSep ( void )
    {
      switch (FST)
      {
        case c_FAT : return c_DOS_DIR_SEP ;
        case c_XFS : return c_UNIX_DIR_SEP ;
	default :
              L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFST) ;
              return NULL ;
      }
    }

    T_CHAR *V_DIR_AllEntry ( void )
    {
      switch (FSL)
      {
        case c_LDOS    : return c_FFFN_DIR_ALLENTRY ;
        case c_LDIRENT : return c_DIRENT_DIR_ALLENTRY ;
	default :
              L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFST) ;
              return NULL ;
      }
    }

    T_BOOL V_DIR_IsAttr ( IN  T_INT  fattrib,
                          IN  T_INT  patron )
    {
      switch (FSL)
      {
        case c_LDOS :
             switch(patron)
             {
               case DE_DIR    : return I_FFFN_IsAttr(fattrib,FA_DIREC) ;
               case DE_ARCH   : return I_FFFN_IsAttr(fattrib,FA_ARCH) ;
               case DE_RDONLY : return I_FFFN_IsAttr(fattrib,FA_RDONLY) ;
               case DE_HIDDEN : return I_FFFN_IsAttr(fattrib,FA_HIDDEN) ;
               case DE_SYSTEM : return I_FFFN_IsAttr(fattrib,FA_SYSTEM) ;
               case DE_LABEL  : return I_FFFN_IsAttr(fattrib,FA_LABEL) ;
               default : return FALSE ;
	     }
        case c_LDIRENT :
             switch(patron)
             {
               case DE_DIR    : return I_DIRENT_IsAttr(fattrib,S_IFDIR) ;
               case DE_ARCH   : return I_DIRENT_IsAttr(fattrib,S_IFMT) ;
               case DE_RDONLY : return I_DIRENT_IsAttr(fattrib,!S_IWRITE) ;
               default : return FALSE ;
	     }
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFSL) ;
	     return FALSE ;
      }
    }

    T_CHAR *V_DIR_AttrToStr ( IN  T_INT  attr )
    {
      switch (FSL)
      {
        case c_LDOS : return I_FFFN_AttrToStr(attr) ;
        case c_LDIRENT : return I_DIRENT_AttrToStr(attr) ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFSL) ;
      }
      return NULL ;
    }

    T_CHAR *V_DIR_MakeFullPath ( IN  T_CHAR  *path,
                                 IN  T_CHAR  *fname )
    {
      switch (FST)
      {
        case c_FAT :
             return X_STRING_ConcatInStr(path,c_DOS_DIR_SEP,fname) ;
        case c_XFS :
             return X_STRING_ConcatInStr(path,c_UNIX_DIR_SEP,fname) ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFST) ;
             return NULL ;
      }
    }

    T_CHAR *V_DIR_AddDirToPath ( IN  T_CHAR  *path, 
                                 IN  T_CHAR  *dname )
    {
      T_BOOL ok ;
      T_CHAR *astr = path ;

      switch (FST)
      {
        case c_FAT :
             ok=X_STRING_Add2StrToStr(&astr,c_DOS_DIR_SEP,dname) ;
             return ( (ok==TRUE) ? astr : NULL ) ;
        case c_XFS :
             ok=X_STRING_Add2StrToStr(&astr,c_UNIX_DIR_SEP,dname) ;
             return ( (ok==TRUE) ? astr : NULL ) ;
	default :
             L_DEBUG_MSG_Write(ERROR,TRUE,ERR_BADFST) ;
             return NULL ;
      }
    }

    void    V_DIR_MkDir         ( IN  T_CHAR  *dname,
                                  IN  T_INT    dirMode )
    {
      #if (defined(__MSDOS__))
           mkdir(dname) ;
      #endif
      #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
           mkdir(dname,dirMode) ;
      #endif
    }


   /* ................................................................... */


