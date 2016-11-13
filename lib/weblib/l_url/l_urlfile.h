

 #ifndef L_URLFILE_H
 #define L_URLFILE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_file/l_file.h"
      #include "weblib/l_ws/c_ws.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlstr.h"


   /* ... Const / Constantes ............................................ */

      /* ... Dirs and Files ... */
      #define CURR_DIR        "./"
      #define UP_DIR          "../"
      #define SLAS            "/"
      #define INDEX_HTML      "index.html"
      #define S_INDEX_HTML    "/index.html"
      #define INDEX_XML       "index.xml"
      #define S_INDEX_XML     "/index.xml"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_URLFILE_OpenInsideUrl        ( INOUT  t_url    *urlRel,
                                                IN     t_url    *urlBase,
                                                IN     T_CHAR   *relPath ) ;
     /* - If 'relPath' is a url, put it at 'urlRel',
          else see it like a relative from 'urlBase', 
          using 'L_URLFILE_OpenReativePath'. */
     /* - Si 'relPath' es un url, lo translada a 'urlRel', 
          de otra forma, lo vera como un path relativo
          a 'urlBase', usando 'L_URLFILE_OpenReativePath'. */

      T_BOOL   L_URLFILE_OpenReativePath      ( INOUT  t_url    *urlRel,
                                                IN     t_url    *urlBase,
                                                IN     T_CHAR   *relPath ) ;
     /* - In 'urlRel' we found a url relative to
          'urlBase', with offset 'path' */
     /* - En 'urlRel' esta la referencia a un fichero,
          relativo a la direccion en 'urlBase', con
          desplazamiento 'path' */

     T_CHAR   *L_URLFILE_MirrorUrlName        ( IN     t_url  *url,
                                                IN     T_INT   tms ) ;
     /* - Return a malloc string that mirror
          a url. */
     /* - */

     T_CHAR   *L_URLFILE_MirrorUrlNameFrom    ( IN     t_url  *url,
                                                IN     t_url  *purlFrom,
                                                IN     T_INT   tms ) ;
     /* - Return a malloc string. That string is a
          file name that mirror 'url', from the
          point of view of url 'purlFrom'. */
     /* - */

     T_BOOL    L_URLFILE_MakeIndexUrl         ( IN     t_url    *url ) ;
     /* - Add a '/' at url->file. */
     /* - */

     T_BOOL    L_URLFILE_IsBin                ( IN     T_CHAR   *strurl ) ;
     /* - File refereced by 'strurl' has a 
          common binary extension. */
     /* - */

     T_BOOL    L_URLFILE_FromSamePath         ( IN     t_url    *purl,
                                                IN     T_CHAR   *strurl ) ;
     /* - Return TRUE if 'strurl' file has same
          base path that 'purl' */
     /* - */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

