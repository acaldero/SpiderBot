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



   /* ... Inclusiones .................................................... */

      #include "uilib/l_wterm/m_drv/i_escmap.h"


   /* ... funciones ........................................................ */
  
      T_INT I_ESCMAP_getkey ( void )
      {
#if defined(__MSDOS__)
        return 0 ;
#endif
#if ( defined(__LINUX__) || defined(__SUNOS__) || (__AIX__))
         T_CHAR ch ;

         ch=V_TERM_getch() ;
         switch(ch)
         {
           case c_ESC :
                if (V_TERM_nbgetch(&ch)==FALSE)
                    return c_ESC ;
                if (ch!='[')   return (T_INT) ch ;
                ch=V_TERM_getch() ;
                switch(ch)
                {
                  case c_UP_ESC    : return c_UP ;
                  case c_DOWN_ESC  : return c_DOWN ;
                  case c_RIGHT_ESC : return c_RIGHT ;
                  case c_LEFT_ESC  : return c_LEFT ;
                  case '[' : ch=V_TERM_getch() ;
                             switch(ch)
                             {
                               case c_F2_ESC    : return c_F2 ;
                               case c_F3_ESC    : return c_F3 ;
                             }
                  case c_AVPAG_ESC : V_TERM_nbgetch(&ch) ;
                                       return c_AVPAG ;
                  case c_REPAG_ESC : V_TERM_nbgetch(&ch) ;
                                       return c_REPAG ;
                  case c_BEGIN_ESC : V_TERM_nbgetch(&ch) ;
                                       return c_BEGIN ;
                  case c_END_ESC   : V_TERM_nbgetch(&ch) ;
                                       return c_END ;
                  default :  return (T_INT) ch ;
                }
           case c_ENTER_ESC : return c_ENTER ;
           case c_DEL_ESC   : return c_DEL ;
           default :          return (T_INT) ch ;
         }
#endif
      }


 /* ..................................................................... */

