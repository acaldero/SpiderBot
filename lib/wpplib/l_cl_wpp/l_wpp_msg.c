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

      #include "wpplib/l_cl_wpp/l_wpp_msg.h"


   /* ... Functions / Funciones ......................................... */
  

      /* ... presentation ............................................... */
      T_BOOL   L_WPP_MSG_presentation   ( IN   T_CHAR  *wpp_name,
                                          IN   T_CHAR  *wpp_ver ) 
      {
X_PRINT_printf
(
"\n"
"\n"
"\n"
"                                                             %s"
"\n"
"\n"
"\n"
"\n"
"    %s\n",
        wpp_ver, wpp_name
) ;

{
  int i ;

  X_PRINT_printf("   -") ;
  for (i=0; i<strlen(wpp_name); i++)
       X_PRINT_printf("-") ;
  X_PRINT_printf("-") ;
  X_PRINT_printf("\n") ;
}

X_PRINT_printf
(
"\n"
"    Copyright (C) 1997/1999 Alejandro Calderon Mateos\n"
"    %s comes with ABSOLUTELY NO WARRANTY;\n"
"    This is free software, and you are welcome to redistribute\n"
"    it under certain conditions.\n"
"    (See GNU Library General Public License).\n"
"\n",
        wpp_name
) ;

return TRUE ;
      }


      /* ... common command line ........................................ */
      T_BOOL   L_WPP_MSG_common_command_line ( IN   T_CHAR  *wpp_name,
                                               IN   T_CHAR  *wpp_exe_name,
                                               IN   T_INT    i_page,
                                               IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n" 
"                                                                %s\n" 
"                                                                (%i/%i)\n" 
"\n" 
"\n" 
"\n" 
"\n" 
"    Common command line :\n" 
"\n" 
"       $%s -url www.linux.org -maxbytes 1000000\n" 
"\n" 
"           start downloading pages from www.linux.org into current\n" 
"           directory, only 1 Megabyte.\n"
"\n" 
"\n" 
"       $%s -resume resume.www.linux.org\n" 
"\n" 
"           continue download from www.linux.org, because %s\n" 
"           was stoped by user (using Control-C) or any problem occured\n" 
"           while %s was running.\n" 
"\n" 
"\n",

      wpp_name, i_page, n_page, 
      wpp_exe_name, wpp_exe_name,
      wpp_exe_name, wpp_exe_name

) ;

return TRUE ;
      }


      /* ... options .................................................... */
      T_BOOL   L_WPP_MSG_options ( IN   T_CHAR  *wpp_name,
                                   IN   T_INT    i_page,
                                   IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n"
"                                                                %s\n"
"                                                                (%i/%i)\n"
"\n"
"\n"
"\n"
"    Options :\n"
"\n"
"      -url      <web>           Download pages from <web>\n"
"      -resume   <file>          Try recover using <file> file\n"
"      -proxy    <web>           Download throught proxy <web>\n"
"      -ident    <id>       (*)  Use <id> as user:pass\n"
"      -delay    <id>       (*)  Wait <id> seconds between download\n"
"      -maxbytes <number>   (**) Limit download to <number> Bytes\n"
"      -maxurls  <number>   (**) Limit download to <number> Urls\n"
"\n"
"\n"
"\n"
"\n"
"    (*)  -> it is not saved at resume file\n"
"    (**) -> it hide value saved at resume file\n"
"\n",

      wpp_name, i_page, n_page

) ;

return TRUE ;
      }



      /* ... flags ...................................................... */
      T_BOOL   L_WPP_MSG_flags ( IN   T_CHAR  *wpp_name,
                                 IN   T_INT    i_page,
                                 IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n"
"\n"
"                                                                %s\n"
"                                                                (%i/%i)\n"
"\n"
"\n"
"\n"
"    Flags :\n"
"\n"
"      -help          (*) Show this screens\n"
"      -silence       (*) Do not show the download process\n"
"      -skipbin           Only download html files (skip gif, jpg, ...)\n"
"      -samemachine       Download url from same machine, other paths\n"
"      -allmachine        Download url to to others sites\n"
"      -detecthttp        Detect HTTP version (0.9, 1.0, 1.1) and uses it\n"
"      -makequery         Download 'cgi-bin' querys\n"
"      -skipel        (*) Do not get 'exclusion list'\n"
"      -rentry            Ff any problem is found downloading a\n"
"                         file, try get it again\n"
"\n"
"\n"
"    (*)  -> this information is not saved at resume file\n"
"\n",

      wpp_name, i_page, n_page

) ;

