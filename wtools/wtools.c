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

      #include "corelib/l_basic/c_basic.h"
      #include "wtools/l_wtmsg.h"
      #include "wcat/l_wcat.h"
      #include "wdir/l_wdir.h"
      #include "wcopy/l_wcopy.h"
      #include "mklocal/l_mklocal.h"


   /* ... Main .......................................................... */

      int  main ( int argc, char *argv[], char *envp[] )
      {
        T_CHAR  *pch ;


        /* ... getting program name ... */
#if defined(__MSDOS__)
        pch = strrchr(argv[0],'\\') ;
        if (pch != NULL)
            pch ++ ;  /* skip '\\' */
#else
        pch = strrchr(argv[0],'/') ;
        if (pch != NULL)
            pch ++ ;  /* skip '/' */
#endif
        if (pch == NULL)
            pch = argv[0] ;


        /* ... be wcopy ... */
        if ( X_STRING_CaseNEqual(pch,"wcopy",strlen("wcopy"),FALSE) == TRUE)
             return L_WCOPY_main(argc,argv) ;
        if ( X_STRING_CaseNEqual(pch,"wcp",strlen("wcp"),FALSE) == TRUE)
             return L_WCOPY_main(argc,argv) ;

        /* ... be wdir ... */
        if ( X_STRING_CaseNEqual(pch,"wdir",strlen("wdir"),FALSE) == TRUE)
             return L_WDIR_main(argc,argv) ;
        if ( X_STRING_CaseNEqual(pch,"wls",strlen("wls"),FALSE) == TRUE)
             return L_WDIR_main(argc,argv) ;

        /* ... be wcat ... */
        if ( X_STRING_CaseNEqual(pch,"wcat",strlen("wcat"),FALSE) == TRUE)
             return L_WCAT_main(argc,argv) ;
        if ( X_STRING_CaseNEqual(pch,"wtype",strlen("wtype"),FALSE) == TRUE)
             return L_WCAT_main(argc,argv) ;

        /* ... be mklocal ... */
        if ( X_STRING_CaseNEqual(pch,"mklocal",strlen("mklocal"),FALSE) == TRUE)
             return L_MKLOCAL_main(argc,argv) ;


        L_WTMSG_wtools() ;
        return FALSE ; /* TRUE means problems... */
      }


   /* ................................................................... */

