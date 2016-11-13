

 #ifndef V_ALLOC_M
 #define V_ALLOC_M

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/v_alloc.h"


   /* ... Inline / Macros ............................................... */

      #if defined(__MEMORY_DEBUG__)

           #define V_ALLOC_Malloc(size)                            \
                   I_ALLOC_DEBUG_Malloc((size),                    \
                                        __FILE__,__LINE__)

           #define V_ALLOC_Free(ptr)                               \
                   I_ALLOC_DEBUG_Free((ptr),                       \
                                        __FILE__,__LINE__)

           #define V_ALLOC_Realloc(block,size)                     \
                   I_ALLOC_DEBUG_Realloc((block),(size),           \
                                        __FILE__,__LINE__)


           #define V_ALLOC_MemMove(dest,src,count)                 \
                   I_ALLOC_DEBUG_MemMove((dest),(src),(count),     \
                                        __FILE__,__LINE__)

           #define V_ALLOC_MemSet(dest,value,count)                \
                   I_ALLOC_DEBUG_MemSet((dest),(value),(count),    \
                                        __FILE__,__LINE__)


           #define V_ALLOC_Available()                             \
                   I_ALLOC_DEBUG_Available(__FILE__,__LINE__)

           #define V_ALLOC_ChkPtr(ptr)                             \
                   I_ALLOC_DEBUG_ChkPtr((ptr),                     \
                                        __FILE__,__LINE__)

      #else

           #define V_ALLOC_Malloc(size)                            \
                   I_ALLOC_FINAL_Malloc((size))

           #define V_ALLOC_Free(ptr)                               \
                   I_ALLOC_FINAL_Free((ptr))

           #define V_ALLOC_Realloc(block,size)                     \
                   I_ALLOC_FINAL_Realloc((block),(size))


           #define V_ALLOC_MemMove(dest,src,count)                 \
                   I_ALLOC_FINAL_MemMove((dest),(src),(count))

           #define V_ALLOC_MemSet(dest,value,count)                \
                   I_ALLOC_FINAL_MemSet((dest),(value),(count))


           #define V_ALLOC_Available()                             \
                   I_ALLOC_FINAL_Available()

           #define V_ALLOC_ChkPtr(ptr)                             \
                   I_ALLOC_FINAL_ChkPtr((ptr))

      #endif


 /* ...................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif 

