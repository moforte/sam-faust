Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into echo-sam

% faust2sam -midi echo.dsp

The result of this compile is a directory echo-sam with the following three files:

       fast_pow2.h
       samFaustDSP.cpp
       samFaustDSP.h

These 3 files should be placed into the directory sam-baremetal/sam_baremetal_framework_core1/src/faust

In addition there is a header file that is common across all cores called audio_system_config.h.   In this file the following pre-processor variables should be set in the following way.   The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

       #define USE_FAUST_ALGORITHM_CORE1           TRUE
       #define USE_FAUST_ALGORITHM_CORE2           FALSE

Once the project is compiled, linked and loaded to the SAM board, the MIDI control API is as follows:


DelayT60 CC-60
Delay CC-4
Warp CC-62
Feedback CC-3
Amp CC-2
FeedbackSM CC-76
Enable CC-102  

Echo

The Echo unit creates echoes

Parameters:

Delay

Time between echoes in seconds - performable. Under Expert there is a Delay Glide which is a portamento for changing the delay time, and is also performable.

Warp

Warp moves the output delay-line tap at a rate controlled by Glide. It can create temporary "glitching" (low Glide) or Doppler shifts (high Glide) - performable (thanks to Glide)


DelayT60

DelayT60 controls the speed of Delay, Warp. It gives the time to DelayT60 to the next knob setting in seconds. contents. - performable

Amp

Amplitude level of echoes relative to the direct signal - performable

Feedback

Controls the number of echo repetitions between 1 and infinity. - performable

FeedbackSm

When an echo is fed back to echo again, it is also lowpass filtered according to this parameter. Tone = 0 ("Digital") corresponds to no filtering, while Tone = 1 ("Tape") gives maximum lowpass filtering, like an old magnetic tape.

Enable

Turn on/off the effect
