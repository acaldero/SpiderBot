

 #ifndef I_ALLOC_FINAL_M
 #define I_ALLOC_FINAL_M

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/i_alloc_final.h"


   /* ... Inline / Macros ............................................... */

      #define I_ALLOC_FINAL_Malloc(size)                  \
              malloc((size))

      #define I_ALLOC_FINAL_Free(ptr)                     \
              {                                           \
                free((*(ptr))) ;                          \
                (*(ptr)) = NULL ;                         \
              }

      #define I_ALLOC_FINAL_Realloc(block,size)           \
              realloc((block),(size))

      #define I_ALLOC_FINAL_MemSet(dest,value,count)      \
              memset((dest),(value),(count))

      #define I_ALLOC_FINAL_MemMove(dest,src,count)       \
              memmove((dest),(src),(count))

      #define I_ALLOC_FINAL_ChkPtr(ptr)                   \
              (ptr)


 /* ...................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif 

