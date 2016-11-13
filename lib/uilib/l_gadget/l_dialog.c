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

      #include "uilib/l_gadget/l_dialog.h"


   /* ... Functions / Funciones ......................................... */

     T_CHAR *L_DIALOG_SelectString   ( IN t_DiNode *g )
     {
       t_htext htexto ;
       T_INT key, state ;
       T_CHAR *opcionstr ;
 
       htexto=L_HTXT_Open(g) ;
       if (!g)
           return (T_CHAR *)NULL ;
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
       switch (state)
       {
        case c_CHOSE : opcionstr=L_HTXT_GetSelectNodeName(htexto) ;
                       break ;
         default      : opcionstr=(T_CHAR *)NULL ;
       }
       L_HTXT_Close(&htexto) ;
       return opcionstr ;
     }


 /* ...................................................................... */

