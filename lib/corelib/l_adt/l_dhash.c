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

      #include "corelib/l_adt/l_dhash.h"


   /* ... Functions / Funciones ......................................... */

      t_dhash        *L_DHASH_Creat ( void )
      {
        t_dhash  *lpaux ;

        lpaux = X_ALLOC_Malloc(c_DHASH) ;
        NULL_RET_NULL(lpaux) ;
        lpaux->table  = NULL ;
        lpaux->neltos = 0L   ;
        return lpaux ;
      }
 
      T_BOOL          L_DHASH_Destroy  ( INOUT  t_dhash  **dhash )
      {
        T_U_LONG  i ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(dhash) ;
        NULL_RET_TRUE((*dhash)) ;

        /* ... destroy ... */
        for (i=0; i<(**dhash).neltos; i++)
            {
              X_ALLOC_Free( (void **)&((*((**dhash).table[i])).entry.key) ) ;
              X_ALLOC_Free( (void **)&(((**dhash).table[i])) ) ;
            }
        X_ALLOC_Free((void **)&((*dhash)->table)) ;
        X_ALLOC_Free((void **)(dhash)) ;

        return TRUE ;
      }

      T_BOOL      L_DHASH_InsertKV       ( INOUT t_dhash     *dhash,
                                           IN    T_CHAR      *key,
                                           IN    T_POINTER    value )
      {
        T_INT         result ;
        t_entry     *nodo, *nodoin ;
        T_U_LONG      left_right ;
        T_BOOL        found, ok ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(dhash) ;
        NULL__SET_ERROR__RET_FALSE(key) ;
        NULL__SET_ERROR__RET_FALSE(value) ;

        /* ... insert ... */
        nodoin = X_ALLOC_Malloc(c_ENTRY) ;
        NULL_RET_FALSE(nodoin) ;
 	(nodoin->entry).key   = X_STRING_StrDup(key) ;
 	(nodoin->entry).value = value ;
 	(nodoin->left)        = NULL ;
 	(nodoin->right)       = NULL ;
        if ((*dhash).table == NULL)
 	   {
             return L_DARRAY_InsEndDarray( (t_pointerDArray *)&(dhash->table),
                                           (T_U_LONG        *)&(dhash->neltos),
                                           (T_POINTER)nodoin ) ;
 	   } 
        nodo = (*dhash).table[0] ; 
        found = FALSE ;
        do 
        {
          result = X_STRING_CaseStrCmp(key,(nodo->entry).key,FALSE) ;
          if (result == 0)
              return TRUE ;
          if (result <  0)
 	    {
 	      if (nodo->left == 0)
                 {
 		   left_right = 0 ;
 		   found = TRUE ;
 		 }
 		  else nodo = nodo->left ;
 	    }
          if (result >  0)
 	    {
 	      if (nodo->right == 0)
                  {
 		   left_right = 1 ;
 		   found = TRUE ;
 		 }
 		  else nodo = nodo->right ;
 	    }
        } while ( found == FALSE ) ;

        ok = L_DARRAY_InsEndDarray( (t_pointerDArray *)&(dhash->table),
                                    (T_U_LONG        *)&(dhash->neltos),
                                    (T_POINTER)nodoin ) ;
        FALSE_RET_FALSE(ok) ;
        if (left_right == 0)
                 nodo->left  = nodoin ;
            else nodo->right = nodoin ;

        return TRUE ;
      }

      T_POINTER   L_DHASH_ValueOf        ( IN    t_dhash   *dhash,
                                           IN    T_CHAR    *key,
                                           IN    T_BOOL     caseSense )
      {
        t_entry  *naux ;
        T_INT        result ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_NULL(dhash) ;
        NULL__SET_ERROR__RET_NULL(key) ;

        /* ... value of ... */
        if ( (*dhash).table == NULL ) 
           {
             return NULL ;
           }
        naux = (*dhash).table[0] ; 
        while (naux != NULL)
        {
          result = X_STRING_CaseStrCmp(key,(naux->entry).key,caseSense) ;
          if (result ==  0)
              return (naux->entry).value ;
          if (result <  0)
 	     {
 	       if (naux->left == 0)
 	                return NULL ;
 	 	   else naux = naux->left ;
 	     }
          if (result >  0)
 	     {
 	       if (naux->right == 0)
 	                return NULL ;
 	 	   else naux = naux->right ;
 	     }
        }

        return NULL ;
      }


  /* ................................................................... */

