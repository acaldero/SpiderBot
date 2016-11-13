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



   /* ... Includes / Inclusion ........................................... */

      #include "corelib/l_adt/l_dstack.h"


   /* ... Functions / Funciones .......................................... */
    
      T_POINTER L_DSTACK_Pop  ( INOUT t_pointerDStack *p )
      { 
         T_POINTER n ;
         t_pointerDStack wp ;
 
         NULL__SET_ERROR__RET_NULL(p) ;
         n    = (*p)->elemento ;
         wp   = (*p) ;
         (*p) = (*p)->anterior ;
         X_ALLOC_Free((void **)&wp) ;
         return n ;
      }
    
      t_pointerDStack L_DSTACK_Push ( INOUT t_pointerDStack *p,
                                        IN    T_POINTER e )
      {
        t_pointerDStack wp ;
 
        wp = (t_pointerDStack)X_ALLOC_Malloc(c_POINTERPILA) ;
        NULL_RET_NULL(wp) ;
        wp->anterior = (*p) ;
        wp->elemento = e ;
        (*p)         = wp ;
        return (*p) ;
      }
 
      t_pointerDStack L_DSTACK_PushNew ( INOUT t_pointerDStack *p,
                                           IN    T_POINTER e )
      {
        t_pointerDStack wp ;
 
        wp = (*p) ;
        while (wp)
        {
          if ( (wp->elemento) == e )
           return (*p) ;
          wp = wp->anterior ;
        }
        wp=(t_pointerDStack)X_ALLOC_Malloc(c_POINTERPILA) ;
        NULL_RET_NULL(wp) ;
        wp->anterior = (*p) ;
        wp->elemento = e ;
        (*p)         = wp ;
        return (*p) ;
      }
    
      void L_DSTACK_Empty ( INOUT t_pointerDStack *p )
      {
        t_pointerDStack wp ;
    
        while(*p) /* ! esvacia(p) */
        {
          wp=*p ;
          *p=(*p)->anterior ;
          X_ALLOC_Free((void **)&wp) ; /* cima(p) */
        }
      }
    
    
   /* .................................................................... */

