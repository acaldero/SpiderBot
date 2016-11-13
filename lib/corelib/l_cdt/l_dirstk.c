/* ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_cdt/l_dirstk.h"


   /* ... Functions / Funciones ......................................... */
  
      t_di_stack *L_DIRSTK_Pop ( INOUT t_di_stack *p,
                                 INOUT t_dirinfo  *e )
      {
        t_di_stack wp ;
  
        NULL_RET_NULL(*p) ;
        X_ALLOC_MemMove(e,&((*p)->elto),c_DIRINFO) ;
        wp   = (*p) ;
        (*p) = (*p)->anterior ;
        X_ALLOC_Free((void **)&(wp)) ;
        return p ;
      }
  
      t_di_stack L_DIRSTK_Push ( INOUT t_di_stack *p,
                                 IN    t_dirinfo *e   )
      {
        t_di_stack wp ;
  
        wp = (t_di_stack)X_ALLOC_Malloc(c_DISTACK) ;
        NULL_RET_NULL(wp) ;
        wp->anterior = (*p) ;
        X_ALLOC_MemMove(&(wp->elto),e,c_DIRINFO) ;
        (*p) = wp ;
        return (*p) ;
      }
  
      void L_DIRSTK_Empty ( INOUT t_di_stack *p )
      {
        t_di_stack wp ;
  
        while ((*p)!=NULL)
        {
          wp   = (*p) ;
          (*p) = (*p)->anterior ;
          X_ALLOC_Free((void **)&((wp->elto).path)) ;
          X_ALLOC_Free((void **)&(wp)) ;
        }
      }
  

   /* ................................................................... */


