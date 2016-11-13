# SpiderBot

Yo can download SpiderBot(1.60.007) through the official GitHub repository.

. . After you download SpiderBot, with "tar zxvf SpiderBot.tar.gz" you can uncompress source code.  
. . Then, "cd WebUtilities" and "make -f Makefile.linux"  
. . Finally "make -f Makefile.linux install"  

If you want a w95/w98 version, you need Cygnus Develop Kit (cdk.exe).  

. . See in any web search like http://ftpsearch.ntnu.no for a mirror or go directly to http://www.cygnus.com.

SpiderBot.tgz is a "pack" with several robots:

* WCAT

  - % wcat -url www.linuxhq.com/index.html -maxurls 1  | more

      It will send the page index.html to the stdout.

      warnings:
        - -delay params don´t work !  (1.60.004 fix it)
        - -maxurls 2 download only 1  (1.60.004 fix it)


  - % wcat -url http://www.linuxhq.com

      It will send all pages from www.linuxhq.com to stdout.

      warnings:
        - binary file will also be sent, if you want to avoid it please use -skipbin.


  - ( %wcat -url www.linuxhq.com -in1page > index.html )

      It will send the full web site to a single one page (index.html here), leaving binaries inside of a directory tree.
       ( ./www.linuxhq.com/icons/... )

      warnings:
        - errors (like not found pages) are saved in files
          umm, i need study error handler deeper... (:->)


* WDIR

  - % wdir -url www.linux.org | grep http

    It will print all URLs that this site has.

    warnings:
       - fail to scan "mailto:" hrefs (1.60.004 fix it)


* WCOPY

  - % wcopy -url www.linux.org -skipel -makequery >& log1 &

    It will make a mirror from www.linux.org, rewriting links for local browsing (-makerelative)  
    skipping exclusion list (-skipel => exclusion list is a the-facto standard for
    describing the paths inside a file called www.linux.org/robots.txt have to be exclude from the robot work). 
    Also wcopy makes queries to cgi-bin storing its response (-makequery).
    If you want to view the robot output, just type :

    % tail -f log1

    If you want to stop wcopy, you can use:

    % /usr/sbin/fuser log1
    log1:     2094c
    
    % kill -9 2094c
	
  - % wcopy -resume resume.www.linux.org -makerelative -skipel -makequery >& log1 &

     It will resume wcopy from where it was stopped.  

     warnings:
       - AVOID that first url are redirect to a second url.
         if second url is from other web-site, wcopy stop (if command line option '-allsite' is NOT present).
         if second url is from same web-site, wcopy will
         skiped check next urls must be from same path (if command line option '-allmachine' is NOT present)
         (fix in next version)

* MKLOCAL

  - % mklocal -dir www.linux.org -skipbin

     If you forgot "-makerelative" or don't know it was needed, don't warry
     mklocal will rewrite links to offline browsing.

     warning-log:
         - be carefully, if you use "-makerelative" at wcopy and after
           download, use mklocal at same mirror, some links 
           are re-write bad.
           (href=../www.here.linux => href=../www.here.linux/www.here.linux/)

* SpiderBot

  - % SpiderBot

    SpiderBot is easy web download robot. 
    I try to use curses in order to build menus, but I not sure that is what people may want.
    Also, it has a simple command line option set. For example, execute:

       % SpiderBot -url http://www.linux.com -maxbytes 1000000

    and SpiderBot make a directory called "www.linux.com" and try to download
    one megabyte from http://www.linux.com.



