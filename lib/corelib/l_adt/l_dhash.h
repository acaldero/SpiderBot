

 #ifndef L_DHASH_H
 #define L_DHASH_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_adt/l_darray.h"
      #include "corelib/l_string/x_string.h"


   /* ... Types / Tipos ................................................. */
 
      /*
          we will store key and value
      */
      typedef
      struct field_descriptor t_field ;
      struct field_descriptor
      {
        T_CHAR     *key ;
        T_POINTER   value ;
      } ;
 
 
      /* 
         we use a table to store, but we see as binary
         tree when looking for entry.
      */
      typedef 
      struct entry_descriptor t_entry ;
      struct entry_descriptor
      {
        t_field    entry ;
        t_entry   *left ;
        t_entry   *right ;
      } ;
 

      /*
          we will store as table.
      */
      typedef 
      struct dhash_descriptor t_dhash ;
      struct dhash_descriptor
      {
        t_entry    **table ;
        T_U_LONG     neltos  ;
      } ;
 
 
   /* ... Const / Constantes ............................................ */

      #define  c_FIELD    (sizeof(t_field))
      #define  c_ENTRY    (sizeof(t_entry))
      #define  c_DHASH    (sizeof(t_dhash))


   /* ... Functions / Funciones ......................................... */
 
      t_dhash    *L_DHASH_Creat           ( void ) ;
      /*   - Return a pointer to dhash header */
      /*   - Retorna puntero a una cabecera dhash,
             usando 'malloc' */

      T_BOOL      L_DHASH_Destroy        ( INOUT t_dhash     **dhash ) ;
      /*   - Free all entry in '(*dhash)' and (*dhash)' */
      /*   - Borra todos los dhash del tabla y
             despues la tabla */
 
      T_U_LONG    L_DHASH_NumberKV       ( IN    t_dhash      *dhash ) ;
      /*   - Return number elements in dhash. */
      /*   - Retorna el numero de entradas "dhash" 
             almacenados en la lista */

      T_POINTER   L_DHASH_ValueOf        ( IN    t_dhash     *dhash,
                                           IN    T_CHAR      *key,
                                           IN    T_BOOL       caseSense ) ;
      /*   - Return value link to 'key'. */
      /*   - Retorna el valor con clave 'key'. */

      T_BOOL      L_DHASH_InsertKV       ( INOUT t_dhash     *dhash,
                                           IN    T_CHAR      *key,
                                           IN    T_POINTER    value ) ;
      /*   - Add 'key-value' into 'dhash' tree */
      /*   - Anade una entrada dhash al arbol. */

 
   /* ... Inline / Macros ............................................... */

      #define L_DHASH_NumberUrls(UBT)      \
              (                            \
                ((UBT) == NULL) ?          \
                                           \
                   (0L)                    \
                   :                       \
                   ((UBT)->neltos)         \
              )


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif


