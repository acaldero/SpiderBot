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

      #include "corelib/l_adt/l_darray.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL       L_DARRAY_InsEndDarray ( INOUT t_pointerDArray  *t,
                                           INOUT T_U_LONG         *n,
                                           IN    T_POINTER         gptr )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(n) ;

        /* ... InsEndDarray ... */
        if ( (*t)==(t_pointerDArray)NULL )
           {
             (*t)    = (t_pointerDArray) X_ALLOC_Malloc(2*c_POINTER) ;
             NULL_RET_FALSE(*t) ;
             (*n)    = 1 ;
             (*t)[0] = gptr ;
             (*t)[1] = (T_POINTER)NULL ;
           } 
        else  /* ( (*t) != (t_pointerDArray)NULL ) */
           {
             t_pointerDArray taux ;
      
             (*n)++ ;
             taux=(t_pointerDArray)X_ALLOC_Realloc((*t),((*n)+1)*c_POINTER) ;
             NULL_RET_FALSE(taux) ;
             (*t)=taux ;
             taux[(*n)]=(T_POINTER)NULL ;
             taux[(*n)-1]=gptr ;
           }
        return TRUE ;
      }
   
      T_BOOL       L_DARRAY_DelEndDarray ( INOUT t_pointerDArray  *t,
                                           INOUT T_U_LONG         *n,
                                           INOUT T_POINTER        *delGPtr ) 
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(t) ;
        NULL__SET_ERROR__RET_FALSE((*t)) ; 
        NULL__SET_ERROR__RET_FALSE(n) ;

        /* ... DelEndDarray ... */
        if ((*n)!=0)
           {
             (*n)-- ;
             (*delGPtr)=(*t)[(*n)] ;
             (*t)[(*n)]=(T_POINTER)NULL ;
             (*t)=X_ALLOC_Realloc(*t,((*n)+1)*c_POINTER) ;
           }
        if ((*n)==0)
           {
             X_ALLOC_Free((void **)t) ;
           }
        return TRUE ;
      }
   
      T_BOOL       L_DARRAY_DelBeginDarray ( INOUT t_pointerDArray *t,
                                             INOUT T_U_LONG        *n,
                                             INOUT T_POINTER       *delGPtr ) 
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(t) ;
        NULL__SET_ERROR__RET_FALSE((*t)) ;
        NULL__SET_ERROR__RET_FALSE(n) ;

        /* ... DelBeginDarray ... */
        if ((*n)!=0)
           {
             (*n)-- ;
             (*delGPtr)=(*t)[0] ;
             X_ALLOC_MemMove( &((*t)[0]), 
                              &((*t)[1]),
                              (*n)*c_POINTER ) ;
             (*t)[(*n)]=(T_POINTER)NULL ;
             (*t)=X_ALLOC_Realloc(*t,((*n)+1)*c_POINTER) ;
   
           }
        if ((*n)==0)
           {
             X_ALLOC_Free((void **)t) ;
           }
        return TRUE ;
      }
   
      T_BOOL       L_DARRAY_DelNFromDarray ( IN    t_pointerDArray *t,
                                             INOUT T_U_LONG        *n,
                                             IN    T_U_LONG         orden,
                                             INOUT T_POINTER       *delGPtr )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(t) ;
        NULL__SET_ERROR__RET_FALSE((*t)) ;
        NULL__SET_ERROR__RET_FALSE(n) ;
        TRUE__SET_ERROR__RET_FALSE((orden>(*n))) ;

        /* ... _DelNFromDarray ... */
        if ((*n)!=0)
           {
             (*delGPtr)=(*t)[orden] ;
             X_ALLOC_MemMove( &((*t)[orden]), 
                              &((*t)[orden+1]),
                              ((*n)-orden+1)*c_POINTER ) ;
             (*n)-- ;
             (*t)=X_ALLOC_Realloc(*t,((*n)+1)*c_POINTER) ;
           }
        if ((*n)==0)
           {
             X_ALLOC_Free((void **)t) ;
           }
        return TRUE ;
      }

      T_BOOL       L_DARRAY_ChangeNFromDarray ( IN    t_pointerDArray *t,
                                                INOUT T_U_LONG        *n,
                                                IN    T_U_LONG         orden,
                                                INOUT T_POINTER        nPtr )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(t) ;
        NULL__SET_ERROR__RET_FALSE((*t)) ;
        NULL__SET_ERROR__RET_FALSE(n) ;
        TRUE__SET_ERROR__RET_FALSE((orden>(*n))) ;

        /* ... ChangeNFromDarray ... */
        (*t)[orden] = nPtr ;
        return TRUE ;
      }
   
      T_BOOL       L_DARRAY_FreeEltosDarray ( INOUT t_pointerDArray *t,
                                              INOUT T_U_LONG *n,
                                              IN    void (*freef)(T_POINTER) ) 
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(t) ;
        NULL__SET_ERROR__RET_FALSE(n) ;

        /* ... FreeEltosDarray ... */
        if ((*t)!=NULL)
           {
             T_U_LONG i ;
   
             for (i=0; (*t)[i]; i++) 
                 {
                   freef( (*t)[i] ) ;
                 }
             X_ALLOC_Free((void **)t) ;
           }
        (*n) = 0L ;
        return TRUE ;
      }
   
      T_POINTER  L_DARRAY_FindEltoDarray ( IN     t_pointerDArray  t,  
                                           INOUT  T_U_LONG         n,
                                           IN     T_POINTER        gptr,
                                           IN     T_BOOL (*findf)(T_POINTER,T_POINTER) )
      {   
        T_U_LONG  i ;
 
        /* ... FindEltoDarray ... */
        for (i=0; i<n; i++)
            {
              if ((*findf)(gptr,t[i]) == TRUE)
                  return (t[i]) ;
            }
        return NULL ; 
      }
             

      /*  using NULL elto is end  *
       * ------------------------ */
      T_U_LONG     L_DARRAY_GetNDarray ( IN t_pointerDArray t ) 
      {
        register T_U_LONG i ;
   
        i=0 ;
        if (t)
            for(; (t[i]!=NULL); i++) ;
        return i ;
      }
   
      T_BOOL       L_DARRAY_FreeEltosDarray2 ( INOUT t_pointerDArray *t,
                                               IN    void (*freef)(T_POINTER) ) 
      {
        NULL__SET_ERROR__RET_FALSE( t ) ;

        if ((*t)!=NULL)
           {
             T_U_LONG i ;
   
             for (i=0; (*t)[i]; i++) 
                  freef((*t)[i]) ;
             X_ALLOC_Free((void **)t) ;
           }
        return TRUE ;
      }
   
      T_BOOL       L_DARRAY_DelEltoDarray ( INOUT t_pointerDArray *t,
                                            IN    T_POINTER elto ) 
      {
        T_U_LONG c, pentry ;
   
        NULL__SET_ERROR__RET_FALSE( (*t) ) ;
        NULL__SET_ERROR__RET_FALSE( elto ) ;

        for (c=0; ((*t)[c] && ((*t)[c]!=elto)); c++) ; 
        if ( ((*t)[c]) == (t_pointerDArray)NULL )
           {
             errno = ERR__NOT_FOUND ; 
             return FALSE ;
           }
        pentry=c ;
        c++;
        for(; ((*t)[c]!=NULL); c++) ;
        X_ALLOC_MemMove( &((*t)[pentry]),
                         &((*t)[pentry+1]),
                         (c-pentry)*c_POINTER) ;
        (*t)=X_ALLOC_Realloc(*t,c*c_POINTER) ;
        if (c==1)
           { 
             X_ALLOC_Free((void **)t) ;
             /* solo habia un elemento, el borrado!... y NULL */
           }
        return TRUE ;
      }
   
      T_BOOL       L_DARRAY_InsEndDarray2 ( INOUT t_pointerDArray *t,
                                            IN    T_POINTER gptr ) 
      {
        T_U_LONG i ;    /* i is # eltos! */
   
        i=0 ;
        if ( (*t)!=(t_pointerDArray)NULL )
           {
             for (; ((*t)[i]!=NULL); i++) ;  
           }
        return L_DARRAY_InsEndDarray(t,&i,gptr) ;
      } 
   
      T_BOOL       L_DARRAY_DelEndDarray2 ( INOUT t_pointerDArray *t,
                                            INOUT T_POINTER *delGPtr ) 
      {
        T_U_LONG i ;   /* i es la pos del NULL! */
   
        NULL__SET_ERROR__RET_FALSE( (*t) ) ;
        for(i=0; ((*t)[i]!=NULL); i++) ;
        return L_DARRAY_DelEndDarray(t,&i,delGPtr) ;
      } 
   
      T_POINTER  L_DARRAY_GetNFromDarray2 ( IN t_pointerDArray t,
                                            IN T_U_LONG        orden ) 
      {
        T_U_LONG i ;
   
        NULL__SET_ERROR__RET_FALSE( t ) ;

        for(i=0; ((t[i]!=NULL) && (i!=orden)); i++) ;
        if (i!=orden)
           {
             errno = ERR__NOT_FOUND ; 
             return (T_POINTER)NULL ;
           }
        return (t[orden]) ;
      }
   
   
   /* ................................................................... */

