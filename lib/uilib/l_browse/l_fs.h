

 #ifndef L_FS_H
 #define L_FS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_time/v_time.h"
      #include "corelib/l_adt/l_dnodo.h"
      #include "uilib/l_browse/l_wcon.h"
      #include "uilib/l_browse/l_brws1.h"
      #include "corelib/l_dir/x_dir.h"


   /* ... Const / Constantes ............................................ */

      #define c_ID_FILESYDIRS     200
      #define c_FYDP              sizeof(t_fydp)
      #define c_NAVY              c_WIS_STACK


   /* ... Tipe t_fydp ................................................... */

       typedef 
       struct {
                T_LONG     size ;
                T_LONG     ctime ;
                T_U_SHORT  attrib ;
  	      } FyDP ;

        typedef 
        struct {
                 T_INT  id_presentacion ;
                 FyDP   fyd ;
               } t_fydp ;

        typedef
        t_win_stack t_navi ;


   /* ... Functions / Funciones ......................................... */

     /* File system propieties  *
      * ----------------------- */
      t_fydp  *L_FS_CreatByDefault  ( void ) ;
      /* - */
      /* - retorna una zona de memoria pedida con malloc y a la que
           se le asigna los valores por defecto;
           el valor retornado es NULL->mal <else>->OK */
  
       T_BOOL  L_FS_Destroy     ( t_fydp **np ) ;
       /* - */
       /* - libera la memoria que se uso en L_FS_CreatByDefault */


     /* Building file entrys info *
      * ------------------------- */
      T_BOOL L_FS_ReadFydEntrys   ( INOUT t_DiNode **g,
                                   IN    T_CHAR *path,
                                   IN    T_CHAR *patron,
                                   IN    T_INT attr ) ;
      /* - */
      /* - Lee en 'g' el sistema de ficheros. Lee y almacena en 'g' los
           directorios  que esta a partir de 'path', y los ficheros que
           cumplan el patron ( ejemplo de patron: "file??__*" ) y el
           atributo especificados ( 'attrib' ) */


     /* Browsing file entrys info *
      * ------------------------- */
      void    L_FS_WrHelpNavi (t_win wh, t_DiNode *d, T_INT o) ;
      /* - */
      /* - */
      void    L_FS_NaviCoor   (T_INT sonwidth, T_INT sontall, T_INT espaciado,
                               T_INT *cx, T_INT *cy, 
                               T_INT *sx1, T_INT *sy1, T_INT *sx2,
                               T_INT *sy2, T_BOOL *keep) ;
      /* - */
      /* - */

      T_CHAR *L_FS_ReadAndPresent (T_CHAR *dir2, T_CHAR *patron,
                                    T_INT attrib, T_INT x, T_INT y) ;
      /* - */
      /* - Presenta ficheros y subdirectorios, encargandose de
           leer hasta que el usuario elija fichero */

      T_CHAR *L_FS_Present ( t_DiNode *g, T_INT x, T_INT y ) ;
      /* - */
      /* - Presenta los ficheros desde 'g', encargandose de
           navegar hasta que el usuario elija uno */
  
      t_navi  L_FS_Open         (t_DiNode *d, T_INT x, T_INT y) ;
      /* - */
      /* - */

      T_INT   L_FS_KeyProcesing (t_navi *m, T_INT tecla) ;
      /* - */
      /* - */

      void    L_FS_Close        (t_navi *) ;
      /* - */
      /* - */

      T_CHAR *L_FS_GetFileChose (t_navi m, T_CHAR *sep) ;
      /* - */
      /* - */

      T_BOOL  L_FS_PopNWins     (t_navi *m, T_INT ) ;
      /* - */
      /* - */

      void    L_FS_SetColors (t_navi , t_txt_colores , 
                               t_txt_colores , t_txt_colores ,
                               t_txt_colores , t_txt_colores , 
                               t_txt_colores , t_txt_colores , 
                               t_txt_colores , t_txt_colores , 
                               t_txt_colores , t_txt_colores , 
                               t_txt_colores , t_txt_colores , 
                               t_txt_colores , t_txt_colores , 
                               t_txt_colores ) ;
      /* - */
      /* - */

      void    L_FS_GetColors (t_navi , 
                               t_txt_colores *, t_txt_colores *,
                               t_txt_colores *, t_txt_colores *, 
                               t_txt_colores *, t_txt_colores *, 
                               t_txt_colores *, t_txt_colores *, 
                               t_txt_colores *, t_txt_colores *, 
                               t_txt_colores *, t_txt_colores *, 
                               t_txt_colores *, t_txt_colores *, 
                               t_txt_colores *, t_txt_colores *) ;
      /* - */
      /* - */

      void    L_FS_SetFrame   (t_navi m, T_CHAR *) ;
      /* - */
      /* - */

      T_CHAR *L_FS_GetFrame   (t_navi m) ;
      /* - */
      /* - */

      T_BOOL  L_FS_UnHidden   (t_navi m) ;
      /* - */
      /* - */

      T_BOOL  L_FS_Hidden     (t_navi m) ;
      /* - */
      /* - */

      T_CHAR *L_FS_GetFileChose (t_win_stack m, T_CHAR *sep) ;
      /* - */
      /* - */

      T_CHAR *L_FS_GetTHEOption (t_win_stack m) ;
      /* - */
      /* - */



   /* ... Inline ........................................................ */

      #define L_FS_Open(d,x,y)         (t_navi)L_BRWS1_OpenStack(d,x,y,L_FS_WrHelpNavi,L_FS_NaviCoor)
      #define L_FS_KeyProcesing(m,t)   L_BRWS1_KeyProcesing(m,t)
      #define L_FS_Close(m)            L_BRWS1_CloseStack(m)
      #define L_FS_PopNWins(m,s)       L_BRWS1_PopNWins(m,s)
      #define L_FS_SetFrame(m,f)       L_BRWS1_SetFrame(m,f)
      #define L_FS_GetFrame(m)         L_BRWS1_GetFrame(m)
      #define L_FS_UnHidden(m)         L_BRWS1_UnHidden(m)
      #define L_FS_Hidden(m)           L_BRWS1_Hidden(m)
      #define L_FS_SetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)   L_BRWS1_SetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)
      #define L_FS_GetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)   L_BRWS1_GetColors(m,wback,wbback,fwback,fwbback,wfore,wbfore,fwfore,fwbfore,sback,sfore,sbback,sbfore,hback,hbback,hfore,hbfore)
      #define L_FS_GetFileChose(m,s)   L_BRWS1_GetOptionsName(m,s)
      #define L_FS_GetTHEOption(m)     L_BRWS1_GetTHEOption(m)


   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

