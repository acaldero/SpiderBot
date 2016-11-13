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

      #include "uilib/l_wterm/v_drv/i_int86.h"


   /* ... Funtions / Funciones .......................................... */

#if ( defined(__MSDOS__) && !defined(_DOS_ASM_) )

    T_BOOL I_INT86_Begin ( void )
    {
      textmode(C80) ;
      return TRUE ;
    }

    void   I_INT86_End ( void )
    {
    }

    void I_INT86_set_modo_video ( T_INT modo_video )
    {
      struct REGPACK r ;

      r.r_ax=(0x00FF & modo_video) ;
      intr(0x10,&r) ;
    }

    void I_INT86_cgotoxy ( T_INT x, T_INT y )
    {
      union REGS regs ;

      y-- ; /*   Para la T_INT 10h, la esquina */
      x-- ; /* left-up es 0,0 ! */
      regs.h.ah=0x02 ;
      regs.h.bh=0x0 ;
      regs.h.dh=y ;
      regs.h.dl=x ;
      int86(0x10,&regs,&regs) ;
    }

    void I_INT86_cwherexy ( T_INT *x, T_INT *y )
    {
      union REGS regs ;

      regs.h.ah=0x3 ;
      regs.h.bh=0 ;
      int86(0x10,&regs,&regs) ;
      *y=regs.h.dh ;
      *x=regs.h.dl ;
    }

    void   I_INT86_clrscr    ( T_INT x, T_INT y )
    {
      X_ALLOC_MemSet((void *)0xB8000000L,0,2*x*y) ;
    }


    T_BOOL I_INT86_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
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

    void I_INT86_cursor_off ( void )
    {
      struct REGPACK r ;

      r.r_ax=0x0100 ;
      r.r_cx=0x0000 ;
      intr(0x10,&r) ;
    }

    void I_INT86_cursor_on ( void )
    {
      struct REGPACK r ;

      r.r_ax=0x0100 ;
      r.r_cx=0x0809 ;
      intr(0x10,&r) ;
    }

    void I_INT86_set_cursor ( T_INT lini, T_INT lfin )
    {
      union REGS r ;

      r.h.ch=lini ;
      r.h.cl=lfin ;
      r.h.ah=0x01 ;
      int86(0x10,&r,&r) ;
    }

    void I_INT86_AutoDetect ( INOUT T_INT *currmode,  INOUT T_INT *cfilas,
    			      INOUT T_INT *ccolumnas, INOUT T_INT *ncolores )
    {
      struct REGPACK r ;
      T_CHAR *mono_id=(T_CHAR *)0x00410 ;
      T_CHAR buffinfo[64] ;

      r.r_ax = 0x0F00 ;
      intr(0x10,&r) ;
      (*ccolumnas) = r.r_ax >> 8 ;
      (*currmode)  = r.r_ax & 0x00FF ;
      (*ncolores)  = ( (*mono_id & 0x30) == 0x30 ) ? 2 : 16 ;
         /* (*pagina) = r.r_bx & 0x00FF ; */
      (*cfilas) = 25 ;
      r.r_ax = 0x1B00 ;
      r.r_bx = 0x0000 ;
      r.r_es = FP_SEG(buffinfo) ;
      r.r_di = FP_OFF(buffinfo) ;
      intr(0x10,&r) ;
      if (r.r_ax==0x1B00)
         { /* funcion soportada, datos en buff ... */
           (*cfilas) = buffinfo[0x22] ;
         }
    }

#endif


