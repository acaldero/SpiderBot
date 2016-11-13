#!/bin/sh

#
#  Copyright Alejandro Calderon (1997-1999)
#  <acaldero@laurel.datsi.fi.upm.es>
# 
#  permission is hereby granted to copy, modify and redistribute this code
#  in terms of the GNU Library General Public License, Version 2 or later,
#  at your option.
# 



#
# default values ...
#
DEFAULT_INSTALL_DIR="/usr/local/bin"
INSTALL_DIR=""
EXE_WTOOLS="wtools/wtools SpiderBot/SpiderBot"
DAT_WTOOLS="SpiderBot/SpiderBot.dat"


#
# getting install dir ...
#
while [ -z "$INSTALL_DIR" ] ; do

  echo ""
  echo     "   Where you want install Web Utilities ?"
  echo -n  "   write full path [${DEFAULT_INSTALL_DIR}]-> "
  read INSTALL_DIR 
  case "$INSTALL_DIR" in

    "")
        INSTALL_DIR="$DEFAULT_INSTALL_DIR"
        ;;
    *)
        if [ ! -d "$INSTALL_DIR" ] ; then
           echo ""
           echo "   directory $INSTALL_DIR does not exist,"
           echo "   sorry, try again"
           INSTALL_DIR=""
        fi
        ;;
  esac

done


#
# installing ...
#
echo ""
echo "   Installing web utilities at $INSTALL_DIR ..."

rm -fr $INSTALL_DIR/wcopy.exe
rm -fr $INSTALL_DIR/wcopy
rm -fr $INSTALL_DIR/wdir.exe
rm -fr $INSTALL_DIR/wdir
rm -fr $INSTALL_DIR/wcat.exe
rm -fr $INSTALL_DIR/wcat
rm -fr $INSTALL_DIR/mklocal.exe
rm -fr $INSTALL_DIR/mklocal
rm -fr $INSTALL_DIR/wtools.exe
rm -fr $INSTALL_DIR/wtools
rm -fr $INSTALL_DIR/SpiderBot.exe
rm -fr $INSTALL_DIR/SpiderBot
rm -fr $INSTALL_DIR/SpiderBot.dat
strip  $EXE_WTOOLS
cp     $EXE_WTOOLS   $INSTALL_DIR/
cp     $DAT_WTOOLS   $INSTALL_DIR/
ln -s  $INSTALL_DIR/wtools     $INSTALL_DIR/wcopy
ln -s  $INSTALL_DIR/wtools     $INSTALL_DIR/wdir
ln -s  $INSTALL_DIR/wtools     $INSTALL_DIR/wcat
ln -s  $INSTALL_DIR/wtools     $INSTALL_DIR/mklocal

echo "   Ready !"
echo ""


#
# grettings
#
echo ""
echo "   It is easy to use :"
echo "    1.- make a temporal directory"
echo "    2.- change into temporal directory"
echo "    3.- run \"$INSTALL_DIR/{wcopy,wdir,wcat,mklocal}\" with your options"
echo ""



