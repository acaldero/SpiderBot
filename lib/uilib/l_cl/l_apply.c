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

      #include "uilib/l_cl/l_apply.h"


   /* ... Functions / Funciones ......................................... */
   
      T_BOOL L_APPLY_ApplyOptions ( INOUT t_listOptions  *cl_opt )
      {
        T_BOOL          ok ;
        t_cl_option    *elto_opt ;

        /* -help */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_HELP) ; ;
        elto_opt->switch_help = X_STRING_StrDup("help (this screen and exit)") ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* -verbose */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_VERBOSE) ; ;
        elto_opt->switch_help = X_STRING_StrDup("verbose mode (line,list)") ;
        elto_opt->alone  = FALSE ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* -recursive */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_RECURSIVE) ; ;
        elto_opt->switch_help = X_STRING_StrDup("recurse into directories") ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* -dir */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_DIRBASE) ; ;
        elto_opt->switch_help = X_STRING_StrDup("begin in <value>") ;
        elto_opt->alone  = FALSE ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }


     /* Principals *
      * ---------- */
      T_BOOL L_APPLY_ArgProcess ( IN     t_listOptions  *cl_opt,
                                  IN     T_INT           argc,
                                  IN     T_CHAR         **argv,
                                  IN     void            (*intro)(void),
                                  INOUT  T_INT          *verbosemode,
                                  INOUT  T_FLAG         *recurseflag,
                                  INOUT  T_INT          *dirpos )
      {
        T_BOOL          ok ;
        t_cl_option    *elto_opt ;
  
        /* ... default values */
        (*recurseflag) = OFF ;
        (*verbosemode) = c_VERBOSE_NO ;
        (*dirpos)      = argc ;

        /* ... process arguments */
        ok = L_CL_ArgProcess(argc,argv,cl_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* ... process options */
        elto_opt = L_CL_ArgIn(cl_opt,0L) ;
	NULL_RET_FALSE(elto_opt) ;
        if (elto_opt->active == TRUE)
           { /* -help */
             (*intro)() ;
             L_CL_ArgInfo(cl_opt) ;
             L_WIN_Flush() ;
             exit(TRUE) ;
           }
        elto_opt = L_CL_ArgIn(cl_opt,1L) ;
	NULL_RET_FALSE(elto_opt) ;
        (*verbosemode) = c_VERBOSE_NO ;
        if (elto_opt->active == TRUE)
           {
             if (X_STRING_Equal((elto_opt->value),"list") == TRUE)
                  (*verbosemode) = c_VERBOSE_LIST ;
             if (X_STRING_Equal((elto_opt->value),"line") == TRUE)
                  (*verbosemode) = c_VERBOSE_LINE ;
           } 
        elto_opt = L_CL_ArgIn(cl_opt,2L) ;
	NULL_RET_FALSE(elto_opt) ;
        if (elto_opt->active == TRUE)
           {
             (*recurseflag) =  ON ;
           } 
        elto_opt = L_CL_ArgIn(cl_opt,3L) ;
	NULL_RET_FALSE(elto_opt) ;
        if (elto_opt->active == TRUE)
           {
             /* -d <dir name> */
             (*dirpos) = elto_opt->position ;
           } 
	/* ... final check */
        if ((*dirpos) == argc)
           { 
  	     X_PRINT_printf("No directory to work (see %s -h)\n",argv[0]) ;
           } 
        return TRUE ;
      }


   /* ................................................................... */

