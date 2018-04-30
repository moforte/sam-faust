/********************************************************************************
Copyright(c) 2012-2015 Analog Devices, Inc. All Rights Reserved.

This software is proprietary.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

#ifndef SPI_H
#define SPI_H

#include "flash.h"

struct spi_ctlr
{
	int (*spi_open)(int);
	int (*spi_close)(void);
	int (*spi_config)(const struct flash_info *fi);
	int (*spi_enable)(void);
	int (*spi_disable)(void);
	int (*spi_send)(uint8_t *buf, int count);
	int (*spi_recv)(uint8_t *buf, int count);
	int (*spi_recv_until)(int (*condition)(const uint8_t));
	int (*spi_set_mode)(spi_mode_t mode);
	int (*spi_select_slave)(int slave_no);
};

extern const struct spi_ctlr *spi_ctlr;

extern const struct spi_ctlr adi_spi3_ctlr;

extern int spi_open(int);
extern int spi_close(void);
extern int spi_config(const struct flash_info *);
extern int spi_enable(void);
extern int spi_disable(void);
extern int spi_send(uint8_t *, int);
extern int spi_recv(uint8_t *, int);
extern int spi_recv_until(int (*condition)(const uint8_t));
extern int spi_set_mode(spi_mode_t mode);
extern int spi_select_slave(int);

extern int unpack_dual(uint8_t *buf, uint8_t *unpacked_buf, int count, int start_on_mosi);
extern int unpack_quad(uint8_t *buf, uint8_t *unpacked_buf, int count, int start_on_mosi);

#endif /* SPI_H */
