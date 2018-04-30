/* Simple_Sysctrl is a library that provides Arduino-style functionality to the
SHARC and CCES.  It is inspired by the WiringPi library that is widely used on
RaspberryPi to simplify basic GPIO and peripheral programming.

Copyright (c) 2017 Analog Devices.  All rights reserved.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#include "simple_sysctrl.h"

// Local prototypes
void _setupPinInterrupts();

// Global flag to indicate if this core is a master (i.e., it sets up clocks and
// polls HADCs
bool _thisCoreIsMaster = false;

//****************************************************************************
// System tick resources (HADC sampling and delay function support)
//****************************************************************************
volatile uint64_t system_milliticks = 0;
ADI_TMR_HANDLE _Timer_Handle;
uint8_t _Timer_InstanceMemory[ADI_TMR_MEMORY];

//****************************************************************************
// HADC system resources
//****************************************************************************
// Note: for newer SAM boards, the HADC_MIN value will change once these inputs
// are buffered
#define HADC_MIN                (1800.0)
#define HADC_MAX                (4096.0)
#define HADC_CHANNELS           (7)       
#define HADC_CHANNEL_MASK       (0xFF80)
#define HADC_CHANNEL_MASK_INV   (0x7F)

ADI_HADC_HANDLE _HADC_Handle;
uint8_t _HADC_InstanceMemory[ADI_HADC_MEM_SIZE];

// Flag to indicate HADC conversion sequence has completed
bool    _HADC_SeqComplete = false;

// Channels for converted data
uint16_t _HADC_ChannelData_Raw[HADC_CHANNELS];
float    _HADC_ChannelData_Float[HADC_CHANNELS];

/**
 * This is the system tick for this light framework.  It occurs every
 * millisecond (1000 times per second).  It is used to keep track of how many
 * milliseconds have passed which is used by the delay() and millis() functions.
 * It also kicks off a set of conversions for the ADCs.
 */
void _systemTimerHandler(void *pCBParam, uint32_t Event, void *pArg) {

	int i;

    switch(Event)
    {
        case ADI_TMR_EVENT_DATA_INT:

            // Increment our ticks using a big, unsigned 64-bit int.  This is
            // used to support the delay() and millis() functions
        	system_milliticks++;

        	if (_thisCoreIsMaster) {

        		// Normalize our last set of conversions (from 0.0 - 1.0)
				for (i = 0; i < HADC_CHANNELS; i++) {
					_HADC_ChannelData_Float[i] = fmax(0.0,((float) _HADC_ChannelData_Raw[i] - HADC_MIN)/(HADC_MAX-HADC_MIN));
				}

				 // Wait until the conversion sequence to is complete (although it
				 // should be done by now since we're in a 1KHz loop
				ADI_HADC_RESULT result_HADC;

				// Get converted data
				result_HADC = adi_hadc_GetConvertedData(_HADC_Handle, HADC_CHANNEL_MASK_INV, _HADC_ChannelData_Raw);

				// Kick off the next conversion for next time through the timer
				// loop (so we're not wasting time waiting)
				result_HADC = adi_hadc_StartConversion(_HADC_Handle, true);
        	}
            break;

        default:
            break;
    }

    return;

}

/*
 * simple_sysctrl_init() sets up the various back-end functionality required.  It
 * should be called before any other functions in this library.  This library can
 * be used on all 3 cores.  However, one core needs to be the master.
 * This core will maintain the system ticks used by the delay function,
 * set up system clocks, etc. When calling the init function on the core
 * that will handle this housekeeping (likely the ARM), set masterCore = true.
 * Otherwise, leave it as false if WS is being used on additional cores.
 */
