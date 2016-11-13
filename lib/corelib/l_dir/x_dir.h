

 #ifndef X_DIR_H
 #define X_DIR_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_dir/v_dir.h"
      #include "corelib/l_cdt/l_dirstk.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL X_DIR_OperOverFiles  ( IN     T_CHAR *path,
                                    IN     T_CHAR *filtro,
                                    IN     T_BOOL(*fresidual)(T_CHAR *, T_CHAR*) ) ;
      /* - */
      /* - Aplica la funcion fresidual a todos los ficheros del directorio
           path asi como su subdirectorios (recursivamente) */
  
      T_BOOL X_DIR_OperOverEntrys ( IN     T_CHAR *path,
                                    IN     T_CHAR *filtro,
                                    IN     T_BOOL(*fresidual)(T_CHAR *, T_CHAR*) ) ;
      /* - */
      /* - Aplica la funcion fresidual a todas las entradas del directorio
           'path' (ficheros y subdirectorios), asi como su 
           subdirectorios (recursivamente) */
  
      T_BOOL X_DIR_OperOverOneDirFiles ( IN     T_CHAR *path,
                                         IN     T_CHAR *filtro,
                                         IN     T_BOOL(*fresidual)(T_CHAR *, T_CHAR*) ) ;
      /* - */
      /* - Aplica la funcion fresidual solo a los ficheros del directorio
           path, NO a sus subdirectorios */
  

 /* ...................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

