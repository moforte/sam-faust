#!/bin/tcsh

# script to add sam additions to a faust distribution. 
#************************************************************************
# Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.
#************************************************************************


if ("$1" == "") then
    cat <<EOF

Usage: $0 <path to root of faust installation>
       Once this script is run and the additions files are copied 
       to the faust installation, two
       "make installs" will need to be run, typically as root

       % cd <path to the root of faust installation>
       % sudo make -f Makefile.sam install
       % cd <path to the root of faust installation>/tools/faust2appls
       % sudo make -f Makefile.sam install
 
EOF
    exit 1
endif

echo ""
echo "Adding Faust Additions to ["$1"]"
echo "   Validating existing Faust installation ["$1"]"
# Make sure that it exists 

(ls "$1") >& /dev/null
if ($status) then
   echo "      Faust installation directory ["$1"] does not exist"
   exit
else
   echo "      ["$1"] exists"
endif


# Make sure that it exists 

(cd $1) >& /dev/null
if ($status) then
   echo "      ["$1"] is not a directory"
   exit
else
   echo "      ["$1"] Faust installation directory exists"
endif




# Make sure that its really a faust directory

(ls "$1"/architecture) >& /dev/null
if ($status) then
   echo "      ["$1"] does not look like a Faust installation directory"
   exit
else
   echo "      ["$1"] verified as a Faust installation directory"
endif



# Make sure that the faust directory is writable.
cat > /tmp/writeTest.txt <<EOF
data
EOF

(cp /tmp/writeTest.txt "$1") >& /dev/null
if ($status) then
   echo "      Faust directory ["$1"] is NOT writable."
   exit
else
   /bin/rm "$1"/writeTest.txt
   echo "      Faust directory ["$1"] is writable."
endif


set scriptDir = `dirname $0`
set absScriptDir = `cd "$scriptDir" && pwd`
#echo "["$absScriptDir"] ["$1"]"



# copy the additions from the scripts to the faust tree
echo "   Copying Faust additions to the Faust directory"
rsync -a "$absScriptDir"/faust/*  "$1"

# add the sam build lines into the makefiles
echo "   Modifying the Faust Makefile for the faust additions." 
sed -f "$absScriptDir"/scripts/sedScript1.sed < "$1"/Makefile | tr '^' '\t' > /tmp/Makefile; cp /tmp/Makefile "$1"/Makefile.sam

echo "   Modifying the Faust tools Makefile for the faust additions." 
sed -f "$absScriptDir"/scripts/sedScript2.sed < "$1"/tools/faust2appls/Makefile | tr '^' '\t' > /tmp/Makefile.sam1; 
sed -f "$absScriptDir"/scripts/sedScript3.sed < /tmp/Makefile.sam1 | tr '^' '\t' > /tmp/Makefile.sam2; cp /tmp/Makefile.sam2 "$1"/tools/faust2appls/Makefile.sam





echo "Faust additions have been added to the Faust directory"

    cat <<EOF

Two "make installs" now need to be run, typically as root

% cd $1
% sudo make -f Makefile.sam install
% cd $1/tools/faust2appls
% sudo make -f Makefile.sam install
 
EOF

