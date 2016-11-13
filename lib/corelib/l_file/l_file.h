

 #ifndef L_FILE_H
 #define L_FILE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_dir/v_dir.h"


   /* ... Const / Constantes ............................................ */

 #if defined(__SUNOS__)
      #define SEEK_SET 0  /* Seeks from beginning of file */
      #define SEEK_CUR 1  /* Seeks from current position  */
      #define SEEK_END 2  /* Seeks from end of file */
 #endif

      #define  c_FBUFFSIZE       (32*1024)
      #define  c_EXEHEADERSIZE    28
      #define  c_DOSEXEID        "MZ"


   /* ... Functions / Funciones ......................................... */

      /*  File contents ...  *
       * ------------------- */
       T_BOOL    L_FILE_CopyFile ( INOUT  FILE    *fdin,
                                   INOUT  FILE    *fdout,
                                   IN     T_LONG   nbytes ) ;
       /* - Copy from 'fdin' to 'fdout' 'nbytes' bytes, 
            starting at current both position */
       /* - Copia de 'fdin' a 'fdout' nbytes, 
            desde donde esten */

       T_LONG    L_FILE_FileSize ( IN     FILE    *f ) ;
       /* - Return 'f' file size. */
       /* - Retorna el taman~o del fichero 'f' */

       T_BOOL    L_FILE_IsDosExe ( IN     FILE    *f ) ;
       /* - Return if 'f' is a D.O.S. program */
       /* - Retorna si es un fichero ejecutable de D.O.S.  */


      /*  File name ...  *
       * --------------- */
       T_BOOL  L_FILE_Rename      ( IN     T_CHAR   *orig,
                                    IN     T_CHAR   *dest ) ;
       /* - Rename file called 'orig' to 'dest'. */
       /* - Renombra fichero de 'orig' a 'dest'. */

       T_BOOL  L_FILE_Move     ( IN     T_CHAR   *orig,
                                 IN     T_CHAR   *dest ) ;
       /* - Move file called 'orig' to 'dest'. */
       /* - Mueve el fichero de 'orig' a 'dest'. */

       T_CHAR *L_FILE_SpecialName ( IN  T_CHAR  *suffix ) ;
       /* - */
       /* - Pide memoria para generar el nombre de un fichero,
            usando la hora actual, y retorna el string. */

       T_BOOL  L_FILE_SimplifyPath  ( INOUT  T_CHAR  *fpath ) ;
       /* - */
       /* - */


      /*  File descriptor ...  *
       * --------------------- */
       FILE     *L_FILE_FullPathOpen ( IN  T_CHAR  *fpath,
                                       IN  T_CHAR  *fileMode,
                                       IN  T_INT    dirMode ) ;
       /* - Like fopen, but L_FILE_FullPathOpen will created
            directory in 'fpath' if necesary. */
       /* - Como el fopen, pero crea los directorios
            necesarios entremedias. */
 

   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

