/************************************************************************
 ************************************************************************
 sam Faust Architecture File
 Copyright (c) 2017 Analog Devices, Inc.  All rights reserved.
 ************************************************************************
 ************************************************************************/


#include <math.h>
#include <cmath>

#include "faust/misc.h"
#include "faust/gui/UI.h"
#include "faust/dsp/dsp.h"
#include "faust/dsp/dsp-adapter.h"
#include "faust/gui/meta.h"

//**************************************************************
// Intrinsic
//**************************************************************

<<includeIntrinsic>>

<<includeclass>>

//**************************************************************
// Polyphony
//**************************************************************

#include "faust/dsp/faust-poly-engine.h"

//**************************************************************
// Audio driver
//**************************************************************

#include "faust/audio/samAudio.h"

//**************************************************************
// Interface
//**************************************************************

#include "samFaustDSP.h"

std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;

// constructor
samFaustDSP::samFaustDSP(int sampleRate, int bufferSize, int numInputs, int numOutputs)
{
    // create a new instace of the dsp object
    aMyDSP = new mydsp;
    aMyDSP->init(sampleRate);
    
    // create a new instance of the audio driver.
    samAudioDriver = new samAudio;
    samAudioDriver->setDSP_Parameters(sampleRate, bufferSize, numInputs, numOutputs);
    
    // create a new instance of the FaustPolyEngine
    fPolyEngine = new FaustPolyEngine(aMyDSP, samAudioDriver);
    // the constructor calls init
    
#if MIDICTRL
    // might need a version of these.
    //fMidiUI = new MidiUI(new rt_midi());
    //fPolyEngine->buildUserInterface(fMidiUI);
#endif
}


// destructor
samFaustDSP::~samFaustDSP()
{
#if MIDICTRL
    // might need this
    //delete fMidiUI;
#endif
    delete aMyDSP;
    delete samAudioDriver;
    delete fPolyEngine;

}

// setup the sampleRate and bufferSize
// void setDSP_Parameters(int sampleRate, int bufferSize);
void samFaustDSP::setDSP_ChannelBuffers(FAUSTFLOAT *AudioChannelA_0_Left,
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
                       FAUSTFLOAT *AudioChannelB_3_Right)

{
    ((samAudio *)samAudioDriver)->setDSP_ChannelBuffers(AudioChannelA_0_Left,
                                                    AudioChannelA_0_Right,
                                                    AudioChannelA_1_Left,
                                                    AudioChannelA_1_Right,
                                                    AudioChannelA_2_Left,
                                                    AudioChannelA_2_Right,
                                                    AudioChannelA_3_Left,
                                                    AudioChannelA_3_Right,
                                                    AudioChannelB_0_Left,
                                                    AudioChannelB_0_Right,
                                                    AudioChannelB_1_Left,
                                                    AudioChannelB_1_Right,
                                                    AudioChannelB_2_Left,
                                                    AudioChannelB_2_Right,
                                                    AudioChannelB_3_Left,
                                                    AudioChannelB_3_Right);

}

void samFaustDSP::processAudioCallback()
{
    // ask the driver to process the audio callback
    samAudioDriver->processAudioCallback();
}


void samFaustDSP::propagateMidi(int count, double time, int type, int channel, int data1, int data2)
{
    fPolyEngine->propagateMidi(count, time, type, channel, data1, data2);
}




