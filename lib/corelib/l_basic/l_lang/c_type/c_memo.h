

 #ifndef C_MEMO_H
 #define C_MEMO_H


  /* ... Types / Tipos ........................................*/

     #define T_BYTE       unsigned char 
     #define T_WORD       unsigned int
     #define T_POINTER    void *


  /* ... Consts / Constantes .................................. */

     /* ... byte size ... */
     #define c_BYTE       sizeof(T_BYTE)
     #define c_WORD       sizeof(T_WORD)
     #define c_POINTER    sizeof(T_POINTER)

     /* ... string format size ... */
     #define c_STR_BYTE       1
     #define c_STR_WORD       5
     #define c_STR_POINTER    11


  /* ... Macros / Macros ...................................... */

      #define HIGHB(a)            (((a) & 0xFF00) >> 8)
      #define LOWB(a)             ((a) & 0x00FF)
      #define DBYTE(h,l)          (((h) << 8) | ((l) & 0x00FF))

      #define HIGHDB(a)           (((a) & 0xFFFF0000) >> 16)
      #define LOWDB(a)            ((a) & 0x0000FFFF)
      #define DDBYTE(h,l)         (((long)(h) << 16) | ((long)(l) & 0x0000FFFF))


  /* .......................................................... */


#endif

