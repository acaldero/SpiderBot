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

      #include "corelib/l_dir/x_dir.h"
      

   /* ... Functions / Funciones ......................................... */

   T_BOOL X_DIR_OperOverFiles ( IN     T_CHAR  *path,
                                IN     T_CHAR  *filtro,
                                IN     T_BOOL(*fresidual)(T_CHAR *, T_CHAR*) )
   {
     T_BOOL      ok, newDIR ;
     t_di_stack  distack ;
     t_dirinfo   wdi, ndi ;
     T_CHAR      *wpath, *fname, *npath, *nfname ;
     T_CHAR      *SelFilter, *SelAll ;
     T_INT       fattrib ;
     T_LONG      fsize, fctime ;

     distack=NULL ;
     newDIR=FALSE ;
     wpath=X_STRING_StrDup(path) ;
     SelAll=V_DIR_AllEntry() ;
     SelFilter=( (filtro==NULL) ? SelAll : filtro ) ;
     ok=V_DIR_FindFirstEntry(&wdi,wpath,SelAll,&fname) ;
     do
     {
       while (ok==TRUE)
       {
         ok=V_DIR_GetEntryInfo(wpath,fname,&fsize,&fctime,&fattrib) ;
         if (ok==TRUE)
            {
              if (V_DIR_IsAttr(fattrib,DE_DIR)==TRUE)
              {
                if ( (X_STRING_Equal(fname,".") == FALSE) 
                                 && 
                     (X_STRING_Equal(fname,"..") == FALSE) )
                   {
                     npath=V_DIR_MakeFullPath(wpath,fname) ;
                     ok=V_DIR_FindFirstEntry(&ndi,npath,SelAll,&nfname) ;
                     if (ok==TRUE)
                        {
                          L_DIRSTK_Push(&distack,&wdi) ;
                          X_ALLOC_MemMove(&wdi,&ndi,c_DIRINFO) ;
                          wpath=npath ;
                          X_ALLOC_Free((void **)&(fname)) ;
                          fname=nfname ;
                          newDIR=TRUE ;
                        } else {
                                 X_ALLOC_Free((void **)&(npath)) ;
                                 X_ALLOC_Free((void **)&(nfname)) ;
                               }
	           } 
              } else {
                       if (X_STRING_Match(fname,SelFilter,TRUE)==TRUE)
                          {
                            if (fresidual(wpath,fname)==FALSE)
                               {
                                 X_ALLOC_Free((void **)&(fname)) ;
                                 X_ALLOC_Free((void **)&(wpath)) ;
                                 L_DIRSTK_Empty(&distack) ;
                                 return FALSE ;
                               }
                          }
                     }
            }
         if (newDIR==TRUE)
            {
              newDIR=FALSE ;
            } else {
                     X_ALLOC_Free((void **)&(fname)) ;
                     ok=V_DIR_FindNextEntry(&wdi,&fname) ;
                   }
       }
       X_ALLOC_Free((void **)&(wpath)) ;
       if (L_DIRSTK_IsEmpty(distack))
          {
            return TRUE ;
          } else {
                   L_DIRSTK_Pop(&distack,&wdi) ;
		   wpath=wdi.path ;
                   ok=V_DIR_FindNextEntry(&wdi,&fname) ;
                 }
     } while (TRUE) ;
   }

   T_BOOL X_DIR_OperOverOneDirFiles ( IN     T_CHAR *path,
                                      IN     T_CHAR *filtro,
                                      IN     T_BOOL(*fresidual)(T_CHAR *, T_CHAR*) )
   {
     T_BOOL      ok ;
     t_dirinfo   wdi ;
     T_CHAR      *wpath, *fname, *SelFilter ;
     T_INT       fattrib ;
     T_LONG      fsize, fctime ;

     wpath=X_STRING_StrDup(path) ;
     SelFilter=(filtro==NULL) ? V_DIR_AllEntry() : filtro ;
     ok=V_DIR_FindFirstEntry(&wdi,wpath,SelFilter,&fname) ;
     while (ok==TRUE)
     {
       ok=V_DIR_GetEntryInfo(wpath,fname,&fsize,&fctime,&fattrib) ;
       if (ok==TRUE)
          {
            if (fresidual(wpath,fname)==FALSE)
               {
                 X_ALLOC_Free((void **)&(fname)) ;
                 X_ALLOC_Free((void **)&(wpath)) ;
                 return FALSE ;
               }
          }
       X_ALLOC_Free((void **)&(fname)) ;
       ok=V_DIR_FindNextEntry(&wdi,&fname) ;
     }
     X_ALLOC_Free((void **)&(wpath)) ;
     return TRUE ;
   }

   T_BOOL X_DIR_OperOverEntrys ( IN     T_CHAR *path,
                                 IN     T_CHAR *filtro,
                                 IN     T_BOOL(*fresidual)(T_CHAR *, T_CHAR*) )
   {
     T_BOOL      ok, newDIR ;
     t_di_stack  distack ;
     t_dirinfo   wdi, ndi ;
     T_CHAR      *wpath, *fname, *npath, *nfname ;
     T_CHAR      *SelFilter, *SelAll ;
     T_INT       fattrib ;
     T_LONG      fsize, fctime ;

     distack=NULL ;
     newDIR=FALSE ;
     wpath=X_STRING_StrDup(path) ;
     SelAll=V_DIR_AllEntry() ;
     SelFilter=( (filtro==NULL) ? SelAll : filtro ) ;
     ok=V_DIR_FindFirstEntry(&wdi,wpath,SelAll,&fname) ;
     do
     {
       while (ok==TRUE)
       {
         ok=V_DIR_GetEntryInfo(wpath,fname,&fsize,&fctime,&fattrib) ;
         if (ok==TRUE)
            {
              if (X_STRING_Match(fname,SelFilter,TRUE)==TRUE)
                 {
                   if (fresidual(wpath,fname)==FALSE)
                      {
                        X_ALLOC_Free((void **)&(fname)) ;
                        X_ALLOC_Free((void **)&(wpath)) ;
                        L_DIRSTK_Empty(&distack) ;
                        return FALSE ;
                      }
                 }
              if (V_DIR_IsAttr(fattrib,DE_DIR)==TRUE)
              {
                if ( (X_STRING_Equal(fname,".") == FALSE) 
                                 && 
                     (X_STRING_Equal(fname,"..") == FALSE) )
                   {
                     npath=V_DIR_MakeFullPath(wpath,fname) ;
                     ok=V_DIR_FindFirstEntry(&ndi,npath,SelAll,&nfname) ;
                     if (ok==TRUE)
                        {
                          L_DIRSTK_Push(&distack,&wdi) ;
                          X_ALLOC_MemMove(&wdi,&ndi,c_DIRINFO) ;
                          wpath=npath ;
                          X_ALLOC_Free((void **)&(fname)) ;
                          fname=nfname ;
                          newDIR=TRUE ;
                        } else {
                                 X_ALLOC_Free((void **)&(npath)) ;
                                 X_ALLOC_Free((void **)&(nfname)) ;
                               }
	           } 
              }
            }
         if (newDIR==TRUE)
            {
              newDIR=FALSE ;
            } else {
                     X_ALLOC_Free((void **)&(fname)) ;
                     ok=V_DIR_FindNextEntry(&wdi,&fname) ;
                   }
       }
       X_ALLOC_Free((void **)&(wpath)) ;
       if (L_DIRSTK_IsEmpty(distack))
          {
            return TRUE ;
          } else {
                   L_DIRSTK_Pop(&distack,&wdi) ;
		   wpath=wdi.path ;
                   ok=V_DIR_FindNextEntry(&wdi,&fname) ;
                 }
     } while (TRUE) ;
   }


/* ....................................................................... */

