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



 /* ... Includes / Inclusiones ........................................... */

    #include "uilib/l_wterm/l_win.h"


 /* ... Global vars / Vars. globales ..................................... */

    t_wpanstruct wpan ;
    t_win        MainWin ;


 /* ... Functions / Funciones ............................................ */

    T_BOOL  L_WIN_WriteStr       ( INOUT  t_win W,
                                   IN     T_CHAR *str )
                                     
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      if ( (str == NULL) || (*str=='\0')  )
          return TRUE ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_WriteStr(&(wpan.wpan),&(W->W),str) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL    L_WIN_Exist        ( INOUT  t_win W )
    {
      NULL_RET_FALSE(W) ;
      return L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
    }

    t_win   L_WIN_Open           ( IN     T_INT x1,
                                   IN     T_INT y1,
                                   IN     T_INT x2,
                                   IN     T_INT y2 )
    {
      t_win waux ;
      T_BOOL ok ;

      waux = X_ALLOC_Malloc(c_WIN) ;
      NULL_RET_NULL(waux) ;
      ok = L_WTERM_Open(&(wpan.wpan),&(waux->W),x1,y1,x2,y2) ;
      if ( ok == FALSE  )
         {
           X_ALLOC_Free((void **)&waux) ;
           return NULL ;
         }
      X_THREAD_init(&(waux->mtsda)) ;
      return waux ;
    }

    T_BOOL  L_WIN_Close          ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      X_THREAD_destroy(&(W->mtsda)) ;
      ok = L_WTERM_Close(&(wpan.wpan),&(W->W)) ;
      X_ALLOC_Free((void **)&W) ;
      return ok ;
    }

    T_BOOL  L_WIN_Flush         ( void )
    {
      T_BOOL ok ;

      X_THREAD_lock(&(wpan.mtsda)) ;
      ok = L_WTERM_Flush(&(wpan.wpan)) ;
      X_THREAD_unlock(&(wpan.mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_FlushAll      ( void ) 
    {
      T_BOOL ok ;

      X_THREAD_lock(&(wpan.mtsda)) ;
      ok = L_WTERM_FlushAll(&(wpan.wpan)) ;
      X_THREAD_unlock(&(wpan.mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_Init          ( void )
    {
      T_BOOL ok ;

      if (wpan.wpan.inicialized == FALSE )
         {
           ok = L_WTERM_Init(&(wpan.wpan)) ;
           MainTWin               = X_ALLOC_Realloc(MainTWin,c_WIN) ;
           NULL_RET_FALSE(MainTWin) ;
           (wpan.wpan).WinList[0] = MainTWin ;
           MainWin                = (t_win)MainTWin ;
           X_THREAD_init(&( wpan.mtsda )) ;
           X_THREAD_init(&( ((t_win)MainWin)->mtsda )) ;
         }
      else
         {
           X_THREAD_lock(&(wpan.mtsda)) ;
           ok = L_WTERM_Init(&(wpan.wpan)) ;
           X_THREAD_unlock(&(wpan.mtsda)) ;
         }
      return ok ;
    }

    T_BOOL  L_WIN_GotoXY      ( INOUT  t_win W,
                                IN     T_INT x,
                                IN     T_INT y )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GotoXY(&(wpan.wpan),&(W->W),x,y) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_WhereXY     ( INOUT  t_win W,
                                IN     T_INT *x,
                                IN     T_INT *y )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_WhereXY(&(wpan.wpan),&(W->W),x,y) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    t_win L_WIN_Which       ( IN     T_INT x,
                              IN     T_INT y )
    {
      return (t_win)L_WTERM_Which(&(wpan.wpan),x,y) ;
      /* Como comienzan en la misma posicion de memoria ... */
    }

    T_BOOL  L_WIN_Coordenate  ( INOUT  t_win W,
                                IN     T_INT *x1,
                                IN     T_INT *y1,
                                IN     T_INT *x2,
                                IN     T_INT *y2 )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Coordenate(&(wpan.wpan),&(W->W),x1,y1,x2,y2) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL    L_WIN_Move      ( INOUT  t_win W,
                                IN     T_INT x1,
                                IN     T_INT y1,
                                IN     T_INT x2, 
                                IN     T_INT y2 )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Move(&(wpan.wpan),&(W->W),x1,y1,x2,y2) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_GetColours  ( INOUT  t_win W,
                                IN     t_txt_colores *wback,
                                IN     t_txt_colores *wfore,
                                IN     t_txt_colores *fback,
                                IN     t_txt_colores *ffore )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GetColours(&(wpan.wpan),&(W->W),wback,wfore,fback,ffore) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    void  L_WIN_SetDefaultColour ( IN     t_txt_colores *wback,
                                   IN     t_txt_colores *wfore,
                                   IN     t_txt_colores *fback,
                                   IN     t_txt_colores *ffore )
    {
      L_WTERM_SetDefaultColour(wback,wfore,fback,ffore) ;
    }

    T_BOOL  L_WIN_SetColours  ( INOUT  t_win W,
                                IN     t_txt_colores wback,
                                IN     t_txt_colores wfore,
                                IN     t_txt_colores fback,
                                IN     t_txt_colores ffore )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_SetColours(&(wpan.wpan),&(W->W),wback,wfore,fback,ffore) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_GetFrame    ( INOUT  t_win W,
                                IN     T_BOOL *FrameOn,
                                IN     T_CHAR Frame[] )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GetFrame(&(wpan.wpan),&(W->W),FrameOn,Frame) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_SetFrame    ( INOUT  t_win W,
                                IN     T_BOOL FrameOn, 
                                IN     T_CHAR Frame[] )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_SetFrame(&(wpan.wpan),&(W->W),FrameOn,Frame) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_Hidden      ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Hidden(&(wpan.wpan),&(W->W),TRUE) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_UnHidden    ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Hidden(&(wpan.wpan),&(W->W),FALSE) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL    L_WIN_WriteLn      ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_WriteLn(&(wpan.wpan),&(W->W)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL L_WIN_Vprintf ( INOUT  t_win W,
                           IN     T_CHAR *format, 
                           IN     va_list arg )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Vprintf(&(wpan.wpan),&(W->W),format,arg) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL L_WIN_Printf ( INOUT  t_win W,
                          IN     T_CHAR *format, ... )
    {
      T_BOOL  ok ;
      va_list arg ;

      va_start(arg,format) ;
      ok = L_WTERM_Vprintf(&(wpan.wpan),&(W->W),format,arg) ;
      va_end(arg) ;
      return ok ;
    }

    T_BOOL  L_WIN_ScrollUp  ( INOUT  t_win W,
                              IN     T_INT numero )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_ScrollUp(&(wpan.wpan),&(W->W),numero) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_ScrollDown  ( INOUT  t_win W,
                                IN     T_INT numero )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_ScrollDown(&(wpan.wpan),&(W->W),numero) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_ScrollLeft  ( INOUT  t_win W,
                                IN     T_INT numero )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_ScrollLeft(&(wpan.wpan),&(W->W),numero) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_ScrollRight ( INOUT  t_win W,
                                IN     T_INT numero )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_ScrollRight(&(wpan.wpan),&(W->W),numero) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_Shadow      ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Shadow(&(wpan.wpan),&(W->W),TRUE) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_UnShadow    ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Shadow(&(wpan.wpan),&(W->W),FALSE) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_Keep        ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Keep(&(wpan.wpan),&(W->W),TRUE) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_UnKeep      ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Keep(&(wpan.wpan),&(W->W),FALSE) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_SetKeepTitle ( INOUT  t_win W,
                                 IN     T_CHAR *ktitle )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_SetKeepTitle(&(wpan.wpan),&(W->W),ktitle) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_GetKeepTitle ( INOUT  t_win W,
                                 IN     T_CHAR **ktitle )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GetKeepTitle(&(wpan.wpan),&(W->W),ktitle) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_KeepAjust   ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_KeepAjust(&(wpan.wpan),&(W->W)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    t_win L_WIN_DupWin      ( INOUT  t_win W,
                              IN     T_INT mode )
    {
      t_win waux ;
      t_twin wtaux ;

      X_THREAD_lock(&(W->mtsda)) ;
      wtaux = L_WTERM_DupWin(&(wpan.wpan),&(W->W),mode) ;
      waux  = X_ALLOC_Realloc(wtaux,c_WIN) ;
      X_THREAD_init(&(waux->mtsda)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return waux ;
    }

    T_BOOL  L_WIN_PutOnTop    ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_PutOnTop(&(wpan.wpan),&(W->W)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_PutOnBeneath ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_PutOnBeneath(&(wpan.wpan),&(W->W)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_Clear       ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_Clear(&(wpan.wpan),&(W->W)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_ClearRestOfLine  ( INOUT  t_win W )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_ClearRestOfLine(&(wpan.wpan),&(W->W)) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL L_WIN_GetTextWin ( INOUT  t_win W,
                              IN     T_CHAR **ptxt, 
                              IN     T_INT *bsize )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GetTextWin(&(wpan.wpan),&(W->W),ptxt,bsize) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL L_WIN_SetTextWin ( INOUT  t_win W,
                              IN     T_CHAR *ptxt, 
                              IN     T_INT bsize )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      FALSE_RET_FALSE(L_WTERM_Exist(&(wpan.wpan),&(W->W))) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_SetTextWin(&(wpan.wpan),&(W->W),ptxt,bsize) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL L_WIN_GetTitle ( INOUT  t_win W,
                            IN     T_INT *TitleMode, 
                            IN     T_CHAR **Title )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GetTitle(&(wpan.wpan),&(W->W),TitleMode,Title) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_SetTitle ( INOUT  t_win W,
                             IN     T_INT TitleMode, 
                             IN     T_CHAR *Title )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_SetTitle(&(wpan.wpan),&(W->W),TitleMode,Title) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_GetInfo  ( INOUT  t_win W,
                             IN     T_INT *uplines, 
                             IN     T_INT *downlines )
    {
      T_BOOL ok ;

      NULL_RET_FALSE(W) ;
      ok = L_WTERM_Exist(&(wpan.wpan),&(W->W)) ;
      FALSE_RET_FALSE(ok) ;
      X_THREAD_lock(&(W->mtsda)) ;
      ok = L_WTERM_GetInfo(&(wpan.wpan),&(W->W),uplines,downlines) ;
      X_THREAD_unlock(&(W->mtsda)) ;
      return ok ;
    }

    T_BOOL  L_WIN_Touch  ( INOUT  t_win W )
    {
      return L_WTERM_Touch(&(wpan.wpan),&(W->W)) ;
    }


/* ....................................................................... */
