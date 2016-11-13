

 #ifndef X_ALLOC_M
 #define X_ALLOC_M

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Inline / Macro ................................................ */

      #define X_ALLOC_Malloc(size) \
              V_ALLOC_Malloc((size))

      #define X_ALLOC_Free(ptr) \
              V_ALLOC_Free((ptr))

      #define X_ALLOC_Realloc(block,size) \
              V_ALLOC_Realloc((block),(size))


      #define X_ALLOC_MemSet(dest,value,count)                          \
              V_ALLOC_MemSet((dest),(value),(count))

      #define X_ALLOC_MemMove(dest,src,count)                           \
              V_ALLOC_MemMove((dest),(src),(count))


      #define X_ALLOC_Available() \
              V_ALLOC_Available()

      #define X_ALLOC_ChkPtr(block) \
              V_ALLOC__ChkPtr((block))


 /* ...................................................................... */

 #ifdef  __cplusplus
    }
 #endif


 #endif 

