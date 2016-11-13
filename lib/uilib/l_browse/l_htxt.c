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

      #include "uilib/l_browse/l_htxt.h"


   /* ... Functions / Funciones ......................................... */

     /* HyperText propieties * 
      * -------------------- */
      t_htxtp *L_HTXT_CreatByDefault ( void )
      {
        t_htxtp *aux ;
   
        aux=(t_htxtp *)X_ALLOC_Malloc(c_HTXTP) ;
        NULL_RET_NULL(aux) ;
        X_ALLOC_MemSet(aux,0,c_HTXTP) ;
        aux->id_presentacion = c_ID_HIPERTXT ;
        return aux ;
      }
      
      void FreeInfoTabla ( t_infonodo *in )
      {
        X_ALLOC_Free((void **)&(in->linkref)) ;
        X_ALLOC_Free((void **)&(in)) ;
      }
   
      T_BOOL L_HTXT_Destroy ( t_htxtp **np )
      {
        NULL_RET_TRUE((*np)) ;
        switch ((*np)->id_presentacion)
        {
          case c_ID_HIPERTXT :
               X_ALLOC_Free((void **)&((*np)->Htxt.htxt)) ;
               L_DARRAY_FreeEltosDarray((t_pointerDArray *)&((*np)->Htxt.ilinks),
                                        (T_LONG *)&((*np)->Htxt.nlinks),
                                     (void (*)(T_POINTER))FreeInfoTabla) ;
               break ;
          default :
               L_DEBUG_MSG_Write(ERROR,FALSE,
                                 "incorrect type propieties identification.") ;
               return FALSE ;
        }
        X_ALLOC_Free((void **)np) ;
        return TRUE ;
      }
   
      T_BOOL  L_HTXT_SetHtxt ( t_htxtp *np, HTxtP *htxtp )
      {
        NULL_RET_FALSE(np) ;
        X_ALLOC_MemMove(&(np->Htxt),htxtp,sizeof(HTxtP)) ;
        return TRUE ;
      }
   
      T_BOOL  L_HTXT_GetHtxt ( t_htxtp *np, INOUT HTxtP *htxtp )
      {
        NULL_RET_FALSE(np) ;
        X_ALLOC_MemMove(htxtp,&(np->Htxt),sizeof(HTxtP)) ;
        return TRUE ;
      }
   

       /* building hypertext ... *           
        * ------------------------ */         
       T_BOOL AddNodeInfo ( INOUT t_infonodo ***tabla, INOUT T_U_INT *ctabla, 
                            IN T_INT noffset, IN T_CHAR *nref )
       {
         t_infonodo *in ;
  
         in=X_ALLOC_Malloc(c_INFONODE) ;
         NULL_RET_FALSE(in) ;
         in->idlink=noffset ;
         in->linkref=nref ;
         return L_DARRAY_InsEndDarray( (t_pointerDArray *)tabla,
                                       (T_U_LONG *)ctabla, 
                                       (T_POINTER)in ) ;
       }

       T_BOOL L_HTXT_GetCoor     ( IN     HTxtP          *htxtp, 
                                   IN     t_htxtsintax   *s, 
                                   INOUT  FILE           *f )
       {
         T_CHAR *coordenadas ;
         T_INT   nvalid ;
         T_BOOL ok ;

         coordenadas = NULL ;
         nvalid      = 0 ;
         coordenadas = L_FSTR_GetItemValue(f,
                       s->HtxtCoor,s->CaseSensitive,s->Delimitadores) ;
         ok = L_FSTR_SearchStr(f,s->HtxtBegin,s->CaseSensitive) ;
         if (ok==FALSE)
          {
            X_ALLOC_Free((void **)&coordenadas) ;
            return FALSE ;
          }
         if (coordenadas)
          {
            nvalid=sscanf(coordenadas,"%d.%d.%d.%d",&(htxtp->px1),
                          &(htxtp->py1),&(htxtp->px2),&(htxtp->py2)) ;
            X_ALLOC_Free((void **)&coordenadas) ;
          }
         if (nvalid<4)
          {
            htxtp->px1=c_DCOORDENATESX1 ;
            htxtp->py1=c_DCOORDENATESY1 ;
            htxtp->px2=c_DCOORDENATESX2 ;
            htxtp->py2=c_DCOORDENATESY2 ;
            L_DEBUG_MSG_Write(WARNING,FALSE,
                              "COORDENATE write incorrectly in file.\n") ;
          }
         return TRUE ;
       }
  
       T_BOOL L_HTXT_ReadHtxtProp ( IN     t_htxtp        *np, 
                                    IN     t_htxtsintax   *s, 
                                    INOUT  FILE           *f )
       {
         T_BOOL ok ;
         T_LONG ipos ;
         HTxtP htxtp ;
         T_INT width, tokfound ;
         T_CHAR *token, **TokEspa, *tref ;

         #define FreeTok(TokEspa)                      \
         {                                             \
           X_ALLOC_Free((void **)&(TokEspa[0])) ;      \
           X_ALLOC_Free((void **)&(TokEspa[1])) ;      \
           X_ALLOC_Free((void **)&TokEspa) ;           \
         }

  
         L_HTXT_GetHtxt(np,&htxtp) ; 
         ok = L_HTXT_GetCoor(&htxtp,s,f) ;
         FALSE_RET_FALSE(ok) ;
         TokEspa=X_ALLOC_Malloc(3*sizeof(char *)) ;
	 NULL_RET_FALSE(TokEspa) ;
         TokEspa[0]=X_STRING_StrDup(s->HtxtEnd) ;
	 NULL_RET_FALSE(TokEspa[0]) ;
         TokEspa[1]=X_STRING_StrDup(s->LinkName) ;
	 NULL_RET_FALSE(TokEspa[1]) ;
         TokEspa[2]=NULL ;
         ipos=ftell(f) ;
         width=htxtp.px2-htxtp.px1-1 ;
         while (TRUE)
         {
           ok = L_FTOKEN_ReadAndExpandTillToken
                (
                  f,TokEspa,&(htxtp.htxt),&(htxtp.ntxt),&tokfound,
                  s->Delimitadores,c_TABHITS,width,v_chclear
                ) ;
           L_HTXT_SetHtxt(np,&htxtp) ;
           if (ok==FALSE)
              {
                fseek(f,ipos,SEEK_SET) ;
                FreeTok(TokEspa) ;
                return FALSE ;
              }
           switch(tokfound)
           {
             case 0 : FreeTok(TokEspa) ;
                      return TRUE ;
             case 1 : L_FCHSET_SkipCharSet(f,s->Delimitadores) ;
                      tref  = L_FCHSET_ReadTillCharSet(f,s->Delimitadores,FALSE) ;
                      L_FCHSET_SkipCharSet(f,s->Delimitadores) ;
                      token = L_FCHSET_ReadTillCharSet(f,s->Delimitadores,FALSE) ;
                      if (X_STRING_Equal(token,"\"") == TRUE)
                         {
                           L_FCHSET_SkipCharSet(f,"\"") ; 
                           X_ALLOC_Free((void **)&token) ;
                           token = L_FCHSET_ReadTillCharSet(f,"\"",FALSE) ;
                           L_FCHSET_SkipCharSet(f,"\"") ; 
                         }
                      ok=L_BUFFA_CatNBytesToCache(&(htxtp.htxt),&(htxtp.ntxt),
                                                    " <",strlen(" <")) ;
                      if (ok==FALSE)
                         {
                           FreeTok(TokEspa) ;
                           X_ALLOC_Free((void **)&token) ;
                           fseek(f,ipos,SEEK_SET) ;
                           L_HTXT_SetHtxt(np,&htxtp) ;
                           return FALSE ;
                         }
                      ok=AddNodeInfo(&(htxtp.ilinks),&(htxtp.nlinks),
                                       htxtp.ntxt,tref) ;
                      if (ok==FALSE)
                         {
                           FreeTok(TokEspa) ;
                           X_ALLOC_Free((void **)&token) ;
                           X_ALLOC_Free((void **)&tref) ;
                           fseek(f,ipos,SEEK_SET) ;
                           L_HTXT_SetHtxt(np,&htxtp) ;
                           return FALSE ;
                         }
                      ok=L_BUFFA_CatNBytesToCache(&(htxtp.htxt),&(htxtp.ntxt),
                                                  token,strlen(token)) ;
                      X_ALLOC_Free((void **)&token) ;
                      if (ok==FALSE)
                         {
                           FreeTok(TokEspa) ;
                           fseek(f,ipos,SEEK_SET) ;
                           L_HTXT_SetHtxt(np,&htxtp) ;
                           return FALSE ;
                         }
                      ok=L_BUFFA_CatNBytesToCache(&(htxtp.htxt),&(htxtp.ntxt),"> ",
                                                  strlen(" >")) ;
                      if (ok==FALSE)
                         {
                           FreeTok(TokEspa) ;
                           fseek(f,ipos,SEEK_SET) ;
                           L_HTXT_SetHtxt(np,&htxtp) ;
                           return FALSE ;
                         }
                      break ;
             default : ;
           }/*switch(tokfound)*/
         }/*while (TRUE)*/
       }
  
       T_BOOL L_HTXT_ReadHtxtNode ( INOUT t_DiNode      **nodo,
                                    IN    t_htxtsintax   *s,
                                    IN    FILE           *f )
       {
         t_htxtp *nprop ;
         T_CHAR *nombre ;
         T_BOOL ok ;
  
        nprop=L_HTXT_CreatByDefault() ;
        NULL_RET_FALSE(nprop) ;
        *nodo=L_GRAFO_NewNode() ;
        NULL_RET_FALSE((*nodo)) ;
        nombre=L_FSTR_GetItemValue(f,
               s->HtxtName,s->CaseSensitive,s->Delimitadores) ;
        if (!nombre)
         {
           L_HTXT_Destroy(&nprop) ;
           L_GRAFO_fFreeNode(nodo,(T_BOOL (*)(T_POINTER *))L_HTXT_Destroy) ;
           (*nodo)=NULL ;
           return FALSE ;
         }
        ok=L_HTXT_ReadHtxtProp(nprop,s,f) ;
        if (ok==FALSE)
         {
           L_HTXT_Destroy(&nprop) ;
           L_GRAFO_fFreeNode(nodo,(T_BOOL (*)(T_POINTER *))L_HTXT_Destroy) ;
           X_ALLOC_Free((void **)&nombre) ;
           (*nodo)=NULL ;
           /*L_HTXT_ErrorInfo(f) ;*/
           return FALSE ;
         }
        L_GRAFO_SetName(*nodo,nombre) ;
        L_GRAFO_SetNodePropiedades(*nodo,nprop) ;
        return TRUE ;
      }
  
       void FreeDinoFromTabla ( t_DiNode *e )
       {
         L_GRAFO_fFreeNode(&e,(T_BOOL (*)(T_POINTER *))L_HTXT_Destroy) ;
       }
       
  
       void FreeTabla ( t_tabla *tabla )
       {
         T_INT ntabla ;
         t_DiNode *e ;
  
        ntabla=L_DARRAY_GetNDarray((t_pointerDArray)(*tabla)) ;
        while(ntabla>1)
        {
        L_TABLA_DelEndTabla(tabla,&ntabla,&e) ;
        if (!L_GRAFO_GetNFathers(e))
           { /* NO podemos llegar a este Node.! */
               T_CHAR *nname ;
  
               nname=L_GRAFO_GetName(e) ;
               L_DEBUG_MSG_PrintF(WARNING,FALSE,
                              "Node \'%s\' NO alcanzable desde otros.",nname) ;
           }
        }
        L_TABLA_DelEndTabla(tabla,&ntabla,&e) ;
      }
  
      T_CHAR *DupId ( T_CHAR *org )
      {
        T_U_INT tocpy ;
        T_CHAR *paux ;
  
        for(tocpy=0;org[tocpy]!='>';tocpy++) ;
        paux=X_ALLOC_MemDup(org,tocpy+1) ;
        NULL_RET_NULL(paux) ;
        paux[tocpy]='\0' ;
        return paux ;
      }
  
  
      T_BOOL L_HTXT_ReadHtxtNodes ( INOUT  t_DiNode      **g, 
                                    IN     t_htxtsintax   *s, 
 			           INOUT  FILE           *f )
      {
        HTxtP htxtp ;
        t_tabla taux ;
        t_DiNode *e, *e2 ;
        T_BOOL ok ;
        T_U_INT ntaux, i, j ;
        t_htxtp *np ;
        T_CHAR *pstr, *idstr ;
  
        (*g)=NULL ;
        taux=NULL ;
        do
        {
          ok=L_HTXT_ReadHtxtNode(&e,s,f) ;
        if (ok==TRUE)
           {
             L_TABLA_InsEndTabla(&taux,&ntaux,e) ;
             L_WIN_Flush() ;
           }
        } while (ok==TRUE) ;
        L_DEBUG_NULL_E_F(taux,"Incorrect File Format.") ;
        for(i=0;i<ntaux;i++)
        {
        e=L_TABLA_GetNFromTabla(taux,i) ;
        np=L_GRAFO_GetNodePropiedades(e) ;
        L_HTXT_GetHtxt(np,&htxtp) ;
        for(j=0;j<htxtp.nlinks;j++)
        {
          pstr=(T_CHAR *)(htxtp.htxt+(htxtp.ilinks[j])->idlink) ;
          idstr=DupId(pstr) ;
          e2=L_TABLA_GetNamedFromTabla(idstr,taux) ;
          X_ALLOC_Free((void **)&idstr) ;
          if (e2 != NULL)
             {
               X_ALLOC_Free((void **)&idstr) ;
               ok=L_GRAFO_NewSonLink(e,e2) ;
               if (ok==FALSE)
                  {
                    L_DARRAY_FreeEltosDarray((t_pointerDArray *)&taux,
                                          (T_U_LONG *)&ntaux,
                                          (void (*)(T_POINTER))FreeDinoFromTabla) ;
                    return FALSE ;
                  }
             }
        }
        }
        (*g)=taux[0] ;
        FreeTabla(&taux) ;
        return TRUE ;
      }
  
      T_BOOL L_HTXT_ReadHtxt ( INOUT  t_DiNode      **g, 
                               IN     t_htxtsintax   *s, 
  			       INOUT  FILE           *f )
      {
        HTxtP htxtp ;
        t_tabla taux ;
        t_DiNode *e, *e2 ;
        T_BOOL ok ;
        T_U_INT ntaux, i, j ;
        t_htxtp *np ;
        T_CHAR *pstr, *idstr ;
  
        (*g)=NULL ;
        taux=NULL ;
        do
        {
          ok=L_HTXT_ReadHtxtNode(&e,s,f) ;
        if (ok==TRUE)
           {
             L_TABLA_InsEndTabla(&taux,&ntaux,e) ;
             L_WIN_Flush() ;
           }
        } while (ok==TRUE) ;
        L_DEBUG_NULL_E_F(taux,"Incorrect File Format.") ;
        for(i=0;i<ntaux;i++)
        {
        e=L_TABLA_GetNFromTabla(taux,i) ;
        np=L_GRAFO_GetNodePropiedades(e) ;
        L_HTXT_GetHtxt(np,&htxtp) ;
        for(j=0;j<htxtp.nlinks;j++)
        {
          pstr=(T_CHAR *)(htxtp.htxt+(htxtp.ilinks[j])->idlink) ;
          idstr=DupId(pstr) ;
          e2=L_TABLA_GetNamedFromTabla(idstr,taux) ;
          if (!e2)
             {
                 T_CHAR *ebuff, *ncaller ;
  
               ncaller = L_GRAFO_GetName(e) ;
               ebuff   = X_ALLOC_Malloc(strlen(ncaller)+strlen(idstr)+1+
                                        strlen("node '' try links with '' that no exist in file")) ;
               if (ebuff)
                  {
                    sprintf(ebuff,
                            "node '%s' try links with '%s' that no exist in file",
                            ncaller,idstr) ;
                    L_DEBUG_MSG_Write(ERROR,FALSE,ebuff) ;
                    X_ALLOC_Free((void **)&ebuff) ;
                  } else {
                           L_DEBUG_MSG_Write(ERROR,FALSE,
                                             "Try link with a not present file node.") ;
                         }
                 L_DARRAY_FreeEltosDarray((t_pointerDArray *)&taux,
                                          (T_U_LONG *)&ntaux,
                                          (void (*)(T_POINTER))FreeDinoFromTabla) ;
                 X_ALLOC_Free((void **)&idstr) ;
               return FALSE ;
             } else {
                      X_ALLOC_Free((void **)&idstr) ;
                      ok=L_GRAFO_NewSonLink(e,e2) ;
                      if (ok==FALSE)
                      {
                        L_DARRAY_FreeEltosDarray((t_pointerDArray *)&taux,
                                          (T_U_LONG *)&ntaux,
                                          (void (*)(T_POINTER))FreeDinoFromTabla) ;
                        return FALSE ;
                      }
                    }
        }
        }
        (*g)=taux[0] ;
        FreeTabla(&taux) ;
        return TRUE ;
      }
  
      T_BOOL L_HTXT_DestroyHtxt ( INOUT t_DiNode      **g )
      {
        L_GRAFO_FreeKill(  g,
                          (T_BOOL (*) (T_POINTER *))L_HTXT_Destroy) ;
        return TRUE ;
      }


      /* browsing hypertext ... *           
       * ------------------------ */         
      T_INT L_HTXT_Present ( t_DiNode *g )
      {
        t_htext htexto ;
        T_INT key, state ;
 
        htexto=L_HTXT_Open(g) ;
        if (!g)
            return c_HTXT_NOMEM ;
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
           default   : state=L_HTXT_KeyProcesing(&htexto,key) ;
         }
        } while (state==c_KEYPROC) ;
        L_HTXT_Close(&htexto) ;
        switch (state)
        {
         case c_CHOSE : return c_HTXT_FALL ;
         case c_ERROR : return c_HTXT_NOMEM ;
         default      : return c_HTXT_OK ;
        }
      }
 
      T_INT L_HTXT_ReadAndPresent ( INOUT FILE *f, IN t_htxtsintax s )
      {
        t_DiNode *g ;
 
        L_HTXT_ReadHtxt(&g,&s,f) ;
        return L_HTXT_Present(g) ;
      }
 
      T_INT L_HTXT_GetSelectNode (IN t_htext hx)
      {
        return ((!hx) ? 0 : hx->linkopcion) ;
      }
 
      T_CHAR *GetInfoofSelect (IN t_htext hx, INOUT T_INT *offset) 
      {
        t_htxtp *np ;
        HTxtP htxtp ;
        T_CHAR *nameopcion ;
        T_CHAR *sini, *sfin ;
 
        np=L_GRAFO_GetNodePropiedades(hx->d) ;
        L_HTXT_GetHtxt(np,&htxtp) ;
        (*offset)=(htxtp.ilinks[(hx->linkopcion)-1])->idlink ;
        sini=&(htxtp.htxt[*offset]) ;
        for (sfin=sini; ((*sfin)!='>') && (*sfin); sfin++) ;
        NULL_RET_NULL(*sfin) ;
        nameopcion=(T_CHAR *)X_ALLOC_MemDup(sini,(T_INT)(sfin-sini+1)) ;
        nameopcion[(T_INT)(sfin-sini)]='\0' ;
        return nameopcion ;
      }
 
      T_CHAR *L_HTXT_GetSelectNodeName (IN t_htext hx)
      {
        t_DiNode *e ;
 
        NULL_RET_NULL(hx) ;
        if (hx->linkopcion<1)
            return NULL ;
        e=L_GRAFO_GetSonN(hx->linkopcion-1,hx->d) ;
        if (e)
          {
             T_CHAR *NName=L_GRAFO_GetName(e) ;
 
             return (T_CHAR *)X_STRING_StrDup(NName) ;
          } else {
                    T_INT opc ;
 
                    return GetInfoofSelect(hx,&opc) ; 
                 }
      }
 
      /* seeing Hipertext ... */
      T_BOOL SenyalaNode (t_htext hx)
      {
        t_htxtp *np ;
        HTxtP htxtp ;
        T_CHAR *nameopcion ;
        T_INT sx1, sy1, sx2, sy2, uplines, downlines, offset, wwidth ;
 
        NULL_RET_FALSE(hx) ;
        NULL_RET_FALSE(hx->ws) ;
        if (hx->linkopcion<1)
           return TRUE ;
        /* nameopcion=GetInfoofSelect(hx,&offset) ; */
 
        np=L_GRAFO_GetNodePropiedades(hx->d) ;
        L_HTXT_GetHtxt(np,&htxtp) ;
        offset=(htxtp.ilinks[(hx->linkopcion)-1])->idlink ;
        nameopcion=L_HTXT_GetSelectNodeName(hx) ;
        NULL_RET_FALSE(nameopcion) ;
        L_WIN_GetInfo(hx->w,&uplines,&downlines) ;
        wwidth=hx->x2-hx->x1-1 ;
        sx1=offset % wwidth ;
        sy1=(offset / wwidth) + (sx1 > 0) ;
        sy1-=uplines ;
        L_WIN_PutOnTop(hx->ws) ;
        if (sy1 <= 0)
          { /* la opcion esta en lineas de arriba de win */
            L_WIN_Hidden(hx->ws) ;
             X_ALLOC_Free((void **)&nameopcion) ;
            return TRUE ;
          }
        if (sy1 >= (hx->y2-hx->y1))
          {  /* opcion debajo ... */
            L_WIN_Hidden(hx->ws) ;
             X_ALLOC_Free((void **)&nameopcion) ;
            return TRUE ;
          }
        sx2=MIN(hx->x1+sx1+strlen(nameopcion)+1,hx->x2) ;
        sy2=hx->y1+sy1+1 ;
        nameopcion[sx2-hx->x1-sx1-1]='\0' ;
        L_WIN_Move(hx->ws,sx1+hx->x1,hx->y1+sy1-1,sx2,sy2) ;
        L_WIN_Clear(hx->ws) ;
        L_WIN_WriteStr(hx->ws,nameopcion) ;
        L_WIN_UnHidden(hx->ws) ;
        X_ALLOC_Free((void **)&nameopcion) ;
        return TRUE ;
      }
 
      T_BOOL OpenHtxt (t_htext *idhtxt, t_DiNode *d)
      {
        t_htxtp *np ;
        HTxtP htxtp ;
        T_BOOL ok ;
        T_INT uplines, downlines, bsize ;
        T_CHAR *pchar ;
 
        np=L_GRAFO_GetNodePropiedades(d) ;
        L_HTXT_GetHtxt(np,&htxtp) ;
        (*idhtxt)->d=d ;
        (*idhtxt)->x1=htxtp.px1 ;
        (*idhtxt)->y1=htxtp.py1 ;
        (*idhtxt)->x2=htxtp.px2 ;
        (*idhtxt)->y2=htxtp.py2 ;
        (*idhtxt)->x1=MAX((*idhtxt)->x1,1) ;
        (*idhtxt)->x2=MIN((*idhtxt)->x2,V_TERM_cmaxX()) ;
        (*idhtxt)->y1=MAX((*idhtxt)->y1,1) ;
        (*idhtxt)->y2=MIN((*idhtxt)->y2,V_TERM_cmaxY()) ;
        #if defined(__COOL__)
          (*idhtxt)->wback=c_Blue ;
          (*idhtxt)->wfore=c_LightGray ;
          (*idhtxt)->wfback=c_Blue ;
          (*idhtxt)->wffore=c_LightGray ;
 
          (*idhtxt)->wsback=c_Cyan ;
          (*idhtxt)->wsfore=c_DarkGray ;
          (*idhtxt)->wsfback=c_Cyan ;
          (*idhtxt)->wsffore=c_DarkGray ;
        #else
          L_WIN_SetDefaultColour(&((*idhtxt)->wback),&((*idhtxt)->wfore),
                                 &((*idhtxt)->wfback),&((*idhtxt)->wffore)) ;
          L_WIN_SetDefaultColour(&((*idhtxt)->wsfback),&((*idhtxt)->wsffore),
                                 &((*idhtxt)->wsfore),&((*idhtxt)->wsback)) ;
        #endif
        (*idhtxt)->w=L_WIN_Open((*idhtxt)->x1,(*idhtxt)->y1,(*idhtxt)->x2,
                               (*idhtxt)->y2) ;
        if (!(*idhtxt)->w)
          {
             X_ALLOC_Free((void **)&(*idhtxt)) ;
            return FALSE ;
          }
        (*idhtxt)->ws=L_WIN_Open(1,1,3,3) ;
        if (!((*idhtxt)->ws))
          {
            L_WIN_Close((*idhtxt)->w) ;
            X_ALLOC_Free((void **)&(*idhtxt)) ;
            return FALSE ;
          }
        L_WIN_Hidden((*idhtxt)->ws) ;
        L_WIN_SetColours((*idhtxt)->ws,(*idhtxt)->wsback,(*idhtxt)->wsfore,
                                   (*idhtxt)->wsfback,(*idhtxt)->wsffore) ;
        L_WIN_SetColours((*idhtxt)->w,(*idhtxt)->wback,(*idhtxt)->wfore,
                                  (*idhtxt)->wfback,(*idhtxt)->wffore) ;
        L_WIN_SetTitle((*idhtxt)->w,c_LEFTUP_TITLE,L_GRAFO_GetName(d)) ;
        L_WIN_SetFrame((*idhtxt)->w,TRUE,c_SIMPLE_FRAME1) ;
        L_WIN_Shadow((*idhtxt)->w) ;
        L_WIN_Keep((*idhtxt)->w) ;
        bsize=strlen(htxtp.htxt) ;
        pchar=X_ALLOC_MemDup(htxtp.htxt,bsize) ;
        NULL_RET_FALSE(pchar) ;
        L_WIN_SetTextWin((*idhtxt)->w,pchar,bsize) ;
        L_WIN_GetInfo((*idhtxt)->w,&uplines,&downlines) ;
        L_WIN_ScrollDown((*idhtxt)->w,uplines) ;
        (*idhtxt)->linkopcion=(htxtp.nlinks) ? 1 : 0 ; /* si no ahi, no senyalo */
        (*idhtxt)->totallinks=htxtp.nlinks ;
        ok=SenyalaNode((*idhtxt)) ;
        if (ok==FALSE)
          {
            L_WIN_Close((*idhtxt)->w) ;
            L_WIN_Close((*idhtxt)->ws) ;
             X_ALLOC_Free((void **)&(*idhtxt)) ;
            return FALSE ;
          }
        return TRUE ;
      }
 
      t_htext L_HTXT_Open (t_DiNode *d)
      {
        t_htext idhtxt ;
        T_BOOL ok ;
 
        idhtxt=X_ALLOC_Malloc(c_HTXT) ;
        NULL_RET_NULL(idhtxt)
        ok=OpenHtxt(&idhtxt,d) ;
        if (ok==FALSE)
          {
             X_ALLOC_Free((void **)&idhtxt) ;
            return NULL ;
          }
        return idhtxt ;
      }
 
      T_INT L_HTXT_KeyProcesing (t_htext *hx, T_INT tecla)
      {
        T_BOOL ok ;
 
        if (!(*hx))
          {
            L_DEBUG_MSG_Write(WARNING,FALSE,
                              "HiperText is NULL.!") ;
            return c_ERROR ;
          }
        if (L_STTBOX_KeyProcessing((*hx)->w,tecla) == c_KEYPROC)
           {
             SenyalaNode((*hx)) ;
             return c_KEYPROC ;
           }
        switch (tecla)
        {
         case c_RIGHT :
         case c_TAB :
              if ((*hx)->linkopcion < (*hx)->totallinks)
                 {
                   ((*hx)->linkopcion)++ ;
                   SenyalaNode((*hx)) ;
                 }
              return c_KEYPROC ;
         case c_LEFT :
         case c_DEL :
              if ((*hx)->linkopcion > 1)
                 {
                   ((*hx)->linkopcion)-- ;
                   SenyalaNode((*hx)) ;
                 }
              return c_KEYPROC ;
         default : break ;
        }
        switch (tecla)
        {
         case c_ENTER :
              if ( ((*hx)->linkopcion) && ((*hx)->d) )
                 {
                   t_DiNode *e ;
 
                   e=L_GRAFO_GetSonN(((*hx)->linkopcion-1),(*hx)->d) ;
                   /* sons go from 0 till n, & linkopcion from 1 till n+1 */
                   if (!e)
                       return c_CHOSE ;
                   L_WIN_Close((*hx)->w) ;
                   L_WIN_Close((*hx)->ws) ;
                   ok=OpenHtxt(hx,e) ;
                   if (ok==FALSE)
                       return c_ERROR ;
                 } else {
                          L_DEBUG_MSG_Write(WARNING,FALSE,
                                            "HiperNode is NULL or select is none.") ;
                        }
              return c_KEYPROC ;
         case c_ESC :
              return c_CLOSE ;
         default :
              L_DEBUG_MSG_Write(WARNING,FALSE,"Unknow key code! ") ;
        }
        return c_KEYPROC ;
      }
 
      void L_HTXT_Close (t_htext *hx)
      {
        if (*hx)
          {
            L_WIN_Close((*hx)->w) ;
            L_WIN_Close((*hx)->ws) ;
             X_ALLOC_Free((void **)&(*hx)) ;
            *hx=NULL ;
          }
      }
 
      void L_HTXT_SetFrame (t_htext hx, T_CHAR *frame)
      {
        if (hx)
           L_WIN_SetFrame(hx->w,TRUE,frame) ;
      }
 
      T_CHAR *L_HTXT_GetFrame (t_htext hx)
      {
        static T_CHAR frame[10] ;
        T_BOOL ok ;
 
        NULL_RET_NULL(hx) ;
        L_WIN_GetFrame(hx->w,&ok,frame) ;
        if (ok==FALSE)
           return NULL ;
        return frame ;
      }
 
      T_BOOL L_HTXT_UnHidden (t_htext hx)
      {
        if (hx)
                return L_WIN_UnHidden(hx->w) ;
           else return FALSE ;
      }
 
      T_BOOL L_HTXT_Hidden(t_htext hx)
      {
        if (hx)
                return L_WIN_Hidden(hx->w) ;
           else return FALSE ;
      }
 
      void L_HTXT_SetColors (t_htext hx,
                             t_txt_colores wback, t_txt_colores wfore,
                             t_txt_colores wfback, t_txt_colores wffore,
                             t_txt_colores wsback, t_txt_colores wsfore,
                             t_txt_colores wsfback, t_txt_colores wsffore)
      {
        if (hx)
          {
            hx->wback=wback ;
            hx->wfore=wfore ;
            hx->wfback=wfback ;
            hx->wffore=wffore ;
            hx->wsback=wsback ;
            hx->wsfore=wsfore ;
            hx->wsfback=wsfback ;
            hx->wsffore=wsffore ;
            L_WIN_SetColours(hx->w,wback,wfore,wfback,wffore) ;
            L_WIN_SetColours(hx->ws,wsback,wsfore,wsfback,wsffore) ;
          }
      }
 
      void L_HTXT_GetColors (t_htext hx,
                             t_txt_colores *wback, t_txt_colores *wfore,
                             t_txt_colores *wfback, t_txt_colores *wffore,
                             t_txt_colores *wsback, t_txt_colores *wsfore,
                             t_txt_colores *wsfback, t_txt_colores *wsffore)
      {
        if (hx)
          {
            *wback=hx->wback ;
            *wfore=hx->wfore ;
            *wfback=hx->wfback ;
            *wffore=hx->wffore ;
            *wsback=hx->wsback ;
            *wsfore=hx->wsfore ;
            *wsfback=hx->wsfback ;
            *wsffore=hx->wsffore ;
          }
      }
 

 /* ...................................................................... */

