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

      #include "wpplib/l_cl_wpp/l_wpp_cl.h"


   /* ... Glob. vars / Vars. globales ................................... */

      T_INT   L_WPP_CL_p_number = 
              22 ; 
      T_CHAR *L_WPP_CL_p_name[] = 
              {
                "-h*",
                "-silen*",
                "-onlyhttp",
                "-allma*",
                "-samema*",
                "-skipb*",
                "-skipe*",
                "-rentr*",
                "-detect*",
                "-makeq*",
                "-makere*",
                "-in1*",
                "-url",
                "-resume",
                "-maxbyt*",
                "-maxurl*",
                "-proxy",
                "-bs*",
                "-resumef*",
                "-id*",
                "-timeli*",
                "-dela*"
              } ;
      T_CHAR *L_WPP_CL_p_help[] = 
              {
                "this screen",
                "be quiet...",
                "DownLoad using only http",
                "DownLoad from all host",
                "DownLoad from same host",
                "skip binary files",
                "skip exclusion list",
                "rentry file, if any problem downloading",
                "ignore autodetected HTTP version",
                "make cgi-bin querys",
                "rewrite url to offline browsing",
                "rewrite urls as relative inside page",
                "download from <choice>",
                "try recover from <choice> file",
                "limit download to <choice> Bytes",
                "limit download to <choice> Urls",
                "use <choice> as proxy server",
                "read in <choice> bytes",
                "save resume each <choice> urls",
                "uses <user:pass> as identification",
                "skip current transfer after <choice> seconds",
                "download after <choice> seconds"
              } ;
      T_BOOL  L_WPP_CL_p_alone[] = 
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
                TRUE,
                TRUE,
                TRUE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE,
                FALSE
              } ;


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_WPP_CL_SetupCommandLine ( IN     t_listOptions  *cl_opt )
      {
        T_BOOL           ok ;
        t_cl_option     *elto_opt ;
        T_INT            i ;

        L_CL_PonerVacia(cl_opt) ;
        for (i=0; i<L_WPP_CL_p_number; i++)
            {
              elto_opt = L_CL_CrearOption() ;
              NULL_RET_FALSE(elto_opt) ;
              elto_opt->switch_name = X_STRING_StrDup(L_WPP_CL_p_name[i]) ;
              elto_opt->switch_help = X_STRING_StrDup(L_WPP_CL_p_help[i]) ;
              elto_opt->alone       = L_WPP_CL_p_alone[i] ;
              ok = L_CL_Insertar(cl_opt,elto_opt) ;
              FALSE_RET_FALSE(ok) ;
            }
        return TRUE ;
      }

      T_BOOL   L_WPP_CL_SetupId             ( IN    T_CHAR          *idFileName,
                                             OUT   t_wppOptions    *wcOpt )
      {
        FILE    *idFile ;
        T_CHAR  *idStr, *pch ;
        T_LONG   idLen ;

        if ( X_STRING_Equal(idFileName,"-") == TRUE )
#if (0)
           {
             idStr = getpass("login:pass -> ") ;
             L_WPP_OPT_DupIdentification(wcOpt,idStr) ;
           }
#else
           {
             T_CHAR  *user, *pass ;

             user = getpass("login: ") ;
             user = X_STRING_StrDup(user) ;
             pass = getpass("pass: ") ;
             pass = X_STRING_StrDup(pass) ;
             idStr = X_STRING_Dsprintf("%s:%s",user,pass) ;
             L_WPP_OPT_DupIdentification(wcOpt,idStr) ;
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
             L_WPP_OPT_DupIdentification(wcOpt,idStr) ;
             X_ALLOC_Free((void **)&idStr) ;
             fclose(idFile) ;
           }
        return TRUE ;
      }

      T_BOOL   L_WPP_CL_ProcessCommandLine  ( IN    t_listOptions   *cl_opt,
                                              OUT   t_wppOptions    *wcOpt )
      {
        t_cl_option     *elto_opt ;
        T_INT            i ;
        T_BOOL           ok ;

        (wcOpt->help_f)          = OFF ;
        (wcOpt->makeRelative_f)  = OFF ;
        (wcOpt->verbose_f)       = ON ;
        (wcOpt->scanGlobal_f)    = OFF ;
        (wcOpt->fromSamePath_f)  = ON ;
        (wcOpt->skipBin_f)       = OFF ;
        (wcOpt->skipEL_f)        = OFF ;
        (wcOpt->rentry_f)        = OFF ;
        (wcOpt->detectHttp_f)    = OFF ;
        (wcOpt->onlyHttp_f)      = OFF ;
        (wcOpt->makeQuery_f)     = OFF ;
        (wcOpt->in1Page_f)       = OFF ;
        (wcOpt->href)            = NULL ;
        (wcOpt->delay)           = 0L ;
        (wcOpt->resumeFrec)      = 1L ;
        (wcOpt->bufSize)         = LONG_MAX ;
        (wcOpt->timeLimit)       = LONG_MAX ;
        (wcOpt->maxUrls)         = LONG_MAX ;
        (wcOpt->maxBytes)        = LONG_MAX ;
        (wcOpt->recoverFile)     = NULL ;
        (wcOpt->proxy)           = NULL ;
        (wcOpt->identification)  = NULL ;

        for (i=0; i<L_WPP_CL_p_number; i++)
        {
          elto_opt = L_CL_ArgIn(cl_opt,i) ;
          if (elto_opt->active == TRUE)
             {
               switch(i) 
               {
                 case 0 :
                      (wcOpt->help_f) = ON ;
                      break ;
                 case 1 :
                      (wcOpt->verbose_f) = OFF ;
                      break ;
                 case 2 :
                      (wcOpt->onlyHttp_f)   = OFF ;
                      break ;
                 case 3 :
                      (wcOpt->scanGlobal_f) = ON ;
                      break ;
                 case 4 :
                      (wcOpt->fromSamePath_f) = OFF ;
                      break ;
                 case 5 :
                      (wcOpt->skipBin_f) = ON ;
                      break ;
                 case 6 :
                      (wcOpt->skipEL_f) = ON ;
                      break ;
                 case 7 :
                      (wcOpt->rentry_f) = ON ;
                      break ;
                 case 8 :
                      (wcOpt->detectHttp_f) = ON ;
                      break ;
                 case 9 :
                      (wcOpt->makeQuery_f) = ON ;
                      break ;
                 case 10 :
                      (wcOpt->makeRelative_f) = ON ;
                      break ;
                 case 11 :
                      (wcOpt->in1Page_f) = ON ;
                      break ;
                 case 12 :
	              L_WPP_OPT_DupHref(wcOpt,elto_opt->value) ;
                      break ;
                 case 13 :
	              L_WPP_OPT_DupRecoverFile(wcOpt,elto_opt->value) ;
                      break ;
                 case 14 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wcOpt->maxBytes) = LONG_MAX ;
                          else (wcOpt->maxBytes) = atoi(elto_opt->value) ;
                      break ;
                 case 15 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wcOpt->maxUrls) = LONG_MAX ;
                          else (wcOpt->maxUrls) = atoi(elto_opt->value) ;
                      break ;
                 case 16 :
	              L_WPP_OPT_DupProxy(wcOpt,elto_opt->value) ;
                      break ;
                 case 17 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wcOpt->bufSize) = LONG_MAX ;
                          else (wcOpt->bufSize) = atoi(elto_opt->value) ;
                      break ;
                 case 18 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wcOpt->resumeFrec) = LONG_MAX ;
                          else (wcOpt->resumeFrec) = atoi(elto_opt->value) ;
                      break ;
                 case 19 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Equal(elto_opt->value,"") == TRUE)
                         )
                         {
	                      L_WPP_OPT_DupIdentification(wcOpt,"") ;
                         }
	                 else {
                                ok = L_WPP_CL_SetupId(elto_opt->value,wcOpt) ;
	                        FALSE_RET_FALSE(ok) ;
	                      }
                      break ;
                 case 20 :
                      if (
                           (elto_opt->value == NULL)
                                    ||
                           (X_STRING_Match(elto_opt->value,"NO_L*",FALSE) == TRUE)
                         )
                               (wcOpt->timeLimit) = LONG_MAX ;
                          else (wcOpt->timeLimit) = atoi(elto_opt->value) ;
                      break ;
                 case 21 :
                      if (
                           (elto_opt->value == NULL)
                         )
                               (wcOpt->delay) = 0L ;
                          else (wcOpt->delay) = atoi(elto_opt->value) ;
                      break ;
                 default :
                      break ;
               }
             }
        }
        return TRUE ;
      }

      T_BOOL   L_WPP_CL_ParseCommandLine  ( OUT   t_wppOptions   *wcOpt,
                                            IN    int             argc,
                                            IN    char           *argv[],
                                            IN    T_CHAR         *wpp_name )
      {
        T_BOOL           ok ;
        t_listOptions    cl_opt ;
      
        ok = L_WPP_CL_SetupCommandLine(&cl_opt) ;
        FALSE_RET_FALSE(ok) ;
        if (argc < 2) 
           { 
             X_PRINT_printf
             (
               "\n"
               "    Please, use '-help' to know %s's options :\n"
               "\n"
               "       $%s -help"
               "\n"
               "\n",
               wpp_name,
               wpp_name
             ) ;
             return FALSE ;
           }
        ok = L_CL_ArgInvalid(argc,argv,&cl_opt) ;
        if (ok == TRUE) 
           { 
             X_PRINT_printf
             (
               "\n"
               "    Please, use '-help' to know valid options :\n"
               "\n"
               "       $%s -help"
               "\n"
               "\n",
               wpp_name
             ) ;
             return FALSE ;
           }
        L_CL_ArgProcess(argc,argv,&cl_opt) ;
        ok = L_WPP_CL_ProcessCommandLine(&cl_opt,wcOpt) ;
        L_CL_Vaciar(&cl_opt) ;
        return ok ;
      }


   /* ................................................................... */

