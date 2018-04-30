Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

The faust code (.dsp) in this directory has been compiled using faust2sam into effects-sam

% faust2sam -midi effects.dsp

The result of this compile is a directory effects-sam with the following three files:

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


Invert		cc-49	Flanger	knob	Enable		cc-103	Flanger	switch	Delay		cc-50	Flanger	knob	Rate		cc-51	Flanger	knob	Depth		cc-52	Flanger	knob	Feedback	cc-53	Flanger	knob	Wave Shape	cc-54	Flanger	knob					Delay		cc-55	Chorus	knob	Enable		cc-104	Chorus	switch	Rate		cc-56	Chorus	knob	Depth		cc-57	Chorus	knob	Deviation	cc-58	Chorus	knob					enable		cc-102	Echo	switch	Delay Portament	cc-60	Echo	knob	Delay		cc-61	Echo	knob	Warp		cc-62	Echo	knob	Feedback	cc-63	Echo	knob	Amp		cc-75	Echo	knob	Feedback sm	cc-76	Echo	knob					Damp		cc-77	Reverb	knob	Enable		cc-105	Reverb	switch	Room Size	cc-78	Reverb	knob	Wet Dry		cc-79	Reverb	knob	



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


----

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

----

effects

The effects effect makes copies of its input sound and remixes them to the stereo field using differently modulated delays, thus simulating a effects of nearly identical sound sources.

The effects output is always stereo, while its input may be either mono or stereo. To minimize CPU usage, place the effects at the point in your Effects Chain where the Effects are mono to the left and stereo to the right.

Parameters:

Rate

The effects Rate (performable) sets the highest frequency used in its LFOs for modulating the delay-line lengths


Depth

The Depth parameter (performable) controls the mixture of the input sound with the delayed-and-scaled copies of itself: 0 means input only (no effects effect), 1/2 means equal balance (maximum incidental "flanging" effects), and 1 means modulated delay-line outputs only (pure effects effect containing only scaling, onset spreading, and decorrelated Doppler shift).

Deviation

The effects Deviation sets the amplitude of its LFOs and therefore the range of delay-line length variation. The Deviation and Rate together determine the maximum Doppler shift applied to the sound.

Delay

The variable delays range between zero and this value

Enable

Turn on/off the effect


----


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



