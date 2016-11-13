

 #ifndef L_DNODE_H
 #define L_DNODE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_adt/l_dstack.h"
      #include "corelib/l_string/x_string.h"


   /* ... Const / Constantes ............................................ */

      #define c_DINODE            sizeof(struct t_DiNode_Descriptor)
      #define c_STATNODE          sizeof(t_StatNode)
 
  
   /* ... Tipo Grafo .................................................... */

     typedef struct t_DiNode_Descriptor t_DiNode ;
     struct  t_DiNode_Descriptor
	     {
	       T_CHAR      *nombre ;
	       T_U_LONG     NSons ;
	       t_DiNode   **hijos ;
	       T_U_LONG     NFathers ;
	       t_DiNode   **padres ;
	       T_POINTER    propiedades ;
	       T_INT        TMP ;
	     } ;

     typedef
     struct {
	      T_U_LONG nhijos ;
	      T_U_LONG npadres ;
	    } t_StatNode  ;

     /* Funciones para el manejo de grafos *
      *	---------------------------------- */
     T_BOOL    L_GRAFO_NewFatherLink (t_DiNode *, t_DiNode *) ;
     /* - Relaciona dos nodos como padre e hijo */

     T_BOOL    L_GRAFO_UnLinkFather (t_DiNode *, t_DiNode *) ;
     /* - Desliga padre de hijo, hijo de padre */

     T_BOOL    L_GRAFO_FreeKill    ( t_DiNode **nodo,
				     T_BOOL   (*FreePropiedades)(T_POINTER *) ) ;
     /* - Borra todo nodo accesible desde nodo! (el sus hijos ...etc) */

     t_DiNode *L_GRAFO_NewNode (void) ;
     /* - Crea un nodo, todo a cero/NULL, mallocating */

     T_BOOL    L_GRAFO_NewSonLink (t_DiNode *, t_DiNode *) ;
     /* - Relaciona dos nodos como padre e hijo */

     t_DiNode *L_GRAFO_NewSon (t_DiNode *) ;
     /* - Algo asi como  NewSonLink(padre,(nn=NewNode)) ->nn */

     t_DiNode *L_GRAFO_NewFather (t_DiNode *) ;
     /* - NewFatherLink(hijo,(nn=NewNode)) -> nn */

     T_BOOL    L_GRAFO_UnLinkSon (t_DiNode *, t_DiNode *) ;
     /* - Desliga padre de hijo, hijo de padre */

     T_BOOL    L_GRAFO_UnLinkAllFathers (t_DiNode *) ;
     /* - Borra las 'ligaduras' de todos sus padres, informandolos */

     T_BOOL    L_GRAFO_UnLinkAllSon (t_DiNode *) ;
     /* - Idem anterior adaptandola, of cuz */

     void    L_GRAFO_pFreeNode ( t_DiNode **nodo,
				 T_BOOL   (*FreePropiedades)(T_POINTER *),
				 t_DiNode ***tabla ) ;
     /* - Borra un nodo, poniendo sus hijos que no tengan otros
	  padres, es decir, otra forma de llegar a ellos, en tabla! */

     t_DiNode **L_GRAFO_fFreeNode ( t_DiNode **nodo,
				    T_BOOL   (*FreePropiedades)(T_POINTER *) ) ;
     /* - Igual que la anterior, pero en lugar de 'darnos' la tabla como
	  parametro de salida, nos lo da como 'return' de la funcion */

     T_BOOL    L_GRAFO_FullFreeNode ( t_DiNode **nodo,
				      T_BOOL   (*FreePropiedades)(T_POINTER *) ) ;
     /* - A usar por FreeKill */

     t_DiNode **L_GRAFO_FreeSubSetNodes ( t_DiNode ***tabla,
					  T_BOOL   (*FreePropiedades)(T_POINTER *),
					  ... ) ;
     /* - Igual que FreeNodeIncondicional, pero permite pasarle
	  varios nodos. En tabla se concatenan sus hijos huerfanos */

     T_CHAR   *L_GRAFO_GetName (t_DiNode *) ;
     /* - Optiene el nombre de un nodo */

     T_BOOL    L_GRAFO_SetName (t_DiNode *, T_CHAR *) ;
     /* - Fija el nombre de un nodo */

     T_U_LONG  L_GRAFO_GetNSons (t_DiNode *) ;
     /* - Pregunta por el numero de hijos de un nodo */

     T_U_LONG  L_GRAFO_GetNFathers (t_DiNode *) ;
     /* - Pregunta por el numero de padres de un nodo */

     T_POINTER  L_GRAFO_GetNodePropiedades (t_DiNode *) ;
     /* - Obtiene las 'propiedades' de un nodo */

     T_BOOL    L_GRAFO_SetNodePropiedades (t_DiNode *, T_POINTER) ;
     /* - El nodo 'memoriza' sus propiedades */

     t_DiNode *L_GRAFO_GetSonN (T_INT ,t_DiNode *) ;
     /* - Obtiene un puntero al hijo orden-esimo del nodo 'padre' */

     t_DiNode *L_GRAFO_GetFatherN (T_INT ,t_DiNode *) ;
     /* - Obtiene un puntero al padre orden-esimo del nodo 'hijo' */

     t_DiNode *L_GRAFO_GetSonName (T_CHAR *,t_DiNode *) ;
     /* - Obtiene un puntero al hijo de nombre 'name_nodo' del
	  nodo 'padre' */

     t_DiNode *L_GRAFO_GetFatherName (T_CHAR *,t_DiNode *) ;
     /* - Obtiene un puntero al padre de nombre 'name_nodo' del
	  nodo 'hijo' */

     T_BOOL    L_GRAFO_OperOverGraf(t_DiNode **, T_BOOL (*)(t_DiNode **n)) ;
     /* - Meta funcion (funcion de funciones) que permite la
	ejecucion de FTN (Funcion Tratamiento Nodes) en todos
	los nodos accesibles desde nodo */

     void    L_GRAFO_SetCoherencia (t_DiNode *) ;
     /* un DiskFix/NDD/ScanDisk para grafos ... ;-) */

     void    L_GRAFO_GetEstadistica (t_DiNode *,t_StatNode *) ;
     /* en stat, debe dejar datos sobre dimensiones del grafo ...
        lugar donde guardar estadisticas del grafo :

	 typedef struct {
                          T_INT nhijos ;
                          T_INT npadres ;
			} t_StatNode  ; */


     #define L_GRAFO_NewFatherLink(h,p)   L_GRAFO_NewSonLink(p,h)
     #define L_GRAFO_UnLinkFather(p,h)    L_GRAFO_UnLinkSon(p,h)


  /* ... Tipo PILA (de nodos) .............................................. */

     typedef
     struct Elto  *t_pila ;

     struct  Elto
     {
       t_DiNode  *elemento ;
       t_pila     anterior ;
     } ;

     /* manejo de la PILA *
      * ----------------- */
     t_pila L_PILA_CrearVacia ( void ) ;
     /* - */
     /* - Inicializa una pila sin elementos */

     T_BOOL   L_PILA_EsVacia (t_pila) ;
     /* - */
     /* - Comprueba si la pila no tiene elementos */

     t_DiNode *L_PILA_Sacar (t_pila *) ;
     /* - */
     /* - Nos da la cima de la pila, quedando la pila sin
          este elemento */

     t_pila L_PILA_Insertar (t_pila *, t_DiNode *) ;
     /* - */
     /* - inserta elto en pila, que sera el primero en salir con cima
          ( pila Last In First Out (LIFO) ) */

     t_pila L_PILA_InsertarNew (t_pila *, t_DiNode *) ;
     /* - */
     /* - */

     void L_PILA_Vaciar (t_pila *) ;
     /* - */
     /* - Vacia la pila, no borrando sus elementos */

     void L_PILA_KillPila ( t_pila *p,
			    T_BOOL   (*FreePropiedades)(T_POINTER *) ) ;
     /* - */
     /* - Vacia la pila, usando FreeKill con cada elemento */


     /* ... Inline ... */
     #define L_PILA_CrearVacia()     \
             (t_pila)L_DSTACK_CreatEmpty()

     #define L_PILA_EsVacia(t)        \
             L_DSTACK_IsEmpty((t_pointerDStack)t)

     #define L_PILA_Sacar(t)         \
             (t_DiNode *)L_DSTACK_Pop((t_pointerDStack *)t)

     #define L_PILA_Insertar(t,e)    \
             (t_pila)L_DSTACK_Push((t_pointerDStack *)t,(T_POINTER)e)

     #define L_PILA_Vaciar(t)         \
             L_DSTACK_Empty((t_pointerDStack *)t)

     #define L_PILA_InsertarNew(p,e)  \
             L_DSTACK_PushNew((t_pointerDStack *)p,(T_POINTER)e)


 /*... Tipo tabla (de nodos) ..............................................*/

     typedef t_DiNode **t_tabla ;

     /* manejo de la tabla *
      * ------------------ */
     T_BOOL      L_TABLA_InsEndTabla(t_tabla *table, 
                                     T_INT *nnodos, 
                                     t_DiNode *nodo) ;
     T_BOOL      L_TABLA_DelEndTabla(t_tabla *table, 
                                     T_INT *nnodos, 
                                     t_DiNode **DelNode) ;
     T_BOOL      L_TABLA_DelEntryTabla(t_tabla *table, 
                                       t_DiNode *entry) ;
     t_DiNode   *L_TABLA_GetNFromTabla(T_INT orden, 
                                       t_tabla tabla) ;
     t_DiNode   *L_TABLA_GetNamedFromTabla(T_CHAR *name_nodo, 
                                           t_tabla tabla) ;

     /* ... Inline ... */
     #define L_TABLA_InsEndTabla(t,nt,n)  \
             L_DARRAY_InsEndDarray((t_pointerDArray *)t,(T_U_LONG *)nt,(T_POINTER)n)
     #define L_TABLA_DelEndTabla(t,nt,n)  \
             L_DARRAY_DelEndDarray((t_pointerDArray *)t,(T_U_LONG *)nt,(T_POINTER *)n)
     #define L_TABLA_DelEntryTabla(t,e)   \
             L_DARRAY_DelEltoDarray((t_pointerDArray *)t,(T_POINTER)e)
     #define L_TABLA_GetNFromTabla(t,o)   \
             (t_DiNode *)L_DARRAY_GetNFromDarray((t_pointerDArray)t,o)


   /* ....................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

