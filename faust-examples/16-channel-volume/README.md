Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into 16-channel-volume-sam

% faust2sam -midi 16-channel-volume.dsp

The result of this compile is a directory 16—channel—volume-sam with the following three files:

       fast_pow2.h
       samFaustDSP.cpp
       samFaustDSP.h

These 3 files should be placed into the directory sam-baremetal/sam_baremetal_framework_core1/src/faust

In addition there is a header file that is common across all cores called audio_system_config.h.   In this file the following pre-processor variables should be set in the following way.   The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

       #define SAM_DIY_MIDI_BOARD_PRESENT          TRUE
       …
       #define FAUST_INSTALLED                     TRUE
       …
       #define USE_FAUST_ALGORITHM_CORE1           TRUE
       #define USE_FAUST_ALGORITHM_CORE2           FALSE
       …
       #define MIDI_UART_MANAGED_BY_SHARC1_CORE    TRUE

Once the project is compiled, linked and loaded to the SAM board, the MIDI control API is as follows:


Volume-01 CC-1
Volume-02 CC-2
Volume-03 CC-3
Volume-04 CC-4
Volume-05 CC-5
Volume-06 CC-6
Volume-07 CC-7
Volume-08 CC-8
Volume-09 CC-9
Volume-10 CC-10
Volume-11 CC-11
Volume-12 CC-12
Volume-13 CC-13
Volume-14 CC-14
Volume-15 CC-15
Volume-16 CC-16

Simple MIDI controlled 16 channel volume control
