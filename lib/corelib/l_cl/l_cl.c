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

      #include "corelib/l_cl/l_cl.h"


   /* ... Functions / Funciones ......................................... */

      /* Option Management *
       * ----------------- */
      t_cl_option         *L_CL_CrearOption ( void )
      {
        t_cl_option    *lpaux ;
 
        lpaux = X_ALLOC_Malloc(c_CL_OPTION) ;
        NULL_RET_NULL(lpaux) ;
        lpaux->switch_name  = NULL ;
        lpaux->switch_help  = NULL ;
        lpaux->alone        = TRUE ;
        lpaux->active       = FALSE ;
        lpaux->value        = NULL ;
        lpaux->position     = 0 ;
        return lpaux ;
      }
 
      void            L_CL_FreeOption ( INOUT  t_cl_option  *elto_opt )
      {
        if (elto_opt == NULL)
 	   {
             errno = ERR__NULL_PARAM ;
 	   }
        else {
               X_ALLOC_Free((void **)&(elto_opt->switch_name)) ;
               X_ALLOC_Free((void **)&(elto_opt->switch_help)) ;
               if ( (elto_opt)->alone == FALSE )
                     X_ALLOC_Free((void **)&(elto_opt->value)) ;
               X_ALLOC_Free((void **)&(elto_opt)) ;
             }
      }


      /* List Management *
       * --------------- */
      t_listOptions       *L_CL_Crear ( void )
      {
        t_listOptions  *lpaux ;
 
        lpaux = X_ALLOC_Malloc(c_LISTOPTIONS) ;
        NULL_RET_NULL(lpaux) ;
        lpaux->lopt = NULL ;
        lpaux->nopt = 0L   ;
        return lpaux ;
      }
 
      T_BOOL      L_CL_Copia ( INOUT t_listOptions      *opt_liDest,
                               IN    t_listOptions      *opt_liOrig )
      {
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(opt_liOrig) ;
        NULL__SET_ERROR__RET_FALSE(opt_liDest) ;

        opt_liDest->lopt = opt_liOrig->lopt  ;
        opt_liDest->nopt = opt_liOrig->nopt ;
        return TRUE ;
      }
 
      T_BOOL          L_CL_Destruir ( INOUT  t_listOptions  **opt_li )
      {
        T_BOOL ok ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE((*opt_li)) ;

        ok = L_DARRAY_FreeEltosDarray( (t_pointerDArray *)&((*opt_li)->lopt),
                                       (T_U_LONG        *)&((*opt_li)->nopt),
                                       (void (*)(T_POINTER))L_CL_FreeOption ) ;
        X_ALLOC_Free((void **)opt_li) ;
        return ok ;
      }
 
      T_BOOL          L_CL_Insertar        ( INOUT t_listOptions     *opt_li,
                                             IN    t_cl_option       *elto )
      {
        T_CHAR  *myelto ;
 
        /* ... check params ... */
        NULL__SET_ERROR__RET_FALSE(opt_li) ;

        myelto = (T_CHAR *)X_ALLOC_MemDup(elto,c_CL_OPTION) ;
        NULL_RET_FALSE(myelto) ;
        return L_DARRAY_InsEndDarray( (t_pointerDArray *)&(opt_li->lopt),
 				      (T_U_LONG        *)&(opt_li->nopt),
 				      (T_POINTER)myelto ) ;
      }
 
      T_BOOL          L_CL_Vaciar   ( INOUT  t_listOptions   *opt_li )
      {
        NULL__SET_ERROR__RET_FALSE(opt_li) ;
        return L_DARRAY_FreeEltosDarray( (t_pointerDArray *)&(opt_li->lopt),
                                         (T_U_LONG        *)&(opt_li->nopt),
                                         (void (*)(T_POINTER))L_CL_FreeOption ) ;
      }
 
      T_BOOL          L_CL_PonerVacia    ( INOUT  t_listOptions   *opt_li )
      {
        NULL__SET_ERROR__RET_FALSE(opt_li) ;
        opt_li->lopt = NULL ;
        opt_li->nopt = 0L ;
        return TRUE ;
      }
 
      t_cl_option *L_CL_ArgIn           ( IN    t_listOptions      *opt_li,
                                          IN    T_U_LONG            indice )
      {
        NULL__SET_ERROR__RET_FALSE(opt_li) ;
        if (indice >= opt_li->nopt)
            return NULL ;
        return (t_cl_option *)L_DARRAY_GetNFromDarray( (t_pointerDArray)(opt_li->lopt),
 			     		                indice ) ;
      }
 

      /* Arg processing *
       * -------------- */
      void   L_CL_ArgInfo ( IN    t_listOptions  *cl_opt )
      {
        T_INT i ;
  
        /* ... check params ... */
        L_DEBUG_assert( (cl_opt == NULL),
                        ERROR,
                        ERR__NULL_PARAM,"null 'cl_opt' params") ;

        X_PRINT_printf("   Opciones :\n") ;
        for (i=0; i<cl_opt->nopt; i++)
            {
              if ( L_CL_ArgIn(cl_opt,i)->alone == TRUE)
                        X_PRINT_printf("\t%-15s\t%s --->  %-40s\n",
                                       L_CL_ArgIn(cl_opt,i)->switch_name,
			               "        ",
			               L_CL_ArgIn(cl_opt,i)->switch_help) ;
                   else X_PRINT_printf("\t%-15s\t%s --->  %-40s\n",
			               L_CL_ArgIn(cl_opt,i)->switch_name,
		        	       "<choice>",
		        	       L_CL_ArgIn(cl_opt,i)->switch_help) ;
            }
        X_PRINT_printf("\n") ;
      }

      T_BOOL L_CL_ArgInvalid ( IN     T_INT            argc, 
                               IN     T_CHAR         **argv,
                               INOUT  t_listOptions   *cl_opt )
      {
        T_INT  i, j ;
        T_BOOL valid_opt, bad ;
  
        bad = FALSE ;
        for (i=1; i<argc; i++)
          {
            valid_opt = FALSE ;
            for (j=0; (i<argc) && (j<cl_opt->nopt); j++)
                {
                  if ( X_STRING_Match( argv[i],
                                    (L_CL_ArgIn(cl_opt,j)->switch_name),
                                    FALSE) == TRUE )
		     {
                       valid_opt = TRUE ;
                       if ( L_CL_ArgIn(cl_opt,j)->alone == FALSE ) 
                          {
                            i++ ;
                            continue ;
                          }
		     }
                }
            if (valid_opt == FALSE)
               {
                 X_PRINT_printf("Invalid option (see %s %s)\n",
                                argv[0],argv[i]) ;
                 bad = TRUE ;
               }
          }
        return bad ;
      }

      T_BOOL L_CL_ArgProcess ( IN     T_INT            argc, 
                               IN     T_CHAR         **argv,
                               INOUT  t_listOptions   *cl_opt )
      {
        T_INT  i, j ;
  
        for (i=1; i<argc; i++)
          {
            for (j=0; (i<argc) && (j<cl_opt->nopt); j++)
                {
                  if ( X_STRING_Match( argv[i],
                                    (L_CL_ArgIn(cl_opt,j)->switch_name),
                                    FALSE) == TRUE )
                     {
                       L_CL_ArgIn(cl_opt,j)->active   = TRUE ;
                       L_CL_ArgIn(cl_opt,j)->position = i ;
                       if ( L_CL_ArgIn(cl_opt,j)->alone == FALSE ) 
                          {
                            L_CL_ArgIn(cl_opt,j)->value = X_STRING_StrDup((T_CHAR *)(argv[i+1])) ;
                            i++ ;
                            continue ;
                          }
                     }
                }
          }
        return TRUE ;
      }
  

   /* ................................................................... */

