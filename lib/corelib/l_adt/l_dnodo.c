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



   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_adt/l_dnodo.h"


   /* ... Functions / Funciones ......................................... */

      /* ... Tabla de t_DiNode ... */
      t_DiNode *L_TABLA_GetNamedFromTabla ( IN    T_CHAR  *name_nodo,
                                            IN    t_tabla  tabla )
      {
        T_INT c;
   
        NULL__SET_ERROR__RET_NULL( tabla ) ;
        for (c=0; (
                    (tabla[c] != NULL) 
                            && 
                    (! X_STRING_Equal(tabla[c]->nombre,name_nodo))
                  );
             c++) 
            { /* counting ... */ ; }
        NULL__SET_ERROR__RET_NULL( tabla[c] ) ;
        return tabla[c] ;
      }
   

      /* ... Pila de t_DiNode ... */
      void L_PILA_KillPila ( INOUT t_pila   *p,
                             IN    T_BOOL  (*FreePropiedades)(T_POINTER *) )
      {
        t_DiNode *g ;
   
        while (!L_PILA_EsVacia(*p))
        {
          g = L_PILA_Sacar(p) ;
          L_GRAFO_FreeKill(&g,FreePropiedades) ;
        }
      }
   

      /* ... Grafo de t_DiNode ... */
      /* === creat... === */
      t_DiNode *L_GRAFO_NewNode ( void )
      {
        t_DiNode *nodo ;
   
        nodo=(t_DiNode *)X_ALLOC_Malloc(c_DINODE) ;
        NULL_RET_NULL(nodo) ;
        X_ALLOC_MemSet(nodo,0,c_DINODE) ;
        nodo->TMP=1 ;
        return nodo ;
      }
   
      T_BOOL  L_GRAFO_NewSonLink (t_DiNode *padre,t_DiNode *hijo)
      {
        NULL__SET_ERROR__RET_FALSE(padre) ;
        NULL__SET_ERROR__RET_FALSE(hijo) ;
        if (L_TABLA_InsEndTabla(&(padre->hijos),&(padre->NSons),hijo)==FALSE)
            return FALSE ;
        if (L_TABLA_InsEndTabla(&(hijo->padres),&(hijo->NFathers),padre)==FALSE)
            return FALSE ;
        return TRUE ;
      }
   
      t_DiNode *L_GRAFO_NewSon (t_DiNode *padre)
      {
        t_DiNode *nodo ;
   
        NULL__SET_ERROR__RET_NULL(padre ) ;
        nodo=L_GRAFO_NewNode() ;
        if (nodo)
            L_GRAFO_NewSonLink(padre,nodo) ;
        return nodo ;
      }
   
      t_DiNode *L_GRAFO_NewFather (t_DiNode *hijo)
      {
        t_DiNode *nodo ;
   
        NULL__SET_ERROR__RET_NULL(hijo ) ;
        nodo=L_GRAFO_NewNode() ;
        if (nodo)
            L_GRAFO_NewFatherLink(hijo,nodo) ;
        return nodo ;
       }
   
       /* === free... === */
       T_BOOL  L_GRAFO_UnLinkFather(t_DiNode *padre, t_DiNode *hijo)
       {
         if (hijo == NULL)
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"hijo is a NULL ptr.") ;
         } 
         else 
         {
           if (L_TABLA_DelEntryTabla(&(hijo->padres),padre)==TRUE)
              {
                if (!hijo->NFathers)
                   {
                      L_DEBUG_MSG_Write(ERROR,FALSE,"incorrect fathers number.") ;
                   } else {
                            hijo->NFathers-- ;
                          }
              }
         }
         if (padre == NULL)
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"padre is a NULL ptr.") ;
         } 
         else 
         {
           if (L_TABLA_DelEntryTabla(&(padre->hijos),hijo)==TRUE)
              {
                if (!padre->NSons)
                   {
                      L_DEBUG_MSG_Write(ERROR,FALSE,"incorrect sons number") ;
                   } else {
                            padre->NSons-- ;
                          }
              }
         }
         return TRUE ;
       }
   
        T_BOOL L_GRAFO_UnLinkAllFathers(t_DiNode *hijo)
        {
          T_U_LONG np, i ;
   
          NULL__SET_ERROR__RET_TRUE(hijo) ;
          np=hijo->NFathers ;
          for (i=0; i<np; i++)
               L_GRAFO_UnLinkFather(hijo->padres[0],hijo) ;
          return TRUE ;
        }
   
        T_BOOL L_GRAFO_UnLinkAllSon(t_DiNode *padre)
        {
          T_U_LONG nh, i ;
   
          NULL__SET_ERROR__RET_TRUE(padre) ;
          nh = padre->NSons ;
          for (i=0; i<nh; i++)
               L_GRAFO_UnLinkFather(padre,padre->hijos[0]) ;
          return TRUE ;
        }
   
        void L_GRAFO_pFreeNode ( t_DiNode **nodo,
                                 T_BOOL   (*FreePropiedades)(T_POINTER *),
                                 t_DiNode ***tabla )
        {
          /* Borra nodo, guardando hijos en tabla */
          T_U_LONG i, nh, ntabla ;
   
          nh=(*nodo)->NSons ;
          for(i=0; i<nh; i++)
             {
               if ( ((*nodo)->hijos[0])->NFathers==1 )
                  {
                     L_TABLA_InsEndTabla(tabla,&ntabla,((*nodo)->hijos[0])) ;
                  }
               L_GRAFO_UnLinkSon((*nodo),((*nodo)->hijos[0])) ;
             }
          L_GRAFO_UnLinkAllFathers(*nodo) ;
          if ((*nodo)->propiedades)
              FreePropiedades(&((*nodo)->propiedades)) ;
          X_ALLOC_Free((void **)&((*nodo)->nombre)) ;
          X_ALLOC_Free((void **)&(*nodo)) ;
        }
   
        t_DiNode **L_GRAFO_fFreeNode ( t_DiNode **nodo,
                                    T_BOOL   (*FreePropiedades)(T_POINTER *) )
        {
          t_DiNode **table=NULL ;
   
          L_GRAFO_pFreeNode(nodo,FreePropiedades,&table) ;
          return table ;
        }
   
        T_BOOL L_GRAFO_FullFreeNode ( t_DiNode **nodo,
                                   T_BOOL   (*FreePropiedades)(T_POINTER *) )
        {
          t_DiNode **table=NULL ;
   
          L_GRAFO_pFreeNode(nodo,FreePropiedades,&table) ;
          X_ALLOC_Free((void **)&table) ;
          return TRUE ;
        }
   
        t_DiNode **L_GRAFO_FreeSubSetNodes ( t_DiNode ***tabla,
                                             T_BOOL   (*FreePropiedades)(T_POINTER *),
                                             ... )
        {
          t_DiNode **nodo ;
          va_list arg;
          va_start(arg,FreePropiedades) ;
   
          while ( (nodo = va_arg(arg,t_DiNode **)) != NULL )
                {
                  L_GRAFO_pFreeNode(nodo,FreePropiedades,tabla) ;
                }
          va_end(arg) ;
          return *tabla ;
        }
   
        /* === Consulta === */
        T_CHAR *L_GRAFO_GetName(t_DiNode *nodo)
        {
           NULL__SET_ERROR__RET_NULL(nodo ) ;
           return (nodo->nombre) ;
        }
   
        T_BOOL L_GRAFO_SetName(t_DiNode *nodo, T_CHAR *Newname)
        { 
          /* 
           * WARNING
           *   not uses memory duplication
           */
          NULL__SET_ERROR__RET_FALSE(nodo) ;
          (nodo->nombre)=Newname ;
          return TRUE ;
        }
   
        T_U_LONG L_GRAFO_GetNSons(t_DiNode *nodo)
        {
          TRUE__SET_ERROR__RET_LONG((nodo == NULL),0L) ;
          return (nodo->NSons) ;
        }
   
        T_U_LONG L_GRAFO_GetNFathers(t_DiNode *nodo)
        {
          TRUE__SET_ERROR__RET_LONG((nodo == NULL),0L) ;
          return (nodo->NFathers) ;
        }
   
        T_POINTER L_GRAFO_GetNodePropiedades ( t_DiNode *nodo )
        {
          NULL__SET_ERROR__RET_NULL(nodo ) ;
          NULL__SET_ERROR__RET_NULL(nodo->propiedades ) ;
          return (nodo->propiedades) ;
        }
   
        T_BOOL L_GRAFO_SetNodePropiedades ( t_DiNode  *nodo,
                                         T_POINTER  p )
        {
          NULL__SET_ERROR__RET_FALSE(nodo) ;
          (nodo->propiedades) = p ;
          return TRUE ;
        }
   
        t_DiNode *L_GRAFO_GetSonN(T_INT orden,t_DiNode *padre)
        {
          NULL__SET_ERROR__RET_NULL(padre ) ;
          if (orden >= padre->NSons)
                   return NULL ;
              else return (L_TABLA_GetNFromTabla(padre->hijos,orden)) ;
        }
   
        t_DiNode *L_GRAFO_GetFatherN(T_INT orden,t_DiNode *hijo)
        {
          NULL__SET_ERROR__RET_NULL(hijo ) ;
          if (orden >= hijo->NFathers)
                   return NULL ;
              else return (L_TABLA_GetNFromTabla(hijo->padres,orden)) ;
        }
   
        t_DiNode *L_GRAFO_GetSonName(T_CHAR *name_nodo,t_DiNode *padre)
        {
          NULL__SET_ERROR__RET_NULL(padre ) ;
          return (L_TABLA_GetNamedFromTabla(name_nodo,padre->hijos)) ;
        }
   
        t_DiNode *L_GRAFO_GetFatherName(T_CHAR *name_nodo,t_DiNode *hijo)
        {
          NULL__SET_ERROR__RET_NULL(hijo ) ;
          return (L_TABLA_GetNamedFromTabla(name_nodo,hijo->padres)) ;
        }
   
        /* === Varios === */
        t_pila  L_GRAFO_NodesInGrafo    ( t_DiNode **nodo )
        {
          t_DiNode  *nodowork ;
          t_pila     Spila, Wpila ;
          T_U_LONG   i, nh, np ;
          T_INT      Etiqueta ;
   
          NULL__SET_ERROR__RET_NULL((*nodo) ) ;
          Etiqueta = !((*nodo)->TMP) ;
          nodowork = NULL ;
          Spila    = L_PILA_CrearVacia() ;
          Wpila    = L_PILA_CrearVacia() ;
          if (L_PILA_Insertar(&Spila,*nodo)==NULL)
           return FALSE ;
          while (!L_PILA_EsVacia(Spila))
             {
               nodowork=L_PILA_Sacar(&Spila) ;
               if (nodowork == NULL)
                   continue ; /* no hacer nada */
               if (nodowork->TMP==Etiqueta)
                   continue ; /* ya visitado */
               nh = nodowork->NSons ;
               np = nodowork->NFathers ;
               for(i=0; i<nh; i++)
                  {
                    if (L_PILA_InsertarNew(&Spila,nodowork->hijos[i]) == NULL)
                       {
                         L_PILA_Vaciar(&Spila) ;
                         L_PILA_Vaciar(&Wpila) ;
                         return FALSE ;
                       }
                  }
               for(i=0; i<np; i++)
                  {
                    if (L_PILA_InsertarNew(&Spila,nodowork->padres[i]) == NULL)
                       {
                         L_PILA_Vaciar(&Spila) ;
                         L_PILA_Vaciar(&Wpila) ;
                         return FALSE ;
                       }
                  }
               nodowork->TMP=Etiqueta ;
               if (L_PILA_InsertarNew(&Wpila,nodowork)==NULL)
                  {
                    L_PILA_Vaciar(&Spila) ;
                    L_PILA_Vaciar(&Wpila) ;
                    return FALSE ;
                  }
             }
          return Wpila ;
        }
   
        T_BOOL L_GRAFO_OperOverGraf ( t_DiNode **nodo,
                                   T_BOOL (*FTN)(t_DiNode **n) )
        {
          t_DiNode *nodowork=NULL ;
          t_pila Wpila ;
   
          NULL__SET_ERROR__RET_TRUE((*nodo)) ;
          Wpila = L_GRAFO_NodesInGrafo(nodo) ;
          while (!L_PILA_EsVacia(Wpila))
             {
               nodowork=L_PILA_Sacar(&Wpila) ;
               (*FTN)(&nodowork) ;
             }
          return TRUE ;
        }
   
        T_BOOL SetNodeCoherence(t_DiNode **n)
        {
          T_U_LONG nhijos, npadres ;
   
          NULL__SET_ERROR__RET_TRUE((*n)) ;
          nhijos  = (*n)->NSons ;
          npadres = (*n)->NFathers ;
          (*n)->NSons  = nhijos ;
          (*n)->NFathers = npadres ;
          if (!((*n)->nombre))
             {
               T_CHAR *msg="SetNodeCoherencia: NoNameNode." ;
               ((*n)->nombre)=(T_CHAR *) X_STRING_StrDup(msg) ;
             }
          return TRUE ;
        }
   
        void L_GRAFO_SetCoherencia(t_DiNode *nodo)
        {
          L_GRAFO_OperOverGraf(&nodo,SetNodeCoherence) ;
        }
   
   
        static t_StatNode st ;
   
        T_BOOL SetNodeEstadistica(t_DiNode **n)
        {
          st.nhijos  += ((*n)->NSons) ;
          st.npadres += (((*n)->NSons)!=0) ;
          return TRUE ;
        }
   
        void L_GRAFO_GetEstadistica(t_DiNode *n,t_StatNode  *stat)
        {
          st.nhijos  = 0 ;
          st.npadres = 0 ;
          L_GRAFO_OperOverGraf(&n,SetNodeEstadistica) ;
          X_ALLOC_MemMove(stat,&st,c_STATNODE) ;
        }
   
        T_BOOL  L_GRAFO_FreeKill    ( t_DiNode **nodo,
                                   T_BOOL   (*FreePropiedades)(T_POINTER *) )
        {
          t_DiNode *nodowork ;
          t_pila Wpila ;
   
          NULL__SET_ERROR__RET_TRUE((*nodo)) ;
          Wpila    = L_GRAFO_NodesInGrafo(nodo) ;
          nodowork = NULL ;
          while (!L_PILA_EsVacia(Wpila))
             {
               nodowork=L_PILA_Sacar(&Wpila) ;
               (*L_GRAFO_FullFreeNode)(&nodowork,FreePropiedades) ;
             }
          return TRUE ;
        }
   

 /* ..................................................................... */

