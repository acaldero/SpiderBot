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

      #include "weblib/l_encode/l_base64.h"


   /* ... Const / Constantes ............................................ */

      static int L_BASE64_tabla [64] = 
             {
               'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 
               'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
               'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
               'Y', 'Z',

               'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
               'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
               'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
               'y', 'z',

               '0', '1', '2', '3', '4', '5', '6', '7',
               '8', '9',

               '+', '/'
             } ;


   /* ... Functions / Funciones ......................................... */

      T_BOOL    L_BASE64_123Encode  ( IN   unsigned char  *instr,
                                      IN   unsigned int    inlen,
                                      OUT  unsigned char **outstr,
                                      OUT  unsigned int   *outlen )
      {
        T_BOOL        ok ;
        unsigned char four[4] ;

        switch (inlen)
        {
          case 3 :
                   four[0] = L_BASE64_tabla[ (instr[0] >> 2) ] ;
                   four[1] = L_BASE64_tabla[
                                             ( ((instr[0] & 3) << 4)
                                                       |
                                               (instr[1] >> 4) )
                                           ] ;
                   four[2] = L_BASE64_tabla[
                                             ( ((instr[1] & 0xF) << 2)
                                                       |
                                               (instr[2] >> 6) )
                                           ] ;
                   four[3] = L_BASE64_tabla[ (instr[2] & 0x3F) ] ;
                   break ;
          case 2 :
                   four[0] = L_BASE64_tabla[ (instr[0] >> 2) ] ;
                   four[1] = L_BASE64_tabla[
                                             ( ((instr[0] & 3) << 4)
                                                       |
                                               (instr[1] >> 4) )
                                           ] ;
                   four[2] = L_BASE64_tabla[
                                             ( ((instr[1] & 0xF) << 2)
                                                       |
                                               (instr[2] >> 6) )
                                           ] ;
                   four[3] = '=' ;
                   break ;
          case 1 :
                   four[0] = L_BASE64_tabla[ (instr[0] >> 2) ] ;
                   four[1] = L_BASE64_tabla[
                                             ( ((instr[0] & 3) << 4)
                                                       |
                                               (instr[1] >> 4) )
                                           ] ;
                   four[2] = '=' ;
                   four[3] = '=' ;
                   break ;
          default :
                   return FALSE ;
                   break ;
        }
        ok = L_BUFFA_CatNBytesToCache((T_CHAR  **)outstr,
                                      (T_U_INT  *)outlen,
                                      (T_CHAR   *)four,
                                      (T_U_INT   )4) ;
        return ok ;
      }

      T_BOOL    L_BASE64_encode     ( IN   unsigned char  *instr,
                                      IN   unsigned int    inlen,
                                      OUT  unsigned char **outstr,
                                      OUT  unsigned int   *outlen )
      {
        T_BOOL   ok ;
        int      i, count, rest ;

        (*outlen) = 0L ;
        (*outstr) = NULL ;
        count = inlen / 3 ;
        for (i=0; i<count ; i++)
        {
          ok = L_BASE64_123Encode(&(instr[3*i]),3,outstr,outlen) ;
          FALSE_RET_FALSE(ok) ;
        }
        rest = inlen % 3 ;
        if (rest != 0)
            ok = L_BASE64_123Encode(&(instr[3*count]),rest,outstr,outlen) ;
        return ok ;
      }


  /* ...................................................................... */

