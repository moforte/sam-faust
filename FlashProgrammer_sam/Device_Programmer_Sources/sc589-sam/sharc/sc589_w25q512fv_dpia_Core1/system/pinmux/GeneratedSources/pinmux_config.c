/*
 **
 ** pinmux_config.c source file generated on April 20, 2016 at 14:21:25.	
 **
 ** Copyright (C) 2000-2016 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** SPI2 (CLK, D2, D3, MISO, MOSI, SEL1)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PC01, PC02, PC03, PC04, PC05, PC06
 */

#include <sys/platform.h>
#include <stdint.h>

#define SPI2_CLK_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<2))
#define SPI2_D2_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<8))
#define SPI2_D3_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<10))
#define SPI2_MISO_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<4))
#define SPI2_MOSI_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<6))
#define SPI2_SEL1_PORTC_MUX  ((uint16_t) ((uint16_t) 0<<12))

#define SPI2_CLK_PORTC_FER  ((uint16_t) ((uint16_t) 1<<1))
#define SPI2_D2_PORTC_FER  ((uint16_t) ((uint16_t) 1<<4))
#define SPI2_D3_PORTC_FER  ((uint16_t) ((uint16_t) 1<<5))
#define SPI2_MISO_PORTC_FER  ((uint16_t) ((uint16_t) 1<<2))
#define SPI2_MOSI_PORTC_FER  ((uint16_t) ((uint16_t) 1<<3))
#define SPI2_SEL1_PORTC_FER  ((uint16_t) ((uint16_t) 1<<6))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {
    /* PORTx_MUX registers */
    *pREG_PORTC_MUX = SPI2_CLK_PORTC_MUX | SPI2_D2_PORTC_MUX
     | SPI2_D3_PORTC_MUX | SPI2_MISO_PORTC_MUX | SPI2_MOSI_PORTC_MUX
     | SPI2_SEL1_PORTC_MUX;

    /* PORTx_FER registers */
    *pREG_PORTC_FER = SPI2_CLK_PORTC_FER | SPI2_D2_PORTC_FER
     | SPI2_D3_PORTC_FER | SPI2_MISO_PORTC_FER | SPI2_MOSI_PORTC_FER
     | SPI2_SEL1_PORTC_FER;
    return 0;
}

