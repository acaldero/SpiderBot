

 #ifndef L_URLLI_H
 #define L_URLLI_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_string/x_string.h"
      #include "weblib/l_url/l_url.h"
      #include "weblib/l_url/l_urlfile.h"
      #include "weblib/l_url/l_urlstream.h"


   /* ... Types / Tipos ................................................. */
 
      /*
          we will store url as alone info
      */
      typedef
      struct url_field_descriptor t_url_field ;
      struct url_field_descriptor
      {
        t_url *furl ;
      } ;
 
 
      /* 
         we use a table to store, but we see as binary
         tree when looking for entry.
      */
      typedef 
      struct entry_descriptor t_entry ;
      struct entry_descriptor
      {
        t_url_field    entry ;
        t_entry       *left ;
        t_entry       *right ;
      } ;
 

      /*
          we will store url as string
      */
      typedef 
      struct urlbt_descriptor t_urlLi ;
      struct urlbt_descriptor
      {
        t_entry    **table ;
        T_U_LONG     neltos  ;
      } ;
 
 
   /* ... Const / Constantes ............................................ */

      #define  c_URL_FIELD   (sizeof(t_url_field))
      #define  c_ENTRY       (sizeof(t_entry))
      #define  c_URLBT       (sizeof(t_urlLi))


   /* ... Functions / Funciones ......................................... */
 
      t_urlLi    *L_URLLI_Creat   ( void ) ;
      /*   - Return a pointer to urls list */
      /*   - Retorna puntero a una lista de urls,
             usando 'malloc' */

      T_BOOL      L_URLLI_Destroy       ( INOUT t_urlLi     **urlbt ) ;
      /*   - Free all url in '(*liurl)' and (*liurl)' */
      /*   - Borra todos los urls del tabla y
             despues la tabla */
 
      T_BOOL      L_URLLI_IsPresent     ( IN    t_urlLi      *urlbt,
                                          IN    t_url        *elto ) ;
      /*   - */
      /*   - Retorna TRUE si los datos de 'elto'
             estan en la tabla ya insertados. */

      T_U_LONG    L_URLLI_NumberUrls    ( IN    t_urlLi      *urlbt ) ;
      /*   - */
      /*   - Retorna el numero de urls almacenados en la lista */

      t_url      *L_URLLI_UrlIn         ( IN    t_urlLi      *urlbt,
                                          IN    T_U_LONG      index  ) ;
      /*   - */
      /*   - Retorna el simbolo que se encuentre 
             en la posicion `index`. */

      T_BOOL      L_URLLI_Insert        ( INOUT t_urlLi      *urlbt,
                                          IN    t_url        *elto ) ;
      /*   - Add 'elto' into 'urlbt' tree */
      /*   - Anade un urls al arbol. */

 
   /* ... Inline / Macros ............................................... */

      #define L_URLLI_NumberUrls(UBT) \
              ( ((UBT) == NULL) ? \
                 (0L) : ((UBT)->neltos) )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif


