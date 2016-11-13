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

      #include "corelib/l_cdt/l_strli.h"


   /* ... Functions / Funciones ......................................... */
 
      t_strLi       *L_STRLI_Creat ( void )
      {
        t_strLi  *lpaux ;
 
        lpaux = X_ALLOC_Malloc(c_STRLI) ;
        NULL_RET_NULL(lpaux) ;
        lpaux->list   = NULL ;
        lpaux->neltos = 0L   ;
        return lpaux ;
      }
 
      T_BOOL      L_STRLI_Copy  ( INOUT t_strLi      *listrDest,
                                  IN    t_strLi      *listrOrig )
      {
        NULL__SET_ERROR__RET_FALSE(listrOrig) ;
        NULL__SET_ERROR__RET_FALSE(listrDest) ;
        listrDest->list   = listrOrig->list   ;
        listrDest->neltos = listrOrig->neltos ;
        return TRUE ;
      }
 
      T_BOOL          L_STRLI_Destroy  ( INOUT  t_strLi  **listr )
      {
        T_BOOL ok ;
 
        NULL__SET_ERROR__RET_FALSE((*listr)) ;
        ok = L_DARRAY_FreeEltosDarray( (t_pointerDArray *)&((*listr)->list ),
                                       (T_U_LONG        *)&((*listr)->neltos),
                                       (void (*)(T_POINTER))free ) ;
        X_ALLOC_Free((void **)listr) ;
        return ok ;
      }
 
      T_BOOL          L_STRLI_Insert          ( INOUT t_strLi      *listr,
                                                IN    T_CHAR       *elto )
      {
        T_CHAR  *strins ;
 
        NULL__SET_ERROR__RET_FALSE(listr) ;
        strins = X_STRING_StrDup(elto) ;
        NULL_RET_FALSE(strins) ;
        return L_DARRAY_InsEndDarray( (t_pointerDArray *)&(listr->list ),
                                      (T_U_LONG        *)&(listr->neltos),
                                      (T_POINTER)strins ) ;
      }
 
      T_BOOL          L_STRLI_Empty    ( INOUT  t_strLi   *listr )
      {
        NULL__SET_ERROR__RET_FALSE(listr) ;
        return L_DARRAY_FreeEltosDarray( (t_pointerDArray *)&(listr->list ),
                                         (T_U_LONG        *)&(listr->neltos),
                                         (void (*)(T_POINTER))free ) ;
      }
 
      T_BOOL          L_STRLI_MakeEmpty     ( INOUT  t_strLi   *listr )
      {
        NULL__SET_ERROR__RET_FALSE(listr) ;
        listr->list   = NULL ;
        listr->neltos = 0L ;
        return TRUE ;
      }
 
      T_CHAR      *L_STRLI_StringIn        ( IN    t_strLi      *listr,
                                             IN    T_U_LONG     index )
      {
        NULL__SET_ERROR__RET_FALSE(listr) ;
        if (index >= listr->neltos)
            return NULL ;
        return (T_CHAR *)L_DARRAY_GetNFromDarray((t_pointerDArray)(listr->list),
                                                 index ) ;
      }
 
      T_BOOL       Iguales                 ( IN    T_CHAR    *elto1,
                                             IN    T_CHAR    *elto2 )
      {
        return (X_STRING_Equal(elto1,elto2)) ;
      }

      T_BOOL       L_STRLI_IsPresent       ( IN    t_strLi   *listr,
                                             IN    T_CHAR    *elto )
      {
        NULL__SET_ERROR__RET_FALSE(listr) ;
        return (
                 L_DARRAY_FindEltoDarray
                 (
                   (t_pointerDArray)(listr->list),
                   (listr->neltos),
                   (T_POINTER)elto,
                   (T_BOOL(*)(T_POINTER,T_POINTER))Iguales
                 ) != NULL
               ) ;
      }
 
      T_BOOL       L_STRLI_Delete          ( INOUT t_strLi   *listr,
                                             IN    T_CHAR    *elto )
      {
        T_CHAR  *delto ;
        T_BOOL   ok ;

        NULL__SET_ERROR__RET_FALSE(listr) ;
        delto = L_DARRAY_FindEltoDarray
                (
                  (t_pointerDArray)(listr->list),
                  (listr->neltos),
                  (T_POINTER)elto,
                  (T_BOOL(*)(T_POINTER,T_POINTER))Iguales
                ) ;
        NULL_RET_FALSE(delto) ;
        ok = L_DARRAY_DelEltoDarray( (t_pointerDArray *)&(listr->list),
                                     (T_POINTER)delto) ;
        if (ok == TRUE)
            (listr->neltos) -- ;
        return ok ;
      }


  /* ................................................................... */

