

 #ifndef L_FSTR_H
 #define L_FSTR_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fchset.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Functions / Funciones ......................................... */

     T_BOOL  L_FSTR_RWTillStr    ( INOUT  FILE    *fin,
                                   INOUT  FILE    *fout,
                                   IN     T_CHAR  *str,
                                   IN     T_BOOL   CaseSense ) ;
     /* - */
     /* - */

     T_BOOL L_FSTR_SkipTillStr   ( INOUT  FILE    *fin,
                                   IN     T_CHAR  *pattern,
			  	   IN     T_BOOL   CaseSense ) ;
     /* - */
     /* - */

     T_BOOL  L_FSTR_AcceptStr    ( INOUT  FILE   *fin,
				   IN     T_CHAR *pattern,
				   IN     T_BOOL  CaseSensetive ) ;
     /* - Read 'pattern' from file.
          If it can not read, file position are NOT modified. */
     /* - Lee 'pattern' del fichero.
	  Si no puede, se queda la posicion de lectura en el punto
	  en el cual comenzo a leer */

     T_CHAR *L_FSTR_GetItemValue ( INOUT  FILE *f,
				   IN     T_CHAR *item,
				   IN     T_BOOL CaseSense,
				   IN     T_CHAR *deli ) ;
     /* - */
     /* - Salta caracteres en 'deli', comprueba que el siguiente
	  item sea 'item' (si no ret NULL), salta 'deli' otra vez y
	  retorna una copia del item leido del fichero hasta
	  encontrar caracteres de 'deli'. (si el valor esta
	  rodeado de comillas, se lee lo que haya entre ellas
	  literalmente */

     T_BOOL  L_FSTR_SearchStr ( INOUT  FILE   *f,
                                IN     T_CHAR *str,
                                IN     T_BOOL  CaseSense ) ;
     /* - */
     /* - */

     T_BOOL  L_FSTR_SkipCharSetAndAcceptStr ( INOUT  FILE    *f,
                                              IN     T_CHAR  *pattern,
                                              IN     T_BOOL   CaseSense,
                                              IN     T_CHAR  *deli ) ;
     /* - */
     /* - */


   /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

