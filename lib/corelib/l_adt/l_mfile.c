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

      #include "corelib/l_adt/l_mfile.h"


   /* ... Functions / Funciones ......................................... */
 
      MFILE    *L_MFILE_open    ( IN T_CHAR   *mdata,
                                  IN T_U_LONG  msize,
                                  IN T_CHAR   *options )
      {
        MFILE   *mfaux ;
 
        mfaux = X_ALLOC_Malloc(c_MFILE) ;
        NULL_RET_NULL(mfaux) ;
        mfaux->mdata      = mdata ;
        mfaux->mfsize     = (mdata==NULL) ? 0L : msize ;
        mfaux->mfposition = 0L ;
        return L_MFILE_options(mfaux,options) ;
      }
 
      void    L_MFILE_close  ( MFILE **mf )
      {
        if (mf != NULL)
          {
            X_ALLOC_Free((void **)mf) ;
          }
      }
 
      T_BOOL   L_MFILE_seek   ( INOUT MFILE  *mf, 
                                IN    T_LONG  offset, 
                                IN    T_INT   whence )
      {
        T_U_LONG finalpos ;
 
        NULL__SET_ERROR__RET_FALSE(mf) ;
        switch(whence)
        {
         case SEEK_SET :
              finalpos=offset ;
              break ;
         case SEEK_CUR :
              finalpos=mf->mfposition+offset ;
              break ;
         case SEEK_END :
              finalpos=mf->mfsize+offset ;
              break ;
         default :;
        }
        if (finalpos <= mf->mfsize)
          {
            mf->mfposition=finalpos ;
            return TRUE ;
          }
        return FALSE ;
      }
 
      T_U_LONG  L_MFILE_write  ( IN     const void *p,
                                 IN     T_U_LONG size,
                                 IN     T_U_LONG n,
                                 INOUT  MFILE *mf )
      {
        T_CHAR   *btmp ;
        T_U_LONG lenblock, newsize ;
 
        TRUE__SET_ERROR__RET_LONG((mf == NULL),0L) ;
        lenblock = n*size ;
        if (mf->overwrite == TRUE)
          {
            newsize = lenblock + mf->mfposition ;
            btmp = X_ALLOC_Realloc(mf->mdata,newsize) ;
            if (btmp==NULL)
                return 0L ;
            X_ALLOC_MemMove( &(btmp[mf->mfposition]),(void *)p,lenblock ) ;
          }
        else
          {
            newsize = mf->mfsize + lenblock ;
            btmp = X_ALLOC_Realloc(mf->mdata,newsize) ;
            if (btmp==NULL)
                return 0L ;
            X_ALLOC_MemMove( &(btmp[mf->mfposition+lenblock]),
                             &(btmp[mf->mfposition]),
                             (mf->mfsize-mf->mfposition) ) ;
            X_ALLOC_MemMove( &(btmp[mf->mfposition]),(void *)p,lenblock ) ;
          }
        if (mf->floatpos==TRUE)
           mf->mfposition+=lenblock ;
        mf->mdata=btmp ;
        mf->mfsize=newsize ;
        return lenblock ;
      }
 
      T_U_INT   L_MFILE_read    ( IN    MFILE    *mf,
                                  INOUT void     *p,
                                  IN    T_U_LONG  size )
      {
        T_U_LONG canread, bytread ;
 
        TRUE__SET_ERROR__RET_LONG((mf == NULL),0L) ;
        canread=(mf->mfsize) - (mf->mfposition) ;
        bytread=MIN(canread,size) ;
        X_ALLOC_MemMove(p,&(mf->mdata[mf->mfposition]),bytread) ;
        if (mf->floatpos==TRUE)
           mf->mfposition+=bytread ;
        return bytread ;
      }
 
      T_U_INT L_MFILE_printf ( INOUT  MFILE   *mf, 
                               IN     T_CHAR  *format, ... )
      {
        va_list    argptr ;
        T_U_LONG   lenbaux ;
 
        va_start(argptr,format) ;
        lenbaux = L_MFILE_vfprintf(mf,format,argptr) ;
        va_end(argptr) ;
        return lenbaux ;
      }
 
      T_U_INT L_MFILE_vfprintf ( INOUT  MFILE    *mf, 
                                 IN     T_CHAR   *format, 
                                 IN     va_list   va )
      {
        T_CHAR    *baux ;
        T_U_LONG   lenbaux ;
 
        TRUE__SET_ERROR__RET_LONG((mf == NULL),0) ;
        baux = X_STRING_Dvsprintf(format,va) ;
        if (baux==NULL)
           return EOF ;
        lenbaux = strlen(baux) ;
        if (L_MFILE_write(baux,lenbaux,1,mf) == 0)
          {
            X_ALLOC_Free((void **)&baux) ;
            return 0L ;
          }
        X_ALLOC_Free((void **)&baux) ;
        return lenbaux ;
      }
 
      MFILE    *L_MFILE_options   ( INOUT  MFILE   *mf,
                                    IN     T_CHAR  *options )
      {
        NULL__SET_ERROR__RET_NULL(mf) ;
        mf->overwrite  = FALSE ;
        mf->floatpos   = FALSE ;
        if (options!=NULL)
          {
            T_U_INT  i, lenoptions ;
 
            lenoptions=strlen(options) ;
            for (i=0; i<lenoptions; i++)
            {
              if ( (options[i]=='o') || (options[i]=='O') )
                    mf->overwrite  = TRUE ;
              if ( (options[i]=='f') || (options[i]=='F') )
                    mf->floatpos   = TRUE ;
            }
          }
        return mf ;
      }
 
      void    L_MFILE_unlink ( INOUT  MFILE  **mf )
      {
        if (mf != NULL)
          {
            X_ALLOC_Free((void **)&((*mf)->mdata)) ;
            X_ALLOC_Free((void **)mf) ;
          }
      }
 
 
      /* Advanced ... *
       * ------------ */
      T_CHAR *L_MFILE_mdataToStr ( IN  MFILE  *mf )
      {
        T_CHAR   *btmp ;
 
        NULL__SET_ERROR__RET_NULL(mf) ;
        btmp = X_ALLOC_Realloc(mf->mdata,mf->mfsize + 1) ;
        NULL_RET_NULL(btmp) ;
        btmp[mf->mfposition]='\0' ;
        mf->mdata=btmp ;
        return btmp ;
      }
 
      void    L_MFILE_Resetmdata ( INOUT  MFILE  *mf )
      {
        if (mf!=NULL)
          {
            X_ALLOC_Free((void **)&(mf->mdata)) ;
            mf->mfsize     = 0L ;
            mf->mfposition = 0L ;
          }
      }
 

   /* ................................................................... */

