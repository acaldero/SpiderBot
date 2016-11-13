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

      #include "uilib/l_gadget/l_pb.h"


   /* ... Functions / Funciones ......................................... */

     T_BOOL L_UI_OpenPB ( INOUT  t_pbar *vpb,
                          IN     T_CHAR *title,
                          IN     T_INT   x,
                          IN     T_INT   y,
                          IN     T_INT   width,
                          IN     T_LONG  total ) 
    {
      vpb->w=L_WIN_Open(x,y,x+width+1,y+2) ;
      NULL_RET_FALSE(vpb->w) ;
      L_WIN_SetFrame(vpb->w,TRUE,c_SIMPLE_FRAME1) ;
      L_WIN_SetTitle(vpb->w,c_LEFTUP_TITLE,title) ;
      vpb->x1=x ;
      vpb->y1=y ;
      vpb->width=width ;
      vpb->total=((total) ? total : 1) ;
      return TRUE ;
    }

    void   L_UI_FillPB_Bird     ( INOUT  t_pbar  *vpb,
                                  IN     T_INT    off,
                                  IN     T_CHAR  *backCh  )
    {
      T_INT i ;

      for (i=1;i<=off;i++)
           switch (i % 4)
           {
             case 0 : L_WIN_WriteStr(vpb->w,"|") ;
                      break ;
             case 1 : L_WIN_WriteStr(vpb->w,"/") ;
                      break ;
             case 2 : L_WIN_WriteStr(vpb->w,"|") ;
                      break ;
             case 3 : L_WIN_WriteStr(vpb->w,"\\") ;
                      break ;
           }
      for (i=off+1;i<vpb->width;i++)
           L_WIN_WriteStr(vpb->w,backCh) ;
    }

    void   L_UI_FillPB_Classic  ( INOUT  t_pbar  *vpb,
                                  IN     T_INT    off,
                                  IN     T_CHAR  *fillCh,
                                  IN     T_CHAR  *backCh  )
    {
      T_INT i ;

      for (i=1;i<=off;i++)
           L_WIN_WriteStr(vpb->w,fillCh) ;
      for (i=off+1;i<vpb->width;i++)
           L_WIN_WriteStr(vpb->w,backCh) ;
    }

    T_BOOL L_UI_ProcesingPB ( INOUT  t_pbar  *vpb,
                              IN     T_LONG   current )
    {
      T_INT off ;

      NULL_RET_FALSE(vpb->w) ;
      L_WIN_GotoXY(vpb->w,1,1) ;
      off=MIN( vpb->width,
               (T_INT)( (float)(vpb->width)*((float)current / (float)(vpb->total)) ) ) ;
      /*L_UI_FillPB_Bird(vpb,off,".") ;*/
      L_UI_FillPB_Classic(vpb,off,c_PBT_CHAR,"-") ;
      return TRUE ;
    }

    T_BOOL L_UI_ClosePB  ( INOUT t_pbar *vpb )
    {
      NULL_RET_FALSE(vpb) ;
      return L_WIN_Close(vpb->w) ;
    }

    T_BOOL L_UI_AjustPB  ( INOUT t_pbar  *vpb,
                           IN    T_LONG   ntotal )
    {
      NULL_RET_FALSE(vpb) ;
      (vpb->total) = ((ntotal) ? ntotal : 1) ;
      return TRUE ;
    }


 /* ..................................................................... */
