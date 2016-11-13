

 #ifndef C_VER_H
 #define C_VER_H


   /* ... Version / Versi'on ............................................ */

      /* ... Version ... */
      #define VERSION_SHORT(a)                             \
              #a
      
      #define VERSION_LONG(a)                              \
              #a" ("__DATE__", "__TIME__")"      
      

      /* ... Version elements ... */
      #define ANDVER                                       \
              ","
      
      #define SYSVER(sysname,sysalt,sysrev)                \
              #sysname"."#sysalt"."#sysrev


      /* ... Version To XZY ... */
      #define VERSION_TOSTRING(a)                          \
              "Version("#a","__DATE__","__TIME__")" 

      #define VERSION_TOXML(a)                             \
              "<version>\n"                                \
                  "<id   value=("#a">\n"                   \
                  "<date value=("__DATE__">\n"             \
                  "<time value=("__TIME__">\n"             \
              "</version>\n"


   /* ................................................................... */

 #endif


