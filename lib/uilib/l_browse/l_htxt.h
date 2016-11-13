

 #ifndef L_HTXT_H
 #define L_HTXT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_adt/l_dnodo.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/l_ftoken.h"
      #include "corelib/l_string/l_fchset.h"
      #include "corelib/l_string/x_string.h"
      #include "uilib/l_gadget/l_sttbox.h"
      #include "uilib/l_browse/l_wcon.h"
      #include "uilib/l_browse/l_brws1.h"


   /* ... Const / Constantes ............................................ */

      #define c_ID_HIPERTXT     150

      #define c_HTXTP             sizeof(t_htxtp)
      #define c_HTXTSINTAX        sizeof(t_menusintax)
      #define c_INFONODE          sizeof(t_infonodo)
      #define c_HTXT              sizeof(t_htext_descriptor)

      #define c_HTXT_NOMEM              0
      #define c_HTXT_OK                 1
      #define c_HTXT_FALL               2      

      #define c_DCOORDENATESX1              5
      #define c_DCOORDENATESY1              4
      #define c_DCOORDENATESX2             75
      #define c_DCOORDENATESY2             21

      /* ... Messages ... */
      #define LHTXT_NO_END      "No leo fin de hypertext."


   /* ... Types / Tipos .......................................... */

       typedef 
       struct {
                T_INT idlink ; /* offset en htxt, del nombre del nodo */
                T_CHAR *linkref ;
              } t_infonodo ;

       typedef 
       struct {
                T_CHAR       *htxt ;
                T_U_INT       ntxt ;
  		t_infonodo  **ilinks ;
                T_U_INT       nlinks ;
                T_INT         px1, py1, px2, py2 ;
  	      } HTxtP ;

        typedef 
        struct {
                 T_INT        id_presentacion ;
                 HTxtP        Htxt ;
               } t_htxtp ;


      typedef
      struct {
                T_CHAR *HtxtName, *HtxtBegin,
                       *HtxtEnd,    *LinkName,  *HtxtCoor ;
                T_CHAR *Delimitadores ;
                T_BOOL  CaseSensitive ; /* UPPER/lower */
             } t_htxtsintax ;


     typedef 
     struct {
               t_win   w, ws ;
               T_U_INT x1,y1,x2,y2 ;
               T_U_INT linkopcion, totallinks ;
               t_txt_colores wback, wfore, wfback, wffore,
                                    wsback, wsfore, wsfback, wsffore ;
               t_DiNode *d ; 
            } t_htext_descriptor ;
     typedef 
     t_htext_descriptor *t_htext ;


   /* ... Functions / Funciones .................................. */

      /* HyperText propieties * 
       * -------------------- */
       t_htxtp *L_HTXT_CreatByDefault ( void ) ;
       /* - */
       /* - Retorna una zona de memoria pedida con 
            malloc y a la que se le asigna los valores 
            por defecto; el valor retornado es 
            NULL->mal <else>->OK */
  
       T_BOOL L_HTXT_Destroy ( INOUT t_htxtp **np ) ;
       /* - */
       /* - Libera la memoria que se uso en L_HTXT_CreatByDefault */
  
       T_BOOL  L_HTXT_SetHtxt ( t_htxtp *, HTxtP * ) ;
       /* - */
       /* - */

       T_BOOL  L_HTXT_GetHtxt ( t_htxtp *, INOUT HTxtP * ) ;
       /* - */
       /* - */


      /* building hypertext ... *           
       * ------------------------ */         
       T_BOOL L_HTXT_ReadHtxt      ( INOUT t_DiNode     **g, 
				    IN    t_htxtsintax  *s,
			            INOUT FILE          *fd ) ;
       /* - */
       /* - Lee en 'g' el hipertexto que esta en el fichero 'fd'    
	    a partir de su posicion actual, usando 's' como la 
	    sintaxis que define a ese hipertexto. */
    
       T_BOOL L_HTXT_ReadHtxtNode  ( INOUT t_DiNode      **g, 
				    IN    t_htxtsintax   *s,
				    INOUT FILE           *fd ) ;
       /* - */
       /* - Lee en 'g' un nodo del hipertexto que esta en el 
	    fichero 'fd' a partir de su posicion actual, 
	    usando 's' como la sintaxis que define a ese hipertexto. */ 

       T_BOOL L_HTXT_ReadHtxtNodes ( INOUT  t_DiNode      **g,
                                    IN     t_htxtsintax   *s,
                                    INOUT  FILE           *f ) ;
       /* - */
       /* - Lee en 'g' el hipertexto que esta en el fichero 'fd'
            a partir de su posicion actual, usando 's' como la
            sintaxis que define a ese hipertexto. 
            Si hay referencias a nodos inexistentes, NO indica
            error, solo las deja "suspendidas". */

       T_BOOL L_HTXT_DestroyHtxt ( INOUT t_DiNode      **g ) ;
       /* - */
       /* - Libera toda la menoria */

    
      /* browsing hypertext ... *           
       * ------------------------ */         
       T_INT     L_HTXT_ReadAndPresent ( INOUT FILE         *f, 
					  IN    t_htxtsintax  s ) ;
       /* - */
       /* - Presenta hypertexto desde fichero, hasta que el
            usuario quiera (de a escape) */
                               
       T_INT     L_HTXT_Present        ( IN t_DiNode *g ) ;
       /* - */
       /* - Presenta hypertexto, hasta que el usuario quiera
            (de a escape) */
      
       t_htext   L_HTXT_Open              (t_DiNode *) ;
       T_INT     L_HTXT_KeyProcesing      (t_htext *, T_INT) ;
       void      L_HTXT_Close             (t_htext *) ;
       T_INT     L_HTXT_GetSelectNode     (IN t_htext hx) ;
       T_CHAR   *L_HTXT_GetSelectNodeName (IN t_htext hx) ;
       void      L_HTXT_SetFrame          (t_htext hx, T_CHAR *frame) ;
       T_CHAR   *L_HTXT_GetFrame          (t_htext hx) ;
       T_BOOL    L_HTXT_UnHidden          (t_htext hx) ;  
       T_BOOL    L_HTXT_Hidden            (t_htext hx) ;
       void      L_HTXT_SetColors  (t_htext hx,       
                                     t_txt_colores wback, 
                                     t_txt_colores wfore,
                                     t_txt_colores fwback, 
                                     t_txt_colores fwfore,
                                     t_txt_colores wsback, 
                                     t_txt_colores wsfore,
                                     t_txt_colores wsfback, 
                                     t_txt_colores wsffore) ;          
       void      L_HTXT_GetColors  (t_htext hx,
                                     t_txt_colores *wback, 
                                     t_txt_colores *wfore,
                                     t_txt_colores *fwback, 
                                     t_txt_colores *fwfore,
                                     t_txt_colores *wsback, 
                                     t_txt_colores *wsfore,
                                     t_txt_colores *wsfback, 
                                     t_txt_colores *wsffore) ;        
  

   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

