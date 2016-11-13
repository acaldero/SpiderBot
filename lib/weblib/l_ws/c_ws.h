

 #ifndef C_WS_H
 #define C_WS_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"


   /* ... Const / Constantes ............................................ */

      /**
       *
       *  When we scan a web page for urls to add
       *  to 'urllist', we can select add :
       *
       *     - (c_SS_GLOBAL)  urls from all web site
       *     - (c_SS_LOCAL)   only add url from same site 
       *     - (c_SS_COUNTRY) only add url from same contry
       *
       */
      #define    c_SS_LOCAL            100
      #define    c_SS_GLOBAL           200
      #define    c_SS_COUNTRY          300

      /**
       *
       *  When we scan a web page for urls to add
       *  to 'urllist', we can select add urls :
       *
       *     - (c_PS_HTTP) from http protocol only 
       *     - (c_PS_FTP) from ftp protocol only 
       *     - (c_PS_ALL) from all protocol 
       *
       */
      #define    c_PS_HTTP             100
      #define    c_PS_FTP              200
      #define    c_PS_ALL              300

      /**
       *
       *  When we rewrite url inside a web page for
       *  local file system browsing, we can select
       *  witch url rewrite using :
       *
       *     - (c_RS_NONE)      not change anything
       *     - (c_RS_SAME_SITE) rewrite only from web site
       *     - (c_RS_ALL_SITE)  rewrite all
       *
       */
      #define    c_RS_NONE             100
      #define    c_RS_SAME_SITE        200
      #define    c_RS_ALL_SITE         300

      /**
       *
       *  When we mirror url contents and when we
       *  rewrite url inside a web page for
       *  local file system browsing, we can select
       *  how rewrite using :
       *
       *     - (c_MS_N_DIRECTORY)   save as tree
       *     - (c_MS_1_PAGE)        save in only 1 page
       *
       */
      #define    c_MS_N_DIRECTORY      100
      #define    c_MS_1_PAGE           200


   /* ................................................................... */


 #ifdef  __cplusplus
    }
 #endif

 #endif

