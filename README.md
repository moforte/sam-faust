Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.

This directory contains the following


faust-addition  - These are additions to be added to an existing Faust distribution with the add_faust_additions.tcsh  script. 
faust-examples  - Example faust algorithms (.dsp) files along with pre-compiled into C++ versions of the algorithms.

   16-channel-volume - A 16 channel MIDI controlled volume example
   chorus	     - A chorus stompbox
   echo		     - An echo stomp box 
   effects           - An effects chain of echo : flanger : chorus : reverb
   flanger           - A flanger stompbox
   freeverb          - A reverb
   minimoog          - The minimoog
   sawtooth_synth    - A simple MIDI controlled sawtooth synth
   sine_synth        - A simple MIDI controlled sine synth
   volume            - A simple MIDI controlled volume 

   buildAllFaustExamples.tcsh - This is a script that will build all the SHARC sam Demos 

For each of the examples there is a directory <algorithm>-sam.  Within this directory are the following 3 files.  This is the faust compiled implementation of the algorithm.

   fast_pow2.h
   samFaustDSP.cpp
   samFaustDSP.h

For each of of the examples there is a file "README.md"  This file describes the algorithm as well as the MIDI controller mappings.  Note that for every algorithm the pots on the DIY board are sending MIDI controllers CC-1,2,3, and the pushbuttons are sending CC-102,103,104,105

These algorithms are meant to be used in conjunction  with the baremetal framework found at  sam-baremetal

Within sam-baremetal there is a subproject directory for each core:

   sam_baremetal_framework_core0
   sam_baremetal_framework_core1
   sam_baremetal_framework_core2

Core 1 and Core 2 are SHARC DSPs.  You can place the 3 faust algorithm files in either:

   sam-baremetal/Workspaces/Baremetal_sam_DIY/sam_baremetal_framework_core1/src/faust

or
   sam-baremetal/Workspaces/Baremetal_sam_DIY/sam_baremetal_framework_core2/src/faust

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

In order to run one of these demos:

1) Copy  fast_pow2.h, samFaustDSP.cpp, samFaustDSP.h to the src/Faust directory for the core that you want to run on.

2) with CCES Open the workspace sam-baremetal

3) Under File> Import> Existing Projects into Workspace and follow the Next> buttons.

4) In the Project explorer open Common_Across_Cores/audio_system_config.h and select a core for the algorithm with USE_FAUST_ALGORITHM_CORE1 or USE_FAUST_ALGORITHM_CORE2.  You can select any combination, no faust algorithms, either of the cores or even both cores.

5) Under Project> Clean do a clean build.   For no faust algorithms the build will take about a minute.  For faust algorithm the built may take up to 5 minutes for each core.

6) Under the Run> Debug Configurations setup a configuration to run.

7) With an ICE connected from your computer to the SHARC sam board, run the code using Run> Debug. 
 




