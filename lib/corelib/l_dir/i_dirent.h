

 #ifndef I_DIRENT_H
 #define I_DIRENT_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... include / inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... consts / constantes ........................................... */

      /* separacion de nombres de directorios en el path */
      #define  c_DOS_DIR_SEP    "\\"
      #define  c_UNIX_DIR_SEP    "/"

      /* como se define 'todos los ficheros y directorios' */
      #define c_DIRENT_DIR_ALLENTRY    "*"

      /* messages */
      #define  ERR_PDENIED   "File with permission denied"


   /* ... functions / funciones ......................................... */

      /* Funciones uso directorios ... *
       * ----------------------------- */
       T_BOOL I_DIRENT_FindFirstEntry ( OUT  DIR     **d,
                                        IN   T_CHAR  *path, 
                                        IN   T_CHAR  *filtro,
                                        OUT  T_CHAR  **name ) ;
       /* - */
       /* - Busca la primera entrada del directorio 'path' que 
            concuerde con el patron 'filtro' */

       T_BOOL I_DIRENT_FindNextEntry  ( OUT  DIR     **d, 
                                        IN   T_CHAR  *filtro,
                                        OUT  T_CHAR  **name ) ;
       /* - */
       /* - Busca la siguiente entrada del directorio 'path' 
            que concuerde con el patron 'filtro' */

       T_BOOL I_DIRENT_GetEntryInfo ( IN   T_CHAR  *path, 
                                      IN   T_CHAR  *name,
                                      IN   T_CHAR  *sep,
                                      OUT  T_LONG  *size,
                                      OUT  T_LONG  *ctime,
                                      OUT  T_INT   *attrib ) ;
       /* - */
       /* - Obtendremos los datos del fichero 'path'+'name' */


      /* Funciones tratamiento Atributos ... *
       * ----------------------------------- */
       T_BOOL I_DIRENT_IsAttr ( IN  T_INT  fattrib, 
                                IN  T_INT  patron ) ;
       /* - */
       /* - Si el atributo 'patron' esta en fattrib, retorna true
            Los atributos son los usuales en unix */

       T_CHAR *I_DIRENT_AttrToStr ( IN  T_INT  attr ) ;
       /* - */
       /* - Ret un string statico (no hace falta hacer free de el) los
            atributos presentes en attr. Se borra en cada llamada el
            contenido del string statico. */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif
