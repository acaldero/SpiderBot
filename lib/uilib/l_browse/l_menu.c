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

      #include "uilib/l_browse/l_menu.h"


   /* ... Functions / Funciones ......................................... */

     /* Menu propieties  *
      * ---------------- */
   t_menup *L_MENU_CreatByDefault ( void )
   {
     t_menup *aux ;

     aux=(t_menup *)X_ALLOC_Malloc(c_MENUP) ;
     NULL_RET_NULL(aux) ;
     X_ALLOC_MemSet(aux,0,c_MENUP) ;
     aux->id_presentacion=c_ID_MENU ;
     return aux ;
   }
   
   T_BOOL L_MENU_Destroy ( t_menup **np )
   {
     NULL_RET_TRUE(*np) ;
     switch ((*np)->id_presentacion)
     {
       case c_ID_MENU :
	    X_ALLOC_Free((void **)&((*np)->Mnu.help)) ;
	    break ;
       default :
	    L_DEBUG_MSG_Write(ERROR,FALSE,"incorrect type propieties identification.") ;
	    return FALSE ;
     }
     X_ALLOC_Free((void **)np) ;
     return TRUE ;
   }


      /* building menus ... *
       * ------------------ */
     T_BOOL L_MENU_DestroyMenu ( INOUT t_DiNode      **g )
     {
       L_GRAFO_FreeKill(  g,
			 (T_BOOL (*) (T_POINTER *))L_MENU_Destroy) ;
       return TRUE ;
     }

     void L_MENU_ErrorInfo ( FILE* fin )
     {
       static T_CHAR sbuff[200] ;
       T_CHAR *serror, *saux ;
       T_INT i ;

       L_DEBUG_MSG_Write(ERROR,FALSE," Last Lines :") ;
       X_ALLOC_MemSet(sbuff,0,200) ;
       serror=sbuff ;
       for (i=0; ((i<5) && (serror==sbuff)); i++)
	   {
	     serror=fgets(sbuff,100,fin) ;
             if (!serror)
                  break ;
	     saux=strchr(serror,'\n') ;
	     if (saux)
		 *saux='\0' ;
	     saux=strchr(serror,'\r') ;
	     if (saux)
		 *saux='\0' ;
	     L_DEBUG_MSG_Write(ERROR,FALSE,sbuff) ;
	  }
       if (serror!=sbuff)
	  {
	    sprintf(sbuff,"%s","   <end of file>") ;
	    L_DEBUG_MSG_Write(ERROR,FALSE,sbuff) ;
	  }
     }

     T_BOOL L_MENU_ReadNode ( IN t_menusintax *s, FILE *f, t_DiNode **nodo )
     {
       t_menup *nprop ;
       T_CHAR *nombre ;

       nprop=L_MENU_CreatByDefault() ;
       NULL_RET_FALSE(nprop) ;
       *nodo=L_GRAFO_NewNode() ;
       NULL_RET_FALSE((*nodo)) ;
       nombre=L_FSTR_GetItemValue(f,s->MenuName,s->CaseSensitive,s->Delimitadores) ;
       L_DEBUG_NULL_E_F(nombre,"I can't read nodo name.") ;
	  /* ret_si : ( (!memory) || (!id) ) */
       nprop->Mnu.help=L_FSTR_GetItemValue(f,s->MenuHelp,s->CaseSensitive,s->Delimitadores) ;
       L_GRAFO_SetName(*nodo,nombre) ;
       L_GRAFO_SetNodePropiedades(*nodo,nprop) ;
       return TRUE ;
     }

     T_LONG L_MENU_ReadMenu ( INOUT t_DiNode      **g,
                             IN    t_menusintax   *s,
                             IN    FILE           *fstream )
     {
       T_LONG ipos,fpos ;
       T_BOOL ok ;
       t_pila Spila ;
       t_DiNode *padre, *hijo ;

       (*g)=NULL ;
       if (fstream == NULL)
	   return 0L ;
       ipos=ftell(fstream) ;
       Spila=L_PILA_CrearVacia() ;
       /* try read first options ... */
       ok = L_MENU_ReadNode(s,fstream,&padre) ;
       if (ok == FALSE)
	  {
	    fpos=ftell(fstream) ;
	    L_MENU_ErrorInfo(fstream) ;
	    return (fpos-ipos) ;
	  }
       /* try read suboptions ... */
       ok = L_FSTR_SkipCharSetAndAcceptStr(fstream,
					   s->MenuBegin,
					   s->CaseSensitive,
					   s->Delimitadores) ;
       if (ok == FALSE)
	  {
	    fpos=ftell(fstream) ;
	    L_MENU_ErrorInfo(fstream) ;
	    L_DEBUG_MSG_Write(ERROR,FALSE,LMENU_NO_BEGIN) ;
	    return (fpos-ipos) ;
	  }
       do
       {
	 while (L_FSTR_SkipCharSetAndAcceptStr(fstream,
					  s->MenuEnd,
					  s->CaseSensitive,
					  s->Delimitadores) == TRUE)
	 {
	   if (L_PILA_EsVacia(Spila))
	      {
		fpos=ftell(fstream) ;
		(*g)=padre ;
		return (fpos-ipos) ;
	      }
	   padre = L_PILA_Sacar(&Spila) ;
	 }
	 if ( (padre != NULL) && (feof(fstream)) )
	    {
	      L_PILA_KillPila(&Spila,(T_BOOL (*) (T_POINTER *))L_MENU_Destroy) ;
	      fpos=ftell(fstream) ;
	      L_MENU_ErrorInfo(fstream) ;
	      L_DEBUG_MSG_Write(ERROR,FALSE,LMENU_NO_END) ;
	      return (fpos-ipos) ;
	    }
	 ok=L_MENU_ReadNode(s,fstream,&hijo) ;
	 if (ok==FALSE)
	    {
	      L_PILA_KillPila(&Spila,(T_BOOL (*) (T_POINTER *))L_MENU_Destroy) ;
	      fpos=ftell(fstream) ;
	      L_MENU_ErrorInfo(fstream) ;
	      return (fpos-ipos) ;
	    }
	 L_GRAFO_NewSonLink(padre,hijo) ;
	 ok = L_FSTR_SkipCharSetAndAcceptStr(fstream,
					     s->MenuBegin,
					     s->CaseSensitive,
					     s->Delimitadores) ;
	 if (ok == TRUE)
	    {
	      L_PILA_Insertar(&Spila,padre) ;
	      padre=hijo ;
	    }
       } while (TRUE) ;
     }


      /* browsing menus ... *
       * ------------------ */
     void L_MENU_WrHelpMenu (t_win wh, t_DiNode *d, T_INT o)
     {
       t_DiNode *phijo ;
       t_menup *npropi ;

       L_WIN_Clear(wh) ;
       phijo=L_GRAFO_GetSonN(o-1,d) ;
       npropi=L_GRAFO_GetNodePropiedades(phijo) ;
       L_WIN_WriteStr(wh,(npropi)->Mnu.help) ;
     }

     void L_MENU_MenuCoor (T_INT sonwidth, T_INT sontall, T_INT espaciado,
                           T_INT *cx, T_INT *cy, T_INT *sx1, T_INT *sy1,
                           T_INT *sx2, T_INT *sy2, T_BOOL *keep)
     {
       T_INT fx1,fy1,fx2,fy2 ;
       T_INT anchowin,largowin ;

       fx1=*sx1 ;
       fy1=*sy1 ;
       fx2=*sx2 ;
       fy2=*sy2 ;
       *keep=FALSE ;
       *cx=1 ;
       *cy=sontall ;
       anchowin=sonwidth+2+2*espaciado-1 ;
       if ((fx1>anchowin) && ((V_TERM_cmaxX()-fx2)<fx1))
	  {
	    *sx2=fx1-1 ;
	    *sx1=*sx2-anchowin ;
	  } else {
		   *sx1=fx2+1 ;
		   *sx2=*sx1+anchowin ;
		 }
       largowin=sontall+2+2*espaciado-1 ;
       if ((fy2>largowin) && ((V_TERM_cmaxY()-fy2)<fy1))
	  {
	    *sy2=fy2 ;
	    *sy1=*sy2-largowin ;
	  } else {
                   *sy2=MIN(V_TERM_cmaxY(),fy1+largowin) ;
		   if (*sy2!=fy1+largowin)
		       *keep=TRUE ;
		   if (!(*keep))
		      {
			*sy1=fy1 ;
		      } else {
			       *sy1=MAX(0,*sy2-largowin) ;
			       if (*sy1==0)
				       *keep=TRUE ;
				  else *keep=FALSE ;
			       if (*keep)
				   *sy1=1 ;
			     }
		 }
     }

     T_INT *L_MENU_Present (t_DiNode *g, T_INT x, T_INT y)
     {
       t_menu mnu ;
       T_INT  key, state, *options ;

       mnu=L_MENU_Open(g,x,y) ;
       NULL_RET_NULL(mnu) ;
       state=c_KEYPROC ;
       do
       {
	 L_WIN_Flush() ;
         key=V_KEYMAP_getkey() ;
	 switch (key)
	 {
	   case c_F2 : L_WCON_Hidden() ;
		       break ;
	   case c_F3 : L_WCON_UnHidden() ;
		       break ;
	   default : state=L_MENU_KeyProcesing(&mnu,key) ;
	 }
       } while (state==c_KEYPROC) ;
       options=L_MENU_GetOptionsNumber(mnu) ;
       L_MENU_Close(&mnu) ;
       if (state==c_CLOSE)
           options[0]=0 ;
       return options ;
     }

     T_INT *L_MENU_ReadAndPresent ( INOUT FILE  *f,
				     IN           t_menusintax s,
				     IN    T_INT  x,
				     IN    T_INT  y )
     {
       t_DiNode *g ;
       T_BOOL   ok ;

       ok = L_MENU_ReadMenu(&g,&s,f) ;
       FALSE_RET_NULL(ok) ;
       return L_MENU_Present(g,x,y) ;
     }


 /* ...................................................................... */

