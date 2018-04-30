/********************************************************************************
Copyright(c) 2014 Analog Devices, Inc. All Rights Reserved.

This software is proprietary.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

#ifndef _TARGET_H_
#define _TARGET_H_

/* Define macros used by adi_spi_bf6xx.c */

#define SPI_UNSELECT_SLAVE              do { *pREG_PORTC_DATA_SET = BITM_PORT_DATA_PX6; } while (0)
#define SPI_SELECT_SLAVE                do { *pREG_PORTC_DATA_CLR = BITM_PORT_DATA_PX6; } while (0)

#endif /* _TARGET_H_ */
