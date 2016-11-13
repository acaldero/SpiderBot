

 #ifndef L_UI_H
 #define L_UI_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "uilib/l_browse/l_brws1.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct {
               t_win   w ;
               T_LONG  total ;
               T_INT   x1, y1, width ;
             } t_pbar ;


   /* ... Const / Constantes ............................................ */
    
      #if defined(__COOL__)
        #define c_PBT_CHAR                  "²"
      #else
        #define c_PBT_CHAR                  "X"
      #endif


   /* ... Functions / Funciones ......................................... */

     T_BOOL L_UI_OpenPB ( INOUT  t_pbar *vpb,
                          IN     T_CHAR *title,
                          IN     T_INT   x,
                          IN     T_INT   y,
                          IN     T_INT   width,
                          IN     T_LONG  total ) ;
     /* - Open a window within a 'percent bar' */
     /* - Abre la ventana que contendra una 'barra de porcentaje' */

     T_BOOL L_UI_ProcesingPB ( INOUT t_pbar *vpb,
                               IN T_LONG current ) ;
     /* - Update information */
     /* - Actualiza la informacion 'estadistica' */

     T_BOOL L_UI_ClosePB ( INOUT t_pbar *vpb ) ;
     /* - Close our 'percent bar' */
     /* - Cierra la ventana que contendra una 'barra de porcentaje' */

     T_BOOL L_UI_AjustPB  ( INOUT t_pbar  *vpb,
                            IN    T_LONG   ntotal ) ;
     /* - Ajust to new total */
     /* - Ajusta el total a 'ntotal' */


   /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

