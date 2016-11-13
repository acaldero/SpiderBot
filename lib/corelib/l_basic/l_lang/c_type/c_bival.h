

 #ifndef C_BIVAL_H
 #define C_BIVAL_H


  /* ... Types / Tipos ........................................*/

     #define T_BOOL       char
     #define T_FLAG       char


  /* ... Consts / Constantes .................................. */

     /* ... byte size ... */
     #define c_BOOL       sizeof(T_BOOL)
     #define c_FLAG       sizeof(T_FLAG)

     /* ... string format size ... */
     #define c_STR_BOOL       6
     #define c_STR_FLAG       4


  /* ... Values / Valores ..................................... */

     #if ( (!defined(TRUE)) || (!defined(FALSE)) )
	#define TRUE        (1)
	#define FALSE       (0)
     #endif
     #if ( (!defined(ON)) || (!defined(OFF)) )
	#define ON          (1)
	#define OFF         (0)
     #endif


/* ....................................................................... */


#endif

