

 #ifndef L_URL_H
 #define L_URL_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"


   /* ... Const / Constantes ............................................ */

      #define c_URL      (sizeof(t_url))


   /* ... Types / Tipos ................................................. */
      
      typedef
      struct urlDescriptor 
      {
        T_CHAR *protocol ;
        T_CHAR *machine ;
        T_CHAR *file ;
        T_CHAR *relative ;
        T_CHAR *params ;
        T_INT   port ;
      } t_url ;
      

   /* ... Functions / Funciones ......................................... */

      /*  Creat *
       * ------ */
      t_url    *L_URL_Creat        ( IN     T_CHAR    *protocol,
                                     IN     T_CHAR    *machine,
                                     IN     T_CHAR    *file,
                                     IN     T_CHAR    *relative,
                                     IN     T_CHAR    *params,
                                     IN     T_INT      port ) ;
      /* - Malloc a new url, with information from 
           params. */
      /* - Crea un url duplicando la informacion de
           sus parametros. */

      t_url    *L_URL_CreatEmpty   ( void ) ;
      /* - Malloc a new url, with default information. */
      /* - Crea una url con la informacion por defecto. */

      t_url    *L_URL_CreatFrom    ( IN     T_CHAR    *protocol,
                                     IN     T_CHAR    *machine,
                                     IN     T_CHAR    *file,
                                     IN     T_CHAR    *relative,
                                     IN     T_CHAR    *params,
                                     IN     T_INT      port ) ;
      /* - */
      /* - Crea url usando la informacion de sus
           parametros. */

      T_BOOL    L_URL_FillFrom     ( OUT    t_url     *url,
                                     IN     T_CHAR    *protocol,
                                     IN     T_CHAR    *machine,
                                     IN     T_CHAR    *file,
                                     IN     T_CHAR    *relative,
                                     IN     T_CHAR    *params,
                                     IN     T_INT      port ) ;
      /* - */
      /* - */

      t_url    *L_URL_UrlDup        ( IN     t_url     *url ) ;
      /* - */
      /* - Duplica 'url' con la misma informacion. */


      /*  Close  *
       * ------- */
      T_BOOL    L_URL_Destroy       ( INOUT  t_url    **url ) ;
      /* - */
      /* - */

      T_BOOL    L_URL_Empty        ( INOUT  t_url     *url ) ;
      /* - */
      /* - */


      /*  Equals  *
       * -------- */
     T_BOOL    L_URL_Equal         ( IN     t_url     *url1,
                                     IN     t_url     *url2 ) ;
     /* - */
     /* - Retorna TRUE si 'url1' y 'url2' identifican
          al mismo cyberobjeto */

     T_BOOL    L_URL_EqualBase     ( IN     t_url     *url1,
                                     IN     t_url     *url2 ) ;
     /* - */
     /* - Retorna TRUE si 'url1' y 'url2' identifican
          al mismo fichero */

     T_BOOL    L_URL_EqualProtocol ( IN     t_url     *url1,
                                     IN     t_url     *url2 ) ;
     /* - */
     /* - */

     T_BOOL    L_URL_EqualMachine  ( IN     t_url     *url1,
                                     IN     t_url     *url2 ) ;
     /* - */
     /* - */

     T_INT     L_URL_UrlCmp        ( IN     t_url     *url1,
                                     IN     t_url     *url2 ) ;
     /* - Like strcmp for urls. */
     /* - Similar a strcmp, pero para urls. */

     T_INT     L_URL_UrlBinCmp     ( IN     t_url     *url1,
                                     IN     t_url     *url2 ) ;
     /* - */
     /* - Similar a la anterior, pero de
          forma heuristica y sin comparar
          el campo relativo. */


      /*  Access  *
       * -------- */
     t_url    *L_URL_Protocol      ( IN     t_url     *url ) ;
     /* - */
     /* - */

     t_url    *L_URL_Machine       ( IN     t_url     *url ) ;
     /* - */
     /* - */

     t_url    *L_URL_File          ( IN     t_url     *url ) ;
     /* - */
     /* - */

     t_url    *L_URL_Relative      ( IN     t_url     *url ) ;
     /* - */
     /* - */

     t_url    *L_URL_Params        ( IN     t_url     *url ) ;
     /* - */
     /* - */

     t_url    *L_URL_Port          ( IN     t_url     *url ) ;
     /* - */
     /* - */


  /* ... Inline / Macro ................................................. */

      /*  Equals  *
       * -------- */
     #define    L_URL_EqualProtocol(url1,url2)           \
                (X_STRING_Equal((url1)->protocol,(url2)->protocol) == TRUE)

     #define    L_URL_EqualMachine(url1,url2)            \
                (X_STRING_Equal((url1)->machine,(url2)->machine) == TRUE)


      /*  Access  *
       * -------- */
     #define    L_URL_Protocol(url)                      \
                ( ((url) != NULL) ?                      \
                  ((url)->protocol) : NULL               \
                )

     #define    L_URL_Machine(url)                       \
                ( ((url) != NULL) ?                      \
                  ((url)->machine ) : NULL               \
                )

     #define    L_URL_File(url)                          \
                ( ((url) != NULL) ?                      \
                  ((url)->file    ) : NULL               \
                )

     #define    L_URL_Relative(url)                      \
                ( ((url) != NULL) ?                      \
                  ((url)->relative) : NULL               \
                )

     #define    L_URL_Params(url)                        \
                ( ((url) != NULL) ?                      \
                  ((url)->params  ) : NULL               \
                )

     #define    L_URL_Port(url)                          \
                ( ((url) != NULL) ?                      \
                  ((url)->port    ) : 0                  \
                )


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

