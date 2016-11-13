

 #ifndef L_MIME_H
 #define L_MIME_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Types / Tipos ................................................. */
 
      /*
          we will store key and value
      */
      typedef
      struct kv_field_descriptor t_kv_field ;
      struct kv_field_descriptor
      {
        T_CHAR  *key ;
        T_CHAR  *value ;
      } ;
 
 
      /* 
         we use a table to store, but we see as binary
         tree when looking for entry.
      */
      typedef 
      struct kv_entry_descriptor t_kv_entry ;
      struct kv_entry_descriptor
      {
        t_kv_field    entry ;
        t_kv_entry   *left ;
        t_kv_entry   *right ;
      } ;
 

      /*
          we will store as table.
      */
      typedef 
      struct mime_descriptor t_mime ;
      struct mime_descriptor
      {
        t_kv_entry    **table ;
        T_U_LONG        neltos  ;
      } ;
 
 
   /* ... Const / Constantes ............................................ */

      #define  c_KV_FIELD    (sizeof(t_kv_field))
      #define  c_KV_ENTRY    (sizeof(t_kv_entry))
      #define  c_MIME        (sizeof(t_mime))


   /* ... Functions / Funciones ......................................... */
 
      t_mime    *L_MIME_Creat           ( void ) ;
      /*   - Return a pointer to mime header */
      /*   - Retorna puntero a una cabecera mime,
             usando 'malloc' */

      T_BOOL      L_MIME_Destroy        ( INOUT t_mime     **mimeh ) ;
      /*   - Free all entry in '(*mimeh)' and (*mimeh)' */
      /*   - Borra todos los mime del tabla y
             despues la tabla */
 
      T_U_LONG    L_MIME_NumberKV       ( IN    t_mime      *mimeh ) ;
      /*   - */
      /*   - Retorna el numero de entradas "mime" 
             almacenados en la lista */

      T_CHAR     *L_MIME_vOf            ( IN    t_mime   *mimeh,
                                          IN    T_CHAR   *key,
                                          IN    T_BOOL    caseSense ) ;
      /*   - */
      /*   - Retorna el valor con clave 'key'. */

      T_BOOL      L_MIME_Insert        ( INOUT t_mime      *mimeh,
                                         IN    T_CHAR      *key,
                                         IN    T_CHAR      *value ) ;
      /*   - Add 'key-value' into 'mimeh' tree */
      /*   - Anade una entrada mime al arbol. */

      T_BOOL      L_MIME_mimeToFile    ( INOUT  FILE       *fout,
                                         INOUT  t_mime     *mimeh ) ;
      /*   - */
      /*   - */

 
   /* ... Inline / Macros ............................................... */

      #define L_MIME_NumberUrls(UBT) \
              ( ((UBT) == NULL) ? \
                 (0L) : ((UBT)->neltos) )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif


