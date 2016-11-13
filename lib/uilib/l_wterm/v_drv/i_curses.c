/* ........................................................................ */



   /* ... Include / Inclusion ........................................... */

      #include "uilib/l_wterm/v_drv/i_curses.h"


   /* ... Global Vars / Vars. Globales .................................. */

      T_BOOL I_CURSES_isInit = FALSE ;


   /* ... Funtions / Funciones .......................................... */


#if (defined(__LCURSES__) || defined(__LNCURSES__))

    /* ... Text Video en i_curses ... */
    void   I_CURSES_cgotoxy    ( T_INT x, T_INT y ) 
    {
      move(y-1,x) ;
    }

    void   I_CURSES_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) 
    {
      getsyx(*y,*x) ;
    }

    void   I_CURSES_clrscr     ( void ) 
    {
      clear() ; 
      refresh() ;
    }

    void   I_CURSES_cursor_off ( void ) 
    {
      curs_set(0) ;
    }

    void   I_CURSES_cursor_on  ( void ) 
    {
      curs_set(1) ;
    }

    void   I_CURSES_set_cursor ( T_INT lini, T_INT lfin )
    {
    }

    T_BOOL I_CURSES_Begin ( void )
    {
      if (I_CURSES_isInit == FALSE)
         {
           initscr() ;
           if (has_colors()==TRUE)
              { 
                start_color() ;
              }
           init_pair(1, COLOR_WHITE, COLOR_BLACK) ;
           attron(COLOR_PAIR(1)) ;
           I_CURSES_isInit = TRUE ;
         }
      return TRUE ;
    }

    void   I_CURSES_End        ( void ) 
    {
      endwin() ;
      I_CURSES_isInit = FALSE ;
    }

    void I_CURSES_AutoDetect ( INOUT T_INT *currmode,  INOUT T_INT *cfilas,   
                               INOUT T_INT *ccolumnas, INOUT T_INT *ncolores )
    {
      extern WINDOW *curscr ;

      (*currmode)  = 0 ;
      (*cfilas)    = LINES ;
      (*ccolumnas) = COLS ;
      (*ncolores)  = COLORS ;
    }

    T_BOOL I_CURSES_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                          T_INT width, T_INT tall,
                          T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 )
    {
      register T_INT   i, j ;
               T_CHAR  oldattr, newattr ; 

      if ( (rx2>width) || (ry2>tall) )
         {
           L_DEBUG_MSG_Write(WARNING,FALSE,ICURSES_BAD_DIMENSIONS) ;
           return FALSE ;
         }
      erase() ;
      if (ncolores>2)
      {
        static T_CHAR Color[]=c_esc_Text16Color ;

        oldattr=~(*attr) ;
        for (j=ry1-1; j<ry2; j++)
        {
          move(j,rx1-1) ;
          for (i=rx1-1; i<rx2; i++)
          {
            newattr=*(attr+j*width+i) ;
            if (oldattr!=newattr) 
               {
                 T_CHAR f, b ;

                 f=Color[newattr & 0x0f] ;
                 b=Color[(newattr >> 4) & 0x0f] ;
                 init_pair(f+b,Color[newattr & 0x0f],
                               Color[(newattr >> 4) & 0x0f] ) ;
                 attrset(COLOR_PAIR((f+b))) ;
                 oldattr=newattr ;
	       }
            addch(*(scr+j*width+i)) ;
          }
        }
      } else {
               oldattr=~(*attr) ;
               for (j=ry1-1; j<ry2; j++)
               {
                 move(j,rx1-1) ;
                 for (i=rx1-1; i<rx2; i++)
                 {
                   newattr=*(attr+j*width+i) ;
                   if (oldattr!=newattr) 
                      {
			if ( ((newattr >> 4) & 0x0f) > 3)
                           { /* background */
			     if ( (newattr & 0x0f) > 8)
                                     attrset(A_BOLD | A_REVERSE) ;
                                else attrset(A_DIM  | A_REVERSE) ;
                           } else {
			            if ( (newattr & 0x0f) > 8)
                                            attrset(A_BOLD | A_NORMAL) ;
                                       else attrset(A_DIM  | A_NORMAL) ;
                                  }
                        oldattr=newattr ;
                      }
                   addch(*(scr+j*width+i)) ;
                 }
               }
             }
      refresh() ;
      return TRUE ;
    }

#endif


#if ( !defined(__LCURSES__) && !defined(__LNCURSES__) )

    /* ... Text Video en i_curses ... */
    void   I_CURSES_cgotoxy    ( T_INT x, T_INT y ) 
    {
    }

    void   I_CURSES_cwherexy   ( INOUT T_INT *x, INOUT T_INT *y ) 
    {
    }

    void   I_CURSES_clrscr     ( void ) 
    {
    }

    void   I_CURSES_cursor_off ( void ) 
    {
    }

    void   I_CURSES_cursor_on  ( void ) 
    {
    }

    void   I_CURSES_set_cursor ( T_INT lini, T_INT lfin )
    {
    }

    T_BOOL I_CURSES_Begin ( void )
    {
      return FALSE ;
    }

    void   I_CURSES_End        ( void ) 
    {
    }

    void I_CURSES_AutoDetect ( INOUT T_INT *currmode,  INOUT T_INT *cfilas,   
                               INOUT T_INT *ccolumnas, INOUT T_INT *ncolores )
    {
      (*currmode)  = 0  ;
      (*cfilas)    = 25 ;
      (*ccolumnas) = 80 ;
      (*ncolores)  = 2  ;
    }

    T_BOOL I_CURSES_cdump ( T_CHAR *scr, T_CHAR *attr, T_INT ncolores,
                          T_INT width, T_INT tall,
                          T_INT rx1, T_INT ry1, T_INT rx2, T_INT ry2 )
    {
      return FALSE ;
    }

#endif


   /* ................................................................... */

