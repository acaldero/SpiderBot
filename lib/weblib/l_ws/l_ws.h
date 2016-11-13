

 #ifndef L_WS_H
 #define L_WS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_thread/x_thread.h"
      #include "weblib/l_wdt/l_urlli.h"
      #include "weblib/l_ws/c_ws.h"


   /* ... Types / Tipos ................................................. */

      typedef
      struct
      {

        /* ... General info ... */
        T_CHAR   *clientNameReal ;
                  /*
                   - web utility's name.
                   - Nombre de la utilidad web.
                  */
        T_CHAR   *clientNameToSend ;
                  /*
                   - identification to send web site.
                   - identificacion para el servidor web.
                  */
        T_CHAR   *identification ;
                  /*
                   - base64(<user>:<pass>) as user identification
                     into web site.
                   - Identificacion de usuario en el sitio web
                     en formato base64(<user>:<pass>)
                  */
        t_url     proxyUrl ;
                  /*
                   - url where our proxy can be found.
                   - url donde podremos encontrar nuestro proxy.
                  */
        T_FLAG    skipEL ;
                  /*
                   - Skip Exclusion List. This is a file called
                     "http://<web site>/robots.txt" with a list of
                     path that a robot OUGHT to avoid explore.
                   - Ignora la lista de exclusion. Esta lista es
                     un fichero "http://<web site>/robots.txt"
                     que contiene la lista caminos que un robot
                     deberia NO explorar.
                  */
        T_FLAG    verbose ;
                  /*
                   - Report what is happing.
                   - Informa de lo que esta haciendo.
                  */
        T_INT     protocolSelection ;
                  /*
                   - Select if only download and explore using
                     http or ftp or ... or all
                   - Selecciona si se quiere transferir usando
                     el protocolo http, o el ftp, ..., o todos
                  */
        T_FLAG    makeQuery ;
                  /*
                   - cgi's querys are rewritten to point to a file with result.
                   - las llamadas a cgi se reescriben como url que apunta
                     al lugar donde se guardan los resultados asociados.
                  */
        FILE     *finfo ;
                  /*
                   - Log file descriptor.
                   - Descriptor del fichero de traza.
                  */
        FILE     *fresume ;
                  /*
                   - Resume file descriptor.
                   - Descriptor del fichero de continuacion.
                  */
        T_U_LONG  bufSize ;
                  /*
                   - 
                   -
                  */
        T_U_LONG  timeLimit ;
                  /*
                   - 
                   -
                  */
        T_U_LONG  delay ;
                  /*
                   - 
                   -
                  */
        T_U_LONG  resumeFrec ;
                  /*
                   - 
                   -
                  */
        t_mtsda   ws_mtsda ;
                  /*
                   - 
                   -
                  */

        /* ... Resume info ... */
        T_U_LONG  i ;  /* elto from list: 0..n-1 */
                  /*
                   - 'i' is current url's position 
                     from 'urllist' to download.
                   - 'i' es el indice en 'urllist' del
                     url a traer.
                  */
        t_urlLi  *urllist ;
                  /*
                   - 'urllist' represents a url's list
                     to download.
                   - 'urllist' representa la lista de
                     urls a traer.
                  */
        T_INT     scanSelection ;
                  /*
                   - Scan url to add to 'urllist' within same
                     web site, any site.
                   - Buscar url que 'sumar' a 'urllist', bien
                     del mismo sitio web, bien de cualquiera.
                  */
        T_INT     rewriteSelection ;
                  /*
                   - If inside a page, a url like (/icon/jpg.gif) is present,
                     it can be converted to (icon/jpg.gif).
                     Also, we can convert url to other web sites
                     (http://<web site i>)
                   - Los url absolutos son tranformados en locales.
                     (/icon/jpg.gif -> icon/jpg.gif)
                     Tambien, se pude convertir los url de otros
                     sitios web.
                  */
        T_INT     mirrorSelection ;
                  /*
                   - Select how store web pages.
                   - Selecciona la forma de almacenar los
                     url.
                  */
        T_FLAG    fromSamePath ;
                  /*
                   - If new urls has same base path that 'url', then
                     insert at list.
                   - solo se insertan los urls que tengan el mismo
                     path base que 'url'
                  */
        T_FLAG    skipBin ;
                  /*
                   - Common binary extension like ".gif", ".jpg", etc.
                     are skipped.
                   - los binario comunes (gif, jpg, ...) no son insertados
                     en la lista 'urlli'.
                  */
        T_FLAG    rentry ;
                  /*
                   - 
                   -
                  */
        T_FLAG    detect_http ;
                  /*
                   - 
                   -
                  */
        T_U_LONG  maxBytes ;
                  /*
                   - 
                   -
                  */
        T_U_LONG  maxUrls ;
                  /*
                   - 
                   -
                  */
        T_U_LONG  currentBytes ;
                  /*
                   - 
                   -
                  */
        T_CHAR   *proxy ;
                  /*
                   - 
                   -
                  */

      } t_downLoadWS ;    /* downLoadWorkSpace */


   /* ... Const / Constantes ............................................ */

      #define c_DOWNLOADWS      sizeof(t_downLoadWS)


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

