

 #ifndef L_MENU_H
 #define L_MENU_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_adt/l_dnodo.h"
      #include "uilib/l_browse/l_wcon.h"
      #include "uilib/l_browse/l_brws1.h"


   /* ... Const / Constantes ............................................ */

      #define c_ID_MENU         100

      #define c_MENUP           sizeof(t_menup)
      #define c_MENUSINTAX      sizeof(t_menusintax)
      #define c_MENU            c_WIS_STACK

      /* ... Messages ... */
      #define LMENU_NO_BEGIN    "no leo id de comienzo enumeracion de hijos"
      #define LMENU_NO_END      "No leo fin de menu."


   /* ... Types / Tipos ................................................. */

       typedef
       struct {
		T_CHAR *help;
	      } MenuP ;

	typedef
	struct {
                 T_INT        id_presentacion ;
                 MenuP        Mnu ;
               } t_menup ;


      typedef
      struct {
                T_CHAR *MenuName,*MenuHelp,
                       *MenuBegin,*MenuEnd ;
                T_CHAR *Delimitadores ;
                T_BOOL  CaseSensitive ; /* UPPER/lower */
             } t_menusintax ;

      typedef
      t_win_stack t_menu ;


   /* ... Functions / Funciones ......................................... */

      /* Menu propieties  *
       * ---------------- */
       t_menup *L_MENU_CreatByDefault ( void ) ;
       /* - */
       /* - Retorna una zona de memoria pedida con malloc y a la que se
	    le asigna los valores por defecto;
	    el valor retornado es NULL->mal <else>->OK */

       T_BOOL L_MENU_Destroy ( t_menup **np ) ;
       /* - */
       /* - Libera la memoria que se uso en L_MENU_CreatByDefault */


      /* building menus ... *
       * ------------------ */
       T_LONG L_MENU_ReadMenu ( INOUT t_DiNode      **g,
			       IN    t_menusintax   *s,
			       IN    FILE           *fd ) ;
       /* - */
       /* - Lee en 'g' el menu que esta en el fichero 'fd' a partir
	    de su posicion actual, usando 's' como la sintaxis que
	    define a ese menu. */

       T_BOOL L_MENU_DestroyMenu ( INOUT t_DiNode      **g ) ;
       /* - */
       /* - Libera toda memoria consumida para leer el menu. */


      /* browsing menus ... *
       * ------------------ */
       void  L_MENU_WrHelpMenu ( t_win wh, 
				 t_DiNode *d, 
				 T_INT o) ;
       /* - */
       /* - Sera la rutina usada para escribir la ayuda en 
            la 'barrita' que sale abajo en la pantalla */
   
       void  L_MENU_MenuCoor   ( T_INT sonwidth, T_INT sontall, 
				 T_INT espaciado,
				 T_INT *cx, T_INT *cy, 
				 T_INT *sx1, T_INT *sy1, T_INT *sx2, T_INT *sy2, 
				 T_BOOL *keep ) ;
       /* - */
       /* - Rutina que calcula las coordenadas mas adecuadas 
	    para poner las ventanas con las opciones de los menus */
   
       T_INT   *L_MENU_Present ( t_DiNode *g, T_INT x, T_INT y ) ;
       /* - */
       /* - Presenta las opciones de un menu, encargandose de 
	    navegar hasta que el usuario elija una */
   
       T_INT   *L_MENU_ReadAndPresent ( INOUT  FILE *f, 
					 IN     t_menusintax s,
                                         T_INT x, T_INT y ) ;
       /* - */
       /* - Presenta menu desde fichero, hasta que el usuario 
	    elija una opcion de trabajo */
   
       t_menu  L_MENU_Open (t_DiNode *, T_INT x, T_INT y) ;
       /* - */
       /* - Abre un menu, mostrando las primeras opciones  
	    en pantalla, situando la ventana en (x,y) a ser posible */
   
       T_INT     L_MENU_KeyProcesing (t_menu *m, T_INT key) ;
       /* - */
       /* - Le pasa al menu una tecla para que realize la 
	    operacion asociada (no hara nada si no es una tecla 
	    asociada a una operacion) */
   
       void    L_MENU_Close ( INOUT t_menu *m ) ;
       /* - */
       /* Cierra las ventanas y libera los recursos usados por
          el menu */
   
       T_INT    *L_MENU_GetOptionsNumber (t_win_stack m) ;
       /* - */
       /* Genera un 'array dinamico' que termina en el entero cero.
          el elemento i-esimo es el numero de opcion de opcion
          elegida en la i-esima ventanas con opciones. Si el primer
          elemento es cero, es que el usuario quiere cerrar el menu.
          Pide memoria, que luego tendras que liberar. */
   
       T_CHAR   *L_MENU_GetOptionsName (t_menu m, T_CHAR *sep) ;
       /* - */
       /* Genera un string que es el resultado de concatenar los
          nombres de las opciones elegidas, usando 'sep' como
          separador de las opciones.
          Pide memoria, que luego tendras que liberar */
   
       t_DiNode  *L_MENU_GetTHEOption (t_menu m) ;
       /* - */
       /* Retorna el nodo que actualmente se esta presentando */
   
       T_BOOL    L_MENU_PopNWins   ( t_menu *m, T_INT s ) ;
       /* - */
       /* - */

       void      L_MENU_SetColors ( t_menu , 
                                     IN      t_txt_colores, t_txt_colores,
                                     IN      t_txt_colores, t_txt_colores, 
                                     IN      t_txt_colores, t_txt_colores, 
                                     IN      t_txt_colores, t_txt_colores,
   			             IN      t_txt_colores, t_txt_colores,
                                     IN      t_txt_colores, t_txt_colores, 
                                     IN      t_txt_colores, t_txt_colores,
   			             IN      t_txt_colores, t_txt_colores ) ;
       /* - */
       /* - */

       void      L_MENU_GetColors ( t_menu , 
                                     IN      t_txt_colores *, t_txt_colores *,
   	  		             IN      t_txt_colores *, t_txt_colores *,
                                     IN      t_txt_colores *, t_txt_colores *,
                                     IN      t_txt_colores *, t_txt_colores *,
   			             IN      t_txt_colores *, t_txt_colores *, 
                                     IN      t_txt_colores *, t_txt_colores *,
                                     IN      t_txt_colores *, t_txt_colores *,
   			             IN      t_txt_colores *, t_txt_colores *) ;
       /* - */
       /* - */

       void      L_MENU_SetFrame   ( t_menu , T_CHAR * ) ;
       /* - */
       /* - */

       T_CHAR   *L_MENU_GetFrame   ( t_menu ) ;
       /* - */
       /* - */

       T_BOOL    L_MENU_UnHidden   ( t_menu ) ;
       /* - */
       /* - */

       T_BOOL    L_MENU_Hidden     ( t_menu ) ;
       /* - */
       /* - */

   
   /* ... Inline ........................................................ */

      #define L_MENU_Open(d,x,y)     (t_menu)L_BRWS1_OpenStack(d,x,y,L_MENU_WrHelpMenu,L_MENU_MenuCoor)
      #define L_MENU_KeyProcesing(m,t)     L_BRWS1_KeyProcesing(m,t)
      #define L_MENU_Close(m)         L_BRWS1_CloseStack(m)
      #define L_MENU_PopNWins(m,s)    L_BRWS1_PopNWins(m,s)
      #define L_MENU_SetFrame(m,f)    L_BRWS1_SetFrame(m,f)
      #define L_MENU_GetFrame(m)      L_BRWS1_GetFrame(m)
      #define L_MENU_UnHidden(m)      L_BRWS1_UnHidden(m)
      #define L_MENU_Hidden(m)        L_BRWS1_Hidden(m)
      #define L_MENU_SetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)   L_BRWS1_SetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)
      #define L_MENU_GetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)   L_BRWS1_GetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)
      #define L_MENU_GetOptionsNumber(m)  L_BRWS1_GetOptionsNumber(m)
      #define L_MENU_GetOptionsName(m,s)  L_BRWS1_GetOptionsName(m,s)
      #define L_MENU_GetTHEOption(m)      L_BRWS1_GetTHEOption(m)


   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

