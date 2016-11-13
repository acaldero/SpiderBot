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

      #include "uilib/l_apps/l_uirc.h"


   /* ... Functions / Funciones ......................................... */
   
      FILE  *L_UIRC_OpenFile ( IN     T_CHAR *progname )
      {
        T_CHAR  *sdat ;
        FILE    *fin ;
  
        sdat=X_ALLOC_MemDup(progname,X_STRING_StrLen(progname)+5) ;
        if ( X_STRING_Match(progname,"*.exe",FALSE) == TRUE)
           { /* progname.exe */
             sdat[X_STRING_StrLen(progname)-4]='\0' ;
           }
        else
           { /* progname */
             sdat=X_ALLOC_MemDup(progname,strlen(progname)+4) ;
           }
        if (sdat == NULL)
           {
             X_PRINT_printf("\nERROR: Insuficiente memoria.!\n") ;
             L_WIN_Flush() ;
             return NULL ;
           }
        strcat(sdat,".dat") ;
        fin=fopen(sdat,"rb") ;
        if (fin==NULL)
           {
             T_CHAR vT_LONG[8] ;
	     T_LONG offsek ;

             X_PRINT_printf("WARNING: I can't open data file (%s)\n",sdat) ;
             X_ALLOC_Free((void **)&sdat) ;       
             L_WIN_Flush() ;
             fin = fopen(progname,"rb") ;
             if (fin == NULL)
                {
                  X_PRINT_printf("WARNING: I can't open exe file (%s)\n",progname) ;
                  L_WIN_Flush() ;
                  return NULL ;
                }
             if (setvbuf(fin,NULL,_IOFBF,16384))
                 setvbuf(fin,NULL,_IOFBF,512) ; /* sino, NO funciona ungetc */
             fseek(fin,0L,SEEK_END) ;
             fseek(fin,ftell(fin)-8,SEEK_SET) ;
             fread(vT_LONG,1,8,fin) ;
             offsek = atol(vT_LONG) ;
	     if (offsek > ftell(fin))
	        {
		  fclose(fin) ;
	          return NULL ;
	        }
             fseek(fin,ftell(fin)-offsek-8,SEEK_SET) ;
             return fin ;
           }
        X_ALLOC_Free((void **)&sdat) ;
        if (setvbuf(fin,NULL,_IOFBF,16384))       
            setvbuf(fin,NULL,_IOFBF,512) ;
	return fin ;
      }

      t_DiNode  *L_UIRC_ReadMenu ( INOUT  FILE   *fin )
      {
        t_DiNode *g ;
        t_menusintax s = { "MENUITEM", "HELP", "BEGIN", "END",
                           "\n\t\r\40", FALSE } ;
  
        if (L_MENU_ReadMenu(&g,&s,fin) == FALSE)   
           {
             X_PRINT_printf("ERROR: I can't read Menu from file.\n") ;
             L_WIN_Flush() ;
             return NULL ;
           }
        return g ;
      }

      t_DiNode  *L_UIRC_ReadDialog  ( INOUT  FILE   *fin )
      {
        t_DiNode *g ;
        t_htxtsintax s = { "NODEID", "BEGIN", "END", "NODELINK", "COORDENATE",
                           "\n\t\r\40", FALSE } ;
  
        if (L_HTXT_ReadHtxtNode(&g,&s,fin) == FALSE)   
           {
             X_PRINT_printf("ERROR: I can't read Dialog from file.\n") ;
             L_WIN_Flush() ;
             return NULL ;
           }
        return g ;
      }

      t_DiNode  *L_UIRC_ReadHtxt  ( INOUT  FILE   *fin )
      {
        t_DiNode *g ;
        t_htxtsintax s = { "NODEID", "BEGIN", "END", "NODELINK", "COORDENATE",
                           "\n\t\r\40", FALSE } ;
  
        if (L_HTXT_ReadHtxt(&g,&s,fin) == FALSE)   
           {
             X_PRINT_printf("ERROR: I can't read HiperText from file.\n") ;
             L_WIN_Flush() ;
             return NULL ;
           }
        return g ;
      }

      t_DiNode  *L_UIRC_ReadAssistant ( INOUT  FILE   *fin )
      {
        t_DiNode *g ;
        t_htxtsintax s = { "NODEID", "BEGIN", "END", "NODELINK", "COORDENATE",
                           "\n\t\r\40", FALSE } ;
  
        if (L_HTXT_ReadHtxtNodes(&g,&s,fin) == FALSE)   
           {
             X_PRINT_printf("ERROR: I can't read HiperText from file.\n") ;
             L_WIN_Flush() ;
             return NULL ;
           }
        return g ;
      }


   /* ................................................................... */

