/************************************************************************
  SHARC Audio Module Faust Architecture File
  Copyright (c) 2018 Analog Devices, Inc. All rights reserved.
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
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
