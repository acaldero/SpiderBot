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

      #include "weblib/l_wdt/l_mime.h"


   /* ... Functions / Funciones ......................................... */

      t_mime        *L_MIME_Creat ( void )
      {
        t_mime  *lpaux ;

        lpaux = X_ALLOC_Malloc(c_MIME) ;
        NULL_RET_NULL(lpaux) ;
        lpaux->table  = NULL ;
        lpaux->neltos = 0L   ;
        return lpaux ;
      }
 
      T_BOOL          L_MIME_Destroy  ( INOUT  t_mime  **mimeh )
      {
        T_U_LONG  i ;

        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(mimeh) ;
        NULL_RET_TRUE((*mimeh)) ;

        /* ... destroy ... */
        for (i=0; i<(**mimeh).neltos; i++)
            {
              X_ALLOC_Free( (void **)&((*((**mimeh).table[i])).entry.key) ) ;
              X_ALLOC_Free( (void **)&((*((**mimeh).table[i])).entry.value) ) ;
              X_ALLOC_Free( (void **)&(((**mimeh).table[i])) ) ;
            }
        X_ALLOC_Free((void **)&((*mimeh)->table)) ;
        X_ALLOC_Free((void **)(mimeh)) ;

        return TRUE ;
      }

      T_BOOL      L_MIME_Insert         ( INOUT t_mime     *mimeh,
                                          IN    T_CHAR     *key,
                                          IN    T_CHAR     *value )
      {
        T_INT         result ;
        t_kv_entry   *nodo, *nodoin ;
        T_U_LONG      left_right ;
        T_BOOL        found, ok ;
 
        /* ... check params ... */
        L_DEBUG_NULL_E_F(mimeh,"NULL mime header") ;
        L_DEBUG_NULL_E_F(key,"NULL mime key") ;

        /* ... insert ... */
        nodoin = X_ALLOC_Malloc(c_KV_ENTRY) ;
        NULL_RET_FALSE(nodoin) ;
 	(nodoin->entry).key   = X_STRING_StrDup(key) ;
 	(nodoin->entry).value = X_STRING_StrDup(value) ;
 	(nodoin->left)        = NULL ;
 	(nodoin->right)       = NULL ;
        if ((*mimeh).table == NULL)
 	   {
             return L_DARRAY_InsEndDarray( (t_pointerDArray *)&(mimeh->table),
                                           (T_U_LONG        *)&(mimeh->neltos),
                                           (T_POINTER)nodoin ) ;
 	   } 
        nodo = (*mimeh).table[0] ; 
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

        ok = L_DARRAY_InsEndDarray( (t_pointerDArray *)&(mimeh->table),
                                    (T_U_LONG        *)&(mimeh->neltos),
                                    (T_POINTER)nodoin ) ;
        FALSE_RET_FALSE(ok) ;
        if (left_right == 0)
                 nodo->left  = nodoin ;
            else nodo->right = nodoin ;

        return TRUE ;
      }

      T_CHAR     *L_MIME_vOf            ( IN    t_mime   *mimeh,
                                          IN    T_CHAR   *key,
                                          IN    T_BOOL    caseSense )
      {
        t_kv_entry  *naux ;
        T_INT        result ;
 
        /* ... check params ... */
        L_DEBUG_NULL_E_N(mimeh,"NULL mime header") ;
        L_DEBUG_NULL_E_N(key,"NULL mime key") ;

        /* ... value of ... */
        if ( (*mimeh).table == NULL ) 
           {
             return NULL ;
           }
        naux = (*mimeh).table[0] ; 
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

      T_BOOL      L_MIME_mimeToFile    ( INOUT  FILE       *fout,
                                         INOUT  t_mime     *mimeh )
      {
        T_U_LONG     i ;
        t_kv_field  *kv_field ;

        /* ... check params ... */
        L_DEBUG_NULL_E_F(mimeh,"NULL mime header") ;

        /* ... to file ... */
        for (i=0; i<(*mimeh).neltos; i++)
            {
              kv_field = &( (*((*mimeh).table[i])).entry ) ;
              if (kv_field != NULL)
                  fprintf(fout,
                          "\t%s: %s\n",
                          kv_field->key,
                          kv_field->value) ;
            }

        return TRUE ;
      }


  /* ................................................................... */

