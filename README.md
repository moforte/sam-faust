# Overview

[Faust](http://faust.grame.fr/) (Functional Audio Stream) is an open-source, functional programming language,
specifically designed for real-time audio signal processing and synthesis. Faust
generates C++, as well as other target languages, for signal processing applications.

Faust programs may be targeted for many different platforms via what is known as “an
architecture”. The script in this repository `faust2sam` calls the Faust compiler using an architecture that is specific to the Analog Devices [SHARC Audio Module](http://analog.com/sharcaudiomodule) platform. When an algorithm is compiled using
`faust2sam`, three C++ source code files are generated for the SHARC Audio Module. These files may then be inserted into a [CrossCore Embedded Studio](http://analog.com/cces) (CCES)
project which can then be compiled into an application that runs on the SHARC Audio
Module hardware.

For more information on `faust2sam` see [Faust Integration with the Analog Devices SHARC Audio Module Platform](SHARC%20Audio%20Module%20Faust%20Interface.pdf) in this directory.
This directory contains the following

# Contents

`faust-addition` - These are additions to be added to an existing Faust distribution with the add_faust_additions.tcsh  script. 

`faust-examples` - Example faust algorithms (.dsp) files along with pre-compiled into C++ versions of the algorithms.

Example             | Description
--------------------|------------------------------------------------------
`16-channel-volume` | A 16 channel MIDI controlled volume example
`chorus`            | A chorus stompbox
`echo`              | An echo stomp box
`effects`           | An effects chain of echo : flanger : chorus : reverb
`flanger`           | A flanger stompbox
`freeverb`          | A reverb
`virtualanalog`     | A virtual analog modeling synth
`sawtooth_synth`    | A simple MIDI controlled sawtooth synth
`sine_synth`        | A simple MIDI controlled sine synth
`volume`            | A simple MIDI controlled volume

`buildAllFaustExamples.tcsh` - This is a script that will build all the SHARC Audio Module Demos

For each of the examples there is a directory named `<algorithm>-sam`.  Within this directory are the following 3 files.  This is the faust compiled implementation of the algorithm.

  - `fast_pow2.h`
  - `samFaustDSP.cpp`
  - `samFaustDSP.h`

For each of of the examples there is a file `README.md`  This file describes the algorithm as well as the MIDI controller mappings.  Note that for every algorithm the pots on the DIY board are sending MIDI controllers CC-1,2,3, and the pushbuttons are sending CC-102,103,104,105

These algorithms are meant to be used in conjunction with the [SHARC Audio Module Bare Metal SDK](https://wiki.analog.com/resources/tools-software/sharc-audio-module/baremetal).

Within the SDK there is a subproject directory for each core:

  - `sam_baremetal_framework_core0`
  - `sam_baremetal_framework_core1`
  - `sam_baremetal_framework_core2`

Core 1 and Core 2 are [SHARC DSPs](http://analog.com/sharc). You can place the 3 faust algorithm files in either:

  - `sam_baremetal_framework_core1/src/faust`

or
  - `sam_baremetal_framework_core2/src/faust`

In addition there is a header file that is common across all cores called `audio_system_config.h`. In this file the following pre-processor variables should be set in the following way.  The example below indicates that a Faust algorithm will only be running on Core1 and that Core2 will be simply passing audio to the codec. 

```
#define SAM_DIY_MIDI_BOARD_PRESENT          TRUE
…
#define FAUST_INSTALLED                     TRUE
…
#define USE_FAUST_ALGORITHM_CORE1           TRUE
#define USE_FAUST_ALGORITHM_CORE2           FALSE
…
#define MIDI_UART_MANAGED_BY_SHARC1_CORE    TRUE
```

# Running the Demos

1. Copy `fast_pow2.h`, `samFaustDSP.cpp`, `samFaustDSP.h` to the `src/Faust` directory for the core that you want to run on.

2. Within [CCES](http://analog.com/cces) create a new workspace

3. Click `File` > `Import` > `Existing Projects into Workspace` and follow the `Next` buttons

4. In the Project explorer open `common/audio_system_config.h` and select a core for the algorithm with `USE_FAUST_ALGORITHM_CORE1` or `USE_FAUST_ALGORITHM_CORE2`.  You can select any combination, no faust algorithms, either of the cores or even both cores.

5. Under `Project` > `Clean` do a clean build. For no faust algorithms the build will take about a minute. For faust algorithm the built may take up to 5 minutes for each core.

6. Under the `Run` > `Debug Configurations` menu setup a configuration to run.

7. With an [ICE-1000](http://analog.com/ice1000) or [ICE-2000](http://analog.com/ice2000) emulator connected from your computer to the SHARC Audio Module board, run the code using `Run` > `Debug`. 
 