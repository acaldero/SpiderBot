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

      #include "uilib/l_wterm/v_drv/i_conio.h"


   /* ... Funtions / Funciones .......................................... */


#if defined(__MSDOS__)

    /* --- Text en x_conio --- */
    void I_CONIO_cgotoxy    ( T_INT x, T_INT y ) 
    {
      gotoxy(x,y) ;
    }

    void I_CONIO_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) 
    {
      (*x) = wherex() ;
      (*y) = wherey() ;
    }

    void I_CONIO_clrscr     ( void ) 
    {
      clrscr() ;
    }

    void I_CONIO_cursor_off ( void )
    {
      #if defined(__BCC__)
          _setcursortype(_NOCURSOR) ;
      #endif
    }

    void I_CONIO_cursor_on  ( void ) 
    {
      #if defined(__BCC__)
          _setcursortype(_NORMALCURSOR) ;
      #endif
    }

    void I_CONIO_set_cursor ( T_INT lini, T_INT lfin )
    {
    }

    T_BOOL I_CONIO_Begin ( void )
    {
      textmode(C80) ;
      return TRUE ;
    }

    void   I_CONIO_End ( void )
    {
    }

    void   I_CONIO_set_modo_video ( T_INT modo_video )
    {
    }

    void I_CONIO_AutoDetect ( INOUT T_INT *currmode,
    			      INOUT T_INT *cfilas,
    			      INOUT T_INT *ccolumnas,
    			      INOUT T_INT *ncolores )
    {
      struct text_info ti ;

      gettextinfo(&ti);
      (*currmode)  = ti.currmode ;
      (*cfilas)    = ti.screenheight ;
      (*ccolumnas) = ti.screenwidth ;
      (*ncolores)  = ( (ti.currmode == BW40) ||
                       (ti.currmode == BW80) ||
                       (ti.currmode == MONO) ) ? 2 : 16 ;
    }

    T_BOOL I_CONIO_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                          T_INT width, T_INT tall,
                          T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 ) 
    {
      register T_INT i, j ;
      T_CHAR *pscr ;

      if ( (rx2>width) || (ry2>tall) )
         {
           L_DEBUG_MSG_Write(WARNING,FALSE,
                         "incoherencia entre coordenadas-taman~o terminal") ;
           return FALSE ;
         }
      pscr=(ncolores==2) ? (T_CHAR *)(0xB0000000L) : (T_CHAR *)(0xB8000000L) ;
      for (j=ry1-1; j<ry2; j++)
      {
        for (i=rx1-1; i<rx2; i++)
        {
          *(pscr+i*2+j*width*2)=(*(scr+i+j*width)) ;
          *(pscr+i*2+j*width*2+1)=*(attr+i+j*width) ;
        }
      }
      return TRUE ;
    }

#endif


#if (! defined(__MSDOS__))

    /* --- Text en x_conio --- */
    void I_CONIO_cgotoxy    ( T_INT x, T_INT y ) 
    {
    }

    void I_CONIO_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) 
    {
    }

    void I_CONIO_clrscr     ( void ) 
    {
    }

    void I_CONIO_cursor_off ( void )
    {
    }

    void I_CONIO_cursor_on  ( void ) 
    {
    }

    void I_CONIO_set_cursor ( T_INT lini, T_INT lfin ) 
    {
    }

    T_BOOL I_CONIO_Begin ( void )
    {
      return FALSE ;
    }

    void   I_CONIO_End ( void )
    {
    }

    void   I_CONIO_set_modo_video ( T_INT modo_video )
    {
    }

    void I_CONIO_AutoDetect ( INOUT T_INT *currmode,
    			      INOUT T_INT *cfilas,
    			      INOUT T_INT *ccolumnas,
    			      INOUT T_INT *ncolores )
    {
      (*currmode)  = 0  ;
      (*cfilas)    = 25 ;
      (*ccolumnas) = 80 ;
      (*ncolores)  = 2  ;
    }

    T_BOOL I_CONIO_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                          T_INT width, T_INT tall,
                          T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 ) 
    {
      return FALSE ;
    }

#endif


  /* .................................................................... */


