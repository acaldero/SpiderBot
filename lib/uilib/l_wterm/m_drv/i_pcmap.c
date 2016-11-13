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

      #include "uilib/l_wterm/m_drv/i_pcmap.h"


   /* ... funciones ........................................................ */
  
      T_INT I_PCMAP_getkey ( void )
      {
        T_CHAR ch ;
  
        ch=V_TERM_getch() ;
        switch(ch)
        {
          case 0          :
               ch=V_TERM_getch() ;
               switch(ch)
               {
                 case c_UP_PC    : return c_UP ;
                 case c_DOWN_PC  : return c_DOWN ;
                 case c_RIGHT_PC : return c_RIGHT ;
                 case c_LEFT_PC  : return c_LEFT ;
                 case c_AVPAG_PC : return c_AVPAG ;
                 case c_REPAG_PC : return c_REPAG ;
                 case c_F2_PC    : return c_F2 ;
                 case c_F3_PC    : return c_F3 ;
                 case c_BEGIN_PC : return c_BEGIN ;
                 case c_END_PC   : return c_END ;
                 default : return (T_INT) ch ;
               }
          case c_ENTER_PC : return c_ENTER ;
          default :         return (T_INT) ch ;
        }
      }


 /* ..................................................................... */

