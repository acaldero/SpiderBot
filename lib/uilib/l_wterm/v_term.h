

 #ifndef V_TERM_H
 #define V_TERM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_uicfg/c_uicfg.h"


   /* ... Types / Tipos ................................................. */
  
       typedef 
       struct {
                /* --- Video section --- */
                   T_INT currmode ;           /* BW40, C80, ... */
                   T_INT cfilas, ccolumnas ;  /* dim. en caracteres */
                   T_INT rvertical, rhorizontal ; /* dim. en pixels */
                   T_INT charheight, charwidth  ; /* dim. char en pixels */
                   T_INT ncolores ;               /* numero de colores */
                   T_INT GestorVideo ;
                /* --- Keyboard section --- */
                   T_INT GestorTeclado ;
                                                  } t_TermState ;
       /* - NOTE:
          coordenates are between [0..(dim. - 1)] ...
          ... And color between   [0..(ncolores-1)] */
       /* NOTA:
          Las coordenadas se mueven entre [0..(dim. - 1)] ...
          ... Y los colores tambien entre [0..(ncolores-1)] */
  
       typedef T_CHAR t_pal16  [48] ;
       typedef T_CHAR t_pal256 [768] ;
       typedef T_INT  t_color ;
       typedef T_INT  t_txt_colores ;
  
  
    /* ... Glob. var / Var. global ....................................... */
  
       extern t_TermState VS ;

      
    /* ... Functions / Funciones ......................................... */
  
      t_TermState *V_TERM_get_profile ( void ) ;
      /* - NOT needed free return pointer
           This function Autodetect current configuration +
           store it in VS + ret VS's address */
      /* - NO hay que hacer free del puntero.
           Realiza varias cosas :
           Autodetecta configuracion + La guarda en VS + ret direccion a VS */
  
      T_INT   V_TERM_Configur  ( T_INT newcfg ) ;
      /* Cambia el gestor que implementa las funciones que a continuacion
         se comentan.
         ( Ver en la Seccion constantes los gestores disponibles ) */
  
  
      /* Gestion del Buffer I/O ... *
       * -------------------------- */
      long  V_TERM_GetSizeObuff ( void ) ;
      /* - Return size of current i/o buffer */
      /* - Retorna el espacio de memoria actualmente usado para
           buffer de salida a la pantalla */
  
      void  V_TERM_FreeObuff ( void ) ;
      /* - Free memory used in i/o buffer */
      /* - Libera el espacio de memoria usado para buffer de salida.
           Es de lo ultimo que ejecuta l_win en L_WIN_CloseSystem */
  
      T_CHAR *V_TERM_MallocObuff ( T_INT size ) ;
      /* - Change i/o buffer size */
      /* - Cambia el taman~o del buffer de salida a size */
  
  
      /* Funciones Video ... *
       * ------------------- */
      T_BOOL  V_TERM_cdump ( T_CHAR *scr, T_CHAR *attr,
                           T_INT with, T_INT tall,
                           T_INT ax1, T_INT ay1, T_INT ax2, T_INT ay2 ) ;
      /* - In 'scr' and 'attr' we will found a 
           "char[tall][with]". In scr are raw char, and
           in attr are char attribs.
           V_TERM_cdump will dump only a window with
           'ax1, ay1...' as coordenates. */
      /* - En scr esta una 'matriz' de caracteres y en 
           attr una 'matriz' de atributos que en una pantalla 
           de ancho 'with' y alto 'tall' seran volcados. 
           Los 'ax1, ay1...' son las coordenadas de la zona de 
           esos arrays a volcar */
  
      void  V_TERM_clrscr   ( void ) ;
      /* - Clear Screen */
      /* - Borra toda la pantalla */
  
      T_INT   V_TERM_cmaxX    ( void ) ;
      /* - Screen width */
      /* - Ancho de la pantalla en 'caracteres', es decir, 
           el numero de caracteres maximo que podemos 
           escribir en una linea */
  
      T_INT   V_TERM_cmaxY    ( void ) ;
      /* - Screen tall */
      /* - Alto de la pantalla en 'caracteres', es decir, 
           el numero de caracteres maximo que podemos 
           escribir en una columna */
  
      void  V_TERM_cgotoxy  ( T_INT x, T_INT y ) ;
      /* - Put cursor at (x,y) */
      /* - Situa el cursor en las coordenadas (x,y), 
           lugar donde se comienzan a poner los caracteres 
           que se escriban a continuacion (x,y) vienen dados 
           en 'caracteres', NO en pixels */
  
      void  V_TERM_cwherexy ( T_INT *x, T_INT *y ) ;
      /* - Store at (*x,*y) where is cursor.
           No portable function. */
      /* - No da la referencia de donde esta el cursor.
           No esta disponible en todos los 'gestores' de video, Ojo.
           (x,y) tambien vienen dados en 'caracteres', NO en pixels */
  
      T_BOOL  V_TERM_cursor_off ( void ) ;
      /* - Hide cursor from screen */
      /* - Quita el cursor de la pantalla. 
           Si ya habia desaparecido, no pasa nada. 
           Para restaurar, usar V_TERM_cursor_on */
  
      T_BOOL  V_TERM_cursor_on  ( void ) ;
      /* - Unhide cursor from screen */
      /* - Pone el cursor el la pantalla. 
           Si ya estaba, no pasa nada */
  
      T_BOOL  V_TERM_set_cursor ( T_INT lini, T_INT lfin ) ;
      /* - Set cursor size.
           No portable function. */
      /* - Define como de ancho quieres el cursor.
           No disponible en todos los 'gestores' */
  
  
      /* Funciones Teclado ... *
       * --------------------- */
      T_CHAR  V_TERM_getch   ( void ) ;
      /* - Return a char WITHOUT echoing */
      /* - Retorna un caracter SIN echo.
           NOTA: Todas estas funciones leen caracteres 'crudos' 
	   hay teclas (F1, F2, Inicio,...) que se leen como 
	   una secuencia de caracteres especiales. 
	   Si lo que te interesa es leer a nivel de teclas 
	   no de caracteres, mira en v_keymap.h */
  
      T_BOOL  V_TERM_nbgetch ( INOUT T_CHAR *ch ) ;
      /* - Check if char is present at input.
           if is char, store it at '*ch' and return TRUE.
           else, return FALSE */
      /* - Mira si hay un caracter a la entrada.
           Si lo hay, lo coloca en ch y retorna TRUE.
           Si NO hay, retorna FALSE y en ch hay 'basura' */
  
      T_BOOL  V_TERM_kbhit   ( void ) ;
      /* - return TRUE if are char at input */
      /* - Retorna si hay algun caracter esperando
           en el buffer de entrada */
  
  
   /* ... Const / Constantes ............................................ */
  
      /* ... mensajes ... */
      #define VTERM_UNKNOW_VIDEO    "Gestor de video NO valido."
      #define VTERM_UNKNOW_KEYB     "Gestor de teclado NO valido."
      #define VTERM_NO_CODE         "NO code for this method."
  
      /* ... term by default ... */
      #if ( defined(__MSDOS__) || defined(__LINUX__) )
            #define _DEFAULT_MONITOR_    \
                    { 0,25,80,25,80,1,1, 16,__MVIDEO__,__MTECLADO__ }
      #else
            #define _DEFAULT_MONITOR_    \
                    { 0,24,80,25,80,1,1, 16,__MVIDEO__,__MTECLADO__ }
      #endif

  
      /* ... tratamientos teclado ... */
      #define c_PCKB         200
      #define c_VTKB         210
      #define c_CURSESKB     220
  
      /* ... tratamientos video   ... */
      #define c_CONIO        100
      #define c_BC_INT10     110
      #define c_BC_GTEXT     120
      #define c_ESC_CMD      140
      #define c_xCURSES      150
      #define c_ZGTXT        160
  
      /* ... ctes colores texto   ... */
      #define c_Black          0 
      #define c_Blue           1 
      #define c_Green          2 
      #define c_Cyan           3 
      #define c_Red            4 
      #define c_Magneta        5 
      #define c_Brown          6 
      #define c_LightGray      7 
      #define c_DarkGray       8 
      /* NO permitidos como Background en dos..., parpadean */
      #define c_LightBlue      9 
      #define c_LightGreen     10 
      #define c_LightCyan      11 
      #define c_LightRed       12 
      #define c_LightMagneta   13 
      #define c_Yellow         14 
      #define c_White          15
  
  
   /* ................................................................... */

  
 #ifdef  __cplusplus
    }
 #endif

 #endif
