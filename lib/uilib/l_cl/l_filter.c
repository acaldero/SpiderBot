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

      #include "uilib/l_cl/l_filter.h"


   /* ... Functions / Funciones ......................................... */
   
      T_BOOL L_FILTER_FilterOptions ( INOUT t_listOptions  *cl_opt )
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
        elto_opt->switch_help = X_STRING_StrDup("verbose") ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* -pipe */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_PIPE) ; ;
        elto_opt->switch_help = X_STRING_StrDup("read file from stdin") ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* -fi */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_INPUT) ; ;
        elto_opt->switch_help = X_STRING_StrDup("use file for read") ;
        elto_opt->alone  = FALSE ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        /* -fo */
        elto_opt = L_CL_CrearOption() ;
        NULL_RET_FALSE(elto_opt) ;
        elto_opt->switch_name = X_STRING_StrDup(c_STR_OUTPUT) ; ;
        elto_opt->switch_help = X_STRING_StrDup("use file for write, not stdout") ;
        elto_opt->alone  = FALSE ;
        ok = L_CL_Insertar(cl_opt,elto_opt) ;
        FALSE_RET_FALSE(ok) ;

        return TRUE ;
      }


     /* Principals *
      * ---------- */
      T_BOOL L_FILTER_ArgProcess ( IN     t_listOptions  *cl_opt,
                                   IN     T_INT           argc, 
                                   IN     T_CHAR        **argv,
                                   IN     void          (*intro)(void),
                                   OUT    FILE          **fdinput, 
                                   OUT    FILE          **fdoutput,
                                   OUT    T_CHAR        **filename,
                                   OUT    T_FLAG         *verboseflag,
                                   OUT    T_FLAG         *pipeflag )
      {
        T_BOOL          ok ;
        t_cl_option    *elto_opt ;
  
        /* ... default values */
        (*pipeflag)    = OFF ;
        (*verboseflag) = OFF ;
        (*fdinput)     = stdin ;
        (*fdoutput)    = stdout ;

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
        if (elto_opt->active == TRUE)
           {
             (*verboseflag) = ON ;
           } 
        elto_opt = L_CL_ArgIn(cl_opt,2L) ;
	NULL_RET_FALSE(elto_opt) ;
        if (elto_opt->active == TRUE)
           {
             (*pipeflag)    = ON ;
           } 
        elto_opt = L_CL_ArgIn(cl_opt,3L) ;
	NULL_RET_FALSE(elto_opt) ;
        if (elto_opt->active == TRUE)
           {
             /* -fi <file where read> */
             (*filename) = X_STRING_StrDup((T_CHAR *)(elto_opt->value)) ;
             if ((*pipeflag) == OFF)
                {
                  (*fdinput)=fopen((*filename),"rt") ;
                  if ((*fdinput) == NULL)
                     {
		       X_PRINT_printf(" ->I can not open input file. !\n") ;
                       exit(TRUE) ;
                     }
                  if ((*verboseflag) == ON)
                     {
                       X_PRINT_printf("   Reading from '%s' file ...\n",
                                      (*filename)) ;
                     }
                } else { 
                         if ((*verboseflag) == ON)
                            {
                              X_PRINT_printf("   Reading '%s' from standar input ...\n",
                                             (*filename)) ; 
                            }
                       }
           } 
        elto_opt = L_CL_ArgIn(cl_opt,4L) ;
	NULL_RET_FALSE(elto_opt) ;
        if (elto_opt->active == TRUE)
           {
             /* -fo <file where write> */
             (*fdoutput) = fopen((elto_opt->value),"wt") ;
             if ((*fdoutput) == NULL)
                {
		  X_PRINT_printf(" ->I can not open output file. !\n") ;
                  exit(TRUE) ;
                }
             if ((*verboseflag) == ON)
                {
                  X_PRINT_printf("   Writing into '%s' file ...\n",
                                 (elto_opt->value)) ;
                }
           } 
	/* ... final check */
        if ( ((*pipeflag) == OFF) && ((*fdinput) == stdin) )
           {
	     X_PRINT_printf("   Please, I need a input file name.\n") ;
             exit(TRUE) ;
           }
        if ((*verboseflag) == ON)
           {
             if ((*fdoutput) == stdout)
	          X_PRINT_printf("   Writing into standar output ...\n") ;
           }
        return TRUE ;
      }


   /* ................................................................... */

