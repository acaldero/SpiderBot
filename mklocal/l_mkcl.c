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

      #include "mklocal/l_mkcl.h"


   /* ... Glob. vars / Vars. globales ................................... */

      T_INT   L_MKCL_p_number = 
              6 ; 
      T_CHAR *L_MKCL_p_name[] = 
              {
                "-h*",
                "-alls*",
                "-skipb*",
                "-makeq*",
                "-sile*",
                "-dir*"
              } ;
      T_CHAR *L_MKCL_p_help[] = 
              {
                "this screen",
                "convert all urls",
                "skip binary files",
                "rewrite cgi's query",
                "be quiet...",
                "use <choice> as working dir"
              } ;
      T_BOOL  L_MKCL_p_alone[] = 
              {
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                FALSE
              } ;


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_MKCL_SetupCommandLine ( IN     t_listOptions  *cl_opt )
      {
        T_BOOL           ok ;
        t_cl_option     *elto_opt ;
        T_INT            i ;

        L_CL_PonerVacia(cl_opt) ;
        for (i=0; i<L_MKCL_p_number; i++)
            {
              elto_opt = L_CL_CrearOption() ;
              NULL_RET_FALSE(elto_opt) ;
              elto_opt->switch_name = X_STRING_StrDup(L_MKCL_p_name[i]) ;
              elto_opt->switch_help = X_STRING_StrDup(L_MKCL_p_help[i]) ;
              elto_opt->alone       = L_MKCL_p_alone[i] ;
              ok = L_CL_Insertar(cl_opt,elto_opt) ;
              FALSE_RET_FALSE(ok) ;
            }
        return TRUE ;
      }

      T_BOOL   L_MKCL_ProcessCommandLine  ( IN    t_listOptions  *cl_opt,
                                            OUT   t_mkOptions    *mkOpt )
      {
        t_cl_option     *elto_opt ;
        T_INT            i ;

        (mkOpt->help_f)          = OFF ;
        (mkOpt->allSites_f)      = OFF ;
        (mkOpt->skipBin_f)       = OFF ;
        (mkOpt->verbose_f)       = ON ;
        (mkOpt->makeQuery_f)     = ON ;
        (mkOpt->webdir)          = NULL ;

        for (i=0; i<L_MKCL_p_number; i++)
        {
          elto_opt = L_CL_ArgIn(cl_opt,i) ;
          if (elto_opt->active == TRUE)
             {
               switch(i) 
               {
                 case 0 :
                      (mkOpt->help_f)      = ON ;
                      break ;
                 case 1 :
                      (mkOpt->allSites_f)  = ON ;
                      break ;
                 case 2 :
                      (mkOpt->skipBin_f)   = ON ;
                      break ;
                 case 3 :
                      (mkOpt->makeQuery_f) = OFF ;
                      break ;
                 case 4 :
                      (mkOpt->verbose_f)   = OFF ;
                      break ;
                 case 5 :
	              L_MKOPT_DupWebDir(mkOpt,elto_opt->value) ;
                      break ;
                 default :
                      break ;
               }
             }
        }
        return TRUE ;
      }

      T_BOOL   L_MKCL_ParseCommandLine  ( OUT   t_mkOptions    *mkOpt,
                                          IN    int             argc,
                                          IN    char           *argv[] )
      {
        T_BOOL           ok ;
        t_listOptions    cl_opt ;
      
        ok = L_MKCL_SetupCommandLine(&cl_opt) ;
        FALSE_RET_FALSE(ok) ;
        if (argc < 2) 
           { 
             X_PRINT_printf(
                    "\n"
                    "    Please, use '-help' to know mklocal's options :\n"
                    "\n"
                    "       $mklocal -help"
                    "\n"
                    "\n") ;
             return FALSE ;
           }
        ok = L_CL_ArgInvalid(argc,argv,&cl_opt) ;
        if (ok == TRUE) 
           { 
             X_PRINT_printf(
                    "\n"
                    "    Please, use '-help' to know valid options :\n"
                    "\n"
                    "       $mklocal -help"
                    "\n"
                    "\n") ;
             return FALSE ;
           }
        L_CL_ArgProcess(argc,argv,&cl_opt) ;
        ok = L_MKCL_ProcessCommandLine(&cl_opt,mkOpt) ;
        L_CL_Vaciar(&cl_opt) ;
        return ok ;
      }


   /* ................................................................... */

