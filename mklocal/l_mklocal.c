

 /* ... Include .......................................................... */

    #include "mklocal/l_mklocal.h"


 /* ... Global Vars / Variables Globales .............................. */

    t_mkOptions  mk_opt ;


 /* ... Inline / Macros ............................................... */

#if defined(__MSDOS__)
    #define   L_MKLOCAL_FileChanged()                      \
              {                                            \
                if (mk_opt.verbose_f == ON)                \
                   {                                       \
                      X_PRINT_printf(" ... changed.\n") ;  \
                   }                                       \
              }

    void   L_MKLOCAL_unVerboseFile(filename)               \
           {                                               \
             if (mk_opt.verbose_f == ON)                   \
                {                                          \
                  X_PRINT_printf("\rscaning : %-*s\r",     \
                                 strlen(filename),         \
                                 " ") ;                    \
                }                                          \
           }

    #define   L_MKLOCAL_VerboseFile(filename)              \
              {                                            \
                if (mk_opt.verbose_f == ON)                \
                   {                                       \
                     X_PRINT_printf("scaning : %*s",       \
                                    strlen(filename),      \
                                    filename) ;            \
                   }                                       \
              }
#endif


#if ( defined(__SUNOS__) || defined(__LINUX__) )
    #define   L_MKLOCAL_FileChanged()                      \
              {                                            \
                if (mk_opt.verbose_f == ON)                \
                   {                                       \
                      X_PRINT_printf(" ... changed.") ;    \
                   }                                       \
              }

    #define   L_MKLOCAL_unVerboseFile(filename)            \
              {                                            \
                if (mk_opt.verbose_f == ON)                \
                   {                                       \
                     X_PRINT_printf("\n") ;                \
                   }                                       \
              }

    #define   L_MKLOCAL_VerboseFile(filename)              \
              {                                            \
                if (mk_opt.verbose_f == ON)                \
                   {                                       \
                      X_PRINT_printf("scaning : %*s",      \
                                     strlen(filename),     \
                                     filename) ;           \
                   }                                       \
              }
#endif


 /* ... Functions / Funciones ......................................... */

    T_BOOL L_MKLOCAL_rewriteUrls ( T_CHAR *path, T_CHAR *fname )
    {
      T_CHAR       *protocol, *machine, *file, *relative, *params ;
      T_CHAR       *ffname, *ffajust ;
      T_CHAR       *pch1 ;
      FILE         *fd_html, *fd_ajust ;
      T_BOOL        ok, updated ;
      t_url         url ;
      t_downLoadWS  dlws ;
  
      ffname = (T_CHAR *)V_DIR_MakeFullPath(path,fname) ;
      if (ffname == NULL)
         {
  	   X_PRINT_printf(" ---> No enought memory.\n") ;
  	   return FALSE ;
         }
      L_MKLOCAL_VerboseFile(ffname) ;

      /* ... skip binary file ... */
      if (
           (mk_opt.skipBin_f == ON)
                  &&
           (L_URLFILE_IsBin(fname) == TRUE)
         )
         {
           L_MKLOCAL_unVerboseFile(ffname) ;
  	   X_ALLOC_Free((void **)&ffname) ;
           return TRUE ;
         }

      /* ... open file ... */
      fd_html = fopen(ffname,"r+b") ;
      if (fd_html == NULL)
         {
  	   X_ALLOC_Free((void **)&ffname) ;
  	   X_PRINT_printf(" ---> i can not open input file.\n") ;
  	   return TRUE ; /*FALSE si se considera error*/
         }

      /* ... build url ... */
      pch1 = strchr(ffname,'/') ;
      if (pch1 == NULL)
         {
           X_ALLOC_Free((void **)&ffname) ;
           X_PRINT_printf(" ---> file not from a 'web site mirror'.\n") ;
           return FALSE ;
         }
      protocol = X_STRING_StrDup("http") ;
      pch1[0]  = '\0' ;
      machine  = X_STRING_StrDup(ffname) ;
      pch1[0]  = '/' ;
      file     = X_STRING_StrDup(pch1) ;
      ok       = L_FILE_SimplifyPath(file) ;
      FALSE_RET_FALSE(ok) ;
      relative = NULL ;
      params   = NULL ;
      L_URL_FillFrom(&url,
                     protocol,machine,file,
                     relative,params,htons(80)) ;

      /* ... try ajust ... */
      ffajust = tmpnam(NULL) ;
      fd_ajust = fopen(ffajust,"w+b") ;
      NULL_RET_FALSE(fd_ajust) ;
      L_SETWS_WorkSpaceSetup
      ( 
        &dlws,
         NULL,
         NULL,
         "",
         "",
         NULL,                       /* identification */
         NULL,                       /* proxy */
         (mk_opt.allSites_f == ON) ? c_RS_ALL_SITE : c_RS_SAME_SITE,
         c_SS_GLOBAL,
         c_PS_ALL,
         c_MS_N_DIRECTORY,
         OFF,                        /* detectHttp_f */
         OFF,                        /* verbose_f */
         OFF,                        /* fromSamePath_f */
         mk_opt.skipBin_f,
         OFF,                        /* skipEL_f */
         OFF,                        /* rentry_f */
         mk_opt.makeQuery_f,
         LONG_MAX,                   /* maxBytes */
         LONG_MAX,                   /* maxUrls */
         0,                          /* delay */
         LONG_MAX,                   /* bufSize */
         LONG_MAX,                   /* timeLimit */
         1                           /* resumeFrec */
      ) ;
      ok = L_URLXML_mkLocal(  fd_html,
                              fd_ajust,
                             &updated,
                             &dlws,
                             &url ) ;
      fclose(fd_ajust) ;
      fclose(fd_html) ;
      if ( (ok == TRUE) && (updated == TRUE) )
         {
           ok = L_FILE_Move(ffajust,ffname) ;
           L_MKLOCAL_FileChanged() ;
         }
      else 
         {
           unlink(ffajust) ;
         }

      /* ... bye ... */
      L_MKLOCAL_unVerboseFile(ffname) ;
      X_ALLOC_Free((void **)&ffname) ;
      L_URL_Empty(&url) ;
      return TRUE ;
    }
  
    /*  main  *
     * ------ */
    T_INT L_MKLOCAL_main ( T_INT argc, T_CHAR *argv[] )
    {
      T_BOOL       ok ;
    
      setbuf(stdin,NULL) ;
      L_MKMSG_presentation(&mk_opt) ;

      ok = L_MKCL_ParseCommandLine(&mk_opt,argc,argv) ;
      if (ok == FALSE)
         {
           X_PRINT_printf("\n\n") ;
           return TRUE ;
         }
      if (mk_opt.help_f == ON)
         {
           ok = L_MKMSG_help(&mk_opt) ;
         }
      if (mk_opt.help_f == OFF)
         {
           ok = L_MKOPT_activeOptToFile(stdout,&mk_opt) ;
           if (ok == FALSE)
              {
                X_PRINT_printf("\n\n") ;
                return TRUE ;
              }
           ok = L_MKOPT_CheckValid(stdout,&mk_opt) ;
           if (ok == FALSE)
              {
                X_PRINT_printf("\n\n") ;
                return TRUE ;
              }
           ok = X_DIR_OperOverFiles( mk_opt.webdir,
                                     NULL,
                                     L_MKLOCAL_rewriteUrls ) ;
           if (ok == FALSE)
               return 2 ;
           X_PRINT_printf("\r   End.                                               \n\n") ;
         }
      X_PRINT_printf("\n") ;
      return 1 ;
    }


  /* ................................................................... */

