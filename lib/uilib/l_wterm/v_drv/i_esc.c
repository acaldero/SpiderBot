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

      #include "uilib/l_wterm/v_drv/i_esc.h"


   /* ... Funtions / Funciones ........................................... */

    T_BOOL I_ESC_Begin ( void )
    {
      /*  Activar el terminal virtual 2..., si es posible */
      printf("\x1B[%dz",(T_INT)(2)) ;
      fflush(stdout) ;
      return TRUE ;
    }

    void I_ESC_End ( void )
    {
      /*  1.- paso a blanco y negro y ...
          2.- ... poner el cursor en (1,1)  */
      printf("\x1B[%d;%dm\x1B[%d;%df",(T_INT)(30+7),(T_INT)(40+0),1,1 ) ;
      printf("\x1B[%dz",(T_INT)(1)) ;
      fflush(stdout) ;
    }

    void I_ESC_set_modo_video ( T_INT modo_video )
    {
    }

    void I_ESC_clrscr ( void )
    {
      /*  1.- borrar la pantalla y ...
          2.- ... poner el cursor en (1,1)  */
      printf("\x1B[2J\x1B[%d;%df",1,1) ;
      fflush(stdout) ;
    }

    void I_ESC_cgotoxy ( T_INT x, T_INT y )
    {
      printf("\x1B[%d;%df",y,x) ;
      fflush(stdout) ;
    }

    void   I_ESC_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y )
    {
    }

    void   I_ESC_cursor_off ( void )
    {
    }

    void   I_ESC_cursor_on  ( void )
    {
    }

    void   I_ESC_set_cursor ( T_INT lini, T_INT lfin )
    {
    }

    void   I_ESC_AutoDetect ( INOUT T_INT *currmode,
                              INOUT T_INT *cfilas,
                              INOUT T_INT *ccolumnas,
                              INOUT T_INT *rvertical,
                              INOUT T_INT *rhorizontal,
                              INOUT T_INT *charheight,
                              INOUT T_INT *charwidth,
                              INOUT T_INT *ncolores )
    {
      (*currmode)    = 0   ;
      (*rvertical)   = 25  ;
      (*rhorizontal) = 80  ;
      (*charheight)  = 1   ;
      (*charwidth)   = 1   ;
      (*cfilas)      = (*rvertical)   / (*charheight) ;
      (*ccolumnas)   = (*rhorizontal) / (*charwidth) ;
      (*ncolores)    = 16 ;
    }


    T_BOOL I_ESC_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                            T_INT width, T_INT tall,
                            T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 )
    {
      T_INT tallxwidth ;
      register T_INT i, j, oi, off ;
      T_CHAR oldattr, newattr, sch, *pch ;

      if ( (rx2>width) || (ry2>tall) )
         {
           L_DEBUG_MSG_Write(WARNING,FALSE,IESC_BAD_DIMENSIONS) ;
           return FALSE ;
         }
      tallxwidth=tall*width ;
      if (2*tallxwidth > gObuffsize)
         {
           gObuff=(T_CHAR *)X_ALLOC_Realloc(gObuff,2*tallxwidth) ;
           if (!gObuff)
              {
                printf("\x1B[%d;%df VTERM: NOT enough memory.",1,1) ;
                return FALSE ;
              }
           gObuffsize=2*tallxwidth ;
           X_ALLOC_MemSet(gObuff,0,(size_t)gObuffsize) ;
         }
      if (ncolores>2)
      {
        static T_CHAR Color[]=c_esc_Text16Color ;

        oldattr=~(*attr) ;
        for (j=ry1-1; j<ry2; j++)
        {
          off=j*width ;
          if ( (!memcmp(scr+off+rx1,gObuff+off+rx1,rx2-rx1))
                                  &&
               (!memcmp(attr+off+rx1,gObuff+tallxwidth+off+rx1,rx2-rx1)) )
             {
               continue ; 
               /* TIP!: memcmp( !, !, rx2-rx1+1), but we read 80 bytes
                  at begin 1921 ... */
             }
          if (j==tall-1)
                   printf("\x1B[%d;%df\x1B[K",j+1,rx1) ;
              else printf("\x1B[%d;%df",j+1,rx1) ;
          for (i=oi=(rx1-1); (i<rx2); i++)
          {
            newattr=*(attr+off+i) ;
            if (oldattr!=newattr)
               {
                 pch=scr+off+i ;
                 sch=*pch ;
                 *pch='\0' ;
                 printf("%s\x1B[%d;%dm",(T_CHAR *)(scr+off+oi),
                                        (T_INT)(30+Color[newattr & 0x07]),
                                        (T_INT)(40+Color[(newattr >> 4) & 0x07]) ) ;
                 *pch=sch ;
                 oi=i ;
                 oldattr=newattr ;
               }
          } 
          pch=scr+off+rx2-((i==width) && (j==tall-1)) ;
          sch=*pch ;
          *pch='\0' ;
          printf("%s",(T_CHAR *)(scr+off+oi)) ;
          *pch=sch ;
        }
      } else {
               for (j=0; j<tall-1; j++)
               {
                 printf("%.*s",width,(scr+j*width)) ;
               }
             }
      fflush(stdout) ;
      X_ALLOC_MemMove(gObuff,scr,(size_t)tallxwidth) ;
      X_ALLOC_MemMove((gObuff+tallxwidth),attr,(size_t)tallxwidth) ;
      return TRUE ;
    }


  /* ................................................................... */

