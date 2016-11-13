

 #ifndef I_FFFN_M
 #define I_FFFN_M

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... include / inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Inline / Codigo en linea ...................................... */

      #if defined(__MSDOS__)
          T_BOOL I_FFFN_FindFirstEntry ( OUT struct ffblk *ff,
      				         IN T_CHAR *path,
				         IN T_CHAR *filtro,
				         OUT T_CHAR **name ) ;
          T_BOOL I_FFFN_FindNextEntry  ( OUT struct ffblk *ff,
				         OUT T_CHAR **name ) ;
          T_BOOL I_FFFN_GetEntryInfo ( IN T_CHAR *path,
				       IN T_CHAR *name,
				       OUT long *size,
				       OUT long *ctime,
				       OUT T_INT *attrib ) ;
          T_BOOL I_FFFN_IsAttr ( IN T_INT fattrib,
			         IN T_INT patron ) ;
          T_CHAR *I_FFFN_AttrToStr ( IN T_INT attr ) ;
      #endif

      #if (!defined(__MSDOS__))
           #define I_FFFN_FindFirstEntry(ff,p,f,n)        (FALSE)
           #define I_FFFN_FindNextEntry(ff,n)             (FALSE)
           #define I_FFFN_GetEntryInfo(p,n,s,c,a)         (FALSE)
           #define I_FFFN_IsAttr(fatt,p)                  (FALSE)
           #define I_FFFN_AttrToStr(a)                    "<NAA>"

           struct ffblk { /*empty*/ } ;
      #endif


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif
