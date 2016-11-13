

 #ifndef L_MFILE_H
 #define L_MFILE_H

 #ifdef  __cplusplus
    extern "C" {
 #endif


   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_alloc/x_alloc.h"
      #include "corelib/l_string/x_string.h"
      #include "corelib/l_debug/l_debug.h"


   /* ... Types / Tipos ................................................. */

      typedef 
      struct mfile_descriptor MFILE ;

      struct 
      mfile_descriptor
      {
        T_CHAR    *mdata ;
        T_U_LONG   mfsize ;
        T_U_LONG   mfposition ;
        T_BOOL     overwrite ;
        T_BOOL     floatpos ;
      } ;


   /* ... Const / Constantes ............................................ */

      #define  c_MFILE          sizeof(struct mfile_descriptor)


   /* ... Functions / Funciones ......................................... */

      MFILE    *L_MFILE_creat   ( IN  T_CHAR  *options ) ;
      /*  - */
      /*  - Crea un 'fichero de memoria', retornando un descriptor
            asociado o NULL si hubo problemas.
            Ver "L_MFILE_options" para mas informacion sobre
            'options' */

      MFILE    *L_MFILE_open    ( IN  T_CHAR   *mdata,
                                  IN  T_U_LONG  msize,
                                  IN  T_CHAR   *options ) ;
      /*  - */
      /*  - Abre un mfichero, retornando un descriptor asociado
            o NULL si hubo problemas.
            Usara "mdata" como buffer de datos asociados. Este
            puntero se cambiara dinamicamente segun sea necesario.
            "msize" es el tamanyo de "mdata" en bytes.
            Si se pasa el valor NULL, se comportara como creat.
            Ver 'L_MFILE_options' para mas informacion sobre
            'options' */

     void      L_MFILE_close   ( INOUT  MFILE  **mf ) ;
      /*  - */
      /* - Cierra '*mf'. Liberara la memoria consumida por el
           descriptor, pero NO la empleada en el buffer de datos.
           NOTA: Si se quiere liberar toda la memoria y cerrar
           el fichero, debera usarse 'L_MFILE_unlink' para ello. */

      T_U_LONG  L_MFILE_length  ( IN  MFILE  *mf ) ;
      /*  - */
      /* - Retorna la longitud del mfichero 'mf' */

      T_U_LONG  L_MFILE_tell    ( IN  MFILE  *mf ) ;
      /*  - */
      /* - Retorna la posicion del puntero de lectura/escritura */

      T_BOOL    L_MFILE_seek    ( INOUT  MFILE   *mf,
                                  IN     T_LONG   offset,
                                  IN     T_INT    whence ) ;
      /*  - */
      /* - Varia la la posicion del puntero de lectura/escritura.
           Retorna si se pudo o no, colocar en 'pos' el puntero.
           Funciona como su homonima en <stdio.h> */

      T_U_LONG  L_MFILE_write   ( IN     const void *p,
                                  IN     T_U_LONG    size,
                                  IN     T_U_LONG    n,
                                  INOUT  MFILE      *mf ) ;
      /*  - */
      /* - Escribe 'size*n' bytes del buffer apuntado por 'p' en
           el mfichero 'mf' */

      T_U_INT   L_MFILE_read    ( IN     MFILE    *mf,
                                  INOUT  void     *p,
                                  IN     T_U_LONG  size ) ;
      /*  - */
      /* - Trata de leer de 'mf', 'size' bytes y los copia
           consecutivamente en el buffer apuntado por p.
           Retorna el numero de bytes que pudo leer.
           Lee desde la posicion actual del fichero y avanza
           el puntero adecuadamente (si floatpos==TRUE). */

      T_U_INT   L_MFILE_printf  ( INOUT  MFILE   *mf,
                                  IN     T_CHAR  *format, ... ) ;
      /*  - */
      /* - Imprime en 'mf' lo que se quiera... */

      T_U_INT   L_MFILE_vfprintf ( INOUT  MFILE   *mf,
                                   IN     T_CHAR  *format,
                                   IN     va_list  va  ) ;
      /*  - */
      /* - Imprime en 'mf' lo que se quiera... */

      MFILE    *L_MFILE_options   ( INOUT  MFILE   *mf,
                                    IN     T_CHAR  *options ) ;
      /*  - */
      /* - Modifica las opciones antes definidas para "mf",
           retornando el descriptor modificado adecuadamente.
           Las opciones son independientes.
           Significan :
            -- overwrite.- A TRUE, si la posicion de escritura esta
               dentro del fichero, las siguientes escrituras
               sobreescribiran el contenido existente. A FALSE hara
               que se "ensanche" el fichero para que se anyada lo
               que se escriba
            -- floatpos.-  Indica que a cada escritura debe avanzar
               el puntero de escritura o permaneces siempre en la
               misma posicion (TRUE, FALSE respectivamente).
           Se codifican :
            ""/NULL   -> ambas falsas
            "o"       -> overwrite = TRUE
            "f"       -> floatpos  = TRUE
            "fo"/"of" -> ambas a TRUE */

      void      L_MFILE_unlink    ( INOUT MFILE  **mf ) ;
      /*  - */
      /* - Borra todo el contenido del mfile 'mf', y
           el descriptor tambien. */


      /* Advanced ... *
       * ------------ */
      void      L_MFILE_Resetmdata ( INOUT MFILE  *mf ) ;
      /*  - */
      /* - Borra los datos del mfile 'mf' */

      T_CHAR   *L_MFILE_mdataToStr  ( IN MFILE *mf ) ;
      /*  - */
      /* - Retorna una copia a todo el contenido del fichero
           como si fuera un string. */


   /* ... Inline / Codigo en linea ...................................... */

     #define  L_MFILE_length(mf)      ((mf)->mfsize)
     #define  L_MFILE_tell(mf)        ((mf)->mfposition)
     #define  L_MFILE_creat(o)         L_MFILE_open(NULL,0,o)


 /* ...................................................................... */


 #ifdef  __cplusplus
    }
 #endif

#endif

