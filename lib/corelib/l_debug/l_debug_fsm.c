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

      #include "corelib/l_debug/l_debug_fsm.h"


   /* ... Functions / Funciones ......................................... */

      /*  State functions  *
       * ----------------- */
      T_BOOL     L_DEBUG_FSM_writeState    ( IN     int        fsm,
                                             IN     T_CHAR    *state,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        T_CHAR  line1024[1024] ;

        sprintf(line1024,
                "%s %s:%li",
                state,file,line) ;
        lseek(fsm,0,SEEK_SET) ;
        write(fsm,line1024,strlen(line1024)) ;
        return TRUE ;
      }

      T_BOOL     L_DEBUG_FSM_readState     ( IN     int         fsm,
                                             INOUT  T_CHAR     *state,
                                             INOUT  T_CHAR     *file,
                                             INOUT  T_U_LONG   *line )
      {
        T_CHAR  line1024[1024] ;

        lseek(fsm,0,SEEK_SET) ;
        read(fsm,line1024,sizeof(line1024)) ;
        sscanf(line1024,
               "%s %s:%li",
               state,file,line) ;
        return TRUE ;
      }

      T_BOOL     L_DEBUG_FSM_existTransition ( IN     t_fsm    *fsmType,
                                               IN     T_CHAR   *state_orig,
                                               IN     T_CHAR   *state_dest )
      {
        T_U_LONG  i ;

        for (i=0; (fsmType->transitions)[i].state_orig != NULL; i++)
            {
              if (
                   (! strcmp((fsmType->transitions)[i].state_orig,state_orig))
                                            &&
                   (! strcmp((fsmType->transitions)[i].state_dest,state_dest))
                 )
                 {
                   return TRUE ;
                 }
            }
        return FALSE ;
      }


      /*  Basic functions  *
       * ----------------- */
      T_CHAR    *L_DEBUG_FSM_getName       ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        static  T_CHAR  L_DEBUG_FSM_name[1024] ;

#if defined(HAVE_PTHREAD_H)
        sprintf(L_DEBUG_FSM_name,
                "%s.%p.%li.%li",
                fsmType->name,
                fsmId,
                (long)getpid(),
                (long)pthread_self()) ;
#else
        sprintf(L_DEBUG_FSM_name,
                "%s.%p.%li",
                fsmType->name,
                fsmId,
                (long)getpid()) ;
#endif
        return L_DEBUG_FSM_name ;
      }

      int        L_DEBUG_FSM_open          ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        T_CHAR  *fsmName ;
        int      ret ;

        fsmName = L_DEBUG_FSM_getName(fsmType,fsmId,file,line) ;
        ret = open(fsmName,O_RDWR) ;
        return ret ;
      }

      void       L_DEBUG_FSM_close         ( INOUT  int        fsm )
      {
        close(fsm) ;
      }

      void       L_DEBUG_FSM_creat         ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        T_CHAR  *fsmName ;
        int      ret ;

        fsmName = L_DEBUG_FSM_getName(fsmType,fsmId,file,line) ;
        ret = creat(fsmName,S_IRWXU) ;
        if (ret < 0)
           {
             /* debug is NOT posible ... */
             X_PRINT_printf( "[%s:%li] I can NOT creat %s reference\n",
                             file,line,fsmName) ;
             exit(1) ;
           }
        L_DEBUG_FSM_writeState(ret,"begin",file,line) ;
        close(ret) ;
      }

      void       L_DEBUG_FSM_remove        ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        T_CHAR  *fsmName ;
        int      ret ;

        fsmName = L_DEBUG_FSM_getName(fsmType,fsmId,file,line) ;
        ret = unlink(fsmName) ;
        if (ret < 0)
           {
             X_PRINT_printf( "[%s:%li] unknow reference to %s\n",
                             file,line,fsmName) ;
           }
      }

      void       L_DEBUG_FSM_rename        ( IN     t_fsm     *fsmType,
                                             IN     void      *oldFsmId,
                                             IN     void      *newFsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        if ( oldFsmId != newFsmId )
           {
             T_CHAR  *oldFsmName ;
             T_CHAR  *newFsmName ;
             int      ret ;

             oldFsmName = L_DEBUG_FSM_getName(fsmType,oldFsmId,file,line) ;
             newFsmName = L_DEBUG_FSM_getName(fsmType,newFsmId,file,line) ;
             ret = rename(oldFsmName,newFsmName) ;
             if (ret < 0)
                {
                  X_PRINT_printf( "[%s:%li] unknow reference to %s\n",
                                  file,line,oldFsmName) ;
                }
           }
      }

      T_BOOL     L_DEBUG_FSM_exist         ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        T_CHAR  *fsmName ;
        int      ret ;

        fsmName = L_DEBUG_FSM_getName(fsmType,fsmId,file,line) ;
        ret = access(fsmName,F_OK) ;
        if (ret < 0)
           {
             X_PRINT_printf( "[%s:%li] unknow reference to %s\n",
                             file,line,fsmName) ;
             return FALSE ;
           }
        return TRUE ;
      }


      /*  Moving FSM  *
       * ------------ */
      T_BOOL     L_DEBUG_FSM_doTransition  ( IN     t_fsm     *fsmType,
                                             IN     void      *fsmId,
                                             IN     T_CHAR    *newState,
                                             IN     T_CHAR    *file,
                                             IN     T_U_LONG   line )
      {
        T_BOOL     ok ;
        T_CHAR    *fsmName ;
        int        ret ;
        T_CHAR     oldState[1024] ;
        T_CHAR     oldFile[1024] ;
        T_U_LONG   oldLine ;

        /* ... check if exist fsm ... */
        fsmName = L_DEBUG_FSM_getName(fsmType,fsmId,file,line) ;
        ret = access(fsmName,F_OK) ;
        if (ret < 0)
           {
             L_DEBUG_FSM_creat(fsmType,fsmId,file,line) ;
           }

        /* ... check newState is valid ... */
        oldState[0] = '\0' ;
        ret = open(fsmName,O_RDWR) ;
        if (ret < 0)
           {
             X_PRINT_printf( "[%s:%li] unknow reference to '%s'\n",
                             file,line,fsmName) ;
             return FALSE ;
           }
        ok  = L_DEBUG_FSM_readState(ret,oldState,oldFile,&oldLine) ;
        if (ok == FALSE)
           {
             X_PRINT_printf( "[%s:%li] invalid reference to '%s'\n",
                             file,line,fsmName) ;
             return FALSE ;
           }
        ok  = L_DEBUG_FSM_existTransition(fsmType,oldState,newState) ;
        if (ok == FALSE)
           {
             X_PRINT_printf( "[%s:%li] invalid transition in '%s', from '%s' to '%s'\n",
                             file,line,fsmName,oldState,newState) ;
             return FALSE ;
           }

        /* ... update new state ... */
        L_DEBUG_FSM_writeState(ret,newState,file,line) ;
        close(ret) ;

        /* ... check final state ... */
        ok  = L_DEBUG_FSM_existTransition(fsmType,newState,"end") ;
        if (ok == TRUE)
           {
             L_DEBUG_FSM_remove(fsmType,fsmId,file,line) ;
           }

        return TRUE ;
      }


   /* ................................................................... */

