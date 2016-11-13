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

      #include "SpiderBot/l_sbotmnu.h"


   /* ... Functions / Funciones ......................................... */

      T_BOOL   L_SBOTMNU_setupOptions ( IN    int           *chosen,
                                        INOUT t_wppOptions  *spiderOpt )
      {
        T_CHAR *value ;

        NULL__SET_ERROR__RET_FALSE(chosen) ;
        NULL__SET_ERROR__RET_FALSE(spiderOpt) ;
        switch(chosen[0])
        {
          case 1 : /* url... */
               value = L_EDTBOX_WriteString
                       (
                         1,5,80,7,
                         " -url- ",
                         4*1024
                       ) ;
               L_WPP_OPT_DupHref(spiderOpt,value) ;
               X_ALLOC_Free((void **)&value) ;
               break ;
          case 2 : /* resume... */
               value = L_EDTBOX_WriteString
                       (
                         1,5,80,7,
                         " -resume- ",
                         4*1024
                       );
               L_WPP_OPT_DupRecoverFile(spiderOpt,value) ;
               X_ALLOC_Free((void **)&value) ;
               break ;
          case 3 : /* maxbytes... */
               value = L_EDTBOX_WriteString
                      (
                        1,5,80,7,
                        " -maxbytes- ",
                        80
                      );
               spiderOpt->maxBytes = atoi(value) ;
               X_ALLOC_Free((void **)&value) ;
               break ;
          case 4 : /* maxurls... */
               value = L_EDTBOX_WriteString
                      (
                        1,5,80,7,
                        " -maxurls- ",
                        80
                      );
               spiderOpt->maxUrls = atoi(value) ;
               X_ALLOC_Free((void **)&value) ;
               break ;
          case 5 : /* proxy... */
               value = L_EDTBOX_WriteString
                      (
                        1,5,80,7,
                        " -proxy- ",
                        4*1024
                      );
               L_WPP_OPT_DupProxy(spiderOpt,value) ;
               X_ALLOC_Free((void **)&value) ;
               break ;
          case 6 : /* ident... */
               value = L_EDTBOX_WritePasswd
                      (
                        1,5,80,7,
                        " -ident- "
                      );
               L_WPP_OPT_DupIdentification(spiderOpt,value) ;
               X_ALLOC_Free((void **)&value) ;
               break ;
          default : ;
        }
        return TRUE ;
      }

      T_BOOL   L_SBOTMNU_setupFlags   ( IN    int           *chosen,
                                        INOUT t_wppOptions  *spiderOpt )
      {
        NULL__SET_ERROR__RET_FALSE(chosen) ;
        NULL__SET_ERROR__RET_FALSE(spiderOpt) ;
        switch(chosen[0])
        {
          case 1 : /* samemachine... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->fromSamePath_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->fromSamePath_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 2 : /* makequery... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->makeQuery_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->makeQuery_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 3 : /* rentry... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->rentry_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->rentry_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 4 : /* skipel... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->skipEL_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->skipEL_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 5 : /* detectHttp... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->detectHttp_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->detectHttp_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 6 : /* onlyHttp... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->onlyHttp_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->onlyHttp_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 7 : /* makeRelative... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->makeRelative_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->makeRelative_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          case 8 : /* skipBin... */
               switch(chosen[1])
               {
                 case  1 : /* on */
                           spiderOpt->skipBin_f = ON ;
                           break ;
                 case  2 : /* off */
                           spiderOpt->skipBin_f = OFF ;
                           break ;
                 default : ;
               }
               break ;
          default : ;
        }
        return TRUE ;
      }

      /* ... Menu ... */
      t_menu   L_SBOTMNU_OpenPresent  ( INOUT   t_DiNode *g, 
                                        IN      T_INT     x,
                                        IN      T_INT     y )
      {
        t_menu mnu ;

        mnu=L_MENU_Open(g,x,y) ;
        return mnu ;
      }

      T_INT   *L_SBOTMNU_Select       ( INOUT   t_menu   *mnu )
      {
        T_INT  key, state, *options ;

        NULL_RET_NULL(mnu) ;
        state = c_KEYPROC ;
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
            default : state=L_MENU_KeyProcesing(mnu,key) ;
          }
        } while (state==c_KEYPROC) ;
        options=L_MENU_GetOptionsNumber((*mnu)) ;
        if (state==c_CLOSE)
            options[0]=0 ;
        return options ;
      }

      T_BOOL   L_SBOTMNU_ClosePresent ( INOUT   t_menu   *mnu )
      {
        L_MENU_Close(mnu) ;
        L_WIN_Flush() ;
        return TRUE ;
      }


   /* ................................................................... */