return TRUE ;
      }


      /* ... advanced ................................................... */
      T_BOOL   L_WPP_MSG_advanced   ( IN   T_CHAR  *wpp_name,
                                      IN   T_INT    i_page,
                                      IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n"
"                                                                %s\n"
"                                                                (%i/%i)\n"
"\n"
"\n"
"\n"
"    Options :\n"
"\n"
"      -bs         <number>  (*) Try uses <number> bytes for buffering\n"
"      -resumefrec <id>      (*) Save resume each <id> url's download\n"
"      -timelimit  <id>      (*) Wait <id> second for server response.\n"
"      -onlyHttp                 Only download using http protocol\n"
"      -makerelative             Rewrite urls to offline browsing\n"
"      -in1page                  Rewrite urls pointing inside 1\n"
"                                page, as relative offset\n"
"\n"
"\n"
"\n"
"\n"
"\n"
"    (*)  -> this information is not saved at resume file\n"
"\n",

      wpp_name, i_page, n_page

) ;

return TRUE ;
      }



      /* ... thanks ..................................................... */
      T_BOOL   L_WPP_MSG_thanks_1   ( IN   T_CHAR  *wpp_name,
                                      IN   T_INT    i_page,
                                      IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n"
"\n"
"                                                                %s\n"
"                                                                (%i/%i)\n"
"\n"
"\n"
"               x                                             \n"
"             x           x     x   x  x   x  xxx             \n"
"         x x            x  x   xx  x  x  x  x                \n"
"       x    x     x  x  x  x   x x x  x x    x x             \n" 
"            x     x  x  xxxxx  x  xx  xx        x       x x  \n"
"             x    xxxx  x   x  x   x  x x    x   x         x \n"
"             x    x  x  x   x  x   x  x   x   xxx         x  \n"
"             x    x  x  x                                x   \n"
"             x    x                                     x    \n"
"             x                      x x x x x x x x x x      \n"
"                                                             \n"
"                                                             \n"
"    Thanks to all people that help me in many things...\n"
"    ... people of D.A.T.S.I department, at Facultad de Informatica (U.P.M)\n"
"    ... Juan Jose Amor, Vicente Luque, Guillermo Bautista, Antonio Diaz,...\n"
"    ... and my parents too, too much ;->.\n"
"\n",

      wpp_name, i_page, n_page

) ;

return TRUE ;
      }

      T_BOOL   L_WPP_MSG_thanks_2   ( IN   T_CHAR  *wpp_name,
                                      IN   T_INT    i_page,
                                      IN   T_INT    n_page )
      {
X_PRINT_printf
(
"\n"
"\n"
"                                                                %s\n"
"                                                                (%i/%i)\n"
"\n"
"            x x x x x        xx    x   x  x  x   xxx                     \n"
"                x     x  x  x  x   xx  x  x x   x                        \n"
"                x     xxxx  xxxx   x x x  xx     xxx                     \n" 
"                x     x  x  x  x   x  xx  x x       x                    \n"
"                x     x  x  x  x   x   x  x  x   xxx                     \n"
"                                                                         \n"
"                                                                         \n"
"                                                                         \n"
"   datsi.fi.upm.es                                                       \n"
"   Juan Jose Amor                                                        \n"
"   Vicente Luque                                                         \n"
"   Guillermo Bautista                                                    \n"
"   Antonio Diaz                                                          \n"
"                                                                         \n"
"                                                                         \n"
"                                                                         \n"
"                                 ... and my parents too, too much ;->    \n"
"\n",

      wpp_name, i_page, n_page

) ;

return TRUE ;
      }


   /* ................................................................... */


