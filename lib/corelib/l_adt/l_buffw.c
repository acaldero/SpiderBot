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

      #include "corelib/l_adt/l_buffw.h"


   /* ... Functions / Funciones .......................................... */

     T_BOOL L_BUFFW_CatOneByteToBuffEnd ( INOUT  T_CHAR  **b,
                                          IN     T_U_INT  *c,
					  IN     T_CHAR    ch )
     {
       T_CHAR *nb ;
  
       nb     = X_ALLOC_Realloc(*b,(*c)+2) ;
       NULL_RET_FALSE(nb) ;
       *b     = nb ;
       nb[*c] = ch ;
       (*c)++ ;
       nb[*c] = '\0' ;
       return TRUE ;
     }
  
     T_BOOL L_BUFFW_CatNBytesToBuffEnd ( INOUT  T_CHAR  **b,
					 IN     T_U_INT  *cb,
					 IN     T_CHAR   *s,
                                         IN     T_U_INT   cs )
     {
       T_CHAR *nb ;
  
       nb       = X_ALLOC_Realloc(*b,(*cb)+1+cs) ;
       NULL_RET_FALSE(nb) ;
       *b       = nb ;
       X_ALLOC_MemMove(&(nb[*cb]),s,cs) ;
       (*cb)   += cs ;
       nb[*cb]  = '\0' ;
       return TRUE ;
     } 
       
     T_BOOL L_BUFFW_AddBytesToBuffEnd ( INOUT  T_CHAR   **b, 
					IN     T_U_INT    oldcb,  
                                        IN     T_U_INT    newcb,
					IN     T_U_INT    setval )  
     { 
       T_CHAR *nb ;
  
       TRUE__SET_ERROR__RET_FALSE( (newcb < oldcb) ) ;
       nb   = X_ALLOC_Realloc(*b,newcb) ;
       NULL_RET_FALSE(nb) ;
       *b   = nb ;
       nb  += oldcb ;
       X_ALLOC_MemSet(nb,setval,(newcb-oldcb)) ;
       return TRUE ;
     }

     T_BOOL L_BUFFW_AddBytesToBuffBegin ( INOUT  T_CHAR   **b, 
					  IN     T_U_INT    oldcb,  
                                          IN     T_U_INT    newcb,
					  IN     T_U_INT    setval )  
     {
       T_CHAR *nb ;
  
       TRUE__SET_ERROR__RET_FALSE( (newcb < oldcb) ) ;
       nb   = X_ALLOC_Realloc(*b,newcb) ;
       NULL_RET_FALSE(nb) ;
       *b   = nb ;
       nb  += (newcb-oldcb) ;
       X_ALLOC_MemMove(nb,*b,oldcb) ;
       X_ALLOC_MemSet(nb,setval,(newcb-oldcb)) ;
       return TRUE ;
     }
  

  /* .................................................................... */


