

 #ifndef L_HTTP_RESPONSE_H
 #define L_HTTP_RESPONSE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/l_line.h"
      #include "corelib/l_net/x_socket.h"
      #include "weblib/l_wdt/l_mime.h"
      #include "weblib/l_encode/l_hex.h"


   /* ... Types / Tipos ................................................. */

      typedef
      t_mime   t_http_response ;

      typedef
      enum
      {
        v_1_0, v_1_1, v_0_9
      } t_http_ver ;


   /* ... Const / Constantes ............................................ */

      #define c_HTTP_RESPONSE    sizeof(t_http_response)


   /* ... Functions / Funciones ......................................... */

      /*  header  *
       * -------- */
      t_http_response *L_HTTP_RESPONSE_Creat   ( void ) ;
      /* - */
      /* - */
 
      T_BOOL           L_HTTP_RESPONSE_Destroy ( OUT   t_http_response **httpr ) ;
      /* - */
      /* - */
 

      /*  header <-> file  *
       * ----------------- */
      T_BOOL   L_HTTP_RESPONSE_Read           ( INOUT  t_sock           *sd,
                                                OUT    t_http_response  *httpr ) ;
      /* - */
      /* - */
 
      T_BOOL   L_HTTP_RESPONSE_ResponseToFile ( INOUT  FILE             *fout,
                                                INOUT  t_http_response  *httpr ) ;
      /* - */
      /* - */
 
      T_INT    L_HTTP_RESPONSE_readChuckSize  ( INOUT  t_sock           *sd ) ;
      /* - */
      /* - */
 

      /*  header access  *
       * --------------- */
      T_CHAR  *L_HTTP_RESPONSE_getField  ( INOUT  t_http_response  *httpr,
                                           IN     T_CHAR            *field ) ;


   /* ... Inline / Macros ............................................... */

      /*  header  *
       * -------- */
      #define L_HTTP_RESPONSE_Creat()                       \
              L_MIME_Creat()

      #define L_HTTP_RESPONSE_Destroy(httpr)                \
              L_MIME_Destroy((t_mime **)(httpr))

      /*  header <-> file  *
       * ----------------- */
      #define L_HTTP_RESPONSE_ResponseToFile(fout,httpr)        \
              L_MIME_mimeToFile(fout,(t_mime *)(httpr))


      /*  header access  *
       * --------------- */
      #define L_HTTP_RESPONSE_getField(httpr,field)             \
              L_MIME_vOf((t_mime *)(httpr),(field),FALSE)


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

