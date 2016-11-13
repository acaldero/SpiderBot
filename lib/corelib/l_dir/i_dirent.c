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

      #include "corelib/l_dir/i_dirent.h"


   /* ... Functions / Funciones ......................................... */

   /* Funciones uso directorios ... *
    * ----------------------------- */
    T_BOOL I_DIRENT_FindFirstEntry ( OUT  DIR    **d,
                                     IN   T_CHAR *path, 
                                     IN   T_CHAR *filtro,
                                     OUT  T_CHAR **name )
    {
      (*d)=opendir(path) ;
      if ((*d)==NULL)
           return FALSE ;
      return I_DIRENT_FindNextEntry(d,filtro,name) ;
    }

    T_BOOL I_DIRENT_FindNextEntry  ( OUT  DIR     **d, 
                                     IN   T_CHAR  *filtro,
                                     OUT  T_CHAR  **name )
    {
      struct dirent *dentry ;
      extern int errno ;

      do
      {
        dentry=readdir(*d) ;
        if (dentry==NULL)
           {
             closedir((*d)) ;
             errno=ENOENT ;
             return FALSE ;
           }
      } while (!(X_STRING_Match(dentry->d_name,filtro,TRUE))) ;
      (*name)=X_STRING_StrDup(dentry->d_name) ;
      return TRUE ;
    }

    T_BOOL I_DIRENT_GetEntryInfo ( IN   T_CHAR *path, 
                                   IN   T_CHAR *name,
                                   IN   T_CHAR *sep,
                                   OUT  T_LONG *size,
                                   OUT  T_LONG *ctime,
                                   OUT  T_INT  *attrib )
    {
      T_INT result ;
      struct stat st ;
      T_CHAR *auxpath ;

      auxpath=X_STRING_ConcatInStr(path,sep,name) ;
      NULL_RET_FALSE(auxpath) ;
      result=access(auxpath,04) ;   /* 04.read */
      if (result==-1)
         {
           X_ALLOC_Free((void **)&(auxpath)) ;
           if (errno==ENOENT)
               return FALSE ; /*V_DIR_ErrorInfo(errno) ;*/
           L_DEBUG_MSG_Write(WARNING,TRUE,ERR_PDENIED) ;
           return FALSE ;
         }
      result=stat(auxpath,&st) ;
      X_ALLOC_Free((void **)&(auxpath)) ;
      if (result==-1)
          return FALSE ; /*V_DIR_ErrorInfo(errno) ;*/
      (*attrib)=(unsigned short)st.st_mode ;
      (*size)=st.st_size ;
      (*ctime)=st.st_ctime ;
      (*attrib)=st.st_mode ;
      return TRUE ;
    }


   /* Funciones tratamiento Atributos ... *
    * ----------------------------------- */
    T_BOOL I_DIRENT_IsAttr ( IN T_INT fattrib, 
                             IN T_INT patron )
    {
      switch (patron)
      {
        #if defined(__MSDOS__)
          case  S_IFDIR   :
          case  S_IFMT    :
          case  S_IWRITE  :
          case	S_IEXEC   :
          case	S_IFBLK   :
          case	S_IFCHR   :
          case	S_IFIFO   :
          case	S_IFREG   :
          case	S_IREAD   :
                return ( (fattrib & patron) ? TRUE : FALSE ) ;
        #else
          case  S_IFDIR   : return  S_ISDIR(fattrib) ;
          case  S_IFMT    : return  S_ISREG(fattrib) ;
          case  S_IWRITE  : return  (S_IWUSR & fattrib) ;
        #endif
      }
      return FALSE ;
    }

    T_CHAR *I_DIRENT_AttrToStr ( IN T_INT attr )
    {
      static T_CHAR attrstr[12] ;

      #if defined(__MSDOS__)
        attrstr[0]= (attr & S_IFBLK)  ? 'b' : '-' ;
        attrstr[0]= (attr & S_IFCHR)  ? 'c' : attrstr[0] ;
        attrstr[1]= (attr & S_IREAD)  ? 'r' : '-' ;
        attrstr[2]= (attr & S_IWRITE) ? 'w' : '-' ;
        attrstr[3]= (attr & S_IEXEC)  ? 'x' : '-' ;
        attrstr[4]= (attr & S_IFMT)   ? 'M' : '-' ;
        attrstr[5]= (attr & S_IFDIR)  ? 'd' : '-' ;
        attrstr[6]= (attr & S_IFIFO)  ? 'f' : '-' ;
        attrstr[7]= (attr & S_IFREG)  ? 'r' : '-' ;
        attrstr[8]= '\0' ;
      #else
        attrstr[0]= S_ISDIR(attr)  ? 'd' : '-' ;
        attrstr[1]= (attr & S_IRUSR) ? 'r' : '-' ;
        attrstr[2]= (attr & S_IWUSR) ? 'w' : '-' ;
        attrstr[3]= (attr & S_IXUSR) ? 'x' : '-' ;
        attrstr[4]= (attr & S_IRGRP) ? 'r' : '-' ;
        attrstr[5]= (attr & S_IWGRP) ? 'w' : '-' ;
        attrstr[6]= (attr & S_IXGRP) ? 'x' : '-' ;
        attrstr[7]= (attr & S_IROTH) ? 'r' : '-' ;
        attrstr[8]= (attr & S_IWOTH) ? 'w' : '-' ;
        attrstr[9]= (attr & S_IXOTH) ? 'x' : '-' ;
        attrstr[10]= '\0' ;
      #endif
      return attrstr ;
    }


   /* ................................................................... */


