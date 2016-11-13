

 #ifndef L_BRWS1_H
 #define L_BRWS1_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_adt/l_dnodo.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/x_string.h"
      #include "uilib/l_wterm/l_win.h"


   /* ... Types / Tipos ................................................. */

      typedef 
      struct {
		t_DiNode *d ;
		t_win wframe,wmain,wselect,whelp ;
                T_INT opcion, totalopcion ;
                T_INT fopcion, copcion, sfopcion  ;
                T_INT xoffwin, yoffwin, upfopcion ;
                T_INT widthopcion ;
	     } t_eltos ;

      typedef 
      struct {
		 t_eltos **s ;
                 T_INT neltos ;
		 t_txt_colores wback,wfore,sback,sfore,hback,
			       hfore,sbback,sbfore,wbback,wbfore,
			       hbback,hbfore,fwback,fwfore,fwbback,
			       fwbfore ;
                 T_CHAR *frame ;
                 void (*WrHelp)(t_win ,t_DiNode *,T_INT) ;
                 void (*CalCoor)(T_INT,T_INT,T_INT,T_INT *,T_INT *,T_INT *,
                                 T_INT *,T_INT *,T_INT *,T_BOOL *) ;
	     } t_stack_descriptor ;

    typedef 
    t_stack_descriptor *t_win_stack ;


   /* ... Const / Constantes ............................................ */
    
      #define c_HELP_X1  (2)
      #define c_HELP_Y1  (V_TERM_cmaxY()-2)
      #define c_HELP_X2  (V_TERM_cmaxX()-1)
      #define c_HELP_Y2  (V_TERM_cmaxY())
    
      #define c_WIS_ELTOS  (sizeof(t_eltos))
      #define c_WIS_STACK  (sizeof(t_stack_descriptor))
      #define c_SEP_T_INT    1
    
      /* key_procesing ... */
      #define c_ERROR      -1
      #define c_KEYPROC     0
      #define c_CHOSE       1
      #define c_CLOSE       2
    

   /* ... Functions / Funciones ......................................... */

    t_win_stack L_BRWS1_OpenStack (t_DiNode *, T_INT , T_INT ,
                                   void (*)(t_win ,t_DiNode *,T_INT),
                                   void (*)(T_INT,T_INT,T_INT,T_INT *,T_INT *,T_INT *,
                                   T_INT *,T_INT *,T_INT *,T_BOOL *)) ;
    /* - Return a 'stack windows' descriptor */
    /* - Retorna un descriptor de 'pila de ventanas' */

    T_INT L_BRWS1_KeyProcesing (t_win_stack *ws, 
                                T_INT key) ;
    /* - ws 'stack windows' process 'key', and
         do what this key means (open other 
         windows -push-, move selector, etc */
    /* - Se le pasa a la 'pila de ventanas' una tecla 
         para que actue en consecuencia (abrir otra 
         ventana -push-, mover selector, ... */

    void L_BRWS1_CloseStack (INOUT t_win_stack *ws) ;
    /* - Free resources and close 'stack windows' ws */
    /* - Libera memoria y otros recursos que 
         poseia la 'pila de ventanas' */

    T_INT *L_BRWS1_GetOptionsNumber (t_win_stack) ;
    /* - */
    /* - Retorna una lista de enteros que son las 
         opciones de las ventanas
         'apiladas' que se han ido seleccionando */

    T_CHAR *L_BRWS1_GetOptionsName (t_win_stack, T_CHAR *sep) ;
    /* - */
    /* - Retorna la lista de los nombres de las opciones 
         de las ventanas 'apiladas' que se han ido seleccionando, 
         usando el string 'sep' como separador de esos nombres.
         OJO: pide memoria a malloc para que quepa, memoria que el
         usuario debera liberar con un simple free. */

    t_DiNode *L_BRWS1_GetTHEOption (t_win_stack) ;
    /* - */
    /* - Retorna el 'nodo' que se esta representando 
         en la actual ventana */

    T_BOOL L_BRWS1_PopNWins   (t_win_stack *, T_INT) ;
    /* - */
    /* - Quita las 'N' ventanas de encima de la pila, 
         cerrandolas */

    void L_BRWS1_SetColors (t_win_stack, t_txt_colores , t_txt_colores ,
			    t_txt_colores, t_txt_colores, t_txt_colores,
			    t_txt_colores, t_txt_colores, t_txt_colores,
			    t_txt_colores, t_txt_colores, t_txt_colores,
			    t_txt_colores, t_txt_colores, t_txt_colores,
			    t_txt_colores, t_txt_colores) ;
    /* - */
    /* - Fija los colores a usar el la 'pila de ventanas' */

    void L_BRWS1_GetColors (t_win_stack m,
			    t_txt_colores *wback, t_txt_colores *wbback,
			    t_txt_colores *fwback, t_txt_colores *fwbback,
			    t_txt_colores *wfore, t_txt_colores *wbfore,
			    t_txt_colores *fwfore, t_txt_colores *fwbfore,
			    t_txt_colores *sback, t_txt_colores *sfore,
			    t_txt_colores *sbback, t_txt_colores *sbfore,
			    t_txt_colores *hback, t_txt_colores *hbback,
			    t_txt_colores *hfore, t_txt_colores *hbfore ) ;
    /* - */
    /* - Obtiene los colores usados el la 'pila de ventanas' */

    void L_BRWS1_SetFrame (t_win_stack m, T_CHAR *frame) ;
    /* - */
    /* - Fija el 'marco' de las ventanas a usar el 
         la 'pila de ventanas' */

    T_CHAR *L_BRWS1_GetFrame (t_win_stack m) ;
    /* - */
    /* - Obtiene el 'marco' de las ventanas que se esta usando
         el la 'pila de ventanas' */

    T_BOOL L_BRWS1_UnHidden (t_win_stack m) ;
    /* - */
    /* - Desoculta todas las ventanas de la pila */

    T_BOOL L_BRWS1_Hidden   (t_win_stack m) ;
    /* - */
    /* - Oculta todas las ventanas de la pila */


   /*........................................................................*/


 #ifdef  __cplusplus
    }
 #endif

#endif

