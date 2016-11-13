

 #ifndef L_DEBUG_H
 #define L_DEBUG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug_msg.h"


   /* ... Functions / Funciones ......................................... */
      
      T_BOOL L_DEBUG_assert               ( IN     T_BOOL      condition,
                                            IN     T_U_INT     line,
                                            IN     T_CHAR     *name,
                                            IN     T_INT       type,
                                            IN     int         xerrno,
                                            IN     T_CHAR     *fto,
                                            ... ) ;
      /* - */
      /* - */


      /*  Macros  *
       * -------- */
      void   TRUE__SET_ERROR__RET_LONG    ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_WARNING__RET_LONG  ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_INFO__RET_LONG     ( IN     T_POINTER   ptr ) ;

      void   NULL__SET_ERROR__RET_NULL      ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_ERROR__RET_TRUE      ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_ERROR__RET_FALSE     ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_WARNING__RET_NULL    ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_WARNING__RET_TRUE    ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_WARNING__RET_FALSE   ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_INFO__RET_NULL       ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_INFO__RET_TRUE       ( IN     T_POINTER   ptr ) ;
      void   NULL__SET_INFO__RET_FALSE      ( IN     T_POINTER   ptr ) ;

      void   TRUE__SET_ERROR__RET_NULL      ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_ERROR__RET_TRUE      ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_ERROR__RET_FALSE     ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_WARNING__RET_NULL    ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_WARNING__RET_TRUE    ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_WARNING__RET_FALSE   ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_INFO__RET_NULL       ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_INFO__RET_TRUE       ( IN     T_POINTER   ptr ) ;
      void   TRUE__SET_INFO__RET_FALSE      ( IN     T_POINTER   ptr ) ;

      void   FALSE__SET_ERROR__RET_NULL     ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_ERROR__RET_TRUE     ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_ERROR__RET_FALSE    ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_WARNING__RET_NULL   ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_WARNING__RET_TRUE   ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_WARNING__RET_FALSE  ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_INFO__RET_NULL      ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_INFO__RET_TRUE      ( IN     T_POINTER   ptr ) ;
      void   FALSE__SET_INFO__RET_FALSE     ( IN     T_POINTER   ptr ) ;


   /* ... Inline / Macros ............................................... */

      #include "corelib/l_debug/l_debug.m"


   /* ................................................................... */

 #ifdef  __cplusplus
    }
 #endif


 #endif

