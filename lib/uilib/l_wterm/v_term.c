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

      #include "uilib/l_wterm/v_term.h"
      /* ... video drivers ... */
      #include "uilib/l_wterm/v_drv/i_esc.c"
      #include "uilib/l_wterm/v_drv/i_conio.c"
      #include "uilib/l_wterm/v_drv/i_int86.c"
      #include "uilib/l_wterm/v_drv/i_curses.c"
      #include "uilib/l_wterm/v_drv/i_bcgtxt.c"
      #include "uilib/l_wterm/v_drv/i_zgtxt.c"
      /* ... keyboard drivers ... */
      #include "uilib/l_wterm/k_drv/i_ioctl.c"
      #include "uilib/l_wterm/k_drv/i_kurses.c"
      #include "uilib/l_wterm/k_drv/i_konio.c"


   /* ... Variables globales ........................................... */

      T_BOOL       Init_v_term = FALSE ;
      t_TermState  VS ;
      T_CHAR      *gObuff      = NULL ;
      T_LONG       gObuffsize  = 0 ;


   /* ... Funciones ..................................................... */

    T_BOOL V_TERM_AutoDetect ( void )
    {
      t_TermState vd ;
      t_TermState DefVD=_DEFAULT_MONITOR_ ;

      X_ALLOC_MemMove(&vd,&DefVD,sizeof(t_TermState)) ;
      switch (VS.GestorVideo)
      {
        case c_CONIO      :
             I_CONIO_AutoDetect(&(vd.currmode),&(vd.cfilas),
                                &(vd.ccolumnas),&(vd.ncolores)) ;
	     break ;
	case c_BC_INT10  :
             I_INT86_AutoDetect(&(vd.currmode),&(vd.cfilas),
                                &(vd.ccolumnas),&(vd.ncolores)) ;
	     break ;
        case c_BC_GTEXT   :
             I_BCGTXT_AutoDetect(&(vd.currmode),&(vd.cfilas),
                                 &(vd.ccolumnas),&(vd.rvertical),
                                 &(vd.rhorizontal),&(vd.charheight),
                                 &(vd.charwidth),&(vd.ncolores)) ;
             break ;
	case c_ESC_CMD :
             I_ESC_AutoDetect(&(vd.currmode),&(vd.cfilas),
                                 &(vd.ccolumnas),&(vd.rvertical),
                                 &(vd.rhorizontal),&(vd.charheight),
                                 &(vd.charwidth),&(vd.ncolores)) ;
	     break ;
        case c_xCURSES :
             I_CURSES_AutoDetect(&(vd.currmode),&(vd.cfilas),
                                 &(vd.ccolumnas),&(vd.ncolores)) ;
             break ;
	case c_ZGTXT   :
             I_ZGTXT_AutoDetect(&(vd.currmode),&(vd.cfilas),
                                 &(vd.ccolumnas),&(vd.rvertical),
                                 &(vd.rhorizontal),&(vd.charheight),
                                 &(vd.charwidth),&(vd.ncolores)) ;
	     break ;
	default :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return FALSE ;
      }
      VS.ccolumnas   = vd.ccolumnas ;
      VS.currmode    = vd.currmode ;
      VS.ncolores    = vd.ncolores ;
      VS.cfilas      = vd.cfilas ;
      VS.rvertical   = vd.rvertical ;
      VS.rhorizontal = vd.rhorizontal ;
      VS.charheight  = vd.charheight ;
      VS.charwidth   = vd.charwidth ;
      return TRUE ;
    }

    t_TermState *V_TERM_get_profile ( void )
    {
      if (!Init_v_term)
	 {
           int  ret ;

           ret = V_TERM_Configur(__MVIDEO__) ;
           if (ret < 0)
               return NULL ;
           ret = V_TERM_Configur(__MTECLADO__) ;
           if (ret < 0)
               return NULL ;
           Init_v_term=TRUE ;
	 }
      V_TERM_AutoDetect() ;
      return &VS ;
    }

    void V_TERM_CloseVideo ( T_INT cfg )
    {
      switch (cfg)
      {
        case c_CONIO      :
             I_CONIO_End() ;
             break ;
	case c_BC_INT10   :
             I_INT86_End() ;
             break ;
        case c_BC_GTEXT    :
             I_BCGTXT_End() ;
             break ;
        case c_ESC_CMD :
             I_ESC_End() ;
             break ;
        case c_xCURSES    :
             I_CURSES_End() ;
             break ;
        case c_ZGTXT      :
             I_ZGTXT_End() ;
             break ;
	default : ;
      }
    }

    T_INT V_TERM_OpenVideo ( T_INT cfg )
    {
      switch (cfg)
      {
        case c_CONIO      :
             if (I_CONIO_Begin()==FALSE)
                 return VS.GestorVideo ;
             break ;
	case c_BC_INT10   :
             if (I_INT86_Begin()==FALSE)
                 return VS.GestorVideo ;
             break ;
        case c_BC_GTEXT    :
             if (I_BCGTXT_Begin(&(VS.currmode))==FALSE)
                 return VS.GestorVideo ;
             break ;
        case c_ESC_CMD :
             if (I_ESC_Begin()==FALSE)
                 return VS.GestorVideo ;
             break ;
        case c_xCURSES    :
             if (I_CURSES_Begin()==FALSE)
                 return VS.GestorVideo ;
             break ;
        case c_ZGTXT      :
             if (I_ZGTXT_Begin(&(VS.currmode))==FALSE)
                 return VS.GestorVideo ;
             break ;
	default :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return -1 ;
      }
      return cfg ;
    }

    T_INT V_TERM_Configur ( T_INT newcfg )
    {
      T_INT old ;

      /* ... Teclado ? ... */
      if (VS.GestorTeclado==newcfg)
          return newcfg ;
      switch (newcfg)
      {
	case c_PCKB     :
	case c_VTKB  :
        case c_CURSESKB :
             old=VS.GestorTeclado ;
             VS.GestorTeclado=newcfg ;
             return old ;
      }

      /* ... Video ? ... */
      if (VS.GestorVideo==newcfg)
          return newcfg ;
      V_TERM_CloseVideo(VS.GestorVideo) ;
      old = V_TERM_OpenVideo(newcfg) ;
      if (old==VS.GestorVideo)
         {
           V_TERM_OpenVideo(VS.GestorVideo) ;
           return VS.GestorVideo ;
         }
      if (old==-1)
          return -1 ;
      old = VS.GestorVideo ;
      VS.GestorVideo = newcfg ;
      return old ;
    }


    /* Gestion del Buffer I/O ... *
     * -------------------------- */
    T_LONG  V_TERM_GetSizeObuff ( void )
    {
      return gObuffsize ;
    }

    void  V_TERM_FreeObuff ( void )
    {
      X_ALLOC_Free((void **)&gObuff) ;
      gObuff=(T_CHAR *)NULL ;
      gObuffsize=0 ;
    }

    T_CHAR *V_TERM_MallocObuff ( T_INT size )
    {
      T_CHAR *aux ;

      aux=(T_CHAR *)X_ALLOC_Realloc(gObuff,size) ;
      NULL_RET_NULL(aux) ;
      gObuffsize=size ; 
      gObuff=aux ;
      return aux ;
    }


    /* Funciones Video ... *
     * ------------------- */
    void V_TERM_cgotoxy ( T_INT x, T_INT y )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO      :
             I_CONIO_cgotoxy(x,y) ;
	     break ;
	case c_BC_INT10  :
             I_INT86_cgotoxy(x,y) ;
	     break ;
        case c_BC_GTEXT   :
             x=x * VS.charwidth  ;
             y=y * VS.charheight ;
             I_BCGTXT_cgotoxy(x,y) ;
             break ;
	case c_ESC_CMD    :
             I_ESC_cgotoxy(x,y) ;
	     break ;
        case c_xCURSES  :
             I_CURSES_cgotoxy(x,y) ;
             break ;
	case c_ZGTXT    :
	     break ;
        default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
      }
    }

    void V_TERM_cwherexy ( T_INT *x, T_INT *y )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO      :
             I_CONIO_cwherexy(x,y) ;
	     break ;
	case c_BC_INT10  :
             I_INT86_cwherexy(x,y) ;
	     break ;
        case c_BC_GTEXT   :
             I_BCGTXT_cwherexy(x,y) ;
             (*x)=(*x) / VS.charwidth  ;
             (*y)=(*y) / VS.charheight ;
             break ;
	case c_ESC_CMD    :
             I_ESC_cwherexy(x,y) ;
	     break ;
        case c_xCURSES  :
             I_CURSES_cwherexy(x,y) ;
             break ;
	case c_ZGTXT    :
	     break ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
      }
    }

    void V_TERM_clrscr ( void )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO   :
             I_CONIO_clrscr() ;
	     break ;
	case c_BC_INT10  :
             I_INT86_clrscr(VS.ccolumnas,VS.cfilas) ;
	     break ;
        case c_BC_GTEXT   :
             I_BCGTXT_clrscr() ;
             break ;
	case c_ESC_CMD  :
             I_ESC_clrscr() ;
	     break ;
        case c_xCURSES  :
             I_CURSES_clrscr() ;
             break ;
	case c_ZGTXT    :
             I_ZGTXT_clrscr() ;
	     break ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
      }
    }

    T_BOOL V_TERM_cdump ( T_CHAR *scr, T_CHAR *attr,
                        T_INT width, T_INT tall,
                        T_INT ax1, T_INT ay1, T_INT ax2, T_INT ay2 )
    {
      if ( (!tall) || (!width) )
	   return TRUE ;
      switch (VS.GestorVideo)
      {
        case c_CONIO      :
             return I_CONIO_cdump(scr,attr,VS.ncolores,width,tall,
                                   ax1,ay1,ax2,ay2) ;
	case c_BC_INT10  :
             return I_INT86_cdump(scr,attr,VS.ncolores,width,tall,
                                   ax1,ay1,ax2,ay2) ;
        case c_BC_GTEXT   :
             return I_BCGTXT_cdump(scr,attr,VS.ncolores,width,tall,
                              VS.charwidth,VS.charheight,ax1,ay1,ax2,ay2) ;
	case c_ESC_CMD    :
             return I_ESC_cdump(scr,attr,VS.ncolores,width,tall,
                                     ax1,ay1,ax2,ay2) ;
        case c_xCURSES :
             return I_CURSES_cdump(scr,attr,VS.ncolores,width,tall,
                                  1,1,VS.ccolumnas,VS.cfilas) ;
                                  /*ax1,ay1,ax2,ay2) ;*/
	case c_ZGTXT    :
             return FALSE ;
	default :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return FALSE ;
      }
    }

    T_INT V_TERM_cmaxX ( void )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO      :
	case c_BC_INT10   :
        case c_BC_GTEXT   :
        case c_ESC_CMD    :
        case c_xCURSES    :
	case c_ZGTXT      :
             return VS.ccolumnas ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return -1 ;
      }
    }

    T_INT V_TERM_cmaxY ( void )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO      :
	case c_BC_INT10   :
        case c_BC_GTEXT    :
        case c_ESC_CMD :
        case c_xCURSES    :
	case c_ZGTXT    :
             return VS.cfilas ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return -1 ;
      }
    }

    T_BOOL V_TERM_cursor_off ( void )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO   :
             I_CONIO_cursor_off() ;
	     break ;
	case c_BC_INT10 :
             I_INT86_cursor_off() ;
	     break ;
        case c_BC_GTEXT   :
             I_BCGTXT_cursor_off() ;
             break ;
	case c_ESC_CMD :
             I_ESC_cursor_off() ;
	     break ;
        case c_xCURSES :
             I_CURSES_cursor_off() ;
             break ;
	case c_ZGTXT    :
	     break ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return FALSE ;
      }
      return TRUE ;
    }

    T_BOOL V_TERM_cursor_on ( void )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO   :
             I_CONIO_cursor_on() ;
	     break ;
	case c_BC_INT10 :
             I_INT86_cursor_on() ;
	     break ;
        case c_BC_GTEXT   :
             I_BCGTXT_cursor_on() ;
             break ;
	case c_ESC_CMD :
             I_ESC_cursor_on() ;
	     break ;
        case c_xCURSES :
             I_CURSES_cursor_on() ;
             break ;
	case c_ZGTXT    :
	     break ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return FALSE ;
      }
      return TRUE ;
    }

    T_BOOL V_TERM_set_cursor ( T_INT lini, T_INT lfin )
    {
      switch (VS.GestorVideo)
      {
        case c_CONIO   :
             I_CONIO_set_cursor(lini,lfin) ;
	     break ;
	case c_BC_INT10 :
             I_INT86_set_cursor(lini,lfin) ;
	     break ;
        case c_BC_GTEXT   :
             I_BCGTXT_set_cursor(lini,lfin) ;
             break ;
	case c_ESC_CMD :
             I_ESC_set_cursor(lini,lfin) ;
	     break ;
        case c_xCURSES :
             I_CURSES_set_cursor(lini,lfin) ;
             break ;
	case c_ZGTXT    :
	     break ;
	default      :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_VIDEO) ;
             return FALSE ;
      }
      return TRUE ;
    }


    /* Funciones Teclado ... *
     * --------------------- */
    T_CHAR V_TERM_getch ( void )
    {
      switch (VS.GestorTeclado)
      {
	case c_PCKB    :
             return I_CONIO_getch() ;
	case c_VTKB :
             return I_IOCTL_getch() ;
        case c_CURSESKB :
             return I_CURSES_getch() ;
	default :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_KEYB) ;
             return 0 ;
      }
    }

    T_BOOL V_TERM_nbgetch ( INOUT T_CHAR *ch )
    {
      switch (VS.GestorTeclado)
      {
	case c_PCKB    :
             return I_CONIO_nbgetch(ch) ;
	case c_VTKB :
             return I_IOCTL_nbgetch(ch) ;
        case c_CURSESKB :
             return I_CURSES_nbgetch(ch) ;
	default :
             L_DEBUG_MSG_Write(ERROR,FALSE,VTERM_UNKNOW_KEYB) ;
             return FALSE ;
      }
    }
    
    T_BOOL V_TERM_kbhit ( void )
    {
      T_BOOL ok = FALSE ;
      T_CHAR trash ;
      
      ok=V_TERM_nbgetch(&trash) ;
      if (ok==TRUE)
          ungetc(trash,stdin) ;
      return ok ;
    }


 /* ..................................................................... */