#if ( defined(__MSDOS__) && defined(_DOS_ASM_) )

    T_BOOL I_INT86_Begin ( void )
    {
      asm {
            mov ax, 0x10 ;
            int 0x10 ;
	  }
    }

    void   I_INT86_End ( void )
    {
    }

    void I_INT86_set_modo_video ( T_INT modo_video )
    {
      asm {
  	    mov ax, modo_video ;
            int 0x10 ;
	  }
    }

    void I_INT86_cgotoxy ( T_INT x, T_INT y )
    {
      union REGS regs ;

      y-- ; /*   Para la T_INT 10h, la esquina */
      x-- ; /* left-up es 0,0 ! */
      regs.h.ah=0x02 ;
      regs.h.bh=0x0 ;
      regs.h.dh=y ;
      regs.h.dl=x ;
      int86(0x10,&regs,&regs) ;
    }

    void I_INT86_cwherexy ( T_INT *x, T_INT *y )
    {
      union REGS regs ;

      regs.h.ah=0x3 ;
      regs.h.bh=0 ;
      int86(0x10,&regs,&regs) ;
      *y=regs.h.dh ;
      *x=regs.h.dl ;
    }

    void   I_INT86_clrscr    ( T_INT x, T_INT y )
    {
      X_ALLOC_MemSet((void *)0xB8000000L,0,2*x*y) ;
    }


    T_BOOL I_INT86_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
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

    void I_INT86_cursor_off ( void )
    {
      asm {
            mov ax, 0x0100 ;
            mov cx, 0x0000 ;
            int 0x10 ;
	  }
    }

    void I_INT86_cursor_on ( void )
    {
      asm {
            mov ax, 0x0100 ;
            mov cx, 0x0809 ;
            int 0x10 ;
	  }
    }

    void I_INT86_set_cursor ( T_INT lini, T_INT lfin )
    {
      union REGS r ;

      r.h.ch=lini ;
      r.h.cl=lfin ;
      r.h.ah=0x01 ;
      int86(0x10,&r,&r) ;
    }

    void I_INT86_AutoDetect ( INOUT T_INT *currmode,  INOUT T_INT *cfilas,
    			      INOUT T_INT *ccolumnas, INOUT T_INT *ncolores )
    {
      struct REGPACK r ;
      T_CHAR *mono_id=(T_CHAR *)0x00410 ;
      T_CHAR buffinfo[64] ;

      r.r_ax = 0x0F00 ;
      intr(0x10,&r) ;
      (*ccolumnas) = r.r_ax >> 8 ;
      (*currmode)  = r.r_ax & 0x00FF ;
      (*ncolores)  = ( (*mono_id & 0x30) == 0x30 ) ? 2 : 16 ;
         /* (*pagina) = r.r_bx & 0x00FF ; */
      (*cfilas) = 25 ;
      r.r_ax = 0x1B00 ;
      r.r_bx = 0x0000 ;
      r.r_es = FP_SEG(buffinfo) ;
      r.r_di = FP_OFF(buffinfo) ;
      intr(0x10,&r) ;
      if (r.r_ax==0x1B00)
         { /* funcion soportada, datos en buff ... */
           (*cfilas) = buffinfo[0x22] ;
         }
    }

#endif


#if (! defined(__MSDOS__))

    T_BOOL I_INT86_Begin ( void )
    {
      return FALSE ;
    }

    void   I_INT86_End ( void )
    {
    }

    void I_INT86_set_modo_video ( T_INT modo_video )
    {
    }

    void I_INT86_cgotoxy ( T_INT x, T_INT y )
    {
    }

    void I_INT86_cwherexy ( T_INT *x, T_INT *y )
    {
    }

    void   I_INT86_clrscr    ( T_INT x, T_INT y )
    {
    }


    T_BOOL I_INT86_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                          T_INT width, T_INT tall,
                          T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 ) 
    {
      return FALSE ;
    }

    void I_INT86_cursor_off ( void )
    {
    }

    void I_INT86_cursor_on ( void )
    {
    }

    void I_INT86_set_cursor ( T_INT lini, T_INT lfin )
    {
    }

    void I_INT86_AutoDetect ( INOUT T_INT *currmode,  INOUT T_INT *cfilas,
    			      INOUT T_INT *ccolumnas, INOUT T_INT *ncolores )
    {
      (*ccolumnas) = 80 ;
      (*currmode)  = 00 ;
      (*ncolores)  = 2  ;
      (*cfilas)    = 25 ;
    }

#endif


/* ....................................................................... */

