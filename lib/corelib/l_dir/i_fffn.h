

 #ifndef I_FFFN_H
 #define I_FFFN_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... include / inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"


   /* ... consts / constantes ........................................... */

    /* separacion de nombres de directorios en el path */
    #define  c_DOS_DIR_SEP    "\\"

    /* como se define 'todos los ficheros y directorios' */
    #define c_FFFN_DIR_ALLENTRY    "*.*"

#if (!defined(__MSDOS__))
    #define FA_NORMAL   0x00        /* Normal file, no attributes */
    #define FA_RDONLY   0x01        /* Read only */
    #define FA_HIDDEN   0x02        /* Hidden */
    #define FA_SYSTEM   0x04        /* System */
    #define FA_LABEL    0x08        /* Volume label */
    #define FA_DIREC    0x10        /* Directory */
    #define FA_ARCH     0x20        /* Archive */
#endif


   /* ... functions / funciones ......................................... */

      /* Funciones uso directorios ... *
       * ----------------------------- */
/*
       T_BOOL I_FFFN_FindFirstEntry ( OUT   struct ffblk *ff,
   				      IN    T_CHAR *path,
				      IN    T_CHAR *filtro,
				      OUT   T_CHAR **name ) ;
*/
       /* - */
       /* - Busca la primera entrada del directorio 'path' que 
            concuerde con el patron 'filtro' */

/*
       T_BOOL I_FFFN_FindNextEntry  ( OUT    struct ffblk *ff,
   				      OUT    T_CHAR **name ) ;
*/
       /* - */
       /* - Busca la siguiente entrada del directorio 'path' 
            que concuerde con el patron 'filtro' */

/*
       T_BOOL I_FFFN_GetEntryInfo ( IN T_CHAR *path,
				    IN T_CHAR *name,
				    OUT long *size,
				    OUT long *ctime,
				    OUT T_INT *attrib ) ;
*/
       /* - */
       /* - Obtendremos los datos del fichero 'path'+'name' */


      /* Funciones tratamiento Atributos ... *
       * ----------------------------------- */
       T_BOOL I_FFFN_IsAttr ( IN T_INT fattrib,
			      IN T_INT patron ) ;
       /* - */
       /* - Si el atributo 'patron' esta en fattrib, retorna TRUE
            Los atributos son los de [ms,dr,pc]dos */

       T_CHAR *I_FFFN_AttrToStr ( IN T_INT attr ) ;
       /* - */
       /* - Retorna un string estatico (no hace falta hacer free de el) 
            los atributos presentes en attr. 
            Se borra en cada llamada el contenido del string estatico. */


   /* ... Inline / Codigo en linea ...................................... */

      #include "corelib/l_dir/i_fffn.m"


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif
