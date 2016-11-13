

 #ifndef L_IOBUFF_H
 #define L_IOBUFF_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Types / Tipos ...................................................*/

      typedef struct
      {
        T_CHAR   *buff ;
        T_U_INT   size ;
        FILE     *fasoc ;
      } t_iobuffer ;


   /* ... Functions / Funciones ......................................... */

      void    L_IOBUFF_SetBuffer    ( OUT    t_iobuffer  *iob,
                                      IN     FILE        *fout ) ;
      /* -  */
      /* -  */

      void    L_IOBUFF_FlushBuffer  ( INOUT  t_iobuffer  *iob ) ;
      /* -  */
      /* -  */

      T_BOOL  L_IOBUFF_AddStr       ( INOUT  t_iobuffer  *iob,
                                      IN     T_CHAR      *str ) ;
      /* -  */
      /* -  */


   /* ... Inline / Expansiones .......................................... */

      #define L_IOBUFF_AddStr(iob,str)  \
              L_BUFFA_CatNBytesToCache(&((iob)->buff),&((iob)->size),(str),X_STRING_StrLen((str))) ;


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

