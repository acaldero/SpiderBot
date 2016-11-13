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

      #include "uilib/l_browse/l_fs.h"


   /* ... Functions / Funciones ......................................... */

     /* File sistem propieties  *
      * ----------------------- */
   t_fydp  *L_FS_CreatByDefault ( void )
   {
     t_fydp *aux ;

     aux=(t_fydp *)X_ALLOC_AllocAndSet(c_FYDP,0) ;
     NULL_RET_NULL(aux) ;
     aux->id_presentacion=c_ID_FILESYDIRS ;
     return aux ;
   }
   
   T_BOOL L_FS_Destroy ( t_fydp **np )
   {
     NULL_RET_TRUE(*np) ;
     switch ((*np)->id_presentacion)
     {
       case c_ID_FILESYDIRS :
	    break ;
       default :
	    L_DEBUG_MSG_Write(ERROR,FALSE,"incorrect type propieties identification.") ;
	    return FALSE ;
     }
     X_ALLOC_Free((void **)np) ;
     return TRUE ;
   }


     /* Building file entrys info *
      * ------------------------- */
    T_BOOL NewFullNode ( t_DiNode **td,
                         T_CHAR *name,
                         T_LONG size,
                         T_LONG ctime,
                         T_U_SHORT attrib )
    {
      t_fydp *tp ;
      T_CHAR *tn1 ;

      *td=L_GRAFO_NewNode() ;
      NULL_RET_FALSE((*td)) ;
      tp=L_FS_CreatByDefault() ;
      if (!tp)
	 {
           X_ALLOC_Free((void **)&(*td)) ;
	   return FALSE ;
	 }
      tn1=(T_CHAR *)X_STRING_StrDup(name) ;
      if (!tn1)
	 {
           X_ALLOC_Free((void **)&(*td)) ;
           X_ALLOC_Free((void **)&tp) ;
	   return FALSE ;
	 }
      tp->fyd.attrib=attrib ;
      tp->fyd.size=size ;
      tp->fyd.ctime=ctime ;
      L_GRAFO_SetNodePropiedades((*td),tp) ;
      L_GRAFO_SetName((*td),tn1) ;
      return TRUE ;
    }

    T_BOOL L_FS_ReadFydEntrys  ( INOUT t_DiNode **g,
                                T_CHAR *path,
                                T_CHAR *patron,
                                T_INT attr )
    {
       t_DiNode *e ;
       t_dirinfo k ;
       T_BOOL ok ;
       T_CHAR *name ;
       T_LONG size, ctime ;
       T_INT attrib ;

       if (!(*g))
	   (*g)=L_GRAFO_NewNode() ;
       NULL_RET_FALSE((*g)) ;
       L_GRAFO_SetName(*g,path) ;
       ok=V_DIR_FindFirstEntry(&k,path,patron,&name) ;
       if (ok==TRUE)
           ok=V_DIR_GetEntryInfo(path,name,&size,&ctime,&attrib) ;
       while (ok==TRUE)
       {
	 while ( (ok==TRUE) && (!(attrib & attr)) )
	 {
           X_ALLOC_Free((void **)&name) ;
           ok=V_DIR_FindNextEntry(&k,&name) ;
           if (ok==TRUE)
               ok=V_DIR_GetEntryInfo(path,name,&size,&ctime,&attrib) ;
	 }
	 FALSE_RET_TRUE(ok) ;
	 ok=NewFullNode(&e,name,size,ctime,attrib) ;
	 FALSE_RET_FALSE(ok) ;
	 L_GRAFO_NewSonLink(*g,e) ;
         attrib=!attrib ; /* para entrar en el segundo bucle ... */
       }
       return TRUE ;
     }


     /* Browsing file entrys info *
      * ------------------------- */
     T_CHAR *L_FS_Present ( t_DiNode *g,
			     T_INT x,
			     T_INT y )
     {
       t_navi nav ;
       T_INT  key, state ;
       T_CHAR *filename ;

       nav=L_FS_Open(g,x,y) ;
       NULL_RET_NULL(nav) ;
       state=c_KEYPROC ;
       do
       {
	 L_WIN_Flush() ;
	 key=V_KEYMAP_getkey() ;
	 switch (key)
	 {
	   case c_F2 : L_WCON_Hidden() ;
		       break ;
	   case c_F3 : L_WCON_UnHidden() ;
		       break ;
	   default : state=L_FS_KeyProcesing(&nav,key) ;
	 }
       } while (state==c_KEYPROC) ;
       filename=L_FS_GetFileChose(nav,V_DIR_DirSep()) ;
       L_FS_Close(&nav) ;
       if (state==c_CLOSE)
           filename=NULL ;
       return filename ;
     }

     T_CHAR *L_FS_ReadAndPresent ( T_CHAR *dir2,
				    T_CHAR *patron,
				    T_INT   attrib,
				    T_INT   x,
				    T_INT   y )
     {
       t_DiNode *phijo,*fdir ;
       t_fydp   *npropi ;
       T_U_SHORT npropi_attrib ;
       T_CHAR   *scandir, *scanbase, *sep ;
       T_INT     key, state ;
       T_INT    lensep, lenscandir ;
       T_CHAR  *dir, *paux ;
       t_navi   files ;
       T_BOOL   ok ;

       sep=V_DIR_DirSep() ;
       lensep=strlen(sep) ;
       scandir=(T_CHAR *)X_STRING_StrDup(dir2) ;
       NULL_RET_NULL(scandir) ;
       dir=(T_CHAR *)X_STRING_StrDup(dir2) ;
       if (!dir)
          {
	    X_ALLOC_Free((void **)&scandir) ;
            return NULL ;
          }
       do
       {
         if (X_STRING_Equal(dir,".") == FALSE)
            {
              lenscandir=strlen(scandir) ;
              if (
                   (X_STRING_Equal(dir,"..") == TRUE)
                           &&
                   (lenscandir > (2*lensep+strlen(dir)+1))
                           &&
                   (scandir[lenscandir-lensep-1]!='.')
		 )
              {
                scandir[lenscandir-lensep]='\0' ;
                paux=strrchr(scandir,sep[lensep-1]) ;
                paux[0]='\0' ;
                scandir=X_ALLOC_Realloc(scandir,strlen(scandir)+1) ;
	      } else {
                       scandir=V_DIR_AddDirToPath(scandir,dir) ;
                       if (!scandir)
                          {
                            X_ALLOC_Free((void **)&dir) ;
                            return NULL ;
                          }
                     }
            }
         X_ALLOC_Free((void **)&dir) ;
         scanbase=X_STRING_StrDup(scandir) ;
         if (!scanbase)
            {
              X_ALLOC_Free((void **)&scandir) ;
	      return NULL ;
            }
         fdir=NULL ; /* imprescindible ... */
	 ok=L_FS_ReadFydEntrys(&fdir,scanbase,patron,attrib) ;
	 if (ok==FALSE)
	    {
	      L_GRAFO_FreeKill(&fdir,(T_BOOL (*)(T_POINTER *))L_FS_Destroy) ;
	      return FALSE ;
	    }
	 files=L_FS_Open(fdir,x,y) ;
	 state=c_KEYPROC ;
	 do
	 {
	   L_WIN_Flush() ;
	   key=V_KEYMAP_getkey() ;
	   switch (key)
	   {
	     case c_F2 : L_WCON_Hidden() ;
			 break ;
	     case c_F3 : L_WCON_UnHidden() ;
			 break ;
	     default   : state=L_FS_KeyProcesing(&files,key) ;
	   }
	 } while (state==c_KEYPROC) ;
	 if (state==c_CLOSE)
	    {
	      X_ALLOC_Free((void **)&scandir) ;
	      L_FS_Close(&files) ;
	      L_GRAFO_FreeKill(&fdir,(T_BOOL (*)(T_POINTER *))L_FS_Destroy) ;
	      L_WIN_Flush() ;
	      return NULL ;
	    }
	 if (state==c_CHOSE)
	    {
	      T_CHAR *phijoname ;

	      phijo         = L_FS_GetTHEOption(files) ;
	      npropi        = L_GRAFO_GetNodePropiedades(phijo) ;
	      npropi_attrib = (npropi)->fyd.attrib ;
	      phijoname     = L_GRAFO_GetName(phijo) ;
	      dir           = (T_CHAR *)X_STRING_StrDup(phijoname) ;
	    }
	 L_FS_Close(&files) ;
	 L_GRAFO_FreeKill(&fdir,(T_BOOL (*)(T_POINTER *))L_FS_Destroy) ;
       } while ( V_DIR_IsAttr(npropi_attrib,DE_DIR) ) ;
       L_WIN_Flush() ;
       scandir=V_DIR_AddDirToPath(scandir,dir) ;
       X_ALLOC_Free((void **)&dir) ;
       return scandir ;
     }

     void L_FS_NaviCoor (T_INT sonwidth, T_INT sontall, T_INT espaciado,
                           T_INT *cx, T_INT *cy, T_INT *sx1, T_INT *sy1,
                           T_INT *sx2, T_INT *sy2, T_BOOL *keep)
     {
       T_INT anchowin,largowin ;

       *keep=FALSE ;
       largowin=sontall+2+2*espaciado-1 ;
       *sy2=MIN(V_TERM_cmaxY()-2,(*sy1)+largowin) ;
       *cy=(*sy2)-(*sy1)-(2+2*espaciado-1) ;
       if ((*sy2)!=(*sy1)+largowin)
          {
            T_INT maxcols,needcols ;

            maxcols=(V_TERM_cmaxX()-(*sx1)-1-2*espaciado) / (sonwidth+1) ;
            if (!maxcols)                      /* opc1!opc2!opc3!^^ */
                maxcols=1 ;
            needcols=(sontall / (*cy)) + ((sontall % (*cy)) > 0) ;
            if ( needcols <= maxcols )
               {
                 (*cx)=needcols ;
               } else {
                        *keep=TRUE ;
                        (*cx)=maxcols ;
                      }
          } else {
                   *cx=1 ;
                 }
       anchowin=(*cx)*sonwidth+(*cx)-1+2*espaciado+1 ;
       (*sx2)=*sx1+anchowin ;
       (*cy)=(sontall / (*cx)) + ((sontall % (*cx)) > 0) ;
       (*sy2)=MIN((*sy2),(*sy1)+(*cy)+2+2*espaciado-1) ;
     }

     void L_FS_WrHelpNavi (t_win wh, t_DiNode *d, T_INT o)
     {
       t_DiNode *phijo ;
       t_fydp   *npropi ;
       T_CHAR   *timestr ;

       L_WIN_Clear(wh) ;
       phijo   = L_GRAFO_GetSonN(o-1,d) ;
       npropi  = L_GRAFO_GetNodePropiedades(phijo) ;
       timestr = ctime(&((npropi)->fyd.ctime)) ;
       timestr[strlen(timestr)-1] = '\0' ;
       L_WIN_Printf(wh,"Time=%s, Attr=%s, Size=%li",
			timestr,V_DIR_AttrToStr(npropi->fyd.attrib),npropi->fyd.size) ;
     }


 /* ...................................................................... */

