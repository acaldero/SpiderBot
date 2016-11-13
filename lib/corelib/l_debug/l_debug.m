

 #ifndef L_DEBUG_M
 #define L_DEBUG_M


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Inline / Expansiones .......................................... */
      
      #define XCHECK_RET_XRET(xcheck,xl,xret,xerrno,xmsg)             \
              {                                                       \
                if ((xcheck))                                         \
                   {                                                  \
                     errno = (xerrno) ;                               \
                     L_DEBUG_MSG_Write(xl,FALSE,(xmsg)) ;             \
                     return (xret) ;                                  \
                   }                                                  \
              } 


      /*  TRUE condition  *
       * ---------------- */
      #define TRUE__SET_ERROR__RET_LONG(cond,xlong)                   \
              XCHECK_RET_XRET((cond)==TRUE,ERROR,xlong,ERR__BAD_VALUE,#cond)
      #define TRUE__SET_WARNING__RET_LONG(cond,xlong)                 \
              XCHECK_RET_XRET((cond)==TRUE,WARNING,xlong,ERR__BAD_VALUE,#cond)
      #define TRUE__SET_INFO__RET_LONG(cond,xlong)                    \
              XCHECK_RET_XRET((cond)==TRUE,INFO,xlong,ERR__BAD_VALUE,#cond)


      /*  NULL value  *
       * ------------ */
      #define NULL__SET_ERROR__RET_NULL(ptr)                          \
              XCHECK_RET_XRET((ptr)==NULL,ERROR,NULL,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_ERROR__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==NULL,ERROR,TRUE,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_ERROR__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==NULL,ERROR,FALSE,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_WARNING__RET_NULL(ptr)                          \
              XCHECK_RET_XRET((ptr)==NULL,WARNING,NULL,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_WARNING__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==NULL,WARNING,TRUE,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_WARNING__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==NULL,WARNING,FALSE,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_INFO__RET_NULL(ptr)                          \
              XCHECK_RET_XRET((ptr)==NULL,INFO,NULL,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_INFO__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==NULL,INFO,TRUE,ERR__NULL_PARAM,#ptr" == NULL")
      #define NULL__SET_INFO__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==NULL,INFO,FALSE,ERR__NULL_PARAM,#ptr" == NULL")


      /*  TRUE value  *
       * ------------ */
      #define TRUE__SET_ERROR__RET_NULL(ptr)                          \
              XCHECK_RET_XRET((ptr)==TRUE,ERROR,NULL,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_ERROR__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==TRUE,ERROR,TRUE,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_ERROR__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==TRUE,ERROR,FALSE,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_WARNING__RET_NULL(ptr)                          \
              XCHECK_RET_XRET((ptr)==TRUE,WARNING,NULL,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_WARNING__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==TRUE,WARNING,TRUE,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_WARNING__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==TRUE,WARNING,FALSE,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_INFO__RET_NULL(ptr)                          \
              XCHECK_RET_XRET((ptr)==TRUE,INFO,NULL,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_INFO__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==TRUE,INFO,TRUE,ERR__NULL_PARAM,#ptr" == TRUE")
      #define TRUE__SET_INFO__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==TRUE,INFO,FALSE,ERR__NULL_PARAM,#ptr" == TRUE")


      /*  FALSE value  *
       * ------------- */
      #define FALSE__SET_ERROR__RET_FALSE(ptr)                          \
              XCHECK_RET_XRET((ptr)==FALSE,ERROR,FALSE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_ERROR__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==FALSE,ERROR,TRUE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_ERROR__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==FALSE,ERROR,FALSE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_WARNING__RET_FALSE(ptr)                          \
              XCHECK_RET_XRET((ptr)==FALSE,WARNING,FALSE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_WARNING__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==FALSE,WARNING,TRUE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_WARNING__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==FALSE,WARNING,FALSE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_INFO__RET_FALSE(ptr)                          \
              XCHECK_RET_XRET((ptr)==FALSE,INFO,FALSE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_INFO__RET_TRUE(ptr)                          \
              XCHECK_RET_XRET((ptr)==FALSE,INFO,TRUE,ERR__NULL_PARAM,#ptr" == FALSE")
      #define FALSE__SET_INFO__RET_FALSE(ptr)                         \
              XCHECK_RET_XRET((ptr)==FALSE,INFO,FALSE,ERR__NULL_PARAM,#ptr" == FALSE")


      /*  OLD style  *
       * ----------- */
      #define L_DEBUG_NULL_W_N(ptr,msg)  \
              {                          \
                if (ptr==NULL)           \
                   {                     \
                     L_DEBUG_MSG_Write(WARNING,FALSE,msg) ; \
                     return NULL ;       \
                   }                     \
              } 

      #define L_DEBUG_NULL_E_N(ptr,msg)  \
              {                          \
                if (ptr==NULL)           \
                   {                     \
                     L_DEBUG_MSG_Write(ERROR,FALSE,msg) ; \
                     return NULL ;       \
                   }                     \
              } 

      #define L_DEBUG_NULL_W_T(ptr,msg)  \
              {                          \
                if (ptr==NULL)           \
                   {                     \
                     L_DEBUG_MSG_Write(WARNING,FALSE,msg) ; \
                     return TRUE ;       \
                   }                     \
              } 

      #define L_DEBUG_NULL_E_T(ptr,msg)  \
              {                          \
                if (ptr==NULL)           \
                   {                     \
                     L_DEBUG_MSG_Write(ERROR,FALSE,msg) ; \
                     return TRUE ;       \
                   }                     \
              } 

      #define L_DEBUG_NULL_W_F(ptr,msg)  \
              {                          \
                if (ptr==NULL)           \
                   {                     \
                     L_DEBUG_MSG_Write(WARNING,FALSE,msg) ; \
                     return FALSE ;       \
                   }                     \
              } 

      #define L_DEBUG_NULL_E_F(ptr,msg)  \
              {                          \
                if (ptr==NULL)           \
                   {                     \
                     L_DEBUG_MSG_Write(ERROR,FALSE,msg) ; \
                     return FALSE ;       \
                   }                     \
              } 



   /* ................................................................... */


 #endif

