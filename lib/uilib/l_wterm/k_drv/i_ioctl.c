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

      #include "uilib/l_wterm/k_drv/i_ioctl.h"


   /* ... Funtions / Funciones .......................................... */

#if defined(__LINUX__)

    T_CHAR I_IOCTL_getch ( void )
    {
           struct termios ttyb,tty ;
           T_CHAR ch ;

           ioctl(0,TCGETS,&ttyb) ;
           ioctl(0,TCGETS,&tty) ;
           tty.c_lflag=!ECHO ;
           ioctl(0,TCSETS,&tty) ;
	   read(0,&ch,1) ;
           ioctl(0,TCSETS,&ttyb) ;
           return ch ;
    }

    T_BOOL I_IOCTL_nbgetch ( INOUT T_CHAR *ch )
    {
           struct termios ttyb,tty ;
           int ok ;

           fcntl(0,F_SETFL,O_NONBLOCK) ;
           ioctl(0,TCGETS,&ttyb) ;
           ioctl(0,TCGETS,&tty) ;
           tty.c_lflag=!ECHO ;
           ioctl(0,TCSETS,&tty) ;
           ok=read(0,ch,1) ;
           ioctl(0,TCSETS,&ttyb) ;
           fcntl(0,F_SETFL,!O_NONBLOCK) ;
           return ((ok)!=-1) ;
    }
#endif


#if defined(__SUNOS__)
    T_CHAR I_IOCTL_getch ( void )
    {
           struct sgttyb ttyb,tty ;
           struct sgttyb ttybI,ttyI ;
           T_CHAR ch ;

           ioctl(1,TIOCGETP,&ttyb) ;
           ioctl(1,TIOCGETP,&tty) ;
           ioctl(0,TIOCGETP,&ttybI) ;
           ioctl(0,TIOCGETP,&ttyI) ;
           tty.sg_flags  &= !ECHO ;
           ttyI.sg_flags |= O_CBREAK ;
           ioctl(1,TIOCSETP,&tty) ;
           ioctl(0,TIOCSETP,&ttyI) ;
           fread(&ch,1,1,stdin) ;
           ioctl(1,TIOCSETP,&ttyb) ;
           ioctl(0,TIOCSETP,&ttybI) ;
           return ch ;
    }

    T_BOOL I_IOCTL_nbgetch ( INOUT T_CHAR *ch )
    {
           struct sgttyb ttybO,ttyO ;
           struct sgttyb ttybI,ttyI ;
           int ok ;
	   int oldfflag, fflag ;

           fflag     = fcntl(0,F_GETFL) ;
	   oldfflag  = fflag ;
	   fflag    |= O_NONBLOCK ;
           fcntl(0,F_SETFL,fflag) ;
           ioctl(1,TIOCGETP,&ttybO) ;
           ioctl(1,TIOCGETP,&ttyO) ;
           ioctl(0,TIOCGETP,&ttybI) ;
           ioctl(0,TIOCGETP,&ttyI) ;
           ttyO.sg_flags  &= !ECHO ;
           ttyI.sg_flags  |= O_CBREAK ; 
           ioctl(1,TIOCSETP,&ttyO) ;
           ioctl(0,TIOCSETP,&ttyI) ;
           ok = fread(ch,1,1,stdin) ;
           ioctl(1,TIOCSETP,&ttybO) ;
           ioctl(0,TIOCSETP,&ttybI) ;
           fcntl(0,F_SETFL,oldfflag) ;
           return ((ok)!=-1) ;
    }
#endif


#if defined(__AIX__)
    T_CHAR I_IOCTL_getch ( void )
    {
           struct sgttyb ttyb0,tty0 ;
           struct sgttyb ttyb1,tty1 ;
           T_CHAR ch ;

           ioctl(0,TIOCGETP,&ttyb0) ;
           ioctl(0,TIOCGETP,&tty0) ;
           ioctl(1,TIOCGETP,&ttyb1) ;
           ioctl(1,TIOCGETP,&tty1) ;
           tty1.sg_flags&=!ECHO ;
           tty0.sg_flags|=O_RAW ;
           ioctl(0,TIOCSETP,&tty0) ;
           ioctl(1,TIOCSETP,&tty1) ;
           read(0,&ch,1) ;
           ioctl(0,TIOCSETP,&ttyb0) ;
           ioctl(1,TIOCSETP,&ttyb1) ;
           return ch ;
    }

    T_BOOL I_IOCTL_nbgetch ( INOUT T_CHAR *ch )
    {
           struct sgttyb ttyb,tty ;
           int ok ;

           fcntl(0,F_SETFL,O_NONBLOCK) ;
           ioctl(1,TIOCGETP,&ttyb) ;
           ioctl(1,TIOCGETP,&tty) ;
           tty.sg_flags&=!ECHO ;
           tty.sg_flags|=O_RAW ;
           ioctl(1,TIOCSETP,&tty) ;
           ok=read(0,ch,1) ;
           ioctl(1,TIOCSETP,&ttyb) ;
           fcntl(0,F_SETFL,!O_NONBLOCK) ;
           return ((ok)!=-1) ;
    }
#endif

#if ( !defined(__LINUX__) && !defined(__SUNOS__) && !defined(__AIX__) )
    T_CHAR I_IOCTL_getch ( void )
    {
      return (0) ;
    }

    T_BOOL I_IOCTL_nbgetch ( INOUT T_CHAR *ch )
    {
      (*ch) = '\0' ;
      return FALSE ;
    }
#endif


/* ....................................................................... */

