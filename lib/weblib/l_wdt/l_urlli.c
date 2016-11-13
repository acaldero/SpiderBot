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

      #include "weblib/l_wdt/l_urlli.h"


   /* ... Functions / Funciones ......................................... */

      t_urlLi        *L_URLLI_Creat ( void )
      {
        t_urlLi  *lpaux ;

        lpaux = X_ALLOC_Malloc(c_URLBT) ;
        NULL_RET_NULL(lpaux) ;
        lpaux->table  = NULL ;
        lpaux->neltos = 0L   ;
        return lpaux ;
      }
 
      T_BOOL          L_URLLI_Destroy  ( INOUT  t_urlLi  **urlbt )
      {
        T_U_LONG  i ;
        T_BOOL    ok ;

        ok = TRUE ;
        if (
             (  urlbt  == NULL)
                       ||
             ((*urlbt) == NULL)
           )
           {
             errno = ERR__NULL_PARAM ;
             return FALSE ;
           }
        for (i=0; i<(**urlbt).neltos; i++)
            {
              L_URL_Destroy( &((*((**urlbt).table[i])).entry.furl) ) ;
              X_ALLOC_Free((void **)&(((**urlbt).table[i]))) ;
            }
        X_ALLOC_Free((void **)&((*urlbt)->table)) ;
        X_ALLOC_Free((void **)(urlbt)) ;
        return ok ;
      }

      T_BOOL      L_URLLI_IsPresent     ( IN    t_urlLi   *urlbt,
                                          IN    t_url     *elto )
      {
        t_entry  *naux ;
        T_INT     resultado ;
 
        if (urlbt == NULL)
           {
             errno = ERR__NULL_PARAM ;
             return FALSE ;
           }
        if (elto == NULL)
           {
             errno = ERR__NULL_PARAM ;
             return FALSE ;
           }
        if ( (*urlbt).table == NULL ) 
           {
             return FALSE ;
           }
        naux = (*urlbt).table[0] ; 
        while (naux != NULL)
        {
          resultado = L_URL_UrlBinCmp(elto,(naux->entry).furl) ;
          if (resultado == 0)
              return TRUE ;
          if (resultado <  0)
 	     {
 	       if (naux->left == 0)
 	                return FALSE ;
 	 	   else naux = naux->left ;
 	     }
          if (resultado >  0)
 	     {
 	       if (naux->right == 0)
 	                return FALSE ;
 	 	   else naux = naux->right ;
 	     }
        }
        return FALSE ;
      }

      T_BOOL      L_URLLI_Insert        ( INOUT t_urlLi     *urlbt,
                                          IN    t_url       *elto )
      {
        T_INT      resultado ;
        t_entry   *nodo, *nodoin ;
        T_U_LONG   left_right ;
        T_BOOL     encontrado, ok ;
 
        if (urlbt == NULL)
           {
             errno = ERR__NULL_PARAM ;
             return FALSE ;
           }
        if (elto == NULL)
           {
             errno = ERR__NULL_PARAM ;
             return FALSE ;
           }
        nodoin = X_ALLOC_Malloc(c_ENTRY) ;
        NULL_RET_FALSE(nodoin) ;
 	(nodoin->entry).furl = L_URL_UrlDup(elto) ;
 	(nodoin->left)       = NULL ;
 	(nodoin->right)      = NULL ;
        if ((*urlbt).table == NULL)
 	   {
             return L_DARRAY_InsEndDarray( (t_pointerDArray *)&(urlbt->table),
                                           (T_U_LONG        *)&(urlbt->neltos),
                                           (T_POINTER)nodoin ) ;
 	   } 
        nodo = (*urlbt).table[0] ; 
        encontrado = FALSE ;
        do 
        {
          resultado = L_URL_UrlBinCmp(elto,(nodo->entry).furl) ;
          if (resultado == 0)
              return TRUE ;
          if (resultado <  0)
 	    {
 	      if (nodo->left == 0)
                 {
 		   left_right = 0 ;
 		   encontrado = TRUE ;
 		 }
 		  else nodo = nodo->left ;
 	    }
          if (resultado >  0)
 	    {
 	      if (nodo->right == 0)
                  {
 		   left_right = 1 ;
 		   encontrado = TRUE ;
 		 }
 		  else nodo = nodo->right ;
 	    }
        } while ( encontrado == FALSE ) ;

        ok = L_DARRAY_InsEndDarray( (t_pointerDArray *)&(urlbt->table),
                                    (T_U_LONG        *)&(urlbt->neltos),
                                    (T_POINTER)nodoin ) ;
        FALSE_RET_FALSE(ok) ;
        if (left_right == 0)
                 nodo->left  = nodoin ;
            else nodo->right = nodoin ;
        return TRUE ;
      }

      t_url      *L_URLLI_UrlIn            ( IN    t_urlLi      *urlbt,
                                             IN    T_U_LONG      index )
      {
        t_entry  *nodo ;

        if (urlbt == NULL)
           {
             errno = ERR__NULL_PARAM ;
             return NULL ;
           }
        if (index >= urlbt->neltos)
            return NULL ;
        nodo = (t_entry *)L_DARRAY_GetNFromDarray((t_pointerDArray)(urlbt->table),
                                                 index ) ;
        return (*nodo).entry.furl ;
      }


  /* ................................................................... */

