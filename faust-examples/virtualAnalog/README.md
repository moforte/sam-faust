# Virtual Analog Synthesizer

## Description

An example of an [analog modeling synthesizer](https://en.wikipedia.org/wiki/Analog_modeling_synthesizer) which recreates vintage synthesizer sounds by modeling the original electronic circuitry.

## Parameters

Parameter                   | MIDI CC # | Description
----------------------------|-----------|------------
Octave1                     | `CC-23`   |
DeTuning1                   | `CC-24`   |
Waveform1                   | `CC-25`   |
Osc1 On                     | `CC-12`   |
Osc1 Amp                    | `CC-26`   |
On                          | `CC-13`   |
Ext Input                   | `CC-27`   |
Octave2                     | `CC-28`   |
DeTuning2                   | `CC-29`   |
Waveform2                   | `CC-30`   |
Osc2 On                     | `CC-14`   |
Osc2 Amp                    | `CC-31`   |
Noise Amp                   | `CC-32`   |
Noise On                    | `CC-15`   |
White/Pink                  | `CC-16`   |
Octave3                     | `CC-33`   |
DeTuning3                   | `CC-34`   |
Waveform3                   | `CC-35`   |
Osc3 On                     | `CC-17`   |
Osc3 Amp                    | `CC-36`   |
VCF Freq Cutoff             | `CC-74`   |
Corner Resonance            | `CC-37`   |
Kbd Ctl                     | `CC-38`   |
Filter Mod.                 | `CC-19`   |
Amount of Contour (octaves) | `CC-39`   |
AttackF                     | `CC-40`   |
DecayF                      | `CC-41`   |
SustainF                    | `CC-42`   |
Decay                       | `CC-20`   |
Glide                       | `CC-65`   |
sustain                     | `CC-64`   |
AttackA                     | `CC-43`   |
DecayA                      | `CC-44`   |
SustainA                    | `CC-45`   |
mod                         | `CC-1`    |
MasterVolume                | `CC-7`    |
Tune                        | `CC-47`   |
Glide                       | `CC-5`    |
Mod. Mix                    | `CC-48`   |
Osc. Mod.                   | `CC-22`   |
Osc. 3 Ctl                  | `CC-9`    |

## Building the Example

The faust code (.dsp) in this directory has been compiled using `faust2sam` into `virtualAnalog-sam`

```
% faust2sam -midi virtualAnalog.dsp
```

The result of this compile is a zip file `virtualAnalog-sam.zip` which contains the following three files:

  - `fast_pow2.h`
  - `samFaustDSP.cpp`
  - `samFaustDSP.h`

These 3 files should be placed into the directory `sam_baremetal_framework_core1/src/faust`

In addition there is a header file that is common across all cores called `audio_system_config.h`. In this file the following pre-processor variables should be set in the following way. The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

```
#define USE_FAUST_ALGORITHM_CORE1           TRUE
#define USE_FAUST_ALGORITHM_CORE2           TRUE
```
