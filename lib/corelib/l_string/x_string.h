

 #ifndef X_STRING_H
 #define X_STRING_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Functions / Funciones ......................................... */

      /*  String Length  *
       * --------------- */
       T_U_LONG  X_STRING_StrLen       ( IN  T_CHAR  *str ) ;
       /* - */
       /* - Retorna la longitud de 'str'. 
            (si ('str'==NULL) --> ret 0L) */

       T_U_INT  X_STRING_StrLenF       ( IN  T_CHAR   *format,
                                         IN  va_list   argl ) ;
       /* - */
       /* - */


      /*  Char's string functions  *
       * ------------------------- */
       T_U_LONG  X_STRING_StrChrNumber ( IN  T_CHAR  *str,
     			 	         IN  T_CHAR   ch ) ;
       /* - Return how many times we can found
            'ch' character in string 'str'. */
       /* - Cuenta el numero de veces que se da el 
            caracter ch en el string 'str' */

       T_CHAR   *X_STRING_StrChrSetChange ( INOUT  T_CHAR  *str,
                                            IN     T_CHAR  *chseto,
                                            IN     T_CHAR   chd ) ;
       /* - */
       /* - */

       T_CHAR   *X_STRING_StrChrCh        ( INOUT  T_CHAR  *str,
  	 		                    IN     T_CHAR   cho,
			                    IN     T_CHAR   chd ) ;
       /* - Change each 'cho' character with 'chd' in
            string 'str'. */
       /* - Cambia cada caracter 'cho' que haya en str por el 
            caracter 'chd' */

       T_CHAR   *X_STRING_StrChr       ( IN     T_CHAR  *str,
	 		                 IN     T_CHAR   ch ) ;
       /* - */
       /* - Retorna un puntero a la primera posicion en str 
            con ocurrencia de ch */

       T_CHAR   *X_STRING_CaseStrChr   ( IN     T_CHAR  *str,
  	 		                 IN     T_CHAR   ch,
	 		                 IN     T_BOOL   cs ) ;
       /* - */
       /* - Retorna un puntero a la primera posicion en str 
            con ocurrencia de ch */

       T_CHAR    X_STRING_LastChar     ( IN     T_CHAR  *str ) ;
       /* - */
       /* - Retorna el caracter que ocupa la ultima
            posicion en el string 'str' */

       T_CHAR    X_STRING_FirstChar    ( IN     T_CHAR  *str ) ;
       /* - */
       /* - Retorna el caracter que ocupa la primera
            posicion en el string 'str' */

       T_CHAR    X_STRING_CharIn       ( IN     T_CHAR  *str,
                                         IN     T_INT    index ) ; 
       /* - */
       /* - Retorna el caracter que ocupa la posicion
            'index' en el string (0 .. strlen(str)-1) */


      /*  String compare  *
       * ---------------- */
       T_BOOL    X_STRING_Equal        ( IN  T_CHAR  *str1,
  			                 IN  T_CHAR  *str2 ) ;
       /* - */
       /* - Retorna si el string 'str' es 'model'. */

       T_BOOL    X_STRING_NEqual       ( IN  T_CHAR  *str1,
      			                 IN  T_CHAR  *str2,
			                 IN  T_INT    nchar ) ;
       /* - */
       /* - Retorna si el string 'str' es 'model'. */

       T_BOOL    X_STRING_CaseEqual    ( IN  T_CHAR  *str ,
			                 IN  T_CHAR  *model,
			                 IN  T_BOOL   CSense ) ;
       /* - */
       /* - Retorna si el string 'str' es 'model'. */

       T_BOOL    X_STRING_CaseNEqual   ( IN  T_CHAR  *str ,
			                 IN  T_CHAR  *model,
			                 IN  T_INT    nchar,
			                 IN  T_BOOL   CSense ) ;
       /* - */
       /* - Retorna si el string 'str' es 'model'. */

       T_INT     X_STRING_StrCmp       ( IN  T_CHAR  *str1 ,
			                 IN  T_CHAR  *str2 ) ;
       /* - */
       /* - Como 'strcmp' pero accepta parametros
            que valgan NULL. */

       T_INT     X_STRING_CaseStrCmp   ( IN  T_CHAR  *str1 ,
			                 IN  T_CHAR  *str2 ,
			                 IN  T_BOOL   CSense ) ;
       /* - */
       /* - Como 'X_STRING_StrCmp' pero no importa  
            mayusculas/minusculas. */

       T_BOOL    X_STRING_Match        ( IN  T_CHAR  *str ,
			                 IN  T_CHAR  *model,
			                 IN  T_BOOL   CSense ) ;
       /* - */
       /* - Retorna si el string 'model' modela a 'str'.
            En model SI vale wildcards como '*', '?'. 
            Segun 'CSense' la comparacion diferencia entre 
            mayusculas (TRUE) o no (FALSE) */


      /*  String operations  *
       * ------------------- */
       T_CHAR   *X_STRING_StrUpr       ( IN  T_CHAR  *str ) ;
       /* - Convert string 'str' to upper case. */
       /* - Pone a mayusculas todo 'str' */

       T_CHAR   *X_STRING_StrLwr       ( IN  T_CHAR  *str ) ;
       /* - Convert string 'str' to lower case. */
       /* - Pone a minusculas todo 'str' */


      /*  String MEMORY management functions  *
       * ------------------------------------ */
       T_CHAR *X_STRING_ConcatInStr ( IN  T_CHAR  *str1,
				      IN  T_CHAR  *str2,
				      IN  T_CHAR   *str3 ) ;
       /* - Alloc memory and uset it to concat 
            'str1'+'str2'+'str3'. */
       /* - Pide memoria para concatenar 'str1'+'str2'+'str3', y
  	    retorna el string resultante o NULL si no 
            hay memoria suficiente.  */

       T_BOOL  X_STRING_AddStrToStr ( INOUT  T_CHAR  **strd,
                                      IN     T_CHAR   *str1,
                                      ... ) ;
       /* - Realloc memory used by (*strd), and uset it to 
            concat to (*strd) 'str1'. */
       /* - Pide memoria para concatenar a 'strd' 'str1'.
            Retorna TRUE si todo fue bien */

       T_BOOL  X_STRING_Add2StrToStr ( INOUT  T_CHAR  **strd,
				       IN     T_CHAR   *str1,
				       IN     T_CHAR   *str2 ) ;
       /* - */
       /* - Pide memoria para concatenar a 'strd', 'str1'+'str2'
  	    Retorna TRUE si todo fue bien */

       T_CHAR *X_STRING_StrDup   ( IN  T_CHAR  *str ) ;
       /* - */
       /* - Retorna zona de memoria de memoria con una copia del
  	    string 'str'. Ret. NULL si hubo problemas */

       T_BOOL  X_STRING_StrAjust ( INOUT  T_CHAR  **str ) ;
       /* - */
       /* - El espacio de memo asignado al string 'str', 
            sera su longitud util para quitar la memoria de 
            mas que no se utiliza.
	    Siempre ret. TRUE */

       T_CHAR *X_STRING_Dvsprintf ( IN  T_CHAR   *format,
			            IN  va_list   argl ) ;
       /* - */
       /* - Actual igual que vsprintf, pero pide memoria 
            dinamica para el string donde se imprime.
            Retorna NULL si no pudo.  */

       T_CHAR *X_STRING_Dsprintf ( IN  T_CHAR   *format, ... ) ;
       /* - */
       /* - Igual que la anterior, solo varia los argumentos */


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

