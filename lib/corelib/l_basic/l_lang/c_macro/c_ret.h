

 #ifndef C_RET_H
 #define C_RET_H


   /* ... Include / Inclusiones ......................................... */

      #include "corelib/l_basic/l_lang/c_type.h"


   /* ... Macros / Macros ............................................... */

      #define NULL_RET_NULL(p)      \
              if (!(p)) { return NULL ; }
      #define NULL_RET_TRUE(p)      \
              if (!(p)) { return TRUE ; }
      #define NULL_RET_FALSE(p)     \
              if (!(p)) { return FALSE ; }

      #define FALSE_RET_TRUE(p)     \
              if ((p)==FALSE) { return TRUE ; }
      #define FALSE_RET_FALSE(p)    \
              if ((p)==FALSE) { return FALSE ; }
      #define TRUE_RET_TRUE(p)      \
              if ((p)==TRUE)  { return TRUE ; }
      #define TRUE_RET_FALSE(p)     \
              if ((p)==TRUE)  { return FALSE ; }

      #define FALSE_RET_NULL(p)     \
              if ((p)==FALSE) { return NULL ; }
      #define TRUE_RET_NULL(p)      \
              if ((p)==TRUE)  { return NULL ; }

      #define NULL_UNLOCK_RET_NULL(p,c)      \
              if (!(p)) { pthread_mutex_unlock((c)) ; return NULL ; }
      #define NULL_UNLOCK_RET_TRUE(p,c)      \
              if (!(p)) { pthread_mutex_unlock((c)) ; return TRUE ; }
      #define NULL_UNLOCK_RET_FALSE(p,c)     \
              if (!(p)) { pthread_mutex_unlock((c)) ; return FALSE ; }

      #define FALSE_UNLOCK_RET_TRUE(p,c)     \
              if ((p)==FALSE) { pthread_mutex_unlock((c)) ; return TRUE ; }
      #define FALSE_UNLOCK_RET_FALSE(p,c)    \
              if ((p)==FALSE) { pthread_mutex_unlock((c)) ; return FALSE ; }
      #define TRUE_UNLOCK_RET_TRUE(p,c)      \
              if ((p)==TRUE)  { pthread_mutex_unlock((c)) ; return TRUE ; }
      #define TRUE_UNLOCK_RET_FALSE(p,c)     \
              if ((p)==TRUE)  { pthread_mutex_unlock((c)) ; return FALSE ; }

      #define FALSE_UNLOCK_RET_NULL(p,c)     \
              if ((p)==FALSE) { pthread_mutex_unlock((c)) ; return NULL ; }
      #define TRUE_UNLOCK_RET_NULL(p,c)      \
              if ((p)==TRUE)  { pthread_mutex_unlock((c)) ; return NULL ; }


   /* ................................................................... */

 #endif