void simple_sysctrl_init( bool masterCore, uint8_t timerId ) {

	// Set global variable which is used by the interrupt service routine above
	_thisCoreIsMaster = masterCore;

	// If this core is the master...
	if (_thisCoreIsMaster) {

		// Set up clocks for SHARC SAM board (based on 25MHz external oscillator)
		ADI_PWR_RESULT result_pwr;
		result_pwr = adi_pwr_Init(0, 25000000);
		result_pwr = adi_pwr_SetFreq(0, F_CPU, F_SYSSCLK);

		if (result_pwr != ADI_PWR_SUCCESS ) {
			printf("Error setting up clocks: %d", result_pwr);
			while(1) {}
		}


    // Use this to see current clock settings
	#if 0
		uint32_t fsysclk=0, fsclk0=0, fsclk1=0;

		// Display clock settings to confirm that they are set correctly
		result_pwr = adi_pwr_GetSystemFreq(0, &fsysclk, &fsclk0, &fsclk1);

		printf(" FSYSCLK: %d\n",fsysclk);
		printf(" FSCLK0: %d\n",fsclk0);
		printf(" FSCLK1: %d\n",fsclk1);
	#endif


		// Initialize HADC channels 0-5
		ADI_HADC_RESULT result_HADC;

	   // Flags to capture the events reported by the callback 
		_HADC_SeqComplete = false;

	    // Open the HADC driver 
	    result_HADC = adi_hadc_Open(0, _HADC_InstanceMemory, &_HADC_Handle);

		 // Set the channel mask for the channels to be converted 
		result_HADC = adi_hadc_SetChannelMask(_HADC_Handle, HADC_CHANNEL_MASK);

	    result_HADC = adi_hadc_SetSampleFreqDivFactor(_HADC_Handle, 1);
	    result_HADC = adi_hadc_SetNumConversions(_HADC_Handle, 1);

        // Kick off first conversion
        result_HADC = adi_hadc_StartConversion(_HADC_Handle, true);
    }

	// Initialize 1uS timer ticks regardless of master status
	ADI_TMR_RESULT result_timer;

	if ( (result_timer = adi_tmr_Open(timerId,
								_Timer_InstanceMemory,
								ADI_TMR_MEMORY,
								_systemTimerHandler,
								NULL,
								&_Timer_Handle)) != ADI_TMR_SUCCESS)
	{
	// TODO handle error
	}

	// Set the mode to PWM OUT 
	result_timer = adi_tmr_SetMode(_Timer_Handle, ADI_TMR_MODE_CONTINUOUS_PWMOUT);

	// Set the IRQ mode to get interrupt after timer counts to Delay + Width 
	result_timer = adi_tmr_SetIRQMode(_Timer_Handle, ADI_TMR_IRQMODE_WIDTH_DELAY);

	// Set the Period - once per ms
	result_timer = adi_tmr_SetPeriod(_Timer_Handle, F_SCK0/1000);

	// Set the timer width 
	result_timer = adi_tmr_SetWidth(_Timer_Handle, F_SCK0/1000/2 - 1);

	// Set the timer delay 
	result_timer = adi_tmr_SetDelay(_Timer_Handle, F_SCK0/1000/2 );

	// Enable the timer 
	result_timer = adi_tmr_Enable(_Timer_Handle, true);
	

	// Initialize GPIO interrupts
    _setupPinInterrupts();

}



//******************************************************************************
//  Delay and tick support
//******************************************************************************

// ARDUINO FUNCTION
// Returns the elapsed number of milliseconds 
unsigned long millis(void) {
    return system_milliticks;
}


// ARDUINO FUNCTION
// Adds a delay of a certain number of milliseconds
void delay(unsigned long delay) {

    uint64_t milli_delay = delay + system_milliticks;

    // Check if we wrapped
    if (milli_delay < system_milliticks) {
        while ( milli_delay < system_milliticks ) {}
        while ( milli_delay > system_milliticks ) {}
    } else {
        while(milli_delay > system_milliticks) {}
    }
}

////////////////////////////////////////////////////////////////////////////////


//******************************************************************************
//  GPIO interrupt and pin support support
//******************************************************************************

// User call back functions that can be mapped to pins in each port
void (*_portA_Callbacks[16])(void);
void (*_portB_Callbacks[16])(void);
void (*_portC_Callbacks[16])(void);
void (*_portD_Callbacks[16])(void);
void (*_portE_Callbacks[16])(void);
void (*_portF_Callbacks[16])(void);

