

 #ifndef L_URLXML_H
 #define L_URLXML_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_file/l_file.h"
      #include "corelib/l_net/l_socket.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/l_ftoken.h"
      #include "weblib/l_verbose/l_verbose_log.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlfile.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_ws/l_ws.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL  L_URLXML_AjustPageUrls    ( INOUT  FILE          *fin,
                                          INOUT  FILE          *fout,
                                          INOUT  T_BOOL        *updated,
                                          INOUT  t_downLoadWS  *dlws,
                                          IN     t_url         *url ) ;
      /* - Get url's in file 'fin' and put them in 'dlws->urlli'.
           Uses 'dlws' options :
           makerel, scanGlobal, fromsamepath, skipBin, makeQuery.
      */
      /* - Extrae los url's del fichero 'fin' y los inserta
           en la lista 'dlws->urlli'.
           Usa las opciones de 'dlws' :
           makerel, scanGlobal, fromsamepath, skipBin, makeQuery.
      */

      T_BOOL  L_URLXML_GetPageUrls      ( IN     FILE          *fin,
                                          INOUT  t_downLoadWS  *dlws,
                                          IN     t_url         *url ) ;
      /* - Only get url's at file 'fin' and put 
           them into 'urlli' list. 
           Uses 'dlws' options :
           scanGlobal, fromsamepath, skipBin, makeQuery.
      */
      /* - Solo extrae los urls del fichero 'fin' y los
           inserta en la lista 'urlli'. 
           Usa las opciones de 'dlws' :
           scanGlobal, fromsamepath, skipBin, makeQuery.
      */

      T_BOOL  L_URLXML_mkLocal         ( INOUT  FILE          *fin,
                                         INOUT  FILE          *fout,
                                         INOUT  T_BOOL        *updated,
                                         INOUT  t_downLoadWS  *dlws,
                                         IN     t_url         *url ) ;
      /* - Only get url's at file 'fin' and rewrite
           them into 'fout' file. 
           Uses 'dlws' option :
           mkGlobal.
      */
      /* - Solo extrae los urls del fichero 'fin' y los
           reescribe al fichero 'fout'. 
           Usa la opcion de 'dlws' :
           mkGlobal.
      */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

