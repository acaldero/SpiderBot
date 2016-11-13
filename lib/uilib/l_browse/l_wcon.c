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

      #include "uilib/l_browse/l_wcon.h"


   /* ... Glob var / Var. globales ......................................... */
  
       t_win   g_WConReportWin, g_WConVersionWin ;
       T_BOOL  v_SeeTrace = TRUE ;
  
  
   /*... Functions / Funciones ..............................................*/
  
       void VersionsAtConsole ( const T_CHAR *compo, 
				const T_CHAR *ver )
       {     
         L_WIN_WriteStr(g_WConVersionWin,(T_CHAR *)ver) ;
         L_WIN_WriteStr(g_WConVersionWin," <-> ") ;
         L_WIN_WriteStr(g_WConVersionWin,(T_CHAR *)compo) ;
         L_WIN_WriteLn(g_WConVersionWin) ;
         if (v_SeeTrace==TRUE)
             L_WIN_Flush() ;
       }       
           
       T_INT ReportAtConsole ( T_CHAR  *fto,
			       va_list  argv )
       {
         T_CHAR *pch ;
	 T_INT   pchlen ;

         pch = X_STRING_Dvsprintf(fto,argv) ;
	 pchlen = X_STRING_StrLen(pch) ;
         L_WIN_WriteStr(g_WConReportWin,pch) ;   
         L_WIN_WriteLn(g_WConReportWin) ;
         X_ALLOC_Free((void **)&pch) ;
         if (v_SeeTrace==TRUE)
             L_WIN_Flush() ;
         return pchlen ;
       }
  
       void L_WCON_On ( void )
       {
           g_WConReportWin=L_WIN_Open(c_WCON_MSGSX1,c_WCON_MSGSY1,
                                      c_WCON_MSGSX2,c_WCON_MSGSY2) ;
           g_WConVersionWin=L_WIN_Open(c_WCON_VERX1,c_WCON_VERY1,
                                       c_WCON_VERX2,c_WCON_VERY2) ;
           if ( (g_WConReportWin) && (g_WConVersionWin) )
              {
                L_WIN_SetFrame(g_WConReportWin,TRUE,c_SIMPLE_FRAME1) ;
                L_WIN_SetFrame(g_WConVersionWin,TRUE,c_SIMPLE_FRAME1) ;
                L_WIN_SetTitle(g_WConReportWin,c_RIGHTUP_TITLE,c_WCON_ERRTITLE) ;
                L_WIN_SetTitle(g_WConVersionWin,c_RIGHTUP_TITLE,c_WCON_VERTITLE) ;
                #if defined(__COOL__)
                   L_WIN_SetColours(g_WConReportWin,c_Blue,c_LightGray,
                                                    c_Blue,c_Cyan) ;
                   L_WIN_SetColours(g_WConVersionWin,c_Blue,c_LightGray,
                                                     c_Blue,c_Cyan) ;
                #endif
		L_DEBUG_MSG_PrintMsg = (T_INT (*)(const T_CHAR *,va_list))ReportAtConsole ;
                v_SeeTrace=TRUE ;
              }
       }
  
       void L_WCON_Off ( void )
       {
	   L_DEBUG_MSG_PrintMsg = NULL ;
           L_WIN_Close(g_WConReportWin) ;
           L_WIN_Close(g_WConVersionWin) ;
           if (v_SeeTrace==TRUE)
              {
                L_WIN_Flush() ;
                v_SeeTrace=FALSE ;
              }
       }
  
       void L_WCON_Hidden ( void )
       {
           L_WIN_Hidden(g_WConReportWin) ;
           L_WIN_Hidden(g_WConVersionWin) ;
           if (v_SeeTrace==TRUE)
              {
                L_WIN_Flush() ;
                v_SeeTrace=FALSE ;
              }
       }
  
       void L_WCON_UnHidden ( void )
       {
           static T_INT rotwin=0 ;
  
           L_WIN_UnHidden(g_WConReportWin) ;
           L_WIN_UnHidden(g_WConVersionWin) ;
           switch (rotwin)
           {
             case 0 : L_WIN_PutOnTop(g_WConReportWin) ;
                      break ;
             case 1 : L_WIN_PutOnTop(g_WConVersionWin) ;
                      break ;
             default : rotwin=0 ;
           }
           rotwin= (rotwin==1) ? 0 : rotwin+1 ;
           v_SeeTrace=TRUE ;
           L_WIN_Flush() ;
       }
  
  
   /* ..................................................................... */
  
