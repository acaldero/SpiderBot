

 #ifndef L_URLSTR_H
 #define L_URLSTR_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_url/l_url.h"


   /* ... Functions / Funciones ......................................... */

     T_BOOL    L_URLSTR_StringToUrl        ( OUT   t_url     *url,
                                             IN    T_CHAR    *str ) ;
     /* - */
     /* - Rellena 'url' con la informacion de 'str'.  */

     T_BOOL    L_URLSTR_UrlToString        ( IN     t_url    *url,
                                             OUT    T_CHAR  **str ) ;
     /* - */
     /* - Pone en '*str' la direccion de un string
          el cual representa a 'url'. ES DINAMICO.  */

     T_BOOL    L_URLSTR_GlobalUrlToRequest   ( IN     t_url    *url,
                                               OUT    T_CHAR  **str ) ;
     /* - */
     /* - */

     T_BOOL    L_URLSTR_LocalUrlToRequest    ( IN     t_url    *url,
                                               OUT    T_CHAR  **str ) ;
     /* - */
     /* - */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

