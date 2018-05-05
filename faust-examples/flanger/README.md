Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into flanger-sam

% faust2sam -midi flanger.dsp

The result of this compile is a directory flanger-sam with the following three files:

       fast_pow2.h
       samFaustDSP.cpp
       samFaustDSP.h

These 3 files should be placed into the directory sam-baremetal/sam_baremetal_framework_core1/src/faust

In addition there is a header file that is common across all cores called audio_system_config.h.   In this file the following pre-processor variables should be set in the following way.   The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

       #define USE_FAUST_ALGORITHM_CORE1           TRUE
       #define USE_FAUST_ALGORITHM_CORE2           FALSE

Once the project is compiled, linked and loaded to the SAM board, the MIDI control API is as follows:


Delay CC-50
Rate CC-2
Depth CC-3
Feedback CC-4
Waveshape CC-54
Enable CC-102
Invert CC-49


Flange

The flanger effect impresses uniformly spaced sweeping notches on the sound spectrum. It accomplishes this using a variable comb filter, which works by mixing the input sound with a variably delayed-and-scaled copy of the input. Unlike the phaser, the flanger notches are uniformly spaced on a linear frequency scale, and there can be many more of them at low cost.

Rate

The Flanger Rate parameter sets the frequency of its LFO in Hz - performable


Depth

Depth of spectral notches - performable - Depth = 0 means no effect, Depth = 1 means maximum effect (spectral-notch gains go all the way down to zero).

Delay

Maximum Delay (in ms) used by the flanger - the actual delay at any given time is between this value and zero.

Feedback

Gain applied to the output signal and then summed with the input signal - performable