// Default GPIO pin handlers which call user callback functions
void _PINT0_Handler (uint32_t iid, void *handlerArg)
{
    int i;
    for (i=0;i<16;i++) {
        // Check to see if we have an interrupt pending and it's one we have a
        // call back for
        if (*pREG_PINT0_REQ & (0x1 << i) && _portA_Callbacks[i] != NULL) {
            *pREG_PINT0_REQ |= (0x1 << i);  // Clear interrupt
            _portA_Callbacks[i]();
        }
    }
}
void _PINT1_Handler (uint32_t iid, void *handlerArg)
{
    int i;
    for (i=0;i<16;i++) {
        // Check to see if we have an interrupt pending and it's one we have a
        // call back for
        if (*pREG_PINT1_REQ & (0x1 << i) && _portB_Callbacks[i] != NULL) {
            *pREG_PINT1_REQ |= (0x1 << i);  // Clear interrupt
            _portB_Callbacks[i]();
        }
    }
}
void _PINT2_Handler (uint32_t iid, void *handlerArg)
{
    int i;
    for (i=0;i<16;i++) {
        // Check to see if we have an interrupt pending and it's one we have a
        // call back for
        if (*pREG_PINT2_REQ & (0x1 << i) && _portC_Callbacks[i] != NULL) {
            *pREG_PINT2_REQ |= (0x1 << i);  // Clear interrupt
            _portC_Callbacks[i]();
        }
    }
}
void _PINT3_Handler (uint32_t iid, void *handlerArg)
{
    int i;
    for (i=0;i<16;i++) {
        // Check to see if we have an interrupt pending and it's one we have a
        // call back for
        if (*pREG_PINT3_REQ & (0x1 << i) && _portD_Callbacks[i] != NULL) {
            *pREG_PINT3_REQ |= (0x1 << i);  // Clear interrupt
            _portD_Callbacks[i]();
        }
    }
}
void _PINT4_Handler (uint32_t iid, void *handlerArg)
{
    int i;
    for (i=0;i<16;i++) {
        // Check to see if we have an interrupt pending and it's one we have a
        // call back for
    	if (*pREG_PINT4_REQ & (0x1 << i) && _portE_Callbacks[i] != NULL) {
    		*pREG_PINT4_REQ |= (0x1 << i);  // Clear interrupt
    		_portE_Callbacks[i]();
    	}
    }
}
void _PINT5_Handler (uint32_t iid, void *handlerArg)
{
    int i;
    for (i=0;i<16;i++) {
        // Check to see if we have an interrupt pending and it's one we have a
        // call back for
        if (*pREG_PINT5_REQ & (0x1 << i) && _portF_Callbacks[i] != NULL) {
            *pREG_PINT5_REQ |= (0x1 << i);  // Clear interrupt
            _portF_Callbacks[i]();
        }
    }
}

// Sets up the simple GPIO pin interrupt framework 
void _setupPinInterrupts() {

    int i;

    // For the interrupts, we'll pass a pointer for the pin position that
    // originated the interrupt
    for (i=0;i<16;i++) {
        _portA_Callbacks[i] = NULL;
        _portB_Callbacks[i] = NULL;
        _portC_Callbacks[i] = NULL;
        _portD_Callbacks[i] = NULL;
        _portE_Callbacks[i] = NULL;
        _portF_Callbacks[i] = NULL;
    }

}

// ARDUINO FUNCTION LOW to trigger the interrupt whenever the pin is low,
// RISING to trigger when the pin goes from low to high, FALLING for when the
// pin goes from high to low. Note - there is no support for the CHANGE mode
// since the processor doesn't support both edge interrupts
void attachInterrupt(const uint32_t portpin,void (*callback) (void), int mode) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((portpin >> 16) & 0xF);
    uint16_t pinNumber = (portpin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    switch (port) {
        case ADI_GPIO_PORT_A:
            *pREG_PORTA_INEN_SET = pinMask;
            *pREG_PORTA_DIR_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_B:
            *pREG_PORTB_INEN_SET = pinMask;
            *pREG_PORTB_DIR_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_C:
            *pREG_PORTC_INEN_SET = pinMask;
            *pREG_PORTC_DIR_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_D:
            *pREG_PORTD_INEN_SET = pinMask;
            *pREG_PORTD_DIR_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_E:
            *pREG_PORTE_INEN_SET = pinMask;
            *pREG_PORTE_DIR_CLR = pinMask;
            // Set up edge triggered interrupts for port E
            if (mode == RISING || mode == FALLING) {
                *pREG_PINT4_EDGE_SET = pinMask;
                if      (mode == RISING) *pREG_PINT4_INV_CLR = pinMask;
                else if (mode == FALLING) *pREG_PINT4_INV_SET = pinMask;
            }
            // Set up level triggered interrupts for port E
            else if (mode == LOW) {
                *pREG_PINT4_EDGE_CLR = pinMask;     // Clear edge interrupt
                *pREG_PINT4_INV_SET = pinMask;      // Invert pin for active low
            }

            // Assign PINT4 to PORT E
            *pREG_PINT4_ASSIGN = 0x0000;
            *pREG_PINT4_MSK_SET = pinMask;

            _portE_Callbacks[pinNumber] = callback;
            adi_int_InstallHandler (INTR_PINT4_BLOCK, _PINT4_Handler, 0, true);

            break;
        case ADI_GPIO_PORT_F:
            *pREG_PORTF_INEN_SET = pinMask;
            *pREG_PORTF_DIR_CLR = pinMask;
            // Set up edge triggered interrupts for port E
            if (mode == RISING || mode == FALLING) {
                *pREG_PINT5_EDGE_SET = pinMask;
                if      (mode == RISING) *pREG_PINT5_INV_CLR = pinMask;
                else if (mode == FALLING) *pREG_PINT5_INV_SET = pinMask;
            }
            // Set up level triggered interrupts for port E
            else if (mode == LOW) {
                *pREG_PINT5_EDGE_CLR = pinMask;     // Clear edge interrupt
                *pREG_PINT5_INV_SET = pinMask;      // Invert pin for active low
            }

            // Assign PINT4 to PORT E
            *pREG_PINT5_ASSIGN = 0x0000;
            *pREG_PINT5_MSK_SET = pinMask;

            _portF_Callbacks[pinNumber] = callback;
            adi_int_InstallHandler (INTR_PINT5_BLOCK, _PINT5_Handler, 0, true);

            break;
        default:    break; // TODO - trap illegal input
    }
}

