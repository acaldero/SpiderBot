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

      #include "mklocal/l_mkmsg.h"


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL   L_MKMSG_how_use    ( IN   T_CHAR  *wpp_name,
                                    IN   T_INT    i_page,
                                    IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n"
"\n"
"                                                               %s\n"
"                                                               (%i/%i)\n"
"\n"
"\n"
"    makelocal will ajust links :\n"
"\n"
"      from '/icon/me.gif' to './site.com/icon/me.gif'\n"
"\n"
"\n"
"\n"
"    Options and Flags :\n"
"\n"
"      -help                 show this screens\n"
"      -silence              do not show the work process\n"
"      -skipbin              only scan html files (skip gif, jpg, ...)\n"
"      -allsites             rewrite urls from others sites\n"
"      -makequery            rewrite cgi' querys as saved response\n"
"      -dir     <choice>     mirror is at <choice>\n"
"\n"
"\n",

	wpp_name, i_page, n_page

) ;
        return TRUE ;
      }

  
      T_BOOL   L_MKMSG_help        ( OUT   t_mkOptions   *mkOpt )
      {

        L_MKMSG_how_use(c_MKLOCAL_VERSION,1,2) ;
        X_PRINT_printf("    Press ENTER to continue...\n") ;
        fgetc(stdin) ;

        L_WPP_MSG_thanks_1(c_MKLOCAL_VERSION,2,2) ;
        return TRUE ;
      }


   /* ................................................................... */

