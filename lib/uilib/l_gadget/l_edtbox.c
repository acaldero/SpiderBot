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

      #include "uilib/l_gadget/l_edtbox.h"


   /* ... Functions / Funciones ......................................... */

     T_CHAR *L_EDTBOX_WriteString    ( IN    T_INT    x1,
                                       IN    T_INT    y1,
				       IN    T_INT    x2,
				       IN    T_INT    y2,
				       IN    T_CHAR  *title,
				       IN    T_INT    maxStringLeng )
     {
        T_CHAR  *inbuff ;
        T_INT    i, ch ;
        t_win    wwin ;

        inbuff = X_ALLOC_AllocAndSet(maxStringLeng,0) ;
        NULL_RET_NULL(inbuff) ;
          /* ... open windows */
        wwin = L_WIN_Open(x1,y1,x2,y2) ;
        L_WIN_SetTitle(wwin,c_CENTERUP_TITLE,title) ;
	if (wwin == NULL)
	   {
	     X_ALLOC_Free((void **)&inbuff) ;
	     return NULL ;
	   }
        L_WIN_SetFrame(wwin,TRUE,c_SIMPLE_FRAME) ;
        L_WIN_UnHidden(wwin) ;
        L_WIN_Flush() ;
          /* ... get data */
        i = 0 ;
        do
        {
          ch = V_KEYMAP_getkey() ;
          if (ch == '\\')
             {
               i++ ;
               inbuff[i-1] = inbuff[i] = ch ;
             }
          if (ch == c_DEL)
             {
               if (i > 0)
                   i-- ;
               inbuff[i] = '\0' ;
             } else {
                      if (isprint((T_CHAR)ch) != 0)
                         {
                           inbuff[i] = (T_CHAR)ch ;
                           i++ ;
                         }
                    }
          L_WIN_Clear(wwin) ;
          L_WIN_WriteStr(wwin,inbuff) ;
          L_WIN_Flush() ;
        } while ( (ch != c_ENTER) && (i < maxStringLeng) ) ;
        inbuff[i] = '\0' ;
          /* ... close and return */
        L_WIN_Close(wwin) ;
        return inbuff ;
     }

     T_CHAR *L_EDTBOX_WritePasswd    ( IN    T_INT    x1,
                                       IN    T_INT    y1,
				       IN    T_INT    x2,
				       IN    T_INT    y2,
				       IN    T_CHAR  *title )
     {
        T_CHAR  *inbuff ;
        t_win    wwin ;

        /* ... open windows */
        wwin = L_WIN_Open(x1,y1,x2,y2) ;
        NULL_RET_NULL(wwin) ;
        L_WIN_SetTitle(wwin,c_CENTERUP_TITLE,title) ;
        L_WIN_SetFrame(wwin,TRUE,c_SIMPLE_FRAME) ;
        L_WIN_UnHidden(wwin) ;
        L_WIN_Flush() ;

        /* ... get data */
        inbuff = getpass("login:pass -> ") ;
        inbuff = X_STRING_StrDup(inbuff) ;

        /* ... close and return */
        L_WIN_Close(wwin) ;
        return inbuff ;
     }


 /* ...................................................................... */