// ARDUINO FUNCTION
// Masks the interrupt and detaches callback function
void detachInterrupt(const uint32_t portpin) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((portpin >> 16) & 0xF);
    uint16_t pinNumber = (portpin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

     switch (port) {
        case ADI_GPIO_PORT_A:
            _portA_Callbacks[pinNumber] = NULL;
            *pREG_PINT0_MSK_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_B:
            _portB_Callbacks[pinNumber] = NULL;
            *pREG_PINT1_MSK_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_C:
            _portC_Callbacks[pinNumber] = NULL;
            *pREG_PINT2_MSK_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_D:
            _portD_Callbacks[pinNumber] = NULL;
            *pREG_PINT3_MSK_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_E:
            _portE_Callbacks[pinNumber] = NULL;
            *pREG_PINT4_MSK_CLR = pinMask;
            break;
        case ADI_GPIO_PORT_F:
            _portF_Callbacks[pinNumber] = NULL;
            *pREG_PINT5_MSK_CLR = pinMask;
            break;
        default:    break; // TODO - trap illegal input            
    }

}

// ARDUINO FUNCTION
// Sets the mode for different pins to INPUT or OUTPUT
// TODO - add support for open drain
void pinMode(const uint32_t portpin, uint8_t mode) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((portpin >> 16) & 0xF);
    uint16_t pinNumber = (portpin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    volatile uint32_t * pREG_PORT_DIR_SET, * pREG_PORT_DIR_CLR;

    switch (port) {
        case ADI_GPIO_PORT_A:
            pREG_PORT_DIR_SET = pREG_PORTA_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTA_DIR_CLR;
            break;
        case ADI_GPIO_PORT_B:
            pREG_PORT_DIR_SET = pREG_PORTB_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTB_DIR_CLR;
            break;
        case ADI_GPIO_PORT_C:
            pREG_PORT_DIR_SET = pREG_PORTC_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTC_DIR_CLR;
            break;
        case ADI_GPIO_PORT_D:
            pREG_PORT_DIR_SET = pREG_PORTD_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTD_DIR_CLR;
            break;
        case ADI_GPIO_PORT_E:
            pREG_PORT_DIR_SET = pREG_PORTE_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTE_DIR_CLR;
            break;
        case ADI_GPIO_PORT_F:
            pREG_PORT_DIR_SET = pREG_PORTF_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTF_DIR_CLR;
            break;
        case ADI_GPIO_PORT_G:
            pREG_PORT_DIR_SET = pREG_PORTG_DIR_SET;
            pREG_PORT_DIR_CLR = pREG_PORTG_DIR_CLR;
            break;
        default:    break; // TODO - trap illegal input
    }

    if (mode == OUTPUT) *pREG_PORT_DIR_SET = pinMask;
    else                *pREG_PORT_DIR_CLR = pinMask;
}


