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

      #include "uilib/l_browse/l_brws1.h"


   /* ... Funciones auxiliares .......................................... */

    /*... 1.- Auxiliares gestion ventanas ............*/
    void GetWidthTall (t_DiNode *d, INOUT T_INT *width, INOUT T_INT *tall)
    { /* calculo ancho,largo de la ventana ... */

      T_INT i ;
      t_DiNode *phijo ;

      (*tall)=L_GRAFO_GetNSons(d) ;
      (*width)=0 ;
      for (i=0;i<(*tall);i++)
	  {
	    phijo=L_GRAFO_GetSonN(i,d) ;
	    *width=MAX(*width,strlen(L_GRAFO_GetName(phijo))) ;
	  }
    }

    void WrListSons (t_DiNode *d, t_win w,
                     T_INT ei, T_INT tti, T_INT ti, T_INT wi, T_INT with )
    {
      t_DiNode *phijo ;
      T_INT i,j,ipan,epan,coltall ;

      L_WIN_Clear(w) ;
      epan=( (ei / (ti*wi)) + ((ei % (ti*wi))>0) ) ;
      for (ipan=0; ipan<epan; ipan++)
	  {
            for (j=0; (j<ti) && ((j-1)*wi+ti*wi*ipan<ei); j++)
                {
                  coltall=0 ;
                  for (i=0; (i<wi) && (i+j*wi+ti*wi*ipan<ei); i++)
                      {
			L_WIN_GotoXY(w,i+1+i*with,1+j) ;
                        phijo=L_GRAFO_GetSonN(coltall+ipan*ti+j,d) ;
			coltall+=( tti-(((tti-1)*wi)+i+1>ei) ) ;
			if (phijo)
			    L_WIN_WriteStr(w,L_GRAFO_GetName(phijo)) ;
                      }
                }
	    if ((epan > 1) && (ipan<epan-1))
	       {
                 L_WIN_ScrollUp(w,ti) ;
	       }
	  }
      if (epan > 1)
	  L_WIN_ScrollDown(w,(ei-(ei % (ti*wi))-(!(ei % (ti*wi)))*ti*wi) / wi) ;
    }

    void WrSelect (t_win ws, t_DiNode *d, T_INT o)
    {
      t_DiNode *phijo ;

      L_WIN_Clear(ws) ;
      phijo=L_GRAFO_GetSonN(o-1,d) ;
      L_WIN_WriteStr(ws,L_GRAFO_GetName(phijo)) ;
    }

   T_BOOL InitWinStack (INOUT t_win_stack *ms,
                      void (*WHelp)(t_win ,t_DiNode *,T_INT),
                      void (*CCoor)(T_INT,T_INT,T_INT,T_INT *,T_INT *,T_INT *,
                                    T_INT *,T_INT *,T_INT *,T_BOOL *))
   {
     *ms=(t_win_stack)X_ALLOC_Malloc(c_WIS_STACK) ;
     NULL_RET_FALSE(*ms) ;
     (*ms)->s=NULL ;
     (*ms)->neltos=0 ;
     L_WIN_SetDefaultColour(&((*ms)->wback),&((*ms)->wfore),
			       &((*ms)->fwback),&((*ms)->fwfore)) ;
     L_WIN_SetDefaultColour(&((*ms)->hfore),&((*ms)->hbfore),
			       &((*ms)->hbback),&((*ms)->hback)) ;
     L_WIN_SetDefaultColour(&((*ms)->sfore),&((*ms)->sback),
	                       &((*ms)->sbfore),&((*ms)->sbback)) ;
     L_WIN_SetDefaultColour(&((*ms)->fwbback),&((*ms)->fwbfore),
			       &((*ms)->wbback),&((*ms)->wbfore)) ;
     if (VS.ncolores>2)
        {
      #if defined(__COOL__)
          (*ms)->hfore=c_Black ;
  	  (*ms)->hbfore=c_Magneta ;
	  (*ms)->hbback=c_Black ;
	  (*ms)->hback=c_Magneta ;

	  (*ms)->wfore=c_LightGray ;
	  (*ms)->wback=c_Blue ;
	  (*ms)->wbfore=c_LightGray ;
	  (*ms)->wbback=c_Blue ;

	  (*ms)->fwfore=c_LightGray ;
	  (*ms)->fwback=c_Blue ;
	  (*ms)->fwbfore=c_LightGray ;
	  (*ms)->fwbback=c_Blue ;

	  (*ms)->sfore=c_DarkGray ;
	  (*ms)->sbfore=c_LightGray ;
	  (*ms)->sbback=c_Blue ;
	  (*ms)->sback=c_Cyan ;
      #endif
        }
     (*ms)->frame=X_STRING_StrDup(c_SIMPLE_FRAME1) ;
     if (!(*ms)->frame)
	{
          X_ALLOC_Free((void **)&(*ms)) ;
	  return FALSE ;
	}
     (*ms)->WrHelp=WHelp ;
     (*ms)->CalCoor=CCoor ;
     return TRUE ;
   }

   void EndWinStack (INOUT t_win_stack *m )
   {
     if ((*m) && ((*m)->neltos==0))
	{
          X_ALLOC_Free((void **)&((*m)->frame)) ;
          X_ALLOC_Free((void **)&(*m)) ;
	  *m=NULL ;
	}
   }

    /*... 3.- Stack elementos ........................*/
   T_BOOL L_BRWS1_Push (INOUT t_win_stack *ms, t_eltos *e)
   {
     L_DEBUG_NULL_E_F(*ms,"no stack where put elements.!") ;
     return L_DARRAY_InsEndDarray( (t_pointerDArray *)&((*ms)->s),
				  (T_U_LONG *)&((*ms)->neltos),
				  (T_POINTER)e ) ;
    }

    t_eltos *L_BRWS1_Top (t_win_stack ms)
    {
      if ((!ms) || (!ms->s))
	       return NULL ;
	  else return (ms->s[ms->neltos-1]) ;
    }

    T_INT L_BRWS1_NEltos (t_win_stack ms)
    {
      return ( (ms==NULL) ? 0 : ms->neltos ) ;
    }

    t_eltos *L_BRWS1_Pop (INOUT t_win_stack *ms)
    {
      t_eltos *elto ;

      if ((!*ms) || (!(*ms)->s))
		return NULL ;
	 else {
		L_DARRAY_DelEndDarray( (t_pointerDArray *)&((*ms)->s),
				       (T_U_LONG *)&((*ms)->neltos),
				       (T_POINTER *)&elto ) ;
		return elto ;
	      }
    }

    t_eltos *L_BRWS1_ChTop (t_win_stack ms, t_eltos *e)
    {
      t_eltos *olde ;

      if ((!ms) || (!ms->s) || (!ms->neltos))
	  return NULL ;
      olde=ms->s[(ms->neltos)-1] ;
      ms->s[ms->neltos-1]=e ;
      return olde ;
    }


    /*... 4.- Creacion y presentacion de nueva cima ...*/
    T_BOOL OpenCima (t_win_stack *m, t_DiNode *d, T_INT x, T_INT y)
    {
      T_INT sontall,sonwidth ;
      T_INT sx1,sy1,sx2,sy2,cx,cy ;
      t_eltos *e ;
      T_BOOL ok,keep ;

      GetWidthTall(d,&sonwidth,&sontall) ;
      if (!sontall)
	  return FALSE ;
       /* calculo posicion ... */
      if (!(*m)->neltos)
	 {
	   sx1=sx2=x ;
	   sy1=sy2=y ;
	 } else {
                  e=L_BRWS1_Top(*m) ;
		  L_WIN_Coordenate(e->wselect,&sx1,&sy1,&sx2,&sy2) ;
		}
      (*m)->CalCoor(sonwidth,sontall,c_SEP_T_INT,
                    &cx,&cy,&sx1,&sy1,&sx2,&sy2,&keep) ;
       /* puesta a punto del nuevo elto ... */
      e=(t_eltos *)X_ALLOC_Malloc(c_WIS_ELTOS) ;
      NULL_RET_FALSE(e) ;
      e->d=d ;
      e->opcion=1 ;
      e->totalopcion=sontall ;
      e->fopcion=cy ;   /* total de filas */
      e->copcion=cx ;   /* total de columnas */
      e->sfopcion=sy2-sy1-2*c_SEP_T_INT-1 ; /* filas que veremos en la ventana */
      e->yoffwin=1 ;    /* en que fila de la ventana estoy */
      e->xoffwin=1 ;    /* en que columna de la ventana estoy */
      e->upfopcion=0 ;  /* cuantas filas hay arriba de la ventana */
      e->widthopcion=sonwidth ; /* ancho de las opciones */
      e->wframe=L_WIN_Open(sx1,sy1,sx2,sy2) ;
      if (!e->wframe)
	 {
           X_ALLOC_Free((void **)&e) ;
	   return FALSE ;
	 }
      e->wmain=L_WIN_Open(sx1+c_SEP_T_INT,sy1+c_SEP_T_INT,
			  sx2-c_SEP_T_INT,sy2-c_SEP_T_INT) ;
      if (!e->wmain)
	 {
	   L_WIN_Close(e->wframe) ;
           X_ALLOC_Free((void **)&e) ;
	   return FALSE ;
	 }
      e->wselect=L_WIN_Open(sx1+c_SEP_T_INT,sy1+c_SEP_T_INT,
			    sx1+c_SEP_T_INT+sonwidth+1,
			    sy1+c_SEP_T_INT+1+1) ;
      if (!e->wselect)
	 {
	   L_WIN_Close(e->wmain) ;
	   L_WIN_Close(e->wframe) ;
           X_ALLOC_Free((void **)&e) ;
	   return FALSE ;
	 }
      e->whelp=L_WIN_Open(c_HELP_X1,c_HELP_Y1,c_HELP_X2,c_HELP_Y2) ;
      if (!e->whelp)
	 {
	   L_WIN_Close(e->wmain) ;
	   L_WIN_Close(e->wselect) ;
	   L_WIN_Close(e->wframe) ;
           X_ALLOC_Free((void **)&e) ;
	   return FALSE ;
	 }
      ok=L_BRWS1_Push(m,e) ;
      if (ok==FALSE)
	 {
	   L_WIN_Close(e->wmain) ;
	   L_WIN_Close(e->wselect) ;
	   L_WIN_Close(e->whelp) ;
	   L_WIN_Close(e->wframe) ;
           X_ALLOC_Free((void **)&e) ;
	   return FALSE ;
	 }
       /* actualizar pantallas ... */
      L_WIN_SetColours(e->wmain,(*m)->wback,(*m)->wfore,(*m)->fwback,(*m)->fwfore) ;
      L_WIN_SetColours(e->wframe,(*m)->wback,(*m)->wfore,(*m)->fwback,(*m)->fwfore) ;
      L_WIN_SetColours(e->wselect,(*m)->sback,(*m)->sfore,(*m)->sback,(*m)->sfore) ;
      L_WIN_SetColours(e->whelp,(*m)->hback,(*m)->hfore,(*m)->sback,(*m)->sfore) ;
      L_WIN_Shadow(e->wframe) ;
      #if defined(__COOL__)
	 L_WIN_SetFrame(e->wframe,TRUE,c_SIMPLE_FRAME1) ;
      #else
	 L_WIN_SetFrame(e->wframe,TRUE,(*m)->frame) ;
      #endif
      WrSelect(e->wselect,e->d,1) ;
      ((*m)->WrHelp)(e->whelp,e->d,1) ;
      if (keep==TRUE)
	  L_WIN_Keep(e->wmain) ;
      WrListSons(d,e->wmain,sontall,e->fopcion,e->sfopcion,e->copcion,sonwidth) ;
      return TRUE ;
    }

    T_BOOL CloseCima (INOUT t_win_stack *m, T_INT sublevels)
    {
      t_eltos *e ;
      T_INT i ;

      for (i=0; i<sublevels;i++)
	  {
            e=L_BRWS1_Pop(m) ;
	    if (e)
	       {
		 L_WIN_Close(e->wmain) ;
		 L_WIN_Close(e->whelp) ;
		 L_WIN_Close(e->wframe) ;
		 L_WIN_Close(e->wselect) ;
                 X_ALLOC_Free((void **)&e) ;
	       } else {
			L_DEBUG_MSG_Write(WARNING,FALSE,"Menu allready close") ;
			return TRUE ;
		      }
	  }
      return TRUE ;
    }

    /*... 5.- codigo asociado a cada tecla ...*/
    T_INT  UpKeyCode (t_win_stack m)
    {
      t_eltos *e ;

      e=L_BRWS1_Top(m) ;
      if (e->opcion > 1)
	 {
           T_INT ox1,oy1,ox2,oy2 ;

           L_WIN_Coordenate(e->wselect,&ox1,&oy1,&ox2,&oy2) ;
	   if (e->yoffwin > 1)
	      {
                L_WIN_Move(e->wselect,ox1,oy1-1,ox2,oy2-1) ;
                e->yoffwin-- ;
                e->opcion-- ;
	      } else {
                       if (e->upfopcion > 0)
                       {
                         L_WIN_ScrollDown(e->wmain,1) ;
                         e->upfopcion-- ;
                         e->opcion-- ;
                       }
                     }
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   m->WrHelp(e->whelp,e->d,e->opcion) ;
	 }
      return c_KEYPROC ;
    }

    T_INT  DownKeyCode (t_win_stack m)
    {
      t_eltos *e ;

      e=L_BRWS1_Top(m) ;
      if (e->opcion >= e->totalopcion)
          return c_KEYPROC ;
      if ( (!(((e->fopcion-1)*e->copcion+e->xoffwin>e->totalopcion)
                                   &&
              (e->upfopcion+e->yoffwin+1>=e->fopcion))) )
	 {
           T_INT ox1,oy1,ox2,oy2 ;

           L_WIN_Coordenate(e->wselect,&ox1,&oy1,&ox2,&oy2) ;
           if (e->yoffwin < e->sfopcion)
	      {
                L_WIN_Move(e->wselect,ox1,oy1+1,ox2,oy2+1) ;
                e->yoffwin++ ;
                e->opcion++ ; 
	      } else {
                       if (e->upfopcion+e->sfopcion<e->fopcion)
                       {
                         L_WIN_ScrollUp(e->wmain,1) ;
                         e->upfopcion++ ;
                         e->opcion++ ; 
                       }
		     }
           WrSelect(e->wselect,e->d,e->opcion) ;
           m->WrHelp(e->whelp,e->d,e->opcion) ;
         }
      return c_KEYPROC ;
    }

    T_INT  RightKeyCode (t_win_stack *m)
    {
      t_eltos *e ;
      T_INT cshift, backopcion ;
      extern int EnterKeyCode(t_win_stack *m) ;

      e=L_BRWS1_Top(*m) ;
      cshift=(e->fopcion-1)*e->copcion+e->xoffwin ;
      cshift=e->fopcion-(cshift>e->totalopcion) ;
      backopcion=(e->upfopcion+e->yoffwin-1)*e->copcion+e->xoffwin ;
      if ( ((e->opcion+cshift) <= e->totalopcion)
                          &&
           (backopcion<e->totalopcion) )
	 {
           T_INT wxshift ;
           T_INT ox1,oy1,ox2,oy2 ;

           L_WIN_Coordenate(e->wselect,&ox1,&oy1,&ox2,&oy2) ;
           backopcion=(e->fopcion-1)*e->copcion+e->xoffwin ;
           (e->opcion)+=(e->fopcion-(backopcion>e->totalopcion)) ;
           (e->xoffwin)++ ;
           wxshift=1+(e->widthopcion) ;
           L_WIN_Move(e->wselect,ox1+wxshift,oy1,
                                 ox2+wxshift,oy2) ;
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   (*m)->WrHelp(e->whelp,e->d,e->opcion) ;
         } else EnterKeyCode(m) ;
      return c_KEYPROC ;
    }

    T_INT  LeftKeyCode (t_win_stack *m)
    {
      t_eltos *e ;
      extern T_INT EscKeyCode (t_win_stack *m) ;

      e=L_BRWS1_Top(*m) ;
      if ((e->opcion-e->fopcion) > 0)
	 {
           T_INT wxshift,backopcion ;
           T_INT ox1,oy1,ox2,oy2 ;

           L_WIN_Coordenate(e->wselect,&ox1,&oy1,&ox2,&oy2) ;
           backopcion=(e->fopcion-1)*e->copcion+e->xoffwin-1 ;
           (e->opcion)-=(e->fopcion-(backopcion>e->totalopcion)) ;
           (e->xoffwin)-- ;
           wxshift=1+(e->widthopcion) ;
           L_WIN_Move(e->wselect,ox1-wxshift,oy1,ox2-wxshift,oy2) ;
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   (*m)->WrHelp(e->whelp,e->d,e->opcion) ;
	 } else {
                  if (L_BRWS1_NEltos(*m) > 1)
                      EscKeyCode(m) ;
                }
      return c_KEYPROC ; 
    }

    T_INT  InicioKeyCode (t_win_stack m)
    {
      t_eltos *e ;

      e=L_BRWS1_Top(m) ;
      if (e->opcion > 1)
	 {
           L_WIN_ScrollDown(e->wmain,e->upfopcion) ;
           e->upfopcion=0 ;
           if ( (e->yoffwin > 1) || (e->xoffwin > 1) )
	      {
                T_INT wxshift, wyshift ;
                T_INT ox1,oy1,ox2,oy2 ;

                L_WIN_Coordenate(e->wselect,&ox1,&oy1,&ox2,&oy2) ;
                wxshift=(e->xoffwin-1)*(e->widthopcion)+(e->xoffwin-1) ;
                wyshift=MIN(e->yoffwin,e->fopcion)-1 ;
                L_WIN_Move(e->wselect,ox1-wxshift,oy1-wyshift,
                                      ox2-wxshift,oy2-wyshift) ;
		e->yoffwin=1 ;
                e->xoffwin=1 ;
	      }
	   e->opcion=1 ;
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   m->WrHelp(e->whelp,e->d,e->opcion) ;
	 }
      return c_KEYPROC ;
    }

    T_INT  FinKeyCode (t_win_stack m)
    {
      t_eltos *e ;

      e=L_BRWS1_Top(m) ;
      if (e->opcion < e->totalopcion)
	 {
           T_INT wxshift, wyshift, scrolly, escalon ;
           T_INT ox1,oy1,ox2,oy2 ;

           L_WIN_Coordenate(e->wselect,&ox1,&oy1,&ox2,&oy2) ;
           scrolly=(e->fopcion-e->sfopcion)-e->upfopcion ;
           L_WIN_ScrollUp(e->wmain,scrolly) ;
           e->upfopcion+=scrolly ;
           escalon=(e->totalopcion % e->copcion) ;
           wxshift=(e->copcion-e->xoffwin)*(e->widthopcion)+
                   (e->copcion-e->xoffwin) ;
           wyshift=e->sfopcion-e->yoffwin-(escalon>0) ;
           L_WIN_Move(e->wselect,ox1+wxshift,oy1+wyshift,
                                 ox2+wxshift,oy2+wyshift) ;
           e->yoffwin=e->sfopcion-(escalon>0) ;
           e->xoffwin=e->copcion ;
           e->opcion=e->totalopcion ;
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   m->WrHelp(e->whelp,e->d,e->opcion) ;
	 }
      return c_KEYPROC ;
    }

    T_INT  AvPagKeyCode (t_win_stack m)
    {
      t_eltos *e ;

      e=L_BRWS1_Top(m) ;
      if (e->fopcion - e->upfopcion >= 2*e->sfopcion)
	 {
           L_WIN_ScrollUp(e->wmain,e->sfopcion) ;
           e->upfopcion+=e->sfopcion ;
           e->opcion+=e->sfopcion ;
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   m->WrHelp(e->whelp,e->d,e->opcion) ;
	 }
      return c_KEYPROC ;
    }

    T_INT  RePagKeyCode (t_win_stack m)
    {
      t_eltos *e ;

      e=L_BRWS1_Top(m) ;
      if (e->upfopcion >= e->sfopcion)
	 {
           L_WIN_ScrollDown(e->wmain,e->sfopcion) ;
           e->upfopcion-=e->sfopcion ;
           e->opcion-=e->sfopcion ;
	   WrSelect(e->wselect,e->d,e->opcion) ;
	   m->WrHelp(e->whelp,e->d,e->opcion) ;
	 }
      return c_KEYPROC ;
    }

    T_INT EnterKeyCode (t_win_stack *m)
    {
      t_DiNode *phijo ;
      t_eltos *e ;
      T_BOOL ok ;

      e=L_BRWS1_Top(*m) ;
      phijo=L_GRAFO_GetSonN(e->opcion-1,e->d) ;
      if (!L_GRAFO_GetNSons(phijo))
	  return c_CHOSE ;
      ok=OpenCima(m,phijo,1,1) ;
      if (ok==TRUE)
	 {
	   L_WIN_SetColours(e->wmain,(*m)->wbback,(*m)->wbfore,(*m)->fwbback,(*m)->fwbfore) ;
	   L_WIN_SetColours(e->wframe,(*m)->wbback,(*m)->wbfore,(*m)->fwbback,(*m)->fwbfore) ;
	   L_WIN_SetColours(e->wselect,(*m)->sbback,(*m)->sbfore,(*m)->sbback,(*m)->sbfore) ;
	   return c_KEYPROC ;
	 } else {
		  return c_ERROR ;
		}
    }

    T_INT EscKeyCode (t_win_stack *m)
    {
      t_eltos *e ;

      if (L_BRWS1_NEltos(*m) > 1)
	 {
	   CloseCima(m,1) ;
           e=L_BRWS1_Top(*m) ;
	   L_WIN_SetColours(e->wmain,(*m)->wback,(*m)->wfore,(*m)->fwback,(*m)->fwfore) ;
	   L_WIN_SetColours(e->wframe,(*m)->wback,(*m)->wfore,(*m)->fwback,(*m)->fwfore) ;
	   L_WIN_SetColours(e->wselect,(*m)->sback,(*m)->sfore,(*m)->sback,(*m)->sfore) ;
	   return c_KEYPROC ;
	 }
      return c_CLOSE ;
    }


 /*... Funciones principales presentacion elementos .......................*/

    t_win_stack L_BRWS1_OpenStack (t_DiNode *d, T_INT x, T_INT y,
                                   void (*WHelp)(t_win ,t_DiNode *,T_INT),
                                   void (*CCoor)(T_INT,T_INT,T_INT,T_INT *,T_INT *,T_INT *,
                                                 T_INT *,T_INT *,T_INT *,T_BOOL *))
    {
      t_win_stack wis ;
      T_BOOL ok ;

      NULL_RET_NULL(d) ;
      wis=NULL ;
      ok=InitWinStack(&wis,WHelp,CCoor) ;
      if (ok==FALSE)
	  return NULL ;
      ok=OpenCima(&wis,d,x,y) ;
      if (ok==FALSE)
	 {
	   EndWinStack(&wis) ;
	   return NULL ;
	 }
      return wis ;
    }

    T_INT L_BRWS1_KeyProcesing (t_win_stack *m, T_INT tecla)
    {
      if ( (!m) || (!*m) || (!((*m)->neltos)) )
	 {
	   L_DEBUG_MSG_Write(WARNING,FALSE,"NULL argument or Empty Stack.") ;
	   return c_ERROR ;
	 }
      switch (tecla)
      {
	case c_UP :
	     return UpKeyCode(*m) ;
	case c_DOWN :
	     return DownKeyCode(*m) ;
	case c_LEFT :
	     return LeftKeyCode(m) ;
	case c_BEGIN :
	     return InicioKeyCode(*m) ;
	case c_RIGHT :
             return RightKeyCode(m) ;
	case c_END :
	     return FinKeyCode(*m) ;
        case c_AVPAG :
             return AvPagKeyCode(*m) ;
        case c_REPAG :
             return RePagKeyCode(*m) ;
	default : ;
      }
      switch (tecla)
      {
	case c_ENTER :
	     return EnterKeyCode(m) ;
	case c_ESC :
	     return EscKeyCode(m) ;
      }
      L_DEBUG_MSG_Write(WARNING,FALSE,"Unknow key code! ") ;
      return c_KEYPROC ;
    }

    void L_BRWS1_CloseStack (INOUT t_win_stack *m)
    {
      T_INT i,teltos ;
      t_eltos *e ;

      if (*m)
	 {
	   teltos=(*m)->neltos ;
	   for (i=0; i<teltos; i++)
	       {
                 e=L_BRWS1_Pop(m) ;
		 L_WIN_Close(e->wmain) ;
		 L_WIN_Close(e->wselect) ;
		 L_WIN_Close(e->wframe) ;
		 L_WIN_Close(e->whelp) ;
                 X_ALLOC_Free((void **)&e) ;
	       }
	   EndWinStack(m) ;
	 }
    }

    T_BOOL L_BRWS1_PopNWins (t_win_stack *m, T_INT s)
    {
      if (*m)
	  return CloseCima(m,s) ;
      return FALSE ;
    }

    void L_BRWS1_SetColors (t_win_stack m,
			    t_txt_colores wback, t_txt_colores wbback,
			    t_txt_colores fwback, t_txt_colores fwbback,
			    t_txt_colores wfore, t_txt_colores wbfore,
			    t_txt_colores fwfore, t_txt_colores fwbfore,
			    t_txt_colores sback, t_txt_colores sfore,
			    t_txt_colores sbback, t_txt_colores sbfore,
			    t_txt_colores hback, t_txt_colores hbback,
			    t_txt_colores hfore, t_txt_colores hbfore )
    {
      if (m)
	 {
	   m->wback=wback ;
	   m->wbback=wbback ;
	   m->fwback=fwback ;
	   m->fwbback=fwbback ;
	   m->wfore=wfore ;
	   m->wbfore=wbfore ;
	   m->fwfore=fwfore ;
	   m->fwbfore=fwbfore ;
	   m->sback=sback ;
	   m->sfore=sfore ;
	   m->sbback=sbback ;
	   m->sbfore=sbfore ;
	   m->hback=hback ;
	   m->hbback=hbback ;
	   m->hfore=hfore ;
	   m->hbfore=hbfore ;
	 }
    }

    void L_BRWS1_GetColors (t_win_stack m,
			    t_txt_colores *wback, t_txt_colores *wbback,
			    t_txt_colores *fwback, t_txt_colores *fwbback,
			    t_txt_colores *wfore, t_txt_colores *wbfore,
			    t_txt_colores *fwfore, t_txt_colores *fwbfore,
			    t_txt_colores *sback, t_txt_colores *sfore,
			    t_txt_colores *sbback, t_txt_colores *sbfore,
			    t_txt_colores *hback, t_txt_colores *hbback,
			    t_txt_colores *hfore, t_txt_colores *hbfore )
    {
      if (m)
	 {
	   *wback=m->wback ;
	   *wbback=m->wbback ;
	   *fwback=m->fwback ;
	   *fwbback=m->fwbback ;
	   *wfore=m->wfore ;
	   *wbfore=m->wbfore ;
	   *fwfore=m->fwfore ;
	   *fwbfore=m->fwbfore ;
	   *sback=m->sback ;
	   *sfore=m->sfore ;
	   *sbback=m->sbback ;
	   *sbfore=m->sbfore ;
	   *hback=m->hback ;
	   *hbback=m->hbback ;
	   *hfore=m->hfore ;
	   *hbfore=m->hbfore ;
	 }
    }

    void L_BRWS1_SetFrame (t_win_stack m, T_CHAR *frame)
    {
      if (m)
	  m->frame=X_STRING_StrDup(frame) ;
    }

    T_CHAR *L_BRWS1_GetFrame (t_win_stack m)
    {
      if (m)
	  return (m->frame) ;
      return NULL ;
    }

    T_INT *L_BRWS1_GetOptionsNumber (t_win_stack m)
    {
      T_INT *istack, i, eltos ;

      if ((!m) || (!m->s) || (!m->neltos))
	      {
		eltos=0 ;
	      } else {
		       eltos=m->neltos ;
		     }
      istack=(T_INT *)X_ALLOC_Malloc(sizeof(T_INT)*(eltos+1)) ;
      NULL_RET_NULL(istack) ;
      for (i=0;i<eltos;i++)
	  {
	    istack[i]=m->s[i]->opcion ;
	  }
      istack[eltos]=0 ;
      return istack ;
    }

    T_CHAR *L_BRWS1_GetOptionsName (t_win_stack m, T_CHAR *sep)
    {
      T_CHAR *path, *saux, *npath ;
      T_INT i, eltos, offset ;
      t_DiNode *phijo ;

      if ((!m) || (!m->s) || (!m->neltos))
	 {
	   return NULL ;
	 } else {
		  eltos=m->neltos ;
		}
      npath=NULL ;
      phijo=L_GRAFO_GetSonN(m->s[0]->opcion-1,m->s[0]->d) ;
      saux=L_GRAFO_GetName(phijo) ;
      path=X_STRING_StrDup(saux) ;
      NULL_RET_NULL(path) ;
      for (i=1;i<eltos;i++)
	  {
	    phijo=L_GRAFO_GetSonN(m->s[i]->opcion-1,m->s[i]->d) ;
	    saux=L_GRAFO_GetName(phijo) ;
	    offset=strlen(path) ;
            npath=X_ALLOC_Realloc(path,offset+strlen(sep)+strlen(saux)+1) ;
	    NULL_RET_NULL(npath) ;
	    path=npath ;
            X_ALLOC_MemMove(&(path[offset]),sep,strlen(sep)) ;
	    offset+=strlen(sep) ;
            X_ALLOC_MemMove(&(path[offset]),saux,strlen(saux)+1) ;
	  }
      return path ;
    }

    t_DiNode *L_BRWS1_GetTHEOption (t_win_stack m)
    {
      t_DiNode *phijo ;
      t_eltos *e ;

      if ((!m) || (!m->s) || (!m->neltos))
	  return NULL ;
      e=L_BRWS1_Top(m) ;
      phijo=L_GRAFO_GetSonN(e->opcion-1,e->d) ;
      return phijo ;
    }

    T_BOOL L_BRWS1_UnHidden (t_win_stack m)
    {
      T_INT i ;
      T_BOOL result=TRUE,ok1,ok2,ok3,ok4 ;

      for (i=0;(i<m->neltos) && result; i++)
	  {
	    ok1=L_WIN_UnHidden(m->s[i]->wmain) ;
	    ok4=L_WIN_UnHidden(m->s[i]->wframe) ;
	    ok2=L_WIN_UnHidden(m->s[i]->wselect) ;
	    ok3=L_WIN_UnHidden(m->s[i]->whelp) ;
	    result=ok1 || ok2 || ok3 || ok4 ;
	  }
      return result ;
    }

    T_BOOL L_BRWS1_Hidden (t_win_stack m)
    {
      T_INT i ;
      T_BOOL result=TRUE,ok1,ok2,ok3,ok4 ;

      for (i=0;(i<m->neltos) && result; i++)
	  {
	    ok1=L_WIN_Hidden(m->s[i]->wmain) ;
	    ok2=L_WIN_Hidden(m->s[i]->wselect) ;
	    ok3=L_WIN_Hidden(m->s[i]->whelp) ;
	    ok4=L_WIN_Hidden(m->s[i]->wframe) ;
	    result=ok1 || ok2 || ok3 || ok4 ;
	  }
      return result ;
    }

 /* ..................................................................... */
