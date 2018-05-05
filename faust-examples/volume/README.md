Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into volume-sam

% faust2sam -midi volume.dsp

The result of this compile is a directory volume-sam with the following three files:

       fast_pow2.h
       samFaustDSP.cpp
       samFaustDSP.h

These 3 files should be placed into the directory sam-baremetal/sam_baremetal_framework_core1/src/faust

In addition there is a header file that is common across all cores called audio_system_config.h.   In this file the following pre-processor variables should be set in the following way.   The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

       #define USE_FAUST_ALGORITHM_CORE1           TRUE
       #define USE_FAUST_ALGORITHM_CORE2           FALSE

Once the project is compiled, linked and loaded to the SAM board, the MIDI control API is as follows:


Volume CC-1

Simple MIDI controlled volume control
