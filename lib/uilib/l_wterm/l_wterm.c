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



   /* ... Includes / Inclusiones ......................................... */

      #include "uilib/l_wterm/l_wterm.h"


    /* ... Global vars / Vars. globales ................................... */

    t_twin  MainTWin ;
      /* Contiene el descriptor de la ventana 0, la inicial. */
    T_CHAR  v_chclear=' ' ;
      /* Contiene el caracter de relleno a usar */


   /****************************************************************
    *    Seccion : MISCELANEAS
    ****************************************************************/

    T_BOOL    GoodCoor                      (T_INT x1,T_INT y1,T_INT x2,T_INT y2)
    {
      if ( (x2<=x1) || (y2<=y1) || (x1<0) || (y1<0) )
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,
                             "please check: x1>=0, x2>x1, y1>=0, y2>y1\n") ;
           return FALSE ;
         }
      return TRUE ;
    }

    T_BOOL    GoodDupMode                   (T_INT mode)
    {
      if ( (mode==c_SHARE) || (mode==c_FULL) )
            return TRUE ;
      L_DEBUG_MSG_Write(ERROR,FALSE,"Not c_SHARE, Not c_FULL\n") ;
      return FALSE ;
    }

    T_BOOL    GoodTitleMode                 (T_INT mode)
    {
      if ( (mode>=c_NO_TITLE) || (mode<=c_CENTERDOWN_TITLE) )
            return TRUE ;
      L_DEBUG_MSG_Write(ERROR,FALSE,"Not valid title mode.\n") ;
      return FALSE ;
    }

    T_BOOL    GoodColours                   (t_txt_colores wback,
                                           t_txt_colores wfore,
                                           t_txt_colores fback,
                                           t_txt_colores ffore)
    {
      if ( (wback<c_Black) || (wback>c_White) )
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"NOT valid wback.\n") ;
           return FALSE ;
         }
      if ( (wfore<c_Black) || (wfore>c_White) )
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"NOT valid wfore.\n") ;
           return FALSE ;
         }
      if ( (fback<c_Black) || (fback>c_White) )
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"NOT valid fback.\n") ;
           return FALSE ;
         }
      if ( (ffore<c_Black) || (ffore>c_White) )
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"NOT valid ffore.\n") ;
           return FALSE ;
         }
      return TRUE ;
    }

    T_BOOL    Touch                         (t_tscreen wpan, t_twin W)
    {
      if ((W)->hiddenOn==TRUE)
          return TRUE ;
      if (wpan->dirtyPan==FALSE)
         {
           wpan->fx1=(W)->x1 ;
           wpan->fy1=(W)->y1 ;
           wpan->fx2=(W)->x2 ;
           wpan->fy2=(W)->y2 ;
         } else {
                  wpan->fx1=MIN(wpan->fx1,(W)->x1) ;
                  wpan->fy1=MIN(wpan->fy1,(W)->y1) ;
                  wpan->fx2=MAX(wpan->fx2,(W)->x2) ;
                  wpan->fy2=MAX(wpan->fy2,(W)->y2) ;
                }
      wpan->fx1=MAX(wpan->fx1,1) ;
      wpan->fy1=MAX(wpan->fy1,1) ;
      wpan->fx2=MIN(wpan->fx2,wpan->rho) ;
      wpan->fy2=MIN(wpan->fy2,wpan->rve) ;
      (W)->dirty=TRUE ;
      wpan->dirtyPan=TRUE ;
      return TRUE ;
    }

    T_BOOL    Inside                        (t_twin W, T_INT x, T_INT y)
    {
      if (y >= (W)->y2) return FALSE ;
      if (y <= (W)->y1) return FALSE ;
      if (x >= (W)->x2) return FALSE ;
      if (x <= (W)->x1) return FALSE ;
      return TRUE ;
    }

    void    FillNullWin                   (t_twin W, T_INT x1, T_INT y1,
                                           T_INT x2, T_INT y2, T_INT ticket)
    {
      (W)->x1=x1 ;
      (W)->y1=y1 ;
      (W)->x2=x2 ;
      (W)->y2=y2 ;
      (W)->posx=1 ;
      (W)->posy=1 ;
      (W)->uplines=0 ;
      (W)->downlines=0 ;
      (W)->hiddenOn=FALSE ;
      (W)->frameOn=FALSE ;
      (W)->dirty=TRUE ;
      (W)->keep=FALSE ;
      (W)->shadow=FALSE ;
      (W)->title=NULL ;
      (W)->titlex=1 ;
      (W)->titley=1 ;
      (W)->titlemode=c_NO_TITLE ;
      X_ALLOC_MemMove((W)->frame,c_SIMPLE_FRAME1,8) ;
      X_ALLOC_MemMove((W)->keeptitle,c_SIMPLE_KEEP,4) ;
      L_WTERM_SetDefaultColour(&((W)->wback),&((W)->wfore),
                             &((W)->fback),&((W)->ffore)) ;
      (W)->orden=ticket ;
    }


   /****************************************************************
    *    Seccion : MANEJO DE BUFFERS
    ****************************************************************/

    void    FillIntoBuff                  (T_CHAR *buffd, T_INT x1, T_INT y1,
                                           T_INT wwidtho, T_INT wtallo,
                                           T_INT wwidthd, T_INT wtalld,
                                           T_CHAR cfill)
    /* rellena la ventana [x1, y1, x1+wwidtho-1, y1+wtallo-1] */
    {
      T_INT j ;
      T_CHAR *pchd ;

      if (x1<wwidthd)
         {
           for (j=0; (j<wtallo) && (y1+j<=wtalld); j++)
           {
             pchd=buffd+(y1+j-1)*wwidthd+x1-1 ;
             X_ALLOC_MemSet(pchd,cfill,MIN(wwidtho,(wwidthd-x1+1))) ;
           }
         }
    }

    void    CpIntoBuff                    (T_CHAR *buffd, T_CHAR *buffo,
                                           T_INT x1, T_INT y1, T_INT widtho,
                                           T_INT tallo, T_INT widthd, T_INT talld)
    /*  copia, la ventana widtho*tallo, de buffo a buffd :
        ojo, x1 y y1 son las coordenadas del comienzo del texto
        en la ventana destino. La esquina left-up es 1,1 */
    {
      T_INT j ;
      T_CHAR *pchd,*pcho ;

      if ( (x1<=widthd) && (y1<=talld) )
         {
           for (j=0; (j<tallo) && (y1+j-1<talld); j++)
           {
             pchd=buffd+(y1+j-1)*widthd+x1-1 ;
             pcho=buffo+j*widtho ;
             X_ALLOC_MemMove(pchd,pcho,MIN(widtho,(widthd-x1+1))) ;
           }
         }
    }

    void    WriteBorderIntoBuff           (T_CHAR *buffd, T_INT widthd,
                                           T_INT talld, t_twin W)
    /* Border == frame + title + keep id */
    {
      T_INT j, widtho ;
      T_CHAR *pchd ;

      /* ... Frame ... */
      widtho=((W)->x2-(W)->x1-1) ;
      if (((W)->x1 <= widthd) && ((W)->y1 <= talld))
         {
           for(j=0;(j<widtho+2) && ((W)->x1+j<widthd);j++)
           {
             pchd    = buffd+((W)->y1-1)*widthd+((W)->x1-1+j) ;
             (*pchd) = (W)->frame[1] ;
           }
           pchd=buffd+((W)->y1-1)*widthd+((W)->x1-1) ;
           *pchd=(W)->frame[0] ;
           if ((W)->x1+widtho+1<=widthd)
              *(pchd+widtho+1)=(W)->frame[2] ;
         }
      if (((W)->x1 <= widthd) && ((W)->y2 <= talld))
         {
           for(j=0;(j<widtho+2) && ((W)->x1+j<widthd);j++)
           {
             pchd=buffd+((W)->y2-1)*widthd+((W)->x1-1+j) ;
             *pchd=(W)->frame[6] ;
           }
           pchd=buffd+((W)->y2-1)*widthd+((W)->x1-1) ;
           *pchd=(W)->frame[5] ;
           if ((W)->x1+widtho+1<=widthd)
              *(pchd+widtho+1)=(W)->frame[7] ;
         }
      for (j=(W)->y1+1;(j<(W)->y2) && (j<=talld);j++)
          {
            if ((W)->x1<=widthd)
            {
              pchd=buffd+(j-1)*widthd+((W)->x1-1) ;
              *pchd=(W)->frame[3] ;
            }
            if ((W)->x2<=widthd)
            {
              pchd+=widtho+1 ;
              *pchd=(W)->frame[4] ;
            }
          }
      /* ... Titulo ... */
      if ((W)->titlemode!=c_NO_TITLE)
         {
           CpIntoBuff(buffd,(W)->title,(W)->titlex,(W)->titley,
                      strlen((W)->title),1,widthd,talld) ;
         }
      /* ... Keep Bar ... */
      if ( ((W)->keep) && ((W)->x2<=widthd) && ((W)->uplines || (W)->downlines) )
         {
           T_INT talldo, begblock, endblock ;
           float clines ;

           talldo=((W)->y2-(W)->y1-1) ;
           if (talldo > 2)
           {
             clines=(float)(talldo-2) / (float)((W)->uplines+(W)->downlines+talldo) ;
             begblock=(T_INT)((W)->y1+1+clines*(W)->uplines) ;
             endblock=(T_INT)((W)->y2-1-clines*(W)->downlines) ;
             for (j=(W)->y1+1; (j<begblock) && (j<=talld); j++)
             {
               pchd=buffd+(j-1)*widthd+(W)->x1+widtho ;
               *pchd=(W)->keeptitle[1] ;
             }
             for (j=begblock; (j<endblock) && (j<=talld); j++)
             {
               pchd=buffd+(j-1)*widthd+(W)->x1+widtho ;
               *pchd=(W)->keeptitle[3] ;
             }
             for (j=endblock; (j<(W)->y2) && (j<=talld); j++)
             {
               pchd=buffd+(j-1)*widthd+(W)->x1+widtho ;
               *pchd=(W)->keeptitle[1] ;
             }
             pchd=buffd+(W)->y1*widthd+(W)->x1+widtho ;
             *pchd=(W)->keeptitle[0] ;
             pchd=buffd+(W)->x1+widtho+(j-2)*widthd ;
             *pchd=(W)->keeptitle[2] ;
           }
         }
    }

    void    ShiftDownLines                (T_CHAR *buff, T_INT lines,
                                           T_INT linestomove, T_INT width)
    {
      T_CHAR *pch ;
      T_INT tomove ;

      pch=linestomove*width+buff ;
      tomove=(lines-linestomove)*width ;
      X_ALLOC_MemMove(pch,buff,tomove) ;
      X_ALLOC_MemSet(buff,v_chclear,linestomove*width) ;
    }

    void    ShiftUpLines                  (T_CHAR *buff, T_INT lines,
                                           T_INT linestomove, T_INT width)
    {
      T_CHAR *pch ;
      T_INT tomove ;

      pch=linestomove*width+buff ;
      tomove=(lines-linestomove)*width ;
      X_ALLOC_MemMove(buff,pch,tomove) ;
      pch=buff+tomove ;
      X_ALLOC_MemSet(pch,v_chclear,linestomove*width) ;
    }

    T_BOOL    DumpIntoBuff                  (T_CHAR *tir, T_INT longi,
                                           T_CHAR *buff, T_INT x,
                                           T_INT y, T_INT width)
    {
      T_CHAR *paux ;

      paux=buff+(y-1)*width+x-1 ;
      X_ALLOC_MemMove(paux,tir,longi) ;
      return TRUE ;
    }


   /****************************************************************
    *    Seccion :  GESTION TABLA VENTANA
    ****************************************************************/

    T_INT     AddList                       (t_tscreen wpan, t_twin W)
    {
      /* (wpan->WinNum) :  es el numero de ventanas hay
                        y la posicion donde esta el NULL */
      if ((wpan->WinNum) == 0)
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"Used L_WTERM_Init() FIRST.!!!\n") ;
           return 0 ;
         }
      if ( L_DARRAY_InsEndDarray( (t_pointerDArray *)&(wpan->WinList),
                                  (T_U_LONG *)&(wpan->WinNum),
                                  (T_POINTER)W ) == FALSE )
                return -1 ;
           else return ((wpan->WinNum)-1) ;
    }

    T_BOOL    RmList                        (t_tscreen wpan, T_INT pos)
    {
      T_INT i ;

      if (pos>(wpan->WinNum))
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"Win Allready Close.\n") ;
           return FALSE ;
         }
      if ((pos==0) && ((wpan->WinNum)>1))
         {
           L_DEBUG_MSG_Write(WARNING,FALSE,"do you try remove from winlist the MainTWin ?\n") ;
           return FALSE ;
         }
      X_ALLOC_MemMove( ((T_CHAR *)(wpan->WinList)+pos*sizeof(t_twin)),
                       ((T_CHAR *)(wpan->WinList)+(pos+1)*sizeof(t_twin)),
                       ((wpan->WinNum)-pos)*sizeof(t_twin)) ;
      (wpan->WinList)=X_ALLOC_Realloc((wpan->WinList),(wpan->WinNum)*sizeof(t_twin)) ;
      (wpan->WinNum)-- ;
      for(i=pos; i<(wpan->WinNum); i++)
         {
           (wpan->WinList)[i]->orden=i ;
         }
      return TRUE ;
    }

    T_BOOL    XchInList                     (t_tscreen wpan, T_INT w1, T_INT w2)
    {
      t_twin waux ;

      if (w1>(wpan->WinNum))
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,
                         "do you try exchange with a w1 already close.\n") ;
           return FALSE ;
         }
      if (w2>(wpan->WinNum))
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,
                         "do you try exchange with a w2 already close.\n") ;
           return FALSE ;
         }
      waux=(wpan->WinList)[w1] ;
      (wpan->WinList)[w1]=(wpan->WinList)[w2] ;
      (wpan->WinList)[w2]=waux ;
      waux->orden=w2 ;
      (wpan->WinList)[w1]->orden=w1 ;
      Touch(wpan,waux) ;
      Touch(wpan,(wpan->WinList)[w1]) ;
      return TRUE ;
    }


   /****************************************************************
    *    Seccion : FUNCIONES AUXILIARES RESIDUALES
    ****************************************************************/

    /* ... Auxiliares de L_WTERM_Close ............................. */

    T_BOOL  L_WTERM_CloseSystem ( t_tscreen wpan )
    {
      T_INT i ;

      /* ... No more info ... */
      L_DEBUG_MSG_PrintMsg = NULL ;
      #ifdef _TRACE_ON_
            /* Uncomment for know how are post-morten menssages */
            /*L_DEBUG_MSG_PrintMsg = vprintf ;*/
      #endif
      /* ... close all, less mainwin ... */
      for(i=((wpan->WinNum)-1);i>0;i--)
          L_WTERM_Close(wpan,(wpan->WinList)[i]) ;
      /* ... last flush ... */
      L_WTERM_Flush(wpan) ;
      wpan->dirtyPan=FALSE ;
      /* ... close mainwin ... */
      X_ALLOC_Free((void **)&((wpan->WinList)[0]->forebuff)) ;
      X_ALLOC_Free((void **)&((wpan->WinList)[0]->title)) ;
      X_ALLOC_Free((void **)&((wpan->WinList)[0])) ;
      RmList(wpan,0) ;
      /* ... X_ALLOC_Free rest of list ... */
      X_ALLOC_Free((void **)&((wpan->WinList))) ;
      X_ALLOC_Free((void **)&(wpan->previewBuff)) ;
      X_ALLOC_Free((void **)&(wpan->previewAttr)) ;
      /* ... X_ALLOC_Free iobuff ... */
      V_TERM_FreeObuff() ;
      return TRUE ;
    }

    /* ... Auxiliar de L_WTERM_SetTitle ............................ */
    void AjustTitle(t_twin W, T_INT lentitle)
    {
      T_INT resto ;

      switch((W)->titlemode)
      {
        case c_LEFTUP_TITLE :
             (W)->titlex=(W)->x1+1 ;
             (W)->titley=(W)->y1 ;
             break ;
        case c_RIGHTUP_TITLE :
             (W)->titlex=((W)->x2-1-lentitle) ;
             (W)->titley=(W)->y1 ;
             break ;
        case c_CENTERUP_TITLE :
             resto=((W)->x2-(W)->x1+1)-lentitle ;
             resto /= 2 ;
             (W)->titlex=(W)->x1+resto ;
             (W)->titley=(W)->y1 ;
             break ;
        case c_LEFTDOWN_TITLE :
             (W)->titlex=(W)->x1+1 ;
             (W)->titley=(W)->y2 ;
             break ;
        case c_RIGHTDOWN_TITLE :
             (W)->titlex=((W)->x2-1-lentitle) ;
             (W)->titley=(W)->y2 ;
             break ;
        case c_CENTERDOWN_TITLE :
             resto=((W)->x2-(W)->x1+1)-lentitle ;
             resto /= 2 ;
             (W)->titlex=(W)->x1+resto ;
             (W)->titley=(W)->y2 ;
             break ;
        default :
             L_DEBUG_MSG_Write(ERROR,FALSE,"No valid title method.\n") ;
      }
    }

    /* ... Auxiliar de L_WTERM_WriteStr & Printf ................... */
    T_BOOL  WriteByte    (t_tscreen wpan, t_twin W, T_CHAR *str, T_INT lenstr)
    {
      T_INT quedanbytes,width,tall ;
      T_BOOL ok ;

      if (lenstr == 0)
          return TRUE ;
      width=((W)->x2-(W)->x1-1) ;
      tall=((W)->y2-(W)->y1-1) ;
      if (((W)->posy == tall+1) && ((W)->posx==0))
         { /* un WriteLn pendiente !!! */
           (W)->posx=1 ;
           L_WTERM_ScrollUp(wpan,W,1) ; /* el scroll hara (W)->posy-- */
         }
      if ((W)->posx >= (width+1))
         { /* 'WriteLn' retrasada */
           (W)->posx=1 ;
           (W)->posy++ ;
         }
      quedanbytes=width*(tall-((W)->posy-1))-((W)->posx-1) ;
      if (quedanbytes >= lenstr)
         {
           DumpIntoBuff(str,lenstr,(W)->forebuff,
                        (W)->posx,(W)->posy+(W)->uplines,width) ;
           (W)->posy+=lenstr / width ;
           (W)->posx+=lenstr % width ;
           Touch(wpan,W) ;
           return TRUE ;
         }
      DumpIntoBuff(str,quedanbytes,(W)->forebuff,
                   (W)->posx,(W)->posy+(W)->uplines,width) ;
      str+=quedanbytes ;
      lenstr-=quedanbytes ;
      (W)->posy=tall+1 ; /* el scroll quitara el ...+1 */
      (W)->posx=1 ;
      ok=L_WTERM_ScrollUp(wpan,W,1) ;
      while ( (ok==TRUE) && (lenstr / width) )
          {
            DumpIntoBuff(str,width,(W)->forebuff,
                         (W)->posx,(W)->uplines+(W)->posy,width) ;
            str+=width ;
            lenstr-=width ;
            (W)->posy=tall+1 ;
            (W)->posx=1 ;
            ok=L_WTERM_ScrollUp(wpan,W,1) ;
          }
      if (ok==FALSE)
          return FALSE ;
      DumpIntoBuff(str,(lenstr % width),(W)->forebuff,
                   (W)->posx,(W)->posy+(W)->uplines,width) ;
      (W)->posx=(lenstr % width)+1 ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_WriteStr    (t_tscreen wpan, t_twin W,T_CHAR *str)
    {
      T_BOOL ok ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      if ( (!str) || (*str=='\0') )
          return TRUE ;
      ok = WriteByte(wpan,W,str,strlen(str)) ;
      return ok ;
    }


   /****************************************************************
    *    Seccion : FUNCIONES PUBLICAS
    ****************************************************************/

    T_BOOL    L_WTERM_Exist                   (t_tscreen wpan, t_twin W)
    {
      L_DEBUG_NULL_E_F(W,"Win not exist (NULL pointer).\n") ;
      if ((W)->orden >= (wpan->WinNum))
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"Win not exist (perhaps win close?).\n") ;
           return FALSE ;
         }
      return TRUE ;
    }


    T_BOOL  L_WTERM_Open                (t_tscreen wpan, t_twin W,
                                         T_INT x1,T_INT y1,T_INT x2,T_INT y2) 
    {
      T_INT buffsize, ticket ;

      if (GoodCoor(x1,y1,x2,y2) == FALSE)
           return FALSE ;
      buffsize = (x2-x1-1)*(y2-y1-1) ;
      ticket   = AddList(wpan,W) ;
      if (ticket==-1)
          return FALSE ;
      W->forebuff=(T_CHAR *)X_ALLOC_AllocAndSet(buffsize,v_chclear) ;
      if (!(W->forebuff))
          return FALSE ;
      FillNullWin(W,x1,y1,x2,y2,ticket) ;
      W->dinamic = FALSE ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    t_twin   L_WTERM_Creat                 (t_tscreen wpan, 
                                            T_INT x1,T_INT y1,T_INT x2,T_INT y2)
    {
      T_INT buffsize, ticket ;
      t_twin waux ;

      if (GoodCoor(x1,y1,x2,y2) == FALSE)
           return NULL ;
      buffsize=(x2-x1-1)*(y2-y1-1) ;
      waux=(t_twin)X_ALLOC_Malloc(c_TWIN) ;
      NULL_RET_NULL(waux) ;
      ticket=AddList(wpan,waux) ;
      if (ticket==-1)
         {
           X_ALLOC_Free((void **)&waux) ;
           return NULL ;
         }
      waux->forebuff=(T_CHAR *)X_ALLOC_AllocAndSet(buffsize,v_chclear) ;
      if (!(waux->forebuff))
         {
           X_ALLOC_Free((void **)&waux) ;
           return NULL ;
         }
      FillNullWin(waux,x1,y1,x2,y2,ticket) ;
      waux->dinamic = TRUE ;
      Touch(wpan,waux) ;
      return waux ;
    }

    T_BOOL  L_WTERM_Close       (t_tscreen wpan, t_twin W)
    {
      T_BOOL ok ;

      if (W==MainTWin)
         {
           L_DEBUG_MSG_Write(WARNING,FALSE,"Now you are closing the win system !!!.\n") ;
           return L_WTERM_CloseSystem(wpan) ;
         }
      if (L_WTERM_Hidden(wpan,W,TRUE) == FALSE)
          return FALSE ;
      ok=RmList(wpan,(W)->orden) ;
      X_ALLOC_Free((void **)&((W)->forebuff)) ;
      X_ALLOC_Free((void **)&((W)->title)) ;
      if ((W)->dinamic == TRUE)
           X_ALLOC_Free((void **)&W) ;
      wpan->dirtyPan=TRUE ;
      return ok ;
    }

    T_BOOL L_WTERM_DoUpDate ( t_tscreen wpan )
    /* Retorna si ha sido necesario actualizar */
    {
      T_INT i, width, tall ;
      t_twin waux ;

      if (wpan->dirtyPan==FALSE)
          return FALSE ;
      for (i=0; ((i<(wpan->WinNum)) && (!(wpan->WinList)[i]->dirty)); i++)
           ; /* recorrido para buscar la primera ventana 'sucia' */
      for (; i<(wpan->WinNum); i++)
      {
        waux=(wpan->WinList)[i] ;
        if (waux->hiddenOn==FALSE)
           {
             width=(waux->x2-waux->x1-1) ;
             tall=(waux->y2-waux->y1-1) ;
             if (waux->shadow)
                {
                  FillIntoBuff((T_CHAR *)wpan->previewAttr,waux->x1+2,
                               waux->y1+1,width+2,tall+2,wpan->rho,wpan->rve,
                               (c_Black << 4) | c_LightGray) ;
                }
             if (waux->frameOn)
                {
                  WriteBorderIntoBuff(wpan->previewBuff,wpan->rho,wpan->rve,waux) ;
                  FillIntoBuff((T_CHAR *)wpan->previewAttr,waux->x1,waux->y1,
                               width+2,tall+2,wpan->rho,wpan->rve,
                               (waux->fback << 4) | waux->ffore) ;
                }
             CpIntoBuff( wpan->previewBuff,
                         ((waux->forebuff)+(waux->uplines)*width),
                         waux->x1+1,waux->y1+1,width,tall,
                         wpan->rho,wpan->rve ) ;
             FillIntoBuff((T_CHAR *)wpan->previewAttr,waux->x1+1,waux->y1+1,
                          width,tall,wpan->rho,wpan->rve,
                          (waux->wback << 4) | waux->wfore) ;
             waux->dirty=FALSE ;
           }
      }
      wpan->dirtyPan=FALSE ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_Flush        ( t_tscreen wpan )
    {
      T_INT DirtyDancing ;
      t_twin waux ;
      T_BOOL ok ;

      if (L_WTERM_DoUpDate(wpan)==FALSE)
          return TRUE ;
      ok=V_TERM_cdump(wpan->previewBuff,(T_CHAR *)wpan->previewAttr,
                      wpan->rho,wpan->rve,
                      wpan->fx1,wpan->fy1,wpan->fx2,wpan->fy2) ;
      DirtyDancing=(wpan->WinNum)-1 ;
      waux=(wpan->WinList)[DirtyDancing] ;
      while ((DirtyDancing!=0) && (waux->hiddenOn))
      {
        DirtyDancing-- ;
        waux=(wpan->WinList)[DirtyDancing] ;
      }
      V_TERM_cgotoxy(waux->x1+waux->posx,waux->y1+waux->posy) ;
      return ok ;
    }

    T_BOOL  L_WTERM_FlushAll                  ( t_tscreen wpan ) 
    {
      Touch(wpan,(wpan->WinList)[0]) ;
      V_TERM_FreeObuff() ;
      return L_WTERM_Flush(wpan) ;
    }

    T_BOOL  L_WTERM_Init                      ( t_tscreen wpan )
    {
      t_twin   waux ;
      T_INT    fulltotal ;
      void    *ret ;

      ret = V_TERM_get_profile() ;
      NULL_RET_FALSE(ret) ;
      if (wpan->inicialized == FALSE)
      {
        wpan->rho=V_TERM_cmaxX() ;
        wpan->rve=V_TERM_cmaxY() ;
        fulltotal=wpan->rho*wpan->rve ;
        wpan->previewBuff=X_ALLOC_Malloc(fulltotal) ;
        NULL_RET_FALSE(wpan->previewBuff) ;
        wpan->previewAttr=X_ALLOC_Malloc(fulltotal) ;
        if (!wpan->previewAttr)
           {
             X_ALLOC_Free((void **)&(wpan->previewBuff)) ;
             return FALSE ;
           }
        (wpan->WinList)=NULL ;
        (wpan->WinNum)=1 ; /* enganyo a AddList */
        if ( L_WTERM_Creat(wpan,0,0,wpan->rho+1,wpan->rve+1) == NULL )
           {
             X_ALLOC_Free((void **)&((wpan->WinList))) ;
             X_ALLOC_Free((void **)&(wpan->previewBuff)) ;
             X_ALLOC_Free((void **)&(wpan->previewAttr)) ;
             return FALSE ;
           }
        X_ALLOC_MemSet(wpan->previewBuff,v_chclear,fulltotal) ;
        X_ALLOC_MemSet(wpan->previewAttr,(c_Black << 4 ) | c_White,fulltotal) ;
        wpan->inicialized=TRUE ;
        wpan->fx1=1 ;
        wpan->fy1=1 ;
        wpan->fx1=wpan->fy1=1 ;
        wpan->fx2=wpan->rho ;
        wpan->fy2=wpan->rve ;
        MainTWin=(wpan->WinList)[0] ;   /* pantalla principal */
      }
      else
      {
        T_BOOL ok ;
        T_CHAR *paux ;
        T_INT i, oldsize ;

        fulltotal=(V_TERM_cmaxX()*V_TERM_cmaxY()) ;
        oldsize=wpan->rho*wpan->rve ;
        if (oldsize==fulltotal)
            return TRUE ;
        waux=(wpan->WinList)[0] ;
        ok=L_WTERM_Move(wpan,waux,0,0,V_TERM_cmaxX()+1,V_TERM_cmaxY()+1) ;
        FALSE_RET_TRUE(ok) ;
        paux=(T_CHAR *)X_ALLOC_Realloc(wpan->previewBuff,fulltotal) ;
        if (!paux)
           {
             L_WTERM_Move(wpan,waux,0,0,wpan->rho+1,wpan->rve+1) ;
             return FALSE ;
           }
        wpan->previewBuff=paux ;
        paux=(T_CHAR *)X_ALLOC_Realloc(wpan->previewAttr,fulltotal) ;
        if (!paux)
           {
             wpan->previewBuff=X_ALLOC_Realloc(wpan->previewBuff,wpan->rho*wpan->rve) ;
             L_WTERM_Move(wpan,waux,0,0,wpan->rho+1,wpan->rve+1) ;
             return FALSE ;
           }
        wpan->previewAttr=(t_attrib *)paux ;
        if (oldsize < fulltotal)
           {
             X_ALLOC_MemSet(wpan->previewBuff+oldsize,
                         v_chclear,(fulltotal-oldsize)) ;
             X_ALLOC_MemSet(wpan->previewAttr+oldsize,
                         (c_Black << 4 ) | c_White,(fulltotal-oldsize)) ;
           }
        wpan->rho=V_TERM_cmaxX() ;
        wpan->rve=V_TERM_cmaxY() ;
        for(i=1; i<(wpan->WinNum); i++)
        {
          (wpan->WinList)[i]->dirty=TRUE ;
        }
        wpan->fx1=wpan->fy1=1 ;
        wpan->fx2=wpan->rho ;
        wpan->fy2=wpan->rve ;
        MainTWin=(wpan->WinList)[0] ;   /* pantalla principal */
      }
      return TRUE ;
    }

    T_BOOL  L_WTERM_GotoXY      (t_tscreen wpan, t_twin W,T_INT x,T_INT y)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      (W)->posx=(x>((W)->x2-(W)->x1-1)) ? ((W)->x2-(W)->x1-1) : x ;
      (W)->posy=(y>((W)->y2-(W)->y1-1)) ? ((W)->y2-(W)->y1-1) : y ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_WhereXY     (t_tscreen wpan, t_twin W,T_INT *x,T_INT *y)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      (*x) = (W)->posx ;
      (*y) = (W)->posy ;
      return TRUE ;
    }

    t_twin L_WTERM_Which       (t_tscreen wpan, T_INT x, T_INT y)
    {
      T_INT i ;
      t_twin waux ;

      for (i=(wpan->WinNum)-1 ; i>=0 ; i--)
      {
        waux=(wpan->WinList)[i] ;
        if (Inside(waux,x,y))
            return waux ;
      }
      return NULL ;   /* No debe llegar, la win 0 tiene todo */
    }

    T_BOOL  L_WTERM_Coordenate  (t_tscreen wpan, t_twin W,T_INT *x1,T_INT *y1,T_INT *x2,T_INT *y2)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      *x1=(W)->x1 ;
      *y1=(W)->y1 ;
      *x2=(W)->x2 ;
      *y2=(W)->y2 ;
      return TRUE ;
    }

    T_BOOL    L_WTERM_Move          (t_tscreen wpan, t_twin W,
                                     T_INT x1,T_INT y1, T_INT x2, T_INT y2)
    {
      T_INT oldsize,newsize,upbytes,newupline,newdownline,restobytes,
          offset,newtotalsize,oldtotalsize ;

      if (GoodCoor(x1,y1,x2,y2) == FALSE)
           return FALSE ;
      if (L_WTERM_Hidden(wpan,W,TRUE) == FALSE)
           return FALSE ;
      if (!(W)->keep)
         {
           newsize=(y2-y1-1)*(x2-x1-1) ;
           oldsize=((W)->y2-(W)->y1-1)*((W)->x2-(W)->x1-1) ;
           if (oldsize<newsize)
              { /* bigger */
                L_BUFFW_AddBytesToBuffEnd(&(W)->forebuff,oldsize,
                                          newsize,v_chclear) ;
              }
           if (oldsize>newsize)
              { /* smaller */
                (W)->forebuff=X_ALLOC_Realloc((W)->forebuff,newsize) ;
              }
         }
         else {
                upbytes=(W)->uplines*((W)->x2-(W)->x1-1) ;
                newupline=upbytes / (x2-x1-1) ;
                restobytes=(upbytes % (x2-x1-1)) +
                           ((W)->x2-(W)->x1-1)*((W)->y2-(W)->y1-1+(W)->downlines) ;
                newdownline=(restobytes / (x2-x1-1))-(y2-y1-1)+
                             ((restobytes % (x2-x1-1)) > 1) ;
                if (newdownline < 0)
                    newdownline=0 ;
                newtotalsize=(x2-x1-1)*(y2-y1-1+newupline+newdownline) ;
                oldtotalsize=((W)->x2-(W)->x1-1)*((W)->y2-(W)->y1-1+
                              (W)->uplines+(W)->downlines) ;
                L_BUFFW_AddBytesToBuffEnd(&(W)->forebuff,oldtotalsize,
                                         newtotalsize,v_chclear) ;
                (W)->uplines=newupline ;
                (W)->downlines=newdownline ;
              }
      offset=((W)->posy-1)*((W)->x2-(W)->x1-1)+((W)->posx-1) ;
      (W)->posy=(offset / (x2-x1-1))+1 ;
      (W)->posx=(offset % (x2-x1-1))+1 ;
      if ((W)->posy > (y2-y1-1))
         {
           (W)->posy=y2-y1-1 ;
           (W)->posx=x2-x1-1 ;
         }
      (W)->x1=x1 ;
      (W)->y1=y1 ;
      (W)->x2=x2 ;
      (W)->y2=y2 ;
      L_WTERM_Hidden(wpan,W,FALSE) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_GetColours  (t_tscreen wpan, t_twin W,t_txt_colores *wback,
                             t_txt_colores *wfore,t_txt_colores *fback,
                             t_txt_colores *ffore)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      *wback=(W)->wback ;
      *wfore=(W)->wfore ;
      *fback=(W)->fback ;
      *ffore=(W)->ffore ;
      return TRUE ;
    }

    void  L_WTERM_SetDefaultColour (t_txt_colores *wback,t_txt_colores *wfore,
                                  t_txt_colores *fback,t_txt_colores *ffore)
    {
      extern t_TermState VS ; /* esta en V_TERM.H */

      if (VS.ncolores<=2)
          {
            (*wback)=c_Black ;
            (*wfore)=c_White ;
            (*fback)=c_Black ;
            (*ffore)=c_LightGray ;
          } else {
                   #if defined(__COOL__)
                      (*wback)=c_Blue ;
                      (*wfore)=c_LightGray ;
                      (*fback)=c_Blue ;
                      (*ffore)=c_Red ;
                   #else
                      (*wback)=c_Black ;
                      (*wfore)=c_LightGray ;
                      (*fback)=c_Black ;
                      (*ffore)=c_Red ;
                   #endif
                 }
    }

    T_BOOL  L_WTERM_SetColours  (t_tscreen wpan, t_twin W,t_txt_colores wback,
                             t_txt_colores wfore,t_txt_colores fback,
                             t_txt_colores ffore)
    {
      if (!GoodColours(wback,wfore,fback,ffore))
         {
           L_DEBUG_MSG_Write(ERROR,FALSE,"incorrect colores.\n") ;
           return FALSE ;
         }
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      (W)->wback=wback ;
      (W)->wfore=wfore ;
      (W)->fback=fback ;
      (W)->ffore=ffore ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_GetFrame    (t_tscreen wpan, t_twin W,T_BOOL *FrameOn,T_CHAR Frame[])
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      *FrameOn=(W)->frameOn ;
      X_ALLOC_MemMove(Frame,(W)->frame,8) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_SetFrame    (t_tscreen wpan, t_twin W,T_BOOL FrameOn, T_CHAR Frame[])
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      if (FrameOn)
         {
           X_ALLOC_MemMove((W)->frame,Frame,8) ;
           (W)->frameOn=TRUE ;
         }
         else {
                X_ALLOC_MemSet((W)->frame,0,8) ;
                (W)->frameOn=FALSE ;
              }
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_Hidden      (t_tscreen wpan, t_twin W, T_BOOL mode)
    {
      T_INT i ;
      t_twin waux ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      if ((W)->hiddenOn==mode)
          return TRUE ;
      Touch(wpan,W) ;
      if (mode == FALSE)
         {
           (W)->hiddenOn=FALSE ;
           return TRUE ;
         }
      if (MainTWin==W)
         {
           FillIntoBuff(wpan->previewBuff,1,1,((W)->x2-1),((W)->y2-1),
                        wpan->rho,wpan->rve,v_chclear) ;
         }
         else {
                FillIntoBuff(wpan->previewBuff,(W)->x1,(W)->y1,((W)->x2-(W)->x1+1),
                             ((W)->y2-(W)->y1+1),wpan->rho,wpan->rve,v_chclear) ;
              }
      (W)->hiddenOn=TRUE ;
      for(i=((W)->orden-1);i>=0;i--)
         {
           waux=(wpan->WinList)[i] ;
           if ( (Inside(waux,(W)->x1,(W)->y1) || Inside(waux,(W)->x1,(W)->y2) ||
                 Inside(waux,(W)->x2,(W)->y1) || Inside(waux,(W)->x2,(W)->y2))
                                          ||
                             Inside(W,waux->x1,waux->y1) )
              {
                 /* con la ultima comprobamos que
                    waux no este incluida en W */
                Touch(wpan,waux) ;
              }
         }
      return TRUE ;
    }

    T_BOOL    L_WTERM_WriteLn                 (t_tscreen wpan, t_twin W)
    {
      T_INT tall ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      tall=((W)->y2-(W)->y1-1) ; /* los 'scrolls' hacen un touch! */
      if (((W)->posy == tall+1) && ((W)->posx==0))
         { /* un WriteLn pendiente !!! */
           (W)->posy++ ;
           (W)->posx=1 ;
           L_WTERM_ScrollUp(wpan,W,2) ;
           return TRUE ;
         }
      (W)->posy++ ;
      (W)->posx=1 ;
      if ((W)->posy > tall)
         {
           L_WTERM_ScrollUp(wpan,W,1) ;
           (W)->posy=tall ;
         }
      return TRUE ;
    }

    T_BOOL L_WTERM_Vprintf (t_tscreen wpan, t_twin W, T_CHAR *format, va_list arg)
    {
      T_CHAR *str ;
      T_INT lenstr, si, oldsi ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      NULL_RET_TRUE(format) ;
      str       = X_STRING_Dvsprintf(format,arg) ;
      NULL_RET_FALSE(str) ;
      lenstr = X_STRING_StrLen(str) ;
      oldsi     = 0 ;
      for(si=0;si<=lenstr;si++)
      {
        switch(str[si])
        {
          case '\r' : WriteByte(wpan,W,&(str[oldsi]),si-oldsi) ;
                      if (str[si+1]=='\n')
                               si++ ;
                          else (W)->posx=1 ;
                      oldsi=si + 1 ;
                      break ;
          case '\n' : WriteByte(wpan,W,&(str[oldsi]),si-oldsi) ;
                      L_WTERM_WriteLn(wpan,W) ;
                      oldsi=si+1 ;
                      break ;
          case '\t' : WriteByte(wpan,W,&(str[oldsi]),si-oldsi) ;
                      oldsi=si+1 ;
                      WriteByte(wpan,W,c_TABHITS,strlen(c_TABHITS)) ;
                      break ;
        }
      }
      WriteByte(wpan,W,&(str[oldsi]),lenstr-oldsi) ;
      X_ALLOC_Free((void **)&str) ;
      return TRUE ;
    }

    T_BOOL L_WTERM_Printf (t_tscreen wpan, t_twin W, T_CHAR *format, ...)
    {
      T_BOOL  ok ;
      va_list arg ;

      va_start(arg,format) ;
      ok = L_WTERM_Vprintf(wpan,W,format,arg) ;
      va_end(arg) ;
      return ok ;
    }

    T_BOOL  L_WTERM_ScrollUp    (t_tscreen wpan, t_twin W, T_INT numero)
    {
      T_INT width,tall ;

      if (numero<=0)
          return TRUE ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=((W)->x2-(W)->x1-1) ;
      tall=((W)->y2-(W)->y1-1) ;
      if ((W)->keep==FALSE)
         {
           numero=MIN(numero,tall) ;
           ShiftUpLines((W)->forebuff,tall,numero,width) ;
         }
         else {
                T_INT lines ;

                if ((W)->downlines >= numero)
                   {
                     (W)->downlines-=numero ;
                     (W)->uplines+=numero ;
                   }
                   else {
                          T_BOOL ok ;
                          T_INT olddownlines ;

                          olddownlines=(W)->downlines ;
                          (W)->uplines+=(W)->downlines ;
                          numero-=(W)->downlines ;
                          (W)->downlines=0 ;
                          lines=(W)->uplines+tall ;
                          ok=L_BUFFW_AddBytesToBuffEnd(&(W)->forebuff,
                                                      lines*width,
                                                      (lines+numero)*width,
                                                      v_chclear) ;
                          if (ok == FALSE)
                             {
                               (W)->downlines+=olddownlines ;
                               (W)->uplines-=olddownlines ;
                               return FALSE ;
                             }
                          (W)->uplines+=numero ;
                        }
              }
      (W)->posy-=numero ;
      if ((W)->posy <= 0)
          (W)->posy=1 ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_ScrollDown  (t_tscreen wpan, t_twin W, T_INT numero)
    {
      T_INT width,tall ;

      if (numero<=0)
          return TRUE ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=((W)->x2-(W)->x1-1) ;
      tall=((W)->y2-(W)->y1-1) ;
      if (!(W)->keep)
         {
           numero=MIN(numero,tall) ;
           ShiftDownLines((W)->forebuff,tall,numero,width) ;
         }
         else {
                T_INT lines ;

                if ((W)->uplines >= numero)
                   {
                     (W)->uplines-=numero ;
                     (W)->downlines+=numero ;
                   }
                   else {
                          T_BOOL ok ;
                          T_INT olduplines ;

                          olduplines=(W)->uplines ;
                          (W)->downlines+=(W)->uplines ;
                          numero-=(W)->uplines ;
                          (W)->uplines=0 ;
                          lines=(W)->downlines+tall ;
                          ok=L_BUFFW_AddBytesToBuffBegin(&(W)->forebuff,
                                                         lines*width,
                                                         (lines+numero)*width,
                                                         v_chclear) ;
                          if (ok == FALSE)
                             { /* no dejar inestables resultados ! */
                               (W)->uplines+=olduplines ;
                               (W)->downlines-=olduplines ;
                               return FALSE ;
                             }
                          (W)->downlines+=numero ;
                        }
              }
      (W)->posy+=numero ;
      if ((W)->posy > tall)
          (W)->posy=tall ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_ScrollLeft  (t_tscreen wpan, t_twin W, T_INT numero)
    {
      T_INT j,downy,width,tall ;
      T_CHAR *pch ;

      if (numero<=0)
          return TRUE ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=((W)->x2-(W)->x1-1) ;
      tall=((W)->y2-(W)->y1-1) ;
      downy=numero / width ;
      L_WTERM_ScrollDown(wpan,W,downy) ;
      downy=numero % width ;
      pch=(W)->forebuff+downy ;
      X_ALLOC_MemMove(pch,(W)->forebuff,(tall*width-downy)) ;
      for (j=0;j<tall;j++)
      {
        X_ALLOC_MemSet((W)->forebuff+j*width,v_chclear,downy) ;
      }
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_ScrollRight (t_tscreen wpan, t_twin W, T_INT numero)
    {
      T_INT j,uppy,width,tall ;
      T_CHAR *pch ;

      if (numero<=0)
          return TRUE ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=((W)->x2-(W)->x1-1) ;
      tall=((W)->y2-(W)->y1-1) ;
      uppy=numero / width ;
      L_WTERM_ScrollUp(wpan,W,uppy) ;
      uppy=numero % width ;
      pch=(W)->forebuff+uppy ;
      X_ALLOC_MemMove((W)->forebuff,pch,(tall*width-uppy)) ;
      for (j=0;j<tall;j++)
      {
        X_ALLOC_MemSet((W)->forebuff+width-uppy+j*width,v_chclear,uppy) ;
      }
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_Shadow      (t_tscreen wpan, t_twin W, T_BOOL mode)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      (W)->shadow = mode ;
      return (W)->shadow ;
    }

    T_BOOL  L_WTERM_Keep        (t_tscreen wpan, t_twin W, T_BOOL mode)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      (W)->keep = mode ;
      return (W)->keep ;
    }

    T_BOOL  L_WTERM_SetKeepTitle (t_tscreen wpan, t_twin W, T_CHAR *ktitle)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      X_ALLOC_MemMove((W)->keeptitle,ktitle,4) ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_GetKeepTitle (t_tscreen wpan, t_twin W, T_CHAR **ktitle)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      (*ktitle)=(W)->keeptitle ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_KeepAjust   (t_tscreen wpan, t_twin W)
    {
      T_CHAR *pch ;
      T_INT width,tall ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=((W)->x2-(W)->x1-1) ;
      tall=((W)->y2-(W)->y1-1) ;
      pch=(W)->forebuff+(W)->uplines*width ;
      X_ALLOC_MemMove((W)->forebuff,pch,tall*width) ;
      (W)->forebuff=X_ALLOC_Realloc((W)->forebuff,tall*width) ;
      (W)->uplines=(W)->downlines=0 ;
      return TRUE ;
    }

    t_twin L_WTERM_DupWin      (t_tscreen wpan, t_twin W, T_INT mode)
    {
      t_twin waux ;
      T_INT ticket,totalbytes ;

      if (!GoodDupMode(mode))
          return NULL ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      waux=X_ALLOC_MemDup(W,c_TWIN) ;
      NULL_RET_NULL(waux) ;
      ticket=AddList(wpan,waux) ;
      if (!ticket)
         {
           X_ALLOC_Free((void **)&waux) ;
           return NULL ;
         }
      waux->orden=ticket ;
      if (mode==c_SHARE)
         return waux ;
      totalbytes=((W)->x2-(W)->x1-1)*((W)->y2-(W)->y1-1+(W)->uplines+(W)->downlines) ;
      waux->forebuff=(T_CHAR *)X_ALLOC_MemDup((W)->forebuff,totalbytes) ;
      if (!(waux->forebuff))
         {
           RmList(wpan,waux->orden) ;
           X_ALLOC_Free((void **)&waux) ;
           return NULL ;
         }
       (W)->dinamic = TRUE ;
       return waux ;
    }

    T_BOOL  L_WTERM_PutOnTop    (t_tscreen wpan, t_twin W)
    {
      if (W==MainTWin)
      {
        L_DEBUG_MSG_Write(WARNING,FALSE,"you try putontop main win\n") ;
        return FALSE ;
      }
      if ((wpan->WinNum) == 0)
          return FALSE ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      return XchInList(wpan,(wpan->WinNum)-1,(W)->orden) ;
    }

    T_BOOL  L_WTERM_PutOnBeneath (t_tscreen wpan, t_twin W)
    {
      if (W==MainTWin)
      {
        L_DEBUG_MSG_Write(WARNING,FALSE,"you try putontop main win\n") ;
        return FALSE ;
      }
      if ((wpan->WinNum) == 0)
          return FALSE ;
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      return XchInList(wpan,(W)->orden,1) ;
    }

    T_BOOL  L_WTERM_Clear       (t_tscreen wpan, t_twin W)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      X_ALLOC_MemSet( (W)->forebuff,v_chclear,
                 ((W)->uplines+(W)->downlines+(W)->y2-(W)->y1-1)*((W)->x2-(W)->x1-1)) ;
      (W)->posy=(W)->posx=1 ;
      (W)->downlines+=(W)->uplines ;
      (W)->uplines=0 ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_ClearRestOfLine  (t_tscreen wpan, t_twin W)
    {
      T_INT width ;
      T_CHAR *paux ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=((W)->x2-(W)->x1-1) ;
      paux=(W)->forebuff+((W)->uplines+(W)->posy-1)*width+(W)->posx-1 ;
      X_ALLOC_MemSet(paux,v_chclear,(width-(W)->posx+1)) ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL L_WTERM_GetTextWin (t_tscreen wpan, t_twin W, T_CHAR **ptxt, T_INT *bsize)
    {
      T_INT width ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      width=(W)->x2-(W)->x1-1 ;
      *bsize=((W)->uplines+(W)->downlines+(W)->y2-(W)->y1-1)*width ;
      *ptxt=(W)->forebuff ;
      return TRUE ;
    }

    T_BOOL L_WTERM_SetTextWin (t_tscreen wpan, t_twin W, T_CHAR *ptxt, T_INT bsize)
    {
      T_INT width, tall, blines, needbytes ;
      T_BOOL ok ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      if (bsize == 0)
          return L_WTERM_Clear(wpan,W) ;
      width=(W)->x2-(W)->x1-1 ;
      tall=(W)->y2-(W)->y1-1 ;
      X_ALLOC_Free((void **)&((W)->forebuff)) ;
      (W)->forebuff=ptxt ;
      blines=((bsize / width) + ((bsize % width) > 0)) ;
      if ( (!(blines / tall)) || (blines % width) )
         {
           needbytes=MAX((tall-(bsize / width)),1)*width - (bsize % width) ;
           ok=L_BUFFW_AddBytesToBuffEnd(&((W)->forebuff),bsize,
                                       bsize+needbytes,v_chclear) ;
           if (ok==FALSE)
               return FALSE ;
           (W)->downlines=((bsize+needbytes) / width)-tall ;
           if ((W)->downlines)
              {
                (W)->keep=TRUE ;
              }
         }
      (W)->uplines=0 ;
      (W)->posx=(W)->posy=1 ;
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL L_WTERM_GetTitle (t_tscreen wpan, t_twin W, T_INT *TitleMode, T_CHAR **Title)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      *Title=(W)->title ;
      *TitleMode=(W)->titlemode ;
      return TRUE ;
    }

    T_BOOL L_WTERM_SetTitle      (t_tscreen wpan, 
                                  t_twin W, 
                                  T_INT TitleMode, 
                                  T_CHAR *Title)
    {
      T_INT lenstr,width,lentitle ;

      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      if (!GoodTitleMode(TitleMode))
          return FALSE ;
      if (TitleMode!=c_NO_TITLE)
         {
           if ((W)->title)
              { 
                L_DEBUG_MSG_Write(ERROR,FALSE,
                                  "Win Allready have title, use c_NO_TITLE first.!\n") ;
              }
           lenstr=strlen(Title) ;
           width=(W)->x2-(W)->x1-1 ;
           lentitle=MIN(lenstr,width) ;
           (W)->title=(T_CHAR *)X_ALLOC_Malloc(lentitle+1) ;
           NULL_RET_FALSE((W)->title) ;
           X_ALLOC_MemMove((W)->title,Title,lentitle+1) ;
           (W)->title[lentitle]='\0' ;
           (W)->titlemode=TitleMode ;
           AjustTitle(W,lentitle) ;
         } else {
                  (W)->titlemode=TitleMode ;
                  X_ALLOC_Free((void **)&((W)->title)) ;
                  (W)->title=NULL ;
                }
      Touch(wpan,W) ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_GetInfo  (t_tscreen wpan, 
                              t_twin W, 
                              T_INT *uplines, 
                              T_INT *downlines)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      *uplines=(W)->uplines ;
      *downlines=(W)->downlines ;
      return TRUE ;
    }

    T_BOOL  L_WTERM_Touch  (t_tscreen wpan, 
                            t_twin W)
    {
      if (L_WTERM_Exist(wpan,W) == FALSE)
          return FALSE ;
      Touch(wpan,W) ;
      return TRUE ;
    }


/* ....................................................................... */
