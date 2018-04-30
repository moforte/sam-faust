Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into chorus-sam

% faust2sam -midi chorus.dsp

The result of this compile is a directory chorus-sam with the following three files:

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

Rate CC-01
Depth CC-02
Delay CC-03
Deviation CC-04
Enable CC-102

Chorus

The Chorus effect makes copies of its input sound and remixes them to the stereo field using differently modulated delays, thus simulating a chorus of nearly identical sound sources.

The Chorus output is always stereo, while its input may be either mono or stereo. To minimize CPU usage, place the Chorus at the point in your Effects Chain where the Effects are mono to the left and stereo to the right.

Parameters:

Rate

The Chorus Rate (performable) sets the highest frequency used in its LFOs for modulating the delay-line lengths


Depth

The Depth parameter (performable) controls the mixture of the input sound with the delayed-and-scaled copies of itself: 0 means input only (no chorus effect), 1/2 means equal balance (maximum incidental "flanging" effects), and 1 means modulated delay-line outputs only (pure chorus effect containing only scaling, onset spreading, and decorrelated Doppler shift).

Deviation

The Chorus Deviation sets the amplitude of its LFOs and therefore the range of delay-line length variation. The Deviation and Rate together determine the maximum Doppler shift applied to the sound.

Delay

The variable delays range between zero and this value

Enable

Turn on/off the effect
