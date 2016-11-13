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

      #include "weblib/l_wdt/l_urllistream.h"


   /* ... Const / Constantes ............................................ */
 
      #define  str_NELTOS "neltos"


   /* ... Functions / Funciones ......................................... */

      T_BOOL      L_URLLI_UrlLiToFile  ( INOUT t_urlLi      *listr,
                                         INOUT FILE         *fout )
      {
        t_url     *urlaux ;
        T_U_LONG   i ;

        if (listr == NULL)
           {
             errno = ERR__NULL_PARAM ;
             return FALSE ;
           }
        fprintf(fout,"%s = %li\n",str_NELTOS,listr->neltos) ;
	for (i=0; (i<L_URLLI_NumberUrls(listr)); i++)
	    {
              urlaux = (t_url *) L_URLLI_UrlIn(listr,i) ;
              if (urlaux == NULL)
                  break ;
              L_URLSTREAM_UrlToFile(urlaux,fout) ;
	    }
	return TRUE ;
      }

      T_BOOL      L_URLLI_FileToUrlLi  ( INOUT t_urlLi      *listr,
                                         INOUT FILE         *fin )
      {
        T_CHAR    *pch ;
        T_BOOL     ok ;
        t_url      urlaux ;
        T_U_LONG   i, neltos, fin_size ;

        NULL_RET_FALSE(fin) ;
        fin_size = L_FILE_FileSize(fin) ;
        neltos = LONG_MAX ;
        pch = L_FSTR_GetItemValue(fin,str_NELTOS,FALSE," \t=\n") ;
        if (pch != NULL)
           {
             neltos = atoi(pch) ;
             X_ALLOC_Free((void **)&(pch)) ;
           }
        L_FCHSET_SkipCharSet(fin," \t=\n") ;
	ok  = L_URLSTREAM_FileToUrl(&urlaux,fin) ;
        for (i=0; (ok==TRUE); i++)
        {
	  L_URLLI_Insert(listr,&urlaux) ;
	  ok = L_URLSTREAM_FileToUrl(&urlaux,fin) ;
          if ( (i % 100) == 0 )
                X_PRINT_printf("\r\tReading resume file [%li/%li]",
                               ftell(fin),fin_size) ;
        }
        X_PRINT_printf("\r\tResume file readed                                  ") ;
        if (neltos != i)
           {
             X_PRINT_printf("\n\tnumber elements updated") ;
             neltos = i ;
           }
        X_PRINT_printf("\n") ;
	return TRUE ;
      }


  /* ................................................................... */

