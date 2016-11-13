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

      #include "corelib/l_file/l_file.h"


   /* ... Functions / Funciones ......................................... */
  
      /*  File contents ...  *
       * ------------------- */
      T_BOOL  L_FILE_CopyFile ( INOUT  FILE   *fdin,
    		                INOUT  FILE   *fdout,
                                IN     T_LONG  nbytes )
      {
        T_CHAR  fiobuff[c_FBUFFSIZE] ;
        T_LONG  r, rfin ;
        T_INT   d ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fdin) ;
        NULL__SET_ERROR__RET_FALSE(fdout) ;

        /* ... CopyFile ... */
        rfin=nbytes / c_FBUFFSIZE ;
        for (r=1; r<=rfin; r++)
        {
          d=fread(fiobuff,1,c_FBUFFSIZE,fdin) ;
          fwrite(fiobuff,1,d,fdout) ;
        }
        d=fread(fiobuff,1,(size_t)(nbytes % c_FBUFFSIZE),fdin) ;
        fwrite(fiobuff,1,d,fdout) ;

        return TRUE ;
      }  

      T_LONG L_FILE_FileSize ( IN  FILE  *f )
      {
        T_U_LONG curr_pos, fsize ;

        /* ... check params ... */
        TRUE__SET_ERROR__RET_LONG((f == NULL),0L) ;

        /* ... FileSize ... */
        fsize = 0L ;
        curr_pos=ftell(f) ;
        fseek(f,0L,SEEK_END) ;
        fsize=ftell(f) ;
        fseek(f,curr_pos,SEEK_SET) ;
        return fsize ; 
      }
  
      T_BOOL L_FILE_IsDosExe ( IN  FILE  *f )
      {
        T_CHAR    fileid[2] ;
        T_U_LONG  curr_pos ;
  
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(f) ;

        /* ... search 'MZ' ... */
        curr_pos=ftell(f) ;
        fseek(f,0L,SEEK_SET) ;
        fread(fileid,1,2,f) ;
        fseek(f,curr_pos,SEEK_SET) ;
        if (memcmp(fileid,c_DOSEXEID,2) == 0)
            return TRUE ;
        return FALSE ;
      }
  

      /*  File name ...  *
       * --------------- */
      T_BOOL  L_FILE_Rename   ( IN     T_CHAR   *orig,
                                IN     T_CHAR   *dest )
      {
        T_INT  ret ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(orig) ;
        NULL__SET_ERROR__RET_FALSE(dest) ;

#if (1)
        /* ... remove 'dest' file ... */
        unlink(dest) ;

        /* ... link with other name ... */
        ret = link(orig,dest) ;        
        TRUE__SET_ERROR__RET_FALSE((ret < 0)) ;

        /* ... remove old name ... */
        unlink(orig) ;
        TRUE__SET_ERROR__RET_FALSE((ret < 0)) ;
#else
        rename(orig,dest) ;
#endif

        return TRUE ;
      }  

      T_BOOL  L_FILE_Move     ( IN     T_CHAR   *orig,
                                IN     T_CHAR   *dest )
      {
        T_INT   ret ;
        T_BOOL  ok ;
        T_LONG  nbytes ;
        FILE   *forig, *fdest ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(orig) ;
        NULL__SET_ERROR__RET_FALSE(dest) ;

        /* ... open file ... */
        fdest = L_FILE_FullPathOpen(dest,"w+b",0770) ;
        NULL_RET_FALSE(fdest) ;
        forig = fopen(orig,"rb") ;
        NULL_RET_FALSE(forig) ;

        /* ... move content ... */
        fseek(forig,0,SEEK_END) ;
        nbytes = ftell(forig) ;
        rewind(forig) ;
        rewind(fdest) ;
        ret = ftruncate(fileno(fdest),0) ;
        ok = L_FILE_CopyFile(forig,fdest,nbytes) ;

        /* ... close file and remove 'orig' ... */
        fclose(forig) ;
        fclose(fdest) ;
        FALSE_RET_FALSE(ok) ;
        unlink(orig) ;

        return TRUE ;
      }

      T_CHAR *L_FILE_SpecialName ( IN  T_CHAR  *suffix )
      {
  
  #if ( defined(__SUNOS__) || defined(__LINUX__) )
        static T_CHAR Ipid[11] ;
        T_CHAR *fname, *Isuffix, *Itime, *pstr ;
        time_t  tnow ;
  
        Isuffix = ((suffix==NULL) ? "" : (T_CHAR *)suffix) ;
        time(&tnow) ;
        Itime=ctime(&tnow) ;
        pstr=strchr(Itime,'\n') ;
        if (pstr!=NULL)
            *pstr='.' ;
        sprintf(Ipid,"%li",(T_LONG)getpid()) ;
        fname=X_STRING_ConcatInStr(Isuffix,Itime,Ipid) ;
        return fname ;
  #endif
  
  #if defined(__MSDOS__)
        static T_CHAR Ipid[11] ;
        static T_CHAR Itime[7] ;
        T_CHAR *fname, *Isuffix ;
        struct  time t;
  
        Isuffix = ((suffix==NULL) ? "" : (T_CHAR *)suffix) ;
        gettime(&t);
        sprintf(Itime,"%2d%2d%2d",t.ti_hour,t.ti_min,t.ti_sec) ;
        sprintf(Ipid,"%i",getpid()) ;
        fname=X_STRING_ConcatInStr(Isuffix,Itime,Ipid) ;
        return fname ;
  #endif
  
      }
  
      T_BOOL  L_FILE_SimplifyPath ( INOUT  T_CHAR  *fpath )
      {
        T_CHAR  *sB, *sA ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_TRUE(fpath) ;

	/* ... UNIX style ... */
	sA = NULL ;
        sB = strchr(fpath,'/') ;
        do 
        {
	  if (sB == NULL)
	      break ; /* end do{}while */
	  if ( !strncmp(sB,"/\\",strlen("/\\")) )
             {
	       X_ALLOC_MemMove(sB+1,sB+2,strlen(sB+2)+1) ;
               continue ;
             }
	  if ( !strncmp(sB,"/./",strlen("/./")) )
             {
	       X_ALLOC_MemMove(sB+1,sB+3,strlen(sB+3)+1) ;
               continue ;
             }
	  if ( !strncmp(sB,"//",strlen("//")) )
             {
	       X_ALLOC_MemMove(sB+1,sB+2,strlen(sB+2)+1) ;
               continue ;
             }
	  if ( !strncmp(sB,"/../",strlen("/../")) )
             {
	       if (sA != NULL)
                  {
	            if (
                         (strncmp(sA,"/../",strlen("/../")))
                                        &&
	                 (strncmp(sA,"/./",strlen("/./"))) 
                       )
                       {
	                 X_ALLOC_MemMove(sA+1,sB+4,strlen(sB+4)+1) ;
	                 sA = NULL ;
                         sB = strchr(fpath,'/') ;
                         continue ;
                       }
                  }
	       else
                  {
	            if (strncmp(fpath,"./",strlen("./")))
                       {
	                 X_ALLOC_MemMove(sB+1,sB+4,strlen(sB+4)+1) ;
	                 sA = NULL ;
                         sB = strchr(fpath,'/') ;
                         continue ;
                       }
                  }
             }
	  sA = sB ;
          sB = strchr(sB+1,'/') ;
        } while (sB != NULL) ;

	/* ... DOS style ... */
	sA = NULL ;
        sB = strchr(fpath,'\\') ;
        do 
        {
	  if (sB == NULL)
	      break ; /* end do{}while */
	  if ( !strncmp(sB,"\\/",strlen("\\/")) )
             {
	       X_ALLOC_MemMove(sB+1,sB+2,strlen(sB+2)+1) ;
               continue ;
             }
	  if ( !strncmp(sB,"\\.\\",strlen("\\.\\")) )
             {
	       X_ALLOC_MemMove(sB+1,sB+3,strlen(sB+3)+1) ;
               continue ;
             }
	  if ( !strncmp(sB,"\\\\",strlen("\\\\")) )
             {
	       X_ALLOC_MemMove(sB+1,sB+2,strlen(sB+2)+1) ;
               continue ;
             }
	  if ( !strncmp(sB,"\\..\\",strlen("\\..\\")) )
             {
	       if (sA != NULL)
                  {
	            if (
                         (strncmp(sA,"/../",strlen("/../")))
                                        &&
	                 (strncmp(sA,"/./",strlen("/./"))) 
                       )
                       {
	                 X_ALLOC_MemMove(sA+1,sB+4,strlen(sB+4)+1) ;
	                 sA = NULL ;
                         sB = strchr(fpath,'/') ;
                         continue ;
                       }
                  }
	       else
                  {
	            if (strncmp(fpath,"./",strlen("./")))
                       {
	                 X_ALLOC_MemMove(sB+1,sB+4,strlen(sB+4)+1) ;
     	                 sA = NULL ;
                         sB = strchr(fpath,'\\') ;
                         continue ;
                       }
                  }
             }
	  sA = sB ;
          sB = strchr(sB+1,'\\') ;
        } while (sB != NULL) ;

	/* ... windows "/\/" ... */
	sA = NULL ;
        sB = strchr(fpath,'\\') ;
        do 
        {
	  if (sB == NULL)
	      break ; /* end do{}while */
	  if ( !strncmp(sB,"\\/",strlen("\\/")) )
	       X_ALLOC_MemMove(sB,sB+1,strlen(sB+1)+1) ;
	  if ( (*sB) == '\\' )
	       (*sB) = '/' ;
	  sA = sB ;
          sB = strchr(sB+1,'\\') ;
        } while (sB != NULL) ;

	/* ... Simplyfied! ... */
        return TRUE ;
      }


      /*  File descriptor ...  *
       * --------------------- */
      FILE   *L_FILE_FullPathOpen ( IN  T_CHAR  *fpath,
                                    IN  T_CHAR  *fileMode,
                                    IN  T_INT    dirMode )
      {
        FILE    *faux ;
        T_CHAR  *sorg, *fdirs ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(fpath) ;
        NULL__SET_ERROR__RET_FALSE(fileMode) ;

        /* ... FullPathOpen ... */
        fdirs = X_STRING_StrDup(fpath) ;
        NULL_RET_NULL(fdirs) ;
        sorg = strchr(fdirs,(V_DIR_DirSep()[0])) ;
        while (sorg != NULL)
        { 
          (*sorg) = '\0' ; 
          V_DIR_MkDir(fdirs,dirMode) ;
          (*sorg) = V_DIR_DirSep()[0] ;
          sorg = strchr(sorg+1,(V_DIR_DirSep()[0])) ;
        } 
        faux = fopen(fpath,fileMode) ;
        X_ALLOC_Free((void **)&fdirs) ;
        return faux ;
      }


   /* ................................................................... */

