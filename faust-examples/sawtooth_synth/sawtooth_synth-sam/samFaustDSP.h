#include "../../common/audio_system_config.h"
#include "./samFaustDSPCore.h"
#if USE_FAUST_ALGORITHM
/************************************************************************
 ************************************************************************
 sam Faust Architecture File
 Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.
 ************************************************************************
 ************************************************************************/

#ifndef __sam_faust_dsp__
#define __sam_faust_dsp__

//==========================================

#define sam_SAMPLERATE 44100

class FaustPolyEngine;
class MidiUI;
class samAudio;
class mydsp;

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif



class samFaustDSP
{
    
    private:
    
        // the dsp object
        mydsp* aMyDSP;
    
        // the polyphonic engine
        FaustPolyEngine* fPolyEngine;
    
        // the audio driver
        samAudio* samAudioDriver;
    

    
// not sure if this is needed
#if MIDICTRL
    MidiUI* fMidiUI;
#endif
    
    public:
    
    
         //--------------`DspFaust()`----------------
         // Default constructor,  The audio driver will set
         // the sampleRate and buffer size 
         ///
         //
         //----
         samFaustDSP(int sampleRate, int bufferSize, int numInputs, int numOutputs);

    
        // destructor
        ~samFaustDSP();
    
        // setup the the hardware buffer pointers.
    void setDSP_ChannelBuffers(FAUSTFLOAT *AudioChannelA_0_Left,
                                   FAUSTFLOAT *AudioChannelA_0_Right,
                                   FAUSTFLOAT *AudioChannelA_1_Left,
                                   FAUSTFLOAT *AudioChannelA_1_Right,
                                   FAUSTFLOAT *AudioChannelA_2_Left,
                                   FAUSTFLOAT *AudioChannelA_2_Right,
                                   FAUSTFLOAT *AudioChannelA_3_Left,
                                   FAUSTFLOAT *AudioChannelA_3_Right,
                                   FAUSTFLOAT *AudioChannelB_0_Left,
                                   FAUSTFLOAT *AudioChannelB_0_Right,
                                   FAUSTFLOAT *AudioChannelB_1_Left,
                                   FAUSTFLOAT *AudioChannelB_1_Right,
                                   FAUSTFLOAT *AudioChannelB_2_Left,
                                   FAUSTFLOAT *AudioChannelB_2_Right,
                                   FAUSTFLOAT *AudioChannelB_3_Left,
                                   FAUSTFLOAT *AudioChannelB_3_Right);
    

        

    
        //-----------------`void stop()`--------------------------
        // Callback to render a buffer.
        //--------------------------------------------------------
        void processAudioCallback();
    

        
        //-------`void propagateMidi(int count, double time, int type, int channel, int data1, int data2)`--------
        // Take a raw MIDI message and propagate it to the Faust
        // DSP object. This method can be used concurrently with
        // [`keyOn`](#keyOn) and [`keyOff`](#keyOff).
        //
        // `propagateMidi` can
        // only be used if the `[style:poly]` metadata is used in
        // the Faust code or if `-polyvoices` flag has been
        // provided before compilation.
        //
        // #### Arguments
        //
        // * `count`: size of the message (1-3)
        // * `time`: time stamp
        // * `type`: message type (byte)
        // * `channel`: channel number
        // * `data1`: first data byte (should be `null` if `count<2`)
        // * `data2`: second data byte (should be `null` if `count<3`)
        //--------------------------------------------------------
        void propagateMidi(int, double, int, int, int, int);
        

};
#endif
#endif
