

 #ifndef L_FTOKEN_H
 #define L_FTOKEN_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_debug/l_debug.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_string/l_fchset.h"
      #include "corelib/l_string/l_fstr.h"
      #include "corelib/l_adt/l_buffa.h"


   /* ... Functions / Funciones ......................................... */

     T_BOOL L_FTOKEN_RWTillToken   ( IN     FILE     *fin,
                                     OUT    FILE     *fout,
                                     IN     T_CHAR  **toklist,
                                     INOUT  T_INT    *tokfound,
                                     IN     T_CHAR   *delimitadores,
                                     IN     T_BOOL    casesense ) ;
     /* - Read from 'fin' and write at 'fout', 
          until a token from 'toklist' is read. 
          Token found ( toklist[tokfound] ) IS wrote 
          into 'fout'.*/
     /* - */

     T_BOOL L_FTOKEN_ReadTillToken  ( IN     FILE     *f,
                                      IN     T_CHAR  **toklist,
                                      INOUT  T_CHAR  **buff,
                                      INOUT  T_U_INT  *buffsize,
                                      INOUT  T_INT    *tokfound,
                                      IN     T_CHAR   *delimitadores,
                                      IN     T_BOOL    casesense ) ;
     /* - Same as 'L_FTOKEN_RWTillToken', but what is
          read from 'f' IS catenate at buffer 'buff'. */
     /* - */

     T_BOOL L_FTOKEN_SkipTillToken ( IN     FILE     *fin,
                                     IN     T_CHAR  **toklist,
                                     INOUT  T_INT    *tokfound,
                                     IN     T_CHAR   *delimitadores,
                                     IN     T_BOOL    casesense ) ;
     /* - Read from 'fin' until a token 
          from 'toklist' is read. */
     /* - */

     T_BOOL L_FTOKEN_ReadAndExpandTillToken
            (
              IN     FILE     *f,
              IN     T_CHAR  **toklist,
              INOUT  T_CHAR  **buff,
              INOUT  T_U_INT  *buffsize,
              INOUT  T_INT    *tokfound,
              IN     T_CHAR   *delimitadores,
              IN     T_CHAR   *tabhits,
              IN     T_INT     width,
              IN     T_CHAR    chclear
            ) ;
     /* - Same as 'L_FTOKEN_ReadTillToken', but with
          2 differences :
           - tabular char ('\t'), enter ('\n') are 
             change with spaces in order to fill 
             lines of 'width' chars. 
           - token is NOT written when is found.
     */
     /* - */


   /* .................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

