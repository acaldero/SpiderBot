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

      #include "uilib/l_wterm/k_drv/i_konio.h"


   /* ... Funtions / Funciones .......................................... */


#if defined(__MSDOS__)

    /* --- Keybd en x_conio --- */
    T_CHAR I_CONIO_getch   ( void ) 
    {
      return getch() ;
    }

    T_BOOL I_CONIO_nbgetch ( INOUT T_CHAR *ch )
    {
      if (kbhit())
         {
           (*ch)=getch() ;
            return TRUE ;
         }
      return FALSE ;
    }

#endif


#if (! defined(__MSDOS__))

    /* --- Keybd en x_conio --- */
    T_CHAR I_CONIO_getch   ( void ) 
    {
      return (0) ;
    }

    T_BOOL I_CONIO_nbgetch ( INOUT T_CHAR *ch )
    {
      (*ch) = '\0' ;
      return FALSE ;
    }

#endif


  /* .................................................................... */


