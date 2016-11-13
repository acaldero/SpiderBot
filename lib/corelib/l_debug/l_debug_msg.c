/* ........................................................................
 *
 * Copyright Alejandro Calderon (1997-1999)
 * <acaldero@laurel.datsi.fi.upm.es>
 *
 * permission is hereby granted to copy, modify and redistribute this code
 * in terms of the GNU Library General Public License, Version 2 or later,
 * at your option.
 *
 * ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_debug/l_debug_msg.h"


   /* ... Globla var. / Variables glob. ................................. */

      T_INT  (*L_DEBUG_MSG_PrintMsg)(const T_CHAR *, va_list) = NULL ;


   /* ... Functions / Funciones ......................................... */

      void   L_DEBUG_MSG_PrintFMsg   ( IN  T_CHAR  *fto, ... )
      {
        if (L_DEBUG_MSG_PrintMsg != NULL)
           {
             va_list vl ;

             va_start(vl,fto) ;
             (*L_DEBUG_MSG_PrintMsg)(fto,vl) ; 
       	     va_end(vl) ;
           }
      }

      void   L_DEBUG_MSG_WritePrefix ( IN    T_U_INT  line,
			               IN    T_CHAR  *name,
			               IN    T_INT    type,
			               IN    T_BOOL   printwhere )
      {
        if (L_DEBUG_MSG_PrintMsg != NULL)
           {
             if (printwhere == TRUE)
                {
                  switch(type)
                  {
                    case 0 : L_DEBUG_MSG_PrintFMsg("[INFO::%s::%i] ",
                                                   name,line) ;
                             break ;
                    case 1 : L_DEBUG_MSG_PrintFMsg("[WARNING::%s::%i] ",
                                                   name,line) ;
                             break ;
                    case 2 : L_DEBUG_MSG_PrintFMsg("[ERROR::%s::%i] ",
                                                   name,line) ;
                             break ;
                    default : ;
                  } 
                } 
             if (printwhere != TRUE)
                {
                  switch(type)
                  {
                    case 0 : L_DEBUG_MSG_PrintFMsg("[INFO] ") ;
                             break ;
                    case 1 : L_DEBUG_MSG_PrintFMsg("[WARNING] ") ;
                             break ;
                    case 2 : L_DEBUG_MSG_PrintFMsg("[ERROR] ") ;
                             break ;
                    default : ;
                  }  
                }
           }
      }

      void   L_DEBUG_MSG_Write    ( IN    T_U_INT  line,
			            IN    T_CHAR  *name,
			            IN    T_INT    type,
			            IN    T_BOOL   printwhere,
			            IN    T_CHAR  *msg   )
      {
        if (L_DEBUG_MSG_PrintMsg != NULL)
           {
             L_DEBUG_MSG_WritePrefix(line,name,type,printwhere) ;
             L_DEBUG_MSG_PrintFMsg(msg) ;
           }
      }

      void   L_DEBUG_MSG_VPrintF  ( IN    T_U_INT  line,
 			            IN    T_CHAR  *name,
			            IN    T_INT    type,
			            IN    T_BOOL   printwhere,
			            IN    T_CHAR  *fto,
                                    IN    va_list  vl )
      {
        if (L_DEBUG_MSG_PrintMsg != NULL)
           {
             L_DEBUG_MSG_WritePrefix(line,name,type,printwhere) ;
             (*L_DEBUG_MSG_PrintMsg)(fto,vl) ; 
           }
      }

      void   L_DEBUG_MSG_PrintF   ( IN    T_U_INT  line,
 			            IN    T_CHAR  *name,
			            IN    T_INT    type,
			            IN    T_BOOL   printwhere,
			            IN    T_CHAR  *fto, ... )
      {
        if (L_DEBUG_MSG_PrintMsg != NULL)
           {
             va_list vl ;

             va_start(vl,fto) ;
             L_DEBUG_MSG_WritePrefix(line,name,type,printwhere) ;
             (*L_DEBUG_MSG_PrintMsg)(fto,vl) ; 
       	     va_end(vl) ;
           }
      }


   /* ................................................................... */

