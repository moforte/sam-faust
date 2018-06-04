#!/bin/tcsh

#************************************************************************
# Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.
#************************************************************************

echo "Compiling all the Faust Examples into code for the SHARC Audio Module"

cd 16_channel_volume
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi 16_channel_volume.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for 16_channel_volume.dsp"
faust2caqt -midi 16_channel_volume.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..

cd chorus
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi chorus.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for chorus.dsp"
faust2caqt -midi chorus.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..

cd echo
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi echo.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for echo.dsp"
faust2caqt -midi echo.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..

cd effects
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi effects.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for effects.dsp"
faust2caqt -midi effects.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..

cd flanger
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi flanger.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for flanger.dsp"
faust2caqt -midi flanger.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..

cd freeverb
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi freeverb.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for freeverb.dsp"
faust2caqt -midi freeverb.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null 
cd ..

cd virtualAnalog
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi -nvoices 1 virtualAnalog.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for minimoog.dsp"
faust2caqt -midi -nvoices 1 virtualAnalog.dsp
endif

unzip *.zip  >& /dev/null
/bin/rm *.zip  >& /dev/null
cd ..

cd sawtooth_synth
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi -nvoices 1 sawtooth_synth.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for sawtooth_syth.dsp"
faust2caqt -midi -nvoices 1 sawtooth_synth.dsp
endif

unzip *.zip  >& /dev/null
/bin/rm *.zip  >& /dev/null
cd ..

cd sine_synth
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi sine_synth.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for sine_synth.dsp"
faust2caqt -midi -nvoices 1 sine_synth.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..

cd volume
/bin/rm -r *sam* >& /dev/null
/bin/rm -r *.app >& /dev/null
/bin/rm -r faust.* >& /dev/null

faust2sam -midi volume.dsp

if ($1 == "OSX") then
echo "Creating OS X test App for volume.dsp"
faust2caqt -midi volume.dsp
endif

unzip *.zip >& /dev/null
/bin/rm *.zip >& /dev/null
cd ..


