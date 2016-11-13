

 #ifndef C_SCALAR_H
 #define C_SCALAR_H


  /* ... Types / Tipos ........................................*/

     #define T_SHORT      short
     #define T_U_SHORT    unsigned short
     #define T_INT        int
     #define T_U_INT      unsigned int
     #define T_LONG       long
     #define T_U_LONG     unsigned long


  /* ... Consts / Constantes .................................. */

     /* ... byte size ... */
     #define c_INT        sizeof(T_INT)
     #define c_U_INT      sizeof(T_U_INT)
     #define c_LONG       sizeof(T_LONG)
     #define c_U_LONG     sizeof(T_U_LONG)
     #define c_SHORT      sizeof(T_SHORT)
     #define c_U_SHORT    sizeof(T_U_SHORT)


     /* ... string format size ... */
     #define c_STR_INT        10
     #define c_STR_U_INT      20 
     #define c_STR_LONG       35
     #define c_STR_U_LONG     35
     #define c_STR_SHORT      10
     #define c_STR_U_SHORT    10


  /* ... Macros / Macros ............................................... */

     #define MIN(a,b)           ( ((a)<(b)) ? (a) : (b) )
     #define MAX(a,b)           ( ((a)>(b)) ? (a) : (b) )


  /* ................................................................... */


#endif

