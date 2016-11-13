

 #ifndef L_FILE_COMMAND_H
 #define L_FILE_COMMAND_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_dir/x_dir.h"
      #include "weblib/l_file/l_file_log.h"


   /* ... Functions / Funciones ......................................... */

      /*  File Conection  *
       * ---------------- */
      FILE     *L_FILE_COMMAND_Open         ( IN     T_CHAR     *fname, 
                                              IN     T_CHAR     *fmode ) ;
      /* - */
      /* - */

      void      L_FILE_COMMAND_Close        ( INOUT  FILE       *fd ) ;
      /* - */
      /* - */


      /*  FILE Commands  *
       * --------------- */
      T_BOOL    L_FILE_COMMAND_Read         ( INOUT  FILE       *fd,
                                              IN     T_CHAR     *buffer, 
                                              IN     T_INT       bufferLen) ;
      /* - */
      /* - */

      T_BOOL    L_FILE_COMMAND_Write        ( INOUT  FILE       *fd,
                                              IN     T_CHAR     *buffer, 
                                              IN     T_INT       bufferLen) ;
      /* - */
      /* - */

      T_INT     L_FILE_COMMAND_stat         ( INOUT  T_CHAR       *fname,
                                              IN     struct stat  *statInfo ) ;
      /* - */
      /* - */

      T_BOOL    L_FILE_COMMAND_isDir        ( IN     struct stat  *statInfo ) ;
      /* - */
      /* - */


      /*  DIR Commands  *
       * -------------- */
      T_BOOL    L_FILE_COMMAND_FindFirstEntry  ( OUT   t_dirinfo  *d,
                                                 IN    T_CHAR     *path,
                                                 IN    T_CHAR     *filtro,
                                                 OUT   T_CHAR     **name ) ;
      /* - */
      /* - */

      T_BOOL    L_FILE_COMMAND_FindNextEntry   ( OUT   t_dirinfo  *d,
                                                 OUT   T_CHAR     **name ) ;
      /* - */
      /* - */

      T_BOOL    L_FILE_COMMAND_GetEntryInfo    ( IN    T_CHAR     *path,
                                                 IN    T_CHAR     *name,
                                                 OUT   T_LONG     *size,
                                                 OUT   T_LONG     *ctime,
                                                 OUT   T_INT      *attrib ) ;
      /* - */
      /* - */

      T_CHAR   *L_FILE_COMMAND_AllDirEntry     ( void ) ;
      /* - */
      /* - */


  /* ... Inline / Macros ............................................... */

      /*  File Conection  *
       * ---------------- */
      #define  L_FILE_COMMAND_Open(fname,fmode)                  \
               fopen((fname),(fmode))

      #define  L_FILE_COMMAND_Close(fd)                          \
               fclose((fd))

      #define  L_FILE_COMMAND_Read(buff,buffLen,fd)              \
               fread(buff,1,buffLen,fd)

      #define  L_FILE_COMMAND_Write(buff,buffLen,fd)             \
               fwrite(buff,1,buffLen,fd)

      /*  FILE Commands  *
       * --------------- */
      #define  L_FILE_COMMAND_stat(fname,statInfo)               \
               stat((fname),(statInfo))

      #define  L_FILE_COMMAND_isDir(statInfo)                    \
               (S_ISDIR((statInfo)->st_mode))

      /*  DIR Commands  *
       * -------------- */
      #define  L_FILE_COMMAND_AllDirEntry()                      \
               V_DIR_AllEntry()


  /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

