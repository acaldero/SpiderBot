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

      #include "uilib/l_wterm/v_keymap.h"
      /* ... mapping drivers ... */
      #include "uilib/l_wterm/m_drv/i_pcmap.c"
      #include "uilib/l_wterm/m_drv/i_escmap.c"
      #include "uilib/l_wterm/m_drv/i_curmap.c"


   /* ... variables globales ............................................... */

      T_INT kmaptype=__KEYMAPPING__ ;


   /* ... funciones ........................................................ */

    T_INT V_KEYMAP_Configur ( T_INT newkm )
    {
      T_INT old ;

      switch (newkm)
      {
        case c_PC     :
        case c_ESCAPE :
        case c_CURSES :
                  old=kmaptype ;
                  kmaptype=newkm ;
                  break ;
        default : old= -1 ;
      }
      return old ;
    }

    T_INT V_KEYMAP_getkey ( void )
    {
      switch (kmaptype)
      {
        case c_PC    :
             return I_PCMAP_getkey() ;
        case c_ESCAPE :
             return I_ESCMAP_getkey() ;
        case c_CURSES :
             return I_CURMAP_getkey() ;
        default :
             L_DEBUG_MSG_Write(ERROR,FALSE,VKEYMAP_BAD_KEY) ;
      }
      return c_NINGUNA ;
    }


 /* ..................................................................... */