// ARDUINO FUNCTION
// Writes a value to a given pin
void digitalWrite(const uint32_t portpin, uint8_t value) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((portpin >> 16) & 0xF);
    uint16_t pinNumber = (portpin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    volatile uint32_t * pREG_PORT_DATA_SET, * pREG_PORT_DATA_CLR;

    switch (port) {
        case ADI_GPIO_PORT_A:
            pREG_PORT_DATA_SET = pREG_PORTA_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTA_DATA_CLR;
            break;
        case ADI_GPIO_PORT_B:
            pREG_PORT_DATA_SET = pREG_PORTB_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTB_DATA_CLR;
            break;
        case ADI_GPIO_PORT_C:
            pREG_PORT_DATA_SET = pREG_PORTC_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTC_DATA_CLR;
            break;
        case ADI_GPIO_PORT_D:
            pREG_PORT_DATA_SET = pREG_PORTD_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTD_DATA_CLR;
            break;
        case ADI_GPIO_PORT_E:
            pREG_PORT_DATA_SET = pREG_PORTE_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTE_DATA_CLR;
            break;
        case ADI_GPIO_PORT_F:
            pREG_PORT_DATA_SET = pREG_PORTF_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTF_DATA_CLR;
            break;
        case ADI_GPIO_PORT_G:
            pREG_PORT_DATA_SET = pREG_PORTG_DATA_SET;
            pREG_PORT_DATA_CLR = pREG_PORTG_DATA_CLR;
            break;            
        default:    break; // TODO - trap illegal input
    }

    if (value == HIGH) *pREG_PORT_DATA_SET = pinMask;
    else               *pREG_PORT_DATA_CLR = pinMask;
}

// Reads the value of a given pin
int digitalRead(const uint32_t portpin) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((portpin >> 16) & 0xF);
    uint16_t pinNumber = (portpin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    volatile uint32_t * pREG_PORT_DATA;

    switch (port) {
        case ADI_GPIO_PORT_A:   pREG_PORT_DATA = pREG_PORTA_DATA; break;
        case ADI_GPIO_PORT_B:   pREG_PORT_DATA = pREG_PORTB_DATA; break;
        case ADI_GPIO_PORT_C:   pREG_PORT_DATA = pREG_PORTC_DATA; break;
        case ADI_GPIO_PORT_D:   pREG_PORT_DATA = pREG_PORTD_DATA; break;
        case ADI_GPIO_PORT_E:   pREG_PORT_DATA = pREG_PORTE_DATA; break;
        case ADI_GPIO_PORT_F:   pREG_PORT_DATA = pREG_PORTF_DATA; break;
        case ADI_GPIO_PORT_G:   pREG_PORT_DATA = pREG_PORTG_DATA; break;
        default:    break; // TODO - trap illegal inputAR = pREG_PORTE_DATA_CLEAR;
    }

    if (*pREG_PORT_DATA & pinMask) return 1;
    else return 0;
}

// Toggles a pin (this is not a standard Arduino function)
void digitalToggle(const uint32_t portpin) {

    ADI_GPIO_PORT port = (ADI_GPIO_PORT) ((portpin >> 16) & 0xF);
    uint16_t pinNumber = (portpin & 0x001F);
    uint32_t pinMask = (uint32_t) (1 << pinNumber);

    volatile uint32_t * pREG_PORT_DATA_TGL;

    switch (port) {
        case ADI_GPIO_PORT_A:   pREG_PORT_DATA_TGL = pREG_PORTA_DATA_TGL; break;
        case ADI_GPIO_PORT_B:   pREG_PORT_DATA_TGL = pREG_PORTB_DATA_TGL; break;
        case ADI_GPIO_PORT_C:   pREG_PORT_DATA_TGL = pREG_PORTC_DATA_TGL; break;
        case ADI_GPIO_PORT_D:   pREG_PORT_DATA_TGL = pREG_PORTD_DATA_TGL; break;
        case ADI_GPIO_PORT_E:   pREG_PORT_DATA_TGL = pREG_PORTE_DATA_TGL; break;
        case ADI_GPIO_PORT_F:   pREG_PORT_DATA_TGL = pREG_PORTF_DATA_TGL; break;
        case ADI_GPIO_PORT_G:   pREG_PORT_DATA_TGL = pREG_PORTG_DATA_TGL; break;
        default:    break; // TODO - trap illegal 
    }

    *pREG_PORT_DATA_TGL = pinMask;

}

////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
//  HADC Support
//******************************************************************************

// Performs an analog read of a given HADC channel
// Can be mapped to either continuous mode or blocking mode
float analogReadFloat(uint8_t pin) {
	if (pin >= HADC_CHANNELS) return -1;

    return _HADC_ChannelData_Float[pin];
//    return _analogRead_reg_continuous(pin);
}

// ARDUINO FUNCTION
// 10 bit ADC range
int analogRead(uint8_t pin) {
	if (pin >= HADC_CHANNELS) return -1;

    // Expand to a 10-bit integer (similar to Arduino) for compatibility with
    // existing Arduino libraries
	return (int) _HADC_ChannelData_Float[pin]*1024;
}

////////////////////////////////////////////////////////////////////////////////

