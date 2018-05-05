Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into freeverb-sam

% faust2sam -midi freeverb.dsp

The result of this compile is a directory freeverb-sam with the following three files:

       fast_pow2.h
       samFaustDSP.cpp
       samFaustDSP.h

These 3 files should be placed into the directory sam-baremetal/sam_baremetal_framework_core1/src/faust

In addition there is a header file that is common across all cores called audio_system_config.h.   In this file the following pre-processor variables should be set in the following way.   The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

       #define USE_FAUST_ALGORITHM_CORE1           TRUE
       #define USE_FAUST_ALGORITHM_CORE2           FALSE

Once the project is compiled, linked and loaded to the SAM board, the MIDI control API is as follows:


Damp CC-4
RoomSize CC-3
Wet CC-2
Enable CC-102

Freeverb

A reverberator creates a sense of space. Classic guitar amps use a "spring reverb", which is one or more metal springs through which the sound propagates and disperses. GeoShred uses a more modern design from the field of Computer Music based on delay lines and Schroeder allpass filters

Freeverb is always stereo. It is normally placed last in the Effects Chain.

Parameters:

Damping

Increasing the damping decreases the reverberation time.

Level

Level is the "dry/wet mix": 0 for "dry" (no reverb), and 1 for "wet" (pure reverberator output). Note that stereo imaging is normally reduced by reverberation, because the reverberated sound is supposed sound like it's coming from all directions. Reduce the Reverb Level to better preserve stereo imaging.

Room Size

Increasing the Room Size parameter lengthens the delay lines used in the reverberator, corresponding to longer path lengths between reflections in an acoustic space.

Enable

Turn on/off the effect


