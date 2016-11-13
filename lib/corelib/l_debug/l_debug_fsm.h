

 #ifndef L_DEBUG_FSM_H
 #define L_DEBUG_FSM_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {
         T_CHAR  *state_orig ;
         T_CHAR  *state_dest ;
      } t_fsmTransition ;

      typedef
      struct
      {
        T_CHAR          *name ;
        t_fsmTransition *transitions ;
      } t_fsm ;


   /* ... Functions / Funciones ......................................... */
      

      /*  Basic functions  *
       * ----------------- */
      void       L_DEBUG_FSM_creat         ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line ) ;
      /* - */
      /* - */

      void       L_DEBUG_FSM_remove        ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line ) ;
      /* - */
      /* - */

      void       L_DEBUG_FSM_rename        ( IN     t_fsm     *fsmType,
                                             IN     void      *oldFsmId,
                                             IN     void      *newFsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line ) ;
      /* - */
      /* - */

      T_BOOL     L_DEBUG_FSM_exist         ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line ) ;
      /* - */
      /* - */


      /*  Moving FSM  *
       * ------------ */
      T_BOOL     L_DEBUG_FSM_doTransition  ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *newState,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line ) ;
      /* - */
      /* - */


   /* ................................................................... */

 #ifdef  __cplusplus
    }
 #endif


 #endif

