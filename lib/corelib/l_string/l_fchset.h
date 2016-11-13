

 #ifndef L_FCHSET_H
 #define L_FCHSET_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Functions / Funciones ......................................... */

     T_BOOL L_FCHSET_SkipCharSet ( INOUT  FILE   *f,
				   IN     T_CHAR *s ) ;
     /* - */
     /* - Lee caracteres, descartandolos mientras sean uno de
	  los que componen el string 'cto' y mientras no se
	  llege al final del fichero 'f' */

     T_CHAR *L_FCHSET_ReadTillCharSet  
             ( 
               INOUT  FILE    *f,
	       IN     T_CHAR  *cto,
	       IN     T_BOOL   casesense 
             ) ;
     /* - It reads chars till it found any char that is
          present in set 'cto' */
     /* - Lee caracteres hasta que se encuentre alguno que
	  pertenezca a alguno de 'cto' */

     T_BOOL  L_FCHSET_ReadBinTillCharSet  
             ( 
               INOUT  FILE     *f,
               IN     T_CHAR   *s,
               IN     T_BOOL    cs,
               OUT    T_CHAR  **buff,
               OUT    T_U_INT  *bufflen 
             ) ;
     /* - Equal that 'L_FCHSET_ReadTillCharSet', but 'buff'
          are now a buffer rather than a string */ 
     /* - Igual que 'L_FCHSET_ReadTillCharSet', pero NO
          considera 'buff' como un string */


     T_CHAR *L_FCHSET_ReadAndExpandTillCharSet
             (
               INOUT  FILE   *f,
               IN     T_CHAR *s,
               IN     T_CHAR  ch_clear,
               IN     T_CHAR *tabhits,
               IN     T_INT   width,
               IN     T_INT   wpos
             ) ;
     /* - Equal that 'L_FCHSET_ReadTillCharSet', but 
          making subtitutions at '\t' and '\n' */
     /* - Igual que 'L_FCHSET_ReadTillCharSet', pero
          se cambia '\t' y '\n' por espacios en blanco */

     T_BOOL  L_FCHSET_ReadCRLF           ( INOUT   FILE    *f,
                                           IN      T_CHAR   c ) ;
     /* - Read a enter. (binary or asci file) */
     /* - Lee un enter (tanto en ficheros 
          binarios como en ascii) */
 

 /* ...................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

