

 #ifndef V_DIR_H
 #define V_DIR_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_dir/i_fffn.h"
      #include "corelib/l_dir/i_dirent.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Types / Tipos ................................................... */

      typedef struct {
                       T_CHAR *filtro, *path ;
                       struct ffblk ff ;
                       DIR *d ;
                     } t_dirinfo ;


   /* ... Const / Constantes ............................................ */

      /* tratamientos sistema ficheros */
      #define  c_LDOS       441
      #define  c_LDIRENT    442
      #define  c_FAT        451
      #define  c_XFS        452

      /* atributos 'dir entrys' */
      #define  DE_DIR       550
      #define  DE_ARCH      551
      #define  DE_RDONLY    552
      #define  DE_HIDDEN    553
      #define  DE_SYSTEM    554
      #define  DE_LABEL     555

      /* messages */
      #define  ERR_BADFST   "incorrect file system type."
      #define  ERR_BADFSL   "incorrect file system library."


   /* ... Functions / Funciones ......................................... */

      T_INT  V_DIR_Configur ( IN  T_INT  cfgnew ) ;
      /* - */
      /* - Cambia las opciones por defecto que toma la libreria.
           La nueva opcion es 'cfgnew', retornando la antigua.
           Si hay error, retorna '-1' */

      T_BOOL V_DIR_FindFirstEntry ( OUT  t_dirinfo  *d,
  			            IN   T_CHAR     *path,
                                    IN   T_CHAR     *filtro,
                                    OUT  T_CHAR     **name ) ;
      /* - */
      /* - Busca la primera entrada del directorio 'path' que concuerde con
           el patron 'filtro' */

      T_BOOL V_DIR_FindNextEntry ( OUT  t_dirinfo   *d, 
                                   OUT  T_CHAR     **name ) ;
      /* - */
      /* - Busca la siguiente entrada del directorio que concuerde con el
           'path+filtro' usado en FindFirstEntry */

      T_BOOL  V_DIR_GetEntryInfo ( IN   T_CHAR  *path, 
			           IN   T_CHAR  *name,
                                   OUT  T_LONG  *size,
                                   OUT  T_LONG  *ctime,
                                   OUT  T_INT   *attrib ) ;
      /* - */
      /* - Obtendremos los datos del fichero 'path'+'name' */

      T_BOOL V_DIR_IsAttr ( IN  T_INT  fattrib,
  			    IN  T_INT  patron ) ;
      /* - */
      /* - Si el atributo 'patron' esta en fattrib, retorna true */

      T_CHAR *V_DIR_AttrToStr ( IN  T_INT  attr ) ;
      /* - */
      /* - Ret un string statico (no hace falta hacer free de el) los
           atributos presentes en attr. Se borra en cada llamada el
           contenido del string statico.  */

      T_CHAR *V_DIR_DirSep ( void ) ;
      /* - */
      /* - Que separa directorios en el sistema de ficheros 'x'.
           Es un string estatico.  */

      T_CHAR *V_DIR_AllEntry ( void ) ;
      /* - */
      /* - Retorna el string "*.*" o "*" dependiendo del sistema
           de ficheros que se use. Es un string estatico */

      T_CHAR *V_DIR_MakeFullPath ( IN  T_CHAR  *path,
  				   IN  T_CHAR  *fname ) ;
      /* - */
      /* - Pide memoria para un string de la forma : path+sep+fname */

      T_CHAR *V_DIR_AddDirToPath ( IN  T_CHAR  *path, 
  			           IN  T_CHAR  *dname ) ;
      /* - */
      /* - Pide memoria para concatenar a path el dir 'dname' */

      void   V_DIR_MkDir         ( IN  T_CHAR  *dname,
                                   IN  T_INT    dirMode ) ;
      /* - */
      /* - Crea un directorio con los permisos de 'dirMode' */


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

