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

      #include "SpiderBot/l_sbotcl.h"


   /* ... Glob. vars / Vars. globales ................................... */

      T_INT   L_SBOTCL_p_number = 
              16 ; 
      T_CHAR *L_SBOTCL_p_name[] = 
              {
                "-h*",
                "-silen*",
                "-allma*",
                "-samema*",
                "-skipb*",
                "-skipe*",
                "-rentr*",
                "-detect*",
                "-makeq*",
                "-url",
                "-resume",
                "-maxbyt*",
                "-maxurl*",
                "-proxy",
                "-bs*",
                "-id*"
              } ;
      T_CHAR *L_SBOTCL_p_help[] = 
              {
                "this screen",
                "be quiet...",
                "DownLoad from all host",
                "DownLoad from same host",
                "skip binary files",
                "skip exclusion list",
                "rentry file, if any problem downloading",
                "ignore autodetected HTTP version",
                "make cgi-bin querys",
                "download from <choice>",
                "try recover from <choice> file",
                "limit download to <choice> Bytes",
                "limit download to <choice> Urls",
                "use <choice> as proxy server",
                "read in <choice> bytes",
                "uses <user:pass> as identification"
              } ;
      T_BOOL  L_SBOTCL_p_alone[] = 
              {
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                TRUE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE
              } ;


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_SBOTCL_SetupCommandLine ( IN     t_listOptions  *cl_opt )
      {
        T_BOOL           ok ;
        t_cl_option     *elto_opt ;
        T_INT            i ;

        L_CL_PonerVacia(cl_opt) ;
        for (i=0; i<L_SBOTCL_p_number; i++)
            {
              elto_opt = L_CL_CrearOption() ;
              NULL_RET_FALSE(elto_opt) ;
              elto_opt->switch_name = X_STRING_StrDup(L_SBOTCL_p_name[i]) ;
              elto_opt->switch_help = X_STRING_StrDup(L_SBOTCL_p_help[i]) ;
              elto_opt->alone       = L_SBOTCL_p_alone[i] ;
              ok = L_CL_Insertar(cl_opt,elto_opt) ;
              FALSE_RET_FALSE(ok) ;
            }
        return TRUE ;
      }

      T_BOOL   L_SBOTCL_SetupId             ( IN    T_CHAR         *idFileName,
                                              OUT   t_wppOptions    *wOpt )
      {
        FILE    *idFile ;
        T_CHAR  *idStr, *pch ;
        T_LONG   idLen ;

        if ( X_STRING_Equal(idFileName,"-") == TRUE )
#if (0)
           {
             idStr = getpass("login:pass -> ") ;
             L_WPP_OPT_DupIdentification(wOpt,idStr) ;
           }
#else
           {
             T_CHAR  *user, *pass ;

             user = getpass("login: ") ;
             user = X_STRING_StrDup(user) ;
             pass = getpass("pass: ") ;
             pass = X_STRING_StrDup(pass) ;
             idStr = X_STRING_Dsprintf("%s:%s",user,pass) ;
             L_WPP_OPT_DupIdentification(wOpt,idStr) ;
             X_ALLOC_Free((void **)&user) ;
             X_ALLOC_Free((void **)&pass) ;
             X_ALLOC_Free((void **)&idStr) ;
           }
#endif
        else 
           {
             idFile = fopen(idFileName,"rb") ;
             if (idFile == NULL)
                {
                  X_PRINT_printf("\n"
                                 "    I can NOT open %s file\n",
                                 idFileName) ;
                  return FALSE ;
                }
             idLen = L_FILE_FileSize(idFile) ;
             idStr = X_ALLOC_Malloc(idLen) ;
     	     NULL_RET_FALSE(idStr) ;
     	     fread(idStr,idLen,1,idFile) ;
     	     pch = strchr(idStr,'\n') ;
     	     if (pch != NULL)
                 pch[0] = '\0' ;
             L_WPP_OPT_DupIdentification(wOpt,idStr) ;
             X_ALLOC_Free((void **)&idStr) ;
             fclose(idFile) ;
           }
        return TRUE ;
      }

      T_BOOL   L_SBOTCL_ProcessCommandLine  ( IN    t_listOptions  *cl_opt,
                                              OUT   t_wppOptions    *wOpt )
      {
        t_cl_option     *elto_opt ;
        T_INT            i ;
        T_BOOL           ok ;

        wOpt->href           = NULL ;
        wOpt->proxy          = NULL ;
        wOpt->recoverFile    = NULL ;
        wOpt->identification = NULL ;
        L_SBOTOPT_MakeEmpty(wOpt) ;

        for (i=0; i<L_SBOTCL_p_number; i++)
        {
          elto_opt = L_CL_ArgIn(cl_opt,i) ;
          if (elto_opt->active == TRUE)
             {
               switch(i) 
               {
                 case 0 :
                      (wOpt->help_f) = ON ;
                      break ;
                 case 1 :
                      (wOpt->verbose_f) = OFF ;
                      break ;
                 case 2 :
                      (wOpt->scanGlobal_f) = ON ;
                      break ;
                 case 3 :
                      (wOpt->fromSamePath_f) = OFF ;
                      break ;
                 case 4 :
                      (wOpt->skipBin_f) = ON ;
                      break ;
                 case 5 :
                      (wOpt->skipEL_f) = ON ;
                      break ;
                 case 6 :
                      (wOpt->rentry_f) = ON ;
                      break ;
                 case 7 :
                      (wOpt->detectHttp_f) = ON ;
                      break ;
                 case 8 :
                      (wOpt->makeQuery_f) = ON ;
                      break ;
                 case 9 :
	              L_WPP_OPT_DupHref(wOpt,elto_opt->value) ;
                      break ;
                 case 10 :
	              L_WPP_OPT_DupRecoverFile(wOpt,elto_opt->value) ;
                      break ;
                 case 11 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wOpt->maxBytes) = LONG_MAX ;
                          else (wOpt->maxBytes) = atoi(elto_opt->value) ;
                      break ;
                 case 12 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wOpt->maxUrls) = LONG_MAX ;
                          else (wOpt->maxUrls) = atoi(elto_opt->value) ;
                      break ;
                 case 13 :
	              L_WPP_OPT_DupProxy(wOpt,elto_opt->value) ;
                      break ;
                 case 14 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wOpt->bufSize) = LONG_MAX ;
                          else (wOpt->bufSize) = atoi(elto_opt->value) ;
                      break ;
                 case 15 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Equal(elto_opt->value,"") == TRUE)
                         )
                         {
	                      L_WPP_OPT_DupIdentification(wOpt,"") ;
                         }
	                 else {
                                ok = L_SBOTCL_SetupId(elto_opt->value,wOpt) ;
	                        FALSE_RET_FALSE(ok) ;
	                      }
                      break ;
                 default :
                      break ;
               }
             }
        }
        return TRUE ;
      }

      T_BOOL   L_SBOTCL_ParseCommandLine  ( OUT   t_wppOptions   *wOpt,
                                            IN    int             argc,
                                            IN    char           *argv[] )
      {
        T_BOOL           ok ;
        t_listOptions    cl_opt ;
      
        ok = L_SBOTCL_SetupCommandLine(&cl_opt) ;
        FALSE_RET_FALSE(ok) ;
        if (argc < 2) 
           { 
             return FALSE ;
           }
        ok = L_CL_ArgInvalid(argc,argv,&cl_opt) ;
        if (ok == TRUE) 
           { 
             return FALSE ;
           }
        L_CL_ArgProcess(argc,argv,&cl_opt) ;
        ok = L_SBOTCL_ProcessCommandLine(&cl_opt,wOpt) ;
        L_CL_Vaciar(&cl_opt) ;
        return ok ;
      }


   /* ................................................................... */

