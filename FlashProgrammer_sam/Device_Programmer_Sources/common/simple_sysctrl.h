#ifndef _SIMPLE_SYSCTRL_H
#define _SIMPLE_SYSCTRL_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#include <sys/platform.h>
#include <services/int/adi_int.h>

#include <services/gpio/adi_gpio.h>
#include <services/tmr/adi_tmr.h>
#include <services/pwr/adi_pwr.h>
#include <drivers/hadc/adi_hadc.h>

// Presets for various GPIOs, LEDs and PBs on SHARC SAM platform
#define DIY_SHIELD_LED_1			((ADI_GPIO_PORT_E << 16) + 12)
#define DIY_SHIELD_LED_2 			((ADI_GPIO_PORT_E << 16) + 13)
#define DIY_SHIELD_LED_3 			((ADI_GPIO_PORT_E << 16) + 14)
#define DIY_SHIELD_LED_4 			((ADI_GPIO_PORT_E << 16) + 15)

#define DIY_SHIELD_PB_1 			((ADI_GPIO_PORT_E << 16) + 8)
#define DIY_SHIELD_PB_2 			((ADI_GPIO_PORT_E << 16) + 9)
#define DIY_SHIELD_PB_3 			((ADI_GPIO_PORT_E << 16) + 10)
#define DIY_SHIELD_PB_4 			((ADI_GPIO_PORT_E << 16) + 11)

#define DIY_SHIELD_GPIO_0 			((ADI_GPIO_PORT_E << 16) + 0)
#define DIY_SHIELD_GPIO_1 			((ADI_GPIO_PORT_E << 16) + 1)
#define DIY_SHIELD_GPIO_2 			((ADI_GPIO_PORT_E << 16) + 2)
#define DIY_SHIELD_GPIO_3 			((ADI_GPIO_PORT_E << 16) + 3)
#define DIY_SHIELD_GPIO_4 			((ADI_GPIO_PORT_E << 16) + 4)
#define DIY_SHIELD_GPIO_5 			((ADI_GPIO_PORT_E << 16) + 5)
#define DIY_SHIELD_GPIO_6 			((ADI_GPIO_PORT_E << 16) + 6)
#define DIY_SHIELD_GPIO_7 			((ADI_GPIO_PORT_E << 16) + 7)

#define DIY_SHIELD_SPISEL_PMOD 	((ADI_GPIO_PORT_C << 16) + 7)
#define DIY_SHIELD_SPISEL_ADAF 	((ADI_GPIO_PORT_C << 16) + 12)
#define DIY_SHIELD_ADAFRUIT_LCD_DC ((ADI_GPIO_PORT_G << 16) + 0)

#define SAM_LED10 					((ADI_GPIO_PORT_D << 16) + 1)
#define SAM_LED11 					((ADI_GPIO_PORT_D << 16) + 2)
#define SAM_LED12 					((ADI_GPIO_PORT_D << 16) + 3)

#define SAM_PB1  					((ADI_GPIO_PORT_F << 16) + 0)
#define SAM_PB2  					((ADI_GPIO_PORT_F << 16) + 1)


// ADC Channels
#define DIY_SHIELD_ADC_POT1  (0)
#define DIY_SHIELD_ADC_POT2  (1)
#define DIY_SHIELD_ADC_POT3  (2)
#define DIY_SHIELD_ADC_4     (3)
#define DIY_SHIELD_ADC_5     (4)
#define DIY_SHIELD_ADC_6     (5)
#define DIY_SHIELD_ADC_7     (6)

// Clock presets for ADSP-2158x running at 450MHz
#define F_CPU      (450000000)
#define F_SYSSCLK  (225000000)  
#define F_SCK0     (112500000)
#define F_SCK1     (112500000)

// Arduino-style constants for setting GPIO
#define HIGH 				(1)
#define LOW  				(0)

#define INPUT 				(0)
#define OUTPUT 				(1)
#define INPUT_PULLUP 		(2)

#define CHANGE      		(1)
#define FALLING     		(2)
#define RISING      		(3)

#ifdef __cplusplus
extern "C"{
#endif

// Simple SysCtrl init function
void simple_sysctrl_init( bool, uint8_t );
void _setupPinInterrupts(void);

// Optional prototypes to use to re-create an Arduino-style framework
void setup(void);
void loop(void);

// Arduino-compatibile typedefs 
#define min(a,b) 	((a)<(b)?(a):(b))
#define max(a,b)	((a)>(b)?(a):(b))
#define abs(x) 		((x)>0?(x):-(x))

// Arduino-compatibile typedefs 
typedef unsigned int word;
typedef bool boolean;
typedef uint8_t byte;

// GPIO, interrupt and analog in functions
void 	pinMode(const uint32_t portpin, uint8_t mode);
void 	digitalWrite(const uint32_t portpin, uint8_t value);
int  	digitalRead(const uint32_t portpin);
void 	digitalToggle(const uint32_t portpin);

void 	attachInterrupt(const uint32_t portpin, void (*callback)(void), int mode);
void 	detachInterrupt(const uint32_t portpin);

int 	analogRead(uint8_t);
float 	analogReadFloat(uint8_t pin);

// Delay and timing functions
unsigned long millis(void);
void delay(unsigned long);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _SIMPLE_SYSCTRL_H
