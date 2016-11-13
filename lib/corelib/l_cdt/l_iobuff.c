/* ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_cdt/l_iobuff.h"


   /* ... Functions / Funciones ......................................... */

      void  L_IOBUFF_SetBuffer ( OUT  t_iobuffer  *iob,
                                 IN   FILE        *fout )
      {
        iob->buff  = NULL ;
        iob->size  = 0 ;
        iob->fasoc = fout ;
      }

      void  L_IOBUFF_FlushBuffer ( INOUT  t_iobuffer  *iob )
      {
        if (iob->buff!=NULL)
           {
             fwrite(iob->buff,1,iob->size,iob->fasoc) ;
             X_ALLOC_Free((void **)&(iob->buff)) ;
             iob->size=0 ;
           }
      }


   /* ................................................................... */

