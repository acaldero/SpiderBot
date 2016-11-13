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

      #include "corelib/l_alloc/x_alloc.h"


   /* ... Functions / Funciones ......................................... */

      T_POINTER  X_ALLOC_MemDup ( IN  T_POINTER b,
                                  IN  T_U_INT   bsize )
      {
        void *pvoid ;

        NULL_RET_NULL(b) ;
        pvoid = X_ALLOC_Malloc(bsize) ;
        NULL_RET_NULL(pvoid) ;
        X_ALLOC_MemMove(pvoid,b,bsize) ;
        return pvoid ;
      }

      T_POINTER  X_ALLOC_AllocAndSet ( IN  T_U_INT  bsize,
                                       IN  T_CHAR   setval )
      {
        void *pvoid ;

        pvoid = X_ALLOC_Malloc(bsize) ;
        NULL_RET_NULL(pvoid) ;
        X_ALLOC_MemSet(pvoid,setval,bsize) ;
        return pvoid ;
      }


/* ...................................................................... */

