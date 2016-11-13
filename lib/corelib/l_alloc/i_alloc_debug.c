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

      #include "corelib/l_alloc/i_alloc_debug.h"


   /* ... Functions / Funciones ......................................... */

      t_fsmTransition I_ALLOC_DEBUG_memTRANSITIONS[] =
                      {
                        { "begin", "malloc" },
                        { "begin", "realloc" },
                        { "malloc", "realloc" },
                        { "realloc", "realloc" },
                        { "malloc", "free" },
                        { "realloc", "free" },
                        { "free", "end" },
                        { NULL, NULL }
                      } ;

      t_fsm  I_ALLOC_DEBUG_memFSM =
             {
               "DBG_memory",
               I_ALLOC_DEBUG_memTRANSITIONS
             } ;


      /*  Standard Memory Functions  *
       * --------------------------- */
      T_POINTER  I_ALLOC_DEBUG_Malloc   ( IN     T_U_INT    size,
                                          IN     T_CHAR    *file,
                                          IN     T_INT      line )
      {
        T_POINTER  pvoid ;

        pvoid = malloc(size) ;
        L_DEBUG_assert( (pvoid == NULL),ERROR,
                        errno,"malloc return NULL" ) ;
        L_DEBUG_FSM_doTransition( &I_ALLOC_DEBUG_memFSM,
                                  pvoid,
                                  "malloc",
                                  file,
                                  line ) ;
        return pvoid ;
      }

      void       I_ALLOC_DEBUG_Free     ( INOUT  T_POINTER *ptr,
                                          IN     T_CHAR    *file,
                                          IN     T_INT      line )
      {
        L_DEBUG_FSM_doTransition( &I_ALLOC_DEBUG_memFSM,
                                  (*ptr),
                                  "free",
                                  file,
                                  line ) ;
        if ( (*ptr) != NULL )
           {
             free((*ptr)) ;
             (*ptr) = NULL ;
           }
      }

      T_POINTER  I_ALLOC_DEBUG_Realloc  ( IN     T_POINTER  block, 
                                          IN     T_U_INT    size,
                                          IN     T_CHAR    *file,
                                          IN     T_INT      line )
      {
        T_POINTER  pvoid ;

        pvoid = realloc(block,size) ;
        L_DEBUG_FSM_rename( &I_ALLOC_DEBUG_memFSM,
                            block,
                            pvoid,
                            file,
                            line ) ;
        L_DEBUG_FSM_doTransition( &I_ALLOC_DEBUG_memFSM,
                                  pvoid,
                                  "realloc",
                                  file,
                                  line ) ;
        return pvoid ;
      }
      

      /*  Advanced Memory Functions  *
       * --------------------------- */
      T_POINTER  I_ALLOC_DEBUG_MemMove  ( IN     T_POINTER  dest,
                                          IN     T_POINTER  src,
                                          IN     T_U_INT    count,
                                          IN     T_CHAR    *file,
                                          IN     T_INT      line )
      {

           #if ( defined(__MSDOS__) || defined(__SUNOS__) )
               #define DebugMemMove(a,b,c) \
                       memmove((a),(b),(c))
           #endif
           #if ( defined(__LINUX__) || defined(__AIXCC__) )
               #define DebugMemMove(a,b,c) \
                       bcopy((b),(a),(c))
           #endif


        if (dest != NULL)
            DebugMemMove(dest,src,count) ;
        return dest ;
      }

      T_POINTER  I_ALLOC_DEBUG_MemSet   ( IN     T_POINTER  dest,
                                          IN     T_BYTE     byte,
                                          IN     T_U_INT    count,
                                          IN     T_CHAR    *file,
                                          IN     T_INT      line )
      {
        if (dest != NULL)
            memset(dest,byte,count) ;
        return dest ;
      }


      /*  Control Memory Functions  *
       * -------------------------- */
      T_U_LONG   I_ALLOC_DEBUG_Available ( IN     T_CHAR    *file,
                                           IN     T_INT      line )
      {
        #if defined(__MSDOS__)
            #if (!defined(_Windows))
                 return (T_U_LONG) farcoreleft() ;
            #else
                 return 0L ;
            #endif
        #endif

        #if (defined(__LINUX__) || defined(__SUNOS__) || defined(__AIX__))
             struct rlimit rl ;

             getrlimit(RLIMIT_DATA,&rl) ;
             return rl.rlim_cur ;
        #endif
      }

      T_POINTER  I_ALLOC_DEBUG_ChkPtr  ( IN     T_POINTER   b,
                                         IN     T_CHAR     *file,
                                         IN     T_INT       line )
      {
        if (b == NULL)
            fprintf(stderr,
                    "[%s:%i] Try access into a NIL/NULL pointer !!!\n",
                    file,line) ;

        L_DEBUG_FSM_exist(&I_ALLOC_DEBUG_memFSM,b,file,line) ;
        return b ;
      }


   /* ................................................................... */

