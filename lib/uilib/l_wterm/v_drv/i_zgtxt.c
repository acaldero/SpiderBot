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



   /* ... Includes / Inclusiones ........................................ */

      #include "uilib/l_wterm/v_drv/i_zgtxt.h"


   /* ... Functions / Funciones ......................................... */

    T_BOOL I_ZGTXT_Begin ( IN T_INT *currmode )
    {
#if ( defined(__LINUX__) && defined(__MGRPH__) )
      T_INT errorcode ;

      vga_init() ;
      errorcode = vga_setmode(G640x480x256) ;
      if (errorcode == -1)  /* an error occurred */
         {
           printf("Virtual Terminal ERROR:\n") ;
           printf("Press any key to continue...") ;
           getc(stdin) ;
           return FALSE ;
         }
      vga_clear() ;
      return TRUE ;
#endif

#if (! ( defined(__LINUX__) && defined(__MGRPH__) ) )
      return FALSE ;
#endif
    }

    void I_ZGTXT_End ( void )
    {
#if ( defined(__LINUX__) && defined(__MGRPH__) )
      vga_setmode(TEXT) ;
#endif
    }

    void   I_ZGTXT_set_modo_video ( T_INT modo_video )
    {
#if ( defined(__LINUX__) && defined(__MGRPH__) )
      vga_setmode(modo_video) ;
#endif
    }

    void   I_ZGTXT_cgotoxy    ( IN    T_INT  x, IN    T_INT  y ) 
    {
    }

    void   I_ZGTXT_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) 
    {
    }

    void   I_ZGTXT_cursor_off ( void ) 
    {
    }

    void   I_ZGTXT_cursor_on  ( void ) 
    {
    }

    void   I_ZGTXT_set_cursor ( T_INT lini, T_INT lfin )
    {
    }

    void   I_ZGTXT_clrscr     ( void ) 
    {
    }

    void I_ZGTXT_Line ( T_WORD x1, T_WORD y1, 
                         T_WORD x2, T_WORD y2, 
                         T_BYTE color )
    {
#if ( defined(__LINUX__) && defined(__MGRPH__) )
      vga_setcolor(color) ;
      vga_drawline(x1,y1,x2,y2) ;
#endif

#if (! ( defined(__LINUX__) && defined(__MGRPH__) ) )
#endif
    }

    void I_ZGTXT_Bar ( T_WORD x1, T_WORD y1, 
                        T_WORD x2, T_WORD y2, 
                        T_BYTE color )
    {
#if ( defined(__LINUX__) && defined(__MGRPH__) )
      T_INT j ;


      for (j=y1; j<y2; j++)
          {
            vga_drawline(x1,j,x2,j) ;
          }
#endif

#if (! ( defined(__LINUX__) && defined(__MGRPH__) ) )
#endif
    }

    void   I_ZGTXT_AutoDetect ( INOUT T_INT *currmode,
                                 INOUT T_INT *cfilas,
                                 INOUT T_INT *ccolumnas,
                                 INOUT T_INT *rvertical,
                                 INOUT T_INT *rhorizontal,
                                 INOUT T_INT *charheight,
                                 INOUT T_INT *charwidth,
                                 INOUT T_INT *ncolores )
    {
#if ( defined(__LINUX__) && defined(__MGRPH__) )
      (*currmode)    = vga_lastmodenumber() ;
      (*rvertical)   = vga_getydim() ;
      (*rhorizontal) = vga_getxdim() ;
      (*charheight)  = 8 ;
      (*charwidth)   = 8 ;
      (*cfilas)      = (*rvertical)   / (*charheight) ;
      (*ccolumnas)   = (*rhorizontal) / (*charwidth) ;
      (*ncolores)    = vga_getcolors() ;
#endif

#if (! ( defined(__LINUX__) && defined(__MGRPH__) ) )
      (*currmode)    = 1 ;
      (*rvertical)   = 1 ;
      (*rhorizontal) = 1 ;
      (*charheight)  = 1 ;
      (*charwidth)   = 1 ;
      (*cfilas)      = (*rvertical)   / (*charheight) ;
      (*ccolumnas)   = (*rhorizontal) / (*charwidth) ;
      (*ncolores)    = 2 ;
#endif
    }

    T_BOOL I_ZGTXT_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                          T_INT width, T_INT tall, T_INT charw, T_INT charh,
                          T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 )
    {
      register T_INT j, tallxwidth ;

      if ( (rx2>width) || (ry2>tall) )
         {
           L_DEBUG_MSG_Write(WARNING,FALSE,IBCGTXT_BAD_DIMENSIONS) ;
           return FALSE ;
         }
      tallxwidth=tall*width ;
      if (2*tallxwidth > gObuffsize)
         {
           /*outtextxy((width-strlen(IBCGTXT_INITMSG)-1)*charw,
                     (tall-1)*charh,IBCGTXT_INITMSG) ;*/
           gObuff=(T_CHAR *)X_ALLOC_Realloc(gObuff,2*tallxwidth) ;
           if (gObuff == NULL)
              {
                /*outtextxy(1,1,IBCGTXT_NO_MEMORY) ;*/
                return FALSE ;
              } 
	   gObuffsize=2*tallxwidth ;
	   X_ALLOC_MemSet(gObuff,0,(size_t)gObuffsize) ;
         }
      if (ncolores>2)
      {
        static T_CHAR Color[]=c_bcgtxt_Text16Color ;

        for (j=ry1-1; j<ry2; j++)
        {
          T_INT off ;

          off=j*width ;
          if ( (memcmp(scr+off,gObuff+off,width))
                             ||
               (memcmp(attr+off,gObuff+tallxwidth+off,width)) )
             {
               T_CHAR sch, *po, *pb, *pao, *pab ;
               T_INT i, oi, ofore, fore, oback, back, opt_rx2, opt_rx1 ;

               for (po=scr+off+rx2, pb=gObuff+off+rx2,
                    pao=attr+off+rx2, pab=gObuff+tallxwidth+off+rx2;
                         (po>scr+off) && (*po==*pb) && (*pao==*pab);
                                            po--,pb--,pao--,pab--) ;
               opt_rx2=(T_INT)(po-scr-off) + 1 ;
               /* opt_rx2 es la siguiente columna a la ultima a imprimir */
               for (po=scr+off+rx1, pb=gObuff+off+rx1,
                    pao=attr+off+rx1, pab=gObuff+tallxwidth+off+rx1;
                         (po<scr+off+rx2) && (*po==*pb) && (*pao==*pab);
                                            po++,pb++,pao++,pab++) ;
               opt_rx1=(T_INT)(po-scr-off) ;
               /* opt_rx1 es la primera columna a imprimir */
               ofore=Color[(*(attr+off+rx1)) & 0x07] ;
               oback=Color[((*(attr+off+rx1)) >> 4) & 0x07] ;
               /*setcolor(ofore) ;*/
               /*setfillstyle(SOLID_FILL,oback) ;*/
               ofore=~ofore ;
               oback=~oback ;
               for (i=oi=opt_rx1; i<opt_rx2; i++)
               {
                 fore=Color[(*(attr+off+i)) & 0x07] ;
                 back=Color[((*(attr+off+i)) >> 4) & 0x07] ;
                 if ( (ofore!=fore) || (oback!=back) )
                    {
                      /*bar(oi*charw,j*charh,i*charw,(j+1)*charh-1) ;*/
                      po=scr+off+i ;
                      sch=(*po)  ;
                      (*po)='\0' ;
                      /*outtextxy(oi*charw,j*charh,(T_CHAR *)(scr+off+oi)) ;*/
                      (*po)=sch ;
                      /*setcolor(fore) ;*/
                      /*setfillstyle(SOLID_FILL,back) ;*/
                      ofore=fore ;
                      oback=back ;
                      oi=i ;
                    }
               }
               /*bar(oi*charw,j*charh,opt_rx2*charw-1,(j+1)*charh-1) ;*/
               po=scr+off+opt_rx2 ;
               sch=(*po)  ;
               (*po)='\0' ;
               /*outtextxy(oi*charw,j*charh,(T_CHAR *)(scr+off+oi)) ;*/
               (*po)=sch ;
             }
        }
      } else {
               for (j=ry1-1; j<ry2; j++)
               {
                 T_INT off ;

                 off=j*width ;
                 if (memcmp(scr+off,gObuff+off,width))
                    {
                      T_CHAR sch, *po, *pb ;
                      T_INT opt_rx2 ;

                      for (po=scr+off+rx2, pb=gObuff+off+rx2;
                                     (po>scr+off) && (*po==*pb); po--,pb--) ;
                      opt_rx2=(T_INT)(po-scr-off) + 1 ;
                      po=scr+off+opt_rx2 ;
                      sch=(*po)  ;
                      (*po)='\0' ;
                      /*outtextxy(rx1*charw,j*charh,(T_CHAR *)(scr+off+rx1)) ;*/
                      (*po)=sch ;
                    }
               }
             }
      X_ALLOC_MemMove(gObuff,scr,(size_t)tallxwidth) ;
      X_ALLOC_MemMove((gObuff+tallxwidth),attr,(size_t)tallxwidth) ;
      return TRUE ;
    }


  /* .................................................................... */

