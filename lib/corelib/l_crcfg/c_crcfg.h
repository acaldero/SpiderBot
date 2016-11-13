

 #ifndef C_CRCFG_H
 #define C_CRCFG_H


      #if defined(__MSDOS__)
         #define __BCC__
         #define __FSTYPE__     c_FAT
         #define __FSLIB__      c_LDIRENT
         #define __DEBUG__
      #endif

#if (0)
      #if defined(__MSDOS__)
         #define __TCC__
         #define __FSTYPE__     c_FAT
         #define __FSLIB__      c_LDIRENT
         #define __DEBUG__
      #endif
#endif

      #if defined(__LINUX__)
         #define __GCC__
         #define __FSTYPE__     c_XFS
         #define __FSLIB__      c_LDIRENT
         #define __DEBUG__
         #define HAVE_NETINET_TCP_H 
      #endif

      #if defined(__SUNOS__)
         #define __GCC__
         #define __FSTYPE__     c_XFS
         #define __FSLIB__      c_LDIRENT
         #define __DEBUG__
         #define HAVE_VALUES_H
         #define HAVE_INET_TCP_H 
         #define HAVE_SYS_TTOLD_H
      #endif

      #if defined(__AIX__)
         #define __GCC__
         #define __FSTYPE__     c_XFS
         #define __FSLIB__      c_LDIRENT
         #define __DEBUG__
         #define HAVE_VALUES_H
      #endif


 #endif


