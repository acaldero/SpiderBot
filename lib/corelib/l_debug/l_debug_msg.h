

 #ifndef L_DEBUG_MSG_H
 #define L_DEBUG_MSG_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Consts / Constantes ........................................... */

      #define  INFO     __LINE__,__FILE__,0
      #define  WARNING  __LINE__,__FILE__,1
      #define  ERROR    __LINE__,__FILE__,2
 

   /* ... Globla var. / Variables glob. ................................. */

      extern T_INT  (*L_DEBUG_MSG_PrintMsg)(const T_CHAR *, va_list) ;


   /* ... Functions / Funciones ......................................... */
      
      void   L_DEBUG_MSG_Write    ( IN    T_U_INT  line,
                                    IN    T_CHAR  *name,
			            IN    T_INT    type,
			            IN    T_BOOL   printwhere,
			            IN    T_CHAR  *msg ) ;
      /* - Write a debug string using L_DEBUG_MSG_PrintMsg,
           if this var. is NOT null. */
      /* - Escribe una tira de caracteres usando 
           L_DEBUG_MSG_PrintMsg, si no es null. */

      void   L_DEBUG_MSG_VPrintF  ( IN    T_U_INT  line,
                                    IN    T_CHAR  *name,
                                    IN    T_INT    type,
                                    IN    T_BOOL   printwhere,
                                    IN    T_CHAR  *fto,
                                    IN    va_list  vl ) ;
      /* - */
      /* - Escribe un mensaje, usando formato y lista
           de argumentos variables. */

      void   L_DEBUG_MSG_PrintF   ( IN    T_U_INT  line,
			            IN    T_CHAR  *name,
			            IN    T_INT    type,
			            IN    T_BOOL   printwhere,
			            IN    T_CHAR  *fto, ... ) ;
      /* - */
      /* - Escribe una tira CON FORMATO usando PrintMsg. */


   /* ................................................................... */

 #ifdef  __cplusplus
    }
 #endif


 #endif

