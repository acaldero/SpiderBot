

 #ifndef L_WTERM_H
 #define L_WTERM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_adt/l_buffw.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_wterm/v_term.h"
      #include "uilib/l_wterm/c_wterm.h"


   /* ... Types / Tipos ................................................. */

      typedef 
      struct {
               T_INT    x1,y1,x2,y2 ;
               T_INT    posx,posy,titlex,titley ;
               T_INT    uplines,downlines ;
               T_CHAR  *forebuff ;
               T_CHAR  *title ;
               T_CHAR   frame[8], keeptitle[4] ;
               T_BOOL   dinamic,hiddenOn,frameOn,dirty,keep,shadow ;
               T_INT    titlemode ;
               T_INT    orden ; /*dentro lista wins...*/
	       t_txt_colores    wback,wfore,fback,ffore ;
	    } t_twinstruct ;

      typedef t_twinstruct *t_twin ;

      typedef 
      struct {
               T_U_INT fgc    : 3 ;  /* color fore */
               T_U_INT shine  : 1 ;  /* intensidad */
               T_U_INT bgc    : 3 ;  /* color back */
               T_U_INT blink  : 1 ;  /* parpadeo   */
	     } t_attrib ;

      typedef  
      struct {
               T_INT       rho,rve ;
               T_CHAR     *previewBuff ;
               t_attrib   *previewAttr ;
               T_BOOL      dirtyPan, inicialized ;
	       t_twin      *WinList ;
               T_INT       WinNum ;
               T_INT       fx1, fy1, fx2, fy2 ;
	     } t_tscreenstruct ;

      typedef t_tscreenstruct *t_tscreen ;


   /* ... Var. / Variables .............................................. */

      extern t_twin     MainTWin ;    /* Representa a la pantalla entera */
      extern T_CHAR     v_chclear ;  /* El caracter usado para borrado */


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_WTERM_Init           (t_tscreen wpan) ;
      T_BOOL  L_WTERM_Exist          (t_tscreen wpan,
                                      t_twin W) ;
      t_twin  L_WTERM_Creat          (t_tscreen wpan,
                                      T_INT x1,T_INT y1,T_INT x2,T_INT y2) ;
      T_BOOL  L_WTERM_Open           (t_tscreen wpan,
                                      t_twin W,T_INT x1,T_INT y1,T_INT x2,T_INT y2) ;
      T_BOOL  L_WTERM_Close          (t_tscreen wpan,
                                      t_twin W) ;
      T_BOOL  L_WTERM_CloseSystem    (t_tscreen wpan) ;
      T_BOOL  L_WTERM_GotoXY         (t_tscreen wpan,
                                      t_twin W, T_INT x, T_INT y) ;
      T_BOOL  L_WTERM_WhereXY        (t_tscreen wpan,
                                      t_twin W, T_INT *x, T_INT *y) ;
      t_twin  L_WTERM_Which          (t_tscreen wpan,
                                      T_INT x, T_INT y) ;
      T_BOOL  L_WTERM_Coordenate     (t_tscreen wpan,
                                      t_twin W,
                                      T_INT *x1,T_INT *y1,T_INT *x2,T_INT *y2) ;
      T_BOOL  L_WTERM_Move           (t_tscreen wpan,
                                      t_twin W,
                                      T_INT x1,T_INT y1, T_INT x2, T_INT y2) ;
      T_BOOL  L_WTERM_GetColours     (t_tscreen wpan,
                                      t_twin W,t_txt_colores *wback,
                                      t_txt_colores *wfore,t_txt_colores *fback,
                                      t_txt_colores *ffore) ;
      T_BOOL  L_WTERM_SetColours     (t_tscreen wpan,
                                      t_twin W,t_txt_colores wback,
  	    		              t_txt_colores wfore,t_txt_colores fback,
  			              t_txt_colores ffore) ;
      void  L_WTERM_SetDefaultColour (t_txt_colores *wback,t_txt_colores *wfore,
  		   		      t_txt_colores *fback,t_txt_colores *ffore) ;
      T_BOOL  L_WTERM_GetFrame       (t_tscreen wpan,
                                      t_twin W,T_BOOL *FrameOn,T_CHAR Frame[]) ;
      T_BOOL  L_WTERM_SetFrame       (t_tscreen wpan,
                                      t_twin W,T_BOOL FrameOn, T_CHAR Frame[]) ;
      T_BOOL  L_WTERM_Hidden         (t_tscreen wpan,
                                      t_twin W, T_BOOL mode) ;
      T_BOOL  L_WTERM_WriteStr       (t_tscreen wpan,
                                      t_twin W,T_CHAR *str) ;
      T_BOOL  L_WTERM_WriteLn        (t_tscreen wpan,
                                      t_twin W) ;
      T_BOOL  L_WTERM_Vprintf        (t_tscreen wpan,
                                      t_twin W, T_CHAR *format, va_list arg) ;
      T_BOOL  L_WTERM_Printf         (t_tscreen wpan,
                                      t_twin W, T_CHAR *format, ...) ;
      T_BOOL  L_WTERM_ScrollUp       (t_tscreen wpan,
                                      t_twin W, T_INT numero) ;
      T_BOOL  L_WTERM_ScrollDown     (t_tscreen wpan,
                                      t_twin W, T_INT numero) ;
      T_BOOL  L_WTERM_ScrollLeft     (t_tscreen wpan,
                                      t_twin W, T_INT numero) ;
      T_BOOL  L_WTERM_ScrollRight    (t_tscreen wpan,
                                      t_twin W, T_INT numero) ;
      T_BOOL  L_WTERM_Shadow         (t_tscreen wpan,
                                      t_twin W, T_BOOL mode) ;
      T_BOOL  L_WTERM_Keep           (t_tscreen wpan,
                                      t_twin W, T_BOOL mode) ;
      T_BOOL  L_WTERM_KeepAjust      (t_tscreen wpan,
                                      t_twin W) ;
      t_twin  L_WTERM_DupWin         (t_tscreen wpan,
                                      t_twin W, T_INT mode) ;
      T_BOOL  L_WTERM_Flush          (t_tscreen wpan) ;
      T_BOOL  L_WTERM_FlushAll       (t_tscreen wpan) ;
      T_BOOL  L_WTERM_PutOnTop       (t_tscreen wpan,
                                      t_twin W) ;
      T_BOOL  L_WTERM_PutOnBeneath   (t_tscreen wpan,
                                      t_twin W) ;
      T_BOOL  L_WTERM_Clear           (t_tscreen wpan,
                                      t_twin W) ;
      T_BOOL  L_WTERM_ClearRestOfLine (t_tscreen wpan,
                                       t_twin W) ;
      T_BOOL  L_WTERM_GetTextWin      (t_tscreen wpan,
                                       t_twin W, T_CHAR **ptxt, T_INT *bsize) ;
      T_BOOL  L_WTERM_SetTextWin      (t_tscreen wpan,
                                       t_twin W, T_CHAR *ptxt, T_INT bsize) ;
      T_BOOL  L_WTERM_GetTitle        (t_tscreen wpan,
                                       t_twin W, T_INT *TitleMode, 
					         T_CHAR **Title) ;
      T_BOOL  L_WTERM_SetTitle        (t_tscreen wpan,
                                       t_twin W, T_INT TitleMode, T_CHAR *Title) ;
      T_BOOL  L_WTERM_SetKeepTitle    (t_tscreen wpan,
                                       t_twin W, T_CHAR *ktitle) ;
      T_BOOL  L_WTERM_GetKeepTitle    (t_tscreen wpan,
                                       t_twin W, T_CHAR **ktitle) ;
      T_BOOL  L_WTERM_GetInfo         (t_tscreen wpan,
                                       t_twin W, T_INT *uplines, T_INT *downlines) ;
      T_BOOL  L_WTERM_Touch           (t_tscreen wpan,
                                       t_twin W) ;
  

   /* ... Const / Constantes ............................................ */
  
      /* ... Type size --- Taman~o tipo ... */
      #define c_TWIN     sizeof(t_twinstruct)

      /* ... TIP: see c_wterm.h for more ctes */
  
  
 /* ..................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

