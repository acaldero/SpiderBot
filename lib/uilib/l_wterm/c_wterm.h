

 #ifndef C_WTERM_H
 #define C_WTERM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"


   /* ... Functions / Funciones ......................................... */

      T_CHAR *simple_frame1 ( void ) ;
      T_CHAR *simple_frame2 ( void ) ;


   /* ... Const / Constantes ............................................ */
  
      /* ... Default frames --- Marcos predefinidos ... */
      #if defined(__MSDOS__)
         #define c_SINGLE_FRAME  "ÚÄ¿³³ÀÄÙ"
         #define c_DOUBLE_FRAME  "ÉÍ»ººÈÍ¼"
         #define c_SIMPLE_FRAME  "........" 
         #if defined(__COOL__)
            #define c_SIMPLE_FRAME1  "ÉÍ¿º³ÀÄÙ"
            #define c_SIMPLE_FRAME2  "ÚÄ·³ºÀÍ¼"
         #else
            #define c_SIMPLE_FRAME1  "|~||||_|"
            #define c_SIMPLE_FRAME2  "|\"||||_|"
         #endif
      #endif
      #if (defined(__LINUX__) || defined(__SUNOS__))
         #define c_SINGLE_FRAME  "........" 
         #define c_DOUBLE_FRAME  "::::::::"
         #define c_SIMPLE_FRAME  "........" 
         #if defined(__COOL__)
            #define c_SIMPLE_FRAME1  simple_frame1()
            #define c_SIMPLE_FRAME2  simple_frame2()
         #else
            #define c_SIMPLE_FRAME1  "|~||||_|"
            #define c_SIMPLE_FRAME2  "|\"||||_|"
         #endif
      #endif
      /*
  	      ÚÄ¿     ÉÍ»      ...    |""|
  	      ³ ³     º º      . .    |  |
  	      ÀÄÙ     ÈÍ¼      ...    |__|
  	     single  double  simple1 simple2
       */
  
      /* ... Window dup mode --- Modo de duplicar una ventana ... */
      /* comparten pantalla */ #define c_SHARE   701
      /* son independientes */ #define c_FULL    702
  
      /* ... Cursor states --- Def Cursor ctes ... */
      #define c_ON_CURSOR    -1
      #define c_OFF_CURSOR    0
  
      /* ... Title modes available --- Modos de titulo ... */
      #define c_NO_TITLE             0
      #define c_LEFTUP_TITLE       801
      #define c_RIGHTUP_TITLE      802
      #define c_CENTERUP_TITLE     803
      #define c_LEFTDOWN_TITLE     804
      #define c_RIGHTDOWN_TITLE    805
      #define c_CENTERDOWN_TITLE   806
  
      /* ... Keep styles --- Def Keep str ... */
      #if defined(__MSDOS__)
        #define c_SIMPLE_KEEP      "±v²"
      #endif
      #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
        #define c_SIMPLE_KEEP      "A|V#"
      #endif
  
 /* ..................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

