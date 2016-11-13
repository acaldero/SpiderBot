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

      #include "SpiderBot/l_sbotmsg.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_SBOTMSG_listOptions ( void )
      {
        /* page 1 */
        X_PRINT_printf
        (
"\n"
"                                                             %s\n"
"\n"
"\n"
"    Options :\n"
"\n"
"      -url <web>          download pages from <web>\n"
"      -resume <file>      try recover using <file> file\n"
"      -maxbytes <number>  limit download to <number> Bytes\n"
"                          (it hide value saved at resume file)\n"
"      -proxy <web>        download throught proxy <web>\n"
"      -ident <id>         read from file <id> <user>:<pass>\n"
"                          (it is not saved at resume file)\n"
"\n"
"    Flags :\n"
"\n"
"      -help            show this screens\n"
"      -samemachine     download web referenced from same machine\n"
"      -makequery       download 'cgi-bin' querys\n"
"      -rentry          if any problem is found downloading a file,\n"
"                       try get it again\n"
"\n", c_SPIDERBOT_VER
        ) ;

        return TRUE ;
      }


   /* ................................................................... */

