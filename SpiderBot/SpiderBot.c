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

      #include "corelib/l_basic/c_basic.h"
      #include "corelib/l_file/x_print.h"
      #include "uilib/l_apps/l_info.h"
#if defined(__UILIB__)
      #include "corelib/l_debug/l_debug.h"
      #include "uilib/l_wterm/l_win.h"
      #include "uilib/l_wterm/v_keymap.h"
      #include "uilib/l_browse/l_htxt.h"
      #include "uilib/l_apps/l_uirc.h"
      #include "uilib/l_gadget/l_edtbox.h"
#endif
      #include "SpiderBot/c_spiderbot.h"
      #include "SpiderBot/l_sbotcl.h"
      #include "SpiderBot/l_sbotdl.h"
      #include "SpiderBot/l_sbotmsg.h"
      #include "SpiderBot/l_sbotmnu.h"


   /* ... Main .......................................................... */

      T_INT cl_main ( T_INT argc, T_CHAR *argv[] )
      {
        T_BOOL           ok ;
        t_wppOptions     spiderOpt ;


        setbuf(stdin,NULL) ;
        L_SBOTMSG_presentation() ;

        ok = L_SBOTCL_ParseCommandLine(&spiderOpt,argc,argv) ;
        if (ok == FALSE)
           {
             X_PRINT_printf(
                    "\n"
                    "    Please, use '-help' to know SpiderBot's options :\n"
                    "\n"
                    "       $SpiderBot -help"
                    "\n"
                    "\n"
                    "\n"
                    "\n") ;
             return TRUE ;
           }
        if (spiderOpt.help_f == ON)
           {
             ok = L_SBOTMSG_listOptions() ;
           }
        if (spiderOpt.help_f == OFF)
           {
             ok = L_SBOTOPT_activeWppOptToFile(&spiderOpt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_SBOTOPT_CheckValid(&spiderOpt) ;
             if (ok == FALSE)
                {
                  X_PRINT_printf("\n\n") ;
                  return TRUE ;
                }
             ok = L_SBOTDL_DownLoad(&spiderOpt) ;
           }
        X_PRINT_printf("\n") ;
        return ok ;
      }

      T_INT w_main ( T_INT argc, T_CHAR *argv[] )
      {
#if defined(__UILIB__)
        T_BOOL           ok, do_exit ;
        t_wppOptions     spiderOpt ;
        t_DiNode        *gHelp, *gMenu ;
        FILE            *fin ;


        /* ... load resources ... */
        gHelp = NULL ;
        fin   = L_UIRC_OpenFile(argv[0]) ;
        if (fin == NULL)
           {
             X_PRINT_printf("resorce file for %s is not readable...\n",
                            argv[0]) ;
           }
        if (setvbuf(fin,NULL,_IOFBF,16384))
            setvbuf(fin,NULL,_IOFBF,512) ;
        gMenu = L_UIRC_ReadMenu(fin) ;
        if (gMenu == NULL)
           {
             X_PRINT_printf("(1) resource file for %s is not valid...\n",
                            argv[0]) ;
           }
        gHelp = L_UIRC_ReadHtxt(fin) ;
        if (gHelp == NULL)
           {
             X_PRINT_printf("(2) resource file for %s is not valid...\n",
                            argv[0]) ;
           }
        fclose(fin) ;

        /* ... init text win system ... */
        if (L_WIN_Init()==FALSE)
            exit(TRUE) ;
        L_WIN_SetColours(MainWin,c_Black,c_LightGray,c_Black,c_Black) ;
        L_WIN_FlushAll() ;
        X_PRINT_setPrintWrapper((int (*)(const char *,va_list))L_INFO_wprintf) ;
        L_WCON_On() ;
        L_WCON_Hidden() ;

        /* ... say Hello ... */
        setbuf(stdin,NULL) ;
        L_SBOTMSG_presentation() ;

        ok = L_SBOTCL_ParseCommandLine(&spiderOpt,argc,argv) ;
        if (ok == TRUE)
           {
             if (spiderOpt.help_f == ON)
                {
                  ok = L_SBOTMSG_listOptions() ;
                }
     
             if (spiderOpt.help_f == OFF)
                {
                  ok = L_SBOTOPT_activeWppOptToFile(&spiderOpt) ;
                  if (ok == TRUE)
                      ok = L_SBOTOPT_CheckValid(&spiderOpt) ;
                  X_PRINT_printf("\n\n") ;
                  if (ok == TRUE)
                      ok = L_SBOTDL_DownLoad(&spiderOpt) ;
                }
           }
        if (ok == FALSE)
           {
             T_INT  *chosen ;
             t_menu  mnu ;

             chosen     = NULL ;
             do_exit    = FALSE ;
             spiderOpt.href           = NULL ;
             spiderOpt.proxy          = NULL ;
             spiderOpt.recoverFile    = NULL ;
             spiderOpt.identification = NULL ;
             L_SBOTOPT_MakeEmpty(&spiderOpt) ;
             mnu = L_SBOTMNU_OpenPresent(gMenu,7,22) ;
             do
             {
               chosen = L_SBOTMNU_Select(&mnu) ;
               if (chosen == NULL)
                  {
                    L_WIN_Printf(MainWin,"Insuficiente Memoria. Sorry!.") ;
                    L_WIN_Flush() ;
                    exit(1) ;
                  }
               switch(chosen[0])
               {
                 case 0 : /* exit */
                      do_exit=TRUE ;
                      break ;
                 case 1 : /* help */
                      ok = L_HTXT_Present(gHelp) ;
                      if (ok == FALSE)
                          ok = L_SBOTMSG_listOptions() ;
                      break ;
                 case 2 : /* SpiderBot */
                      switch(chosen[1])
                      {
                        case 1 : /* options */
                             ok = L_SBOTMNU_setupOptions(&(chosen[2]),
                                                         &spiderOpt) ;
                             break ;
                        case 2 : /* flag */
                             ok = L_SBOTMNU_setupFlags(&(chosen[2]),
                                                       &spiderOpt) ;
                             break ;
                        case 3 : /* download */
                             L_SBOTMNU_ClosePresent(&mnu) ;
                             ok = L_SBOTOPT_activeWppOptToFile(&spiderOpt) ;
                             if (ok == TRUE)
                                 ok = L_SBOTOPT_CheckValid(&spiderOpt) ;
                             if (ok == TRUE)
                                 ok = L_SBOTDL_DownLoad(&spiderOpt) ;
                             mnu = L_SBOTMNU_OpenPresent(gMenu,7,22) ;
                             break ;
                        default : ;
                      }
                      break ;
                 case 3 : /* exit */
                      do_exit=TRUE ;
                      break ;
                 default : ;
               }
               L_WIN_FlushAll() ;
               X_ALLOC_Free((void **)&chosen) ;

             } while (do_exit == FALSE) ;
             L_SBOTMNU_ClosePresent(&mnu) ;
           }

        X_PRINT_printf("\n") ;
        L_MENU_DestroyMenu(&gMenu) ;
        L_HTXT_DestroyHtxt(&gHelp) ;
        L_WIN_SetColours(MainWin,c_Black,c_LightGray,c_Black,c_Black) ;
        L_WIN_FlushAll() ;
        return ok ;
#else
        return FALSE ;
#endif
      }

      T_INT main ( T_INT argc, T_CHAR *argv[] )
      {
#if defined(__UILIB__)
        return w_main(argc,argv) ;
#else
        return cl_main(argc,argv) ;
#endif
      }


/* ...................................................................... */


