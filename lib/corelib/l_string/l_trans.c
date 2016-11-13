/* ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "corelib/l_string/l_trans.h"


   /* ... functions / funciones ......................................... */

      /*  Standard String Functions  *
       * --------------------------- */
        T_INT L_TRANS_BinToCard    ( IN    T_CHAR *Bin )
        {
          T_INT result, i, slen, balien ;

          TRUE__SET_ERROR__RET_LONG( (Bin == NULL), 0 ) ;
          slen = strlen(Bin) ;
          balien = strspn(Bin,"01") ;
          if (slen!=balien)
              return X_MATH_Ipow(2,slen) ;
          result=0 ;
          for (i=0; i<slen; i++)
               result=(result*2) + (Bin[i]-'0') ;
          return result ;
        }

        T_INT L_TRANS_SubBinToCard ( IN     const T_CHAR  *l,
                                     IN     T_INT  chi , 
                                     IN     T_INT  num )
        {
          static T_CHAR laux[300] ;

          TRUE__SET_ERROR__RET_LONG( (chi+num >strlen(l)), 0 ) ;
          memcpy(laux,&(l[chi]),num) ;
          laux[num]='\0' ;
          return L_TRANS_BinToCard(laux) ;
        }

        void L_TRANS_StrSwitch   ( IN     T_INT   b,
                                   IN     T_INT   limit, 
                                   OUT    T_CHAR  *l, ... )
        {
          T_INT i ;
          T_CHAR *arg ;
          va_list va ;

          va_start(va,l) ;
          if (b <= limit)
             {
               for (i=0; ((i<=b) && (i<=limit)); i++)
                   {
                     arg=va_arg(va,T_CHAR *) ;
                   }
               strcat(l,arg) ;
             }
        }


   /* ................................................................... */


