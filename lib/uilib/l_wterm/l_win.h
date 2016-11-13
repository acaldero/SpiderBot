

 #ifndef L_WIN_H
 #define L_WIN_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_thread/x_thread.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_wterm/l_wterm.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct {
               t_twinstruct     W ;
               t_mtsda          mtsda ;
             } t_winstruct ;

      typedef t_winstruct *t_win ;

      typedef
      struct {
               t_tscreenstruct  wpan ;
               t_mtsda          mtsda ;
             } t_wpanstruct ;

      typedef t_wpanstruct *t_wpan ;


   /* ... Const / Constantes ............................................ */

      #define  c_WIN   (sizeof(t_winstruct)) 
      #define  c_WPAN  (sizeof(t_wpanstruct)) 


   /* ... Var. / Variables .............................................. */

      extern t_win     MainWin ;
      /*
         -> Representa a la pantalla entera.
         -> It means the full screen.
      */
      extern T_CHAR    v_chclear ;
      /*
         -> El caracter usado para borrado.
         -> eraser char.
      */


   /* ... Functions / Funciones ......................................... */
  
      T_BOOL  L_WIN_Init        ( void ) ;
      /* - Is the first function you MUST call. It will inicialize all
           internal data and other stuff */
      /* - Es el primer procedimiento que hay que llamar.
           Inicializa todas las variables internas y sincroniza
           los modulos inferiores */
  
      T_BOOL  L_WIN_Exist       ( IN     t_win    W ) ;
      /* - return TRUE if 'W' is a valid window. */
      /* - retorna TRUE si es un descriptor valido
           NOTA: La mayoria de las funciones que retornan un 'T_BOOL', usan
                 FALSE si 'W' es un descriptor invalido o ha ocurrido
                 algun error */
  
      t_win L_WIN_Open          ( IN     T_INT    x1, 
                                  IN     T_INT    y1,
                                  IN     T_INT    x2,
                                  IN     T_INT    y2 ) ;
      /* - return our new text window.
           It not appeare till we use L_WIN_Flush */
      /* - crea una ventana y nos retorna su descritor */
  
      T_BOOL  L_WIN_Close       ( INOUT  t_win   W ) ;
      /* - Close 'W', and free all resource that it used */
      /* - cierra la ventana 'W' */
  
      T_BOOL  L_WIN_GotoXY      ( INOUT  t_win   W,  
                                  IN     T_INT   x,  
                                  IN     T_INT   y ) ;
      /* - Move cursor to 'x,y' in 'W' window */
      /* - La posicion de salida de caracteres (y el cursor) asociados
           a la ventana 'W' queda fijada en 'x,y' */
  
      T_BOOL  L_WIN_WhereXY     ( INOUT  t_win  W, 
                                  INOUT  T_INT *x, 
                                  INOUT  T_INT *y ) ;
      /* - Store at 'x,y' where is cursor position in 'W' */
      /* - Almacena en 'x,y' la posicion de salida de caracteres
           (y el cursor) asociados a la ventana 'W' */
  
      t_win L_WIN_Which         ( INOUT  T_INT x, 
                                  INOUT  T_INT y ) ;
      /* - Return the window at 'x,y' that user can see */
      /* - Retorna el descriptor de la ventana que es visible en las
           coordenadas 'x,y' */
  
      T_BOOL  L_WIN_Coordenate  ( INOUT  t_win W,
                                  INOUT  T_INT *x1,
                                  INOUT  T_INT *y1,
                                  INOUT  T_INT *x2,
                                  INOUT  T_INT *y2 ) ;
      /* - Store at x1,y1,x2,y2 windows coordenates */
      /* - Permite conocer las coordenadas de la ventana 'W' */
  
      T_BOOL  L_WIN_Move        ( INOUT  t_win W,
                                  IN     T_INT x1,
                                  IN     T_INT y1,
                                  IN     T_INT x2,
                                  IN     T_INT y2 ) ;
      /* - */
      /* - Cambia las coordenadas de 'W'. 
           Permite tando mover la ventana como 
           cambiarla de taman~o */
  
      T_BOOL  L_WIN_GetColours  ( INOUT  t_win W,
                                  INOUT  t_txt_colores    *wback,
                                  INOUT  t_txt_colores    *wfore,
                                  INOUT  t_txt_colores    *fback,
                                  INOUT  t_txt_colores    *ffore ) ;
      /* - Let us know what colors are been using in 'W' */
      /* - Usada para conocer los colores que se usan en 'W' */
  
      T_BOOL  L_WIN_SetColours  ( INOUT  t_win W,
                                  IN     t_txt_colores    wback,
  			          IN     t_txt_colores    wfore,
                                  IN     t_txt_colores    fback,
  			          IN     t_txt_colores    ffore ) ;
      /* - Change colors to used in 'W' */
      /* - Cambia los colorea a usar en 'W' por los indicados */
  
      void  L_WIN_SetDefaultColour ( INOUT  t_txt_colores *wback,
                                     INOUT  t_txt_colores *wfore,
  				     INOUT  t_txt_colores *fback,
                                     INOUT  t_txt_colores *ffore ) ;
      /* - Used to know what color are used by default */
      /* - Para conocer los colores que la libreria usa por defecto */
  
      T_BOOL  L_WIN_GetFrame ( INOUT  t_win W,
                               INOUT  T_BOOL *FrameOn,
                               INOUT  T_CHAR Frame[] ) ;
      /* - Used to know if 'W' is framed and witch is it */
      /* - Para conocer si la ventana usa 'enmarcado' y cual usa */
  
      T_BOOL  L_WIN_SetFrame ( INOUT  t_win W,
                               IN     T_BOOL FrameOn, 
                               IN     T_CHAR Frame[] ) ;
      /* - Used to reset frame and set 'Frame' like frame */
      /* - Usado para desactivar 'enmarcado' o activarlo y usar 'Frame' */
  
      T_BOOL  L_WIN_Hidden ( INOUT  t_win  W ) ;
      /* - Hide 'W' at screen but Dot not close it */
      /* - Oculta la ventana, no se vera pero esta ahi */
  
      T_BOOL  L_WIN_UnHidden ( INOUT  t_win  W ) ;
      /* - Unhide 'W' and dump it's contents */
      /* - Vuelve a mostrar la ventana */
  
      T_BOOL  L_WIN_WriteStr ( INOUT  t_win W,
                               IN     T_CHAR *str ) ;
      /* - Write 'str' at current cursor position, and move it according to */
      /* - Escribe 'str' en la posicion actual del cursor moviendolo */
  
      T_BOOL  L_WIN_WriteLn ( INOUT  t_win  W ) ;
      /* - Write a Carry return */
      /* - Escribe un Enter */
  
      T_BOOL L_WIN_Vprintf ( INOUT  t_win W, 
                             IN     T_CHAR *format, 
                             IN     va_list arg ) ;
      /* - Write at 'W' what you say in format. */
      /* - Escribe en 'W' segun el formato. */

      T_BOOL  L_WIN_Printf ( INOUT  t_win W, 
                             IN     T_CHAR *format, ... ) ;
      /* - Write at 'W' what you say in format. */
      /* - Escribe en 'W' segun el formato. */
  
      T_BOOL  L_WIN_ScrollUp ( INOUT  t_win W, 
                               IN     T_INT numero ) ;
      /* - Move win contents 'numero' lines UP */
      /* - Mueve el contenido de la ventana 'numero' lineas arriba */
  
      T_BOOL  L_WIN_ScrollDown ( INOUT  t_win W, 
                                 IN     T_INT numero ) ;
      /* - Move win contents 'numero' lines DOWN */
      /* - Mueve el contenido de la ventana 'numero' lineas abajo */
  
      T_BOOL  L_WIN_ScrollLeft ( INOUT  t_win W, 
                                 IN     T_INT numero ) ;
      /* - Move win contents 'numero' lines LEFT */
      /* - Mueve el contenido de la ventana 'numero' lineas izquierda */
  
      T_BOOL  L_WIN_ScrollRight ( INOUT  t_win W, 
                                  IN     T_INT numero ) ;
      /* - Move win contents 'numero' lines RIGHT */
      /* - Mueve el contenido de la ventana 'numero' lineas derecha */
  
      T_BOOL  L_WIN_Shadow ( INOUT  t_win  W ) ;
      /* - Let window have 'shadow' */
      /* - La ventana apareceran como si tuvieran 'sombra' */
  
      T_BOOL  L_WIN_UnShadow ( INOUT  t_win  W ) ;
      /* - Reset win 'shadow' */
      /* - Quita la sombra de la ventana */
  
      T_BOOL  L_WIN_Keep ( INOUT  t_win  W ) ;
      /* - Let keep text when you move UP/DOWN win text and when you
           move in opposite direcction, it will be displayed */
      /* - Permite almacenar el texto que se 'cae' al 'Scrolear'
           y cuando 'scrolees' el texto al reves, lo recuperas */
  
      T_BOOL  L_WIN_UnKeep ( INOUT  t_win  W ) ;
      /* - After this function, text will not be kept */
      /* - A partir de esta llamada, el texto no se almacena */
  
      T_BOOL  L_WIN_KeepAjust ( INOUT  t_win  W ) ;
      /* - Memory used to keep text will be free, and you only have
           what are seeing at screen. Used when you finish with keep */
      /* - La memoria usada para conservar el texto, sera liberada y
           solo quedara el contenido actual de la ventana */
  
      t_win L_WIN_DupWin ( INOUT  t_win W, 
                           IN     T_INT mode ) ;
      /* - Return a win duplicate. Please see in 'Const', 'Window dup mode'*/
      /* - Duplica una ventana. Mirar en 'Const',
           el apartado 'modo de duplicar una ventana' */
  
      T_BOOL  L_WIN_Flush ( void ) ;
      /* - All functions update internal data, but not change screen
           according to. You have to used this function in order to
           see you are doing. This function have been optimized
           and only write changes made from last call. This improve
           i/o perfomance */
      /* - Todas las funciones actualizan los datos internamente, pero
           ninguna modifica el contenido de la pantalla. Para ver
           cualquier modificacion, hay que llamar a esta funcion.
           Esta optimizada para solo imprimir los cambios desde la
           ultima vez que se la llamo */
  
      T_BOOL  L_WIN_FlushAll ( void ) ;
      /* - Redraw All screen. IT is slow in some case, but necesary if
           screen is corrupt (because flush only write changes) */
      /* - Reescribe la pantalla entera. Es lento, pero necesario
           en casos de pantalla con datos corruptos por otro gestor */
  
      T_BOOL  L_WIN_PutOnTop ( INOUT  t_win  W ) ;
      /* - 'W' will be first window at screen */
      /* - 'W' sera la primera ventana en verse */
  
      T_BOOL  L_WIN_PutOnBeneath ( INOUT  t_win  W ) ;
      /* - 'W' will be last window. Opposite to L_WIN_PutOnTop */
      /* - Opuesta a L_WIN_PutOnTop, coloca 'W' como la ultima ventana */
  
      T_BOOL  L_WIN_Clear ( INOUT  t_win  W ) ;
      /* - Clear all text in 'W' and set cursor at (1,1) of this windows */
      /* - Borra 'W' y pone el cursor en la esquina superior izquierda */
  
      T_BOOL  L_WIN_ClearRestOfLine ( INOUT  t_win  W ) ;
      /* - Del text between cursor position and end of line */
      /* - Borra el texto desde la posion del cursor hasta el
           final de la linea */
  
      T_BOOL  L_WIN_GetTextWin ( INOUT  t_win W, 
                                 IN     T_CHAR **ptxt, 
                                 IN     T_INT *bsize ) ;
      /* - We will have address where is kept window's contents,
           and size of memory used */
      /* - Obtenemos un puntero a la memoria donde se almacena el
           contenido de la ventana, y el taman~o de dicha memoria */
  
      T_BOOL  L_WIN_SetTextWin ( INOUT  t_win W, 
                                 IN     T_CHAR *ptxt, 
                                 IN     T_INT bsize ) ;
      /* - Let us set windows contents directly */
      /* - Fijaremos nosotros el contenido de la ventana 'a pelo' */
  
      T_BOOL  L_WIN_GetTitle ( INOUT  t_win W, 
                               IN     T_INT *TitleMode, 
                               IN     T_CHAR **Title ) ;
      /* - Let knew what title and how is it in 'W' */
      /* - Permite el titulo y modo usandose en 'W' */
  
      T_BOOL  L_WIN_SetTitle ( INOUT  t_win W, 
                               IN     T_INT TitleMode, 
                               IN     T_CHAR *Title ) ;
      /* - Set Title an Tilte Mode */
      /* - Para activar titulo y forma de presentarlo */
  
      T_BOOL  L_WIN_SetKeepTitle ( INOUT  t_win W, 
                                   IN     T_CHAR *ktitle ) ;
      /* - Let us defined what T_CHAR are used in the scrollbar that
           appeare when you use L_WIN_Keep */
      /* - Permite definir caracteres usados en la scrollbar que aparece
           al activarse keep */
  
      T_BOOL  L_WIN_GetKeepTitle ( INOUT  t_win W, 
                                   IN     T_CHAR **ktitle ) ;
      /* - Let us know what chars are been using at scrollbar */
      /* - Permite conocer los caracteres que se estan usando en
           la scrollbar */
  
      T_BOOL  L_WIN_GetInfo ( INOUT  t_win W, 
                              IN     T_INT *uplines, 
                              IN     T_INT *downlines ) ;
      /* - When you use L_WIN_Keep, 'uplines' will be the number of
           lines stored with the text that will appeare when we
           use L_WIN_ScrollDown, and viceversa ('downlines' are...) */
      /* - Permite conocer el numero de lineas que estan siendo
           almacenadas y que seran recuperadas al ir 'scroleando'
           Logicamente, si antes de escribir mas texto o desplazar
           el que hay, usamos L_WIN_Keep(W).*/
  
      T_BOOL  L_WIN_Touch  ( INOUT  t_win  W ) ;
      /* - Next time we call L_WIN_Flush, the contents of 'W' will
           be 'flushed' */
      /* - Marca 'W' para que se actualize en pantalla la proxima
           vez que se llame a L_WIN_Flush */
  

 /* ..................................................................... */

 #ifdef  __cplusplus
    }
 #endif


#endif

