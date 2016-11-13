

 #ifndef L_WPP_MSG_H
 #define L_WPP_MSG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "wpplib/l_cl_wpp/c_wpp_id.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_WPP_MSG_presentation        ( IN   T_CHAR  *wpp_name,
                                               IN   T_CHAR  *wpp_ver )  ;
      /* - Print at stdout our presentation. */
      /* - */

      T_BOOL   L_WPP_MSG_common_command_line ( IN   T_CHAR  *wpp_name,
                                               IN   T_CHAR  *wpp_exe_name,
                                               IN   T_INT    i_page,
                                               IN   T_INT    n_page ) ;
      /* - Print at stdout common usual options. */
      /* - */

      T_BOOL   L_WPP_MSG_options   ( IN   T_CHAR  *wpp_name,
                                     IN   T_INT    i_page,
                                     IN   T_INT    n_page ) ;
      /* - Print at stdout options available. */
      /* - */

      T_BOOL   L_WPP_MSG_flags     ( IN   T_CHAR  *wpp_name,
                                     IN   T_INT    i_page,
                                     IN   T_INT    n_page ) ;
      /* - Print at stdout flags options. */
      /* - */

      T_BOOL   L_WPP_MSG_advanced   ( IN   T_CHAR  *wpp_name,
                                      IN   T_INT    i_page,
                                      IN   T_INT    n_page ) ;
      /* - Print at stdout advanced options. */
      /* - */

      T_BOOL   L_WPP_MSG_thanks_1  ( IN   T_CHAR  *wpp_name,
                                     IN   T_INT    i_page,
                                     IN   T_INT    n_page ) ;
      /* - Print at stdout thanks. */
      /* - */

      T_BOOL   L_WPP_MSG_thanks_2  ( IN   T_CHAR  *wpp_name,
                                     IN   T_INT    i_page,
                                     IN   T_INT    n_page ) ;
      /* - Print at stdout thanks. */
      /* - */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

