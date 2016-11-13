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

      #include "mklocal/l_mkopt.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_MKOPT_DupWebDir        ( INOUT  t_mkOptions    *mkOpt,
                                          IN     T_CHAR         *webdir )
      {
        NULL_RET_FALSE(mkOpt) ;
        NULL_RET_FALSE(webdir) ;
        (mkOpt->webdir) = X_STRING_StrDup(webdir) ;
        return TRUE ;
      }

      T_BOOL   L_MKOPT_MakeEmpty        ( OUT   t_mkOptions   *mkOpt )
      {
        NULL_RET_FALSE(mkOpt) ;
        (mkOpt->help_f)          = OFF ;
        (mkOpt->allSites_f)      = OFF ;
        (mkOpt->skipBin_f)       = OFF ;
        (mkOpt->makeQuery_f)     = OFF ;
        (mkOpt->verbose_f)       = ON ;
        X_ALLOC_Free((void **)&(mkOpt->webdir)) ;
        return TRUE ;
      }

      T_BOOL   L_MKOPT_activeOptToFile  ( OUT   FILE           *fout,
                                          IN    t_mkOptions    *mkOpt )
      {
        fprintf(fout,"\tOptions setup...\n") ;

        /* ... Options ... */
        if (mkOpt->webdir      != NULL)
            fprintf(fout,"\twebdir ---------------- %-14s\n", 
                    mkOpt->webdir) ;

        /* ... Flags ... */
        if (mkOpt->skipBin_f != OFF)
            fprintf(fout,"\tSkipBin --------------- ON\n") ;
        if (mkOpt->verbose_f != OFF)
            fprintf(fout,"\tVerbose --------------- ON\n") ;
        if (mkOpt->allSites_f != OFF)
            fprintf(fout,"\tFrom All hosts -------- ON\n") ;
        if (mkOpt->makeQuery_f != OFF)
            fprintf(fout,"\tMake query ------------ ON\n") ;

        fprintf(fout,"\n") ;
        return TRUE ;
      }

      T_BOOL   L_MKOPT_mkOptToFile  ( OUT   FILE           *fout,
                                        IN    t_mkOptions   *mkOpt )
      {
        fprintf(fout,"\tOptions...\n") ;

        fprintf( fout,
                 "\twebdir ---------------- %-14s\n",
                 ((mkOpt->webdir      == NULL) ? "none" : mkOpt->webdir) 
               ) ;
        fprintf( fout,
                 "\tSkipBin --------------- %-14s\n",
                 ((mkOpt->skipBin_f == ON) ? "ON" : "OFF")
               ) ;
        fprintf( fout,
                 "\tVerbose --------------- %-14s\n",
                 ((mkOpt->verbose_f == ON) ? "ON" : "OFF")
               ) ;
        fprintf( fout,
                 "\tConvert all host ------ %-14s\n",
                 ((mkOpt->allSites_f == ON) ? "ON" : "OFF") 
               ) ;
        fprintf( fout,
                 "\tMake query ------------ %-14s\n",
                 ((mkOpt->makeQuery_f == ON) ? "ON" : "OFF") 
               ) ;

        fprintf(fout,"\n") ;
        return TRUE ;
      }

      T_BOOL   L_MKOPT_CheckValid     ( OUT   FILE           *fout,
                                        IN    t_mkOptions    *mkOpt )
      {
        fprintf(fout,"\tOptions check...\n") ;

        if (
             (mkOpt->webdir == NULL) 
           )
           {
             fprintf(fout,
                     "\tSorry, you forgot tell me a directory to work on.\n") ;
             return FALSE ;
           }

        /* ... Finally, ok ... */
        fprintf(fout,"\tok.\n") ;
        fprintf(fout,"\n") ;
        return TRUE ;
      }


   /* ................................................................... */

