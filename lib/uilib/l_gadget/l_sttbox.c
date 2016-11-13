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

      #include "uilib/l_gadget/l_sttbox.h"


   /* ... Functions / Funciones ......................................... */

     t_win    L_STTBOX_Open (  IN    T_INT    x1,
                               IN    T_INT    y1,
                               IN    T_INT    x2,
                               IN    T_INT    y2 )
     {
       t_win wwin ;

       wwin = L_WIN_Open(x1,y1,x2,y2) ;
       NULL_RET_NULL(wwin) ;
       L_WIN_Keep(wwin) ;
       L_WIN_SetFrame(wwin,TRUE,c_DOUBLE_FRAME) ;
       L_WIN_SetTitle(wwin,c_CENTERDOWN_TITLE," Press any key ... ") ;
       L_WIN_Clear(wwin) ;
       return wwin ;
     }

     T_INT   L_STTBOX_KeyProcessing  ( IN    t_win    w,
                                       IN    T_INT    tecla )
     {
        T_INT uplines, downlines, x1, y1, x2, y2, tall ;
 
        TRUE__SET_WARNING__RET_LONG((w == NULL),c_ERROR) ;
        L_WIN_GetInfo(w,&uplines,&downlines) ;
        L_WIN_Coordenate(w,&x1,&y1,&x2,&y2) ;
        tall=y2-y1-1 ;
        switch (tecla)
        {
         case c_UP :
              if (uplines)
                 {
                   L_WIN_ScrollDown(w,1) ;
                 }
              return c_KEYPROC ;
         case c_DOWN :
              if (downlines)
                 {
                   L_WIN_ScrollUp(w,1) ;
                 }
              return c_KEYPROC ;
          case c_REPAG :
              if (uplines)
                 {
                   L_WIN_ScrollDown(w,MIN(uplines,tall)) ;
                 }
              return c_KEYPROC ;
          case c_AVPAG :
              if (downlines)
                 {
                    L_WIN_ScrollUp(w,MIN(downlines,tall)) ;
                 }
              return c_KEYPROC ;
         case c_BEGIN :
              L_WIN_ScrollDown(w,uplines) ;
              return c_KEYPROC ;
         case c_END :
              L_WIN_ScrollUp(w,downlines) ;
              return c_KEYPROC ;
         default : break ;
        }
        return tecla ;
     }

     T_BOOL   L_STTBOX_Show ( IN     t_win wwin )
     {
       T_INT  ch ;

       L_WIN_UnHidden(wwin) ;
       do
       {
         L_WIN_Flush() ;
         ch = V_KEYMAP_getkey() ;
         ch = L_STTBOX_KeyProcessing(wwin,ch) ;
       } while (ch == c_KEYPROC) ;
       return TRUE ;
     }


 /* ...................................................................... */

