/********************************************************************************
Copyright(c) 2012-2015 Analog Devices, Inc. All Rights Reserved.

This software is proprietary.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

#include "spi.h"

const struct spi_ctlr *spi_ctlr;

int spi_open(int spi_no)
{
	return spi_ctlr->spi_open(spi_no);
}

int spi_close(void)
{
	return spi_ctlr->spi_close();
}

int spi_config(const struct flash_info *fi)
{
	return spi_ctlr->spi_config(fi);
}

int spi_enable(void)
{
	return spi_ctlr->spi_enable();
}

int spi_disable(void)
{
	return spi_ctlr->spi_disable();
}

int spi_send(uint8_t *buf, int count)
{
	return spi_ctlr->spi_send(buf, count);
}

int spi_recv(uint8_t *buf, int count)
{
	return spi_ctlr->spi_recv(buf, count);
}

int spi_recv_until(int (*condition)(const uint8_t))
{
	return spi_ctlr->spi_recv_until(condition);
}

int spi_set_mode(spi_mode_t mode)
{
	return spi_ctlr->spi_set_mode(mode);
}

int spi_select_slave(int slave_no)
{
	return spi_ctlr->spi_select_slave(slave_no);
}

int unpack_dual(uint8_t *buf, uint8_t *unpacked_buf, int count, int start_on_mosi)
{
	uint8_t unpack;
	int i;
	int shift = start_on_mosi ? 1 : 0;

	for (i = 0; i < count; i++)
	{
		unpack = ((buf[i] >> 7) & 1) << (6 + shift);
		unpack |= ((buf[i] >> 6) & 1) << (4 + shift);
		unpack |= ((buf[i] >> 5) & 1) << (2 + shift);
		unpack |= ((buf[i] >> 4) & 1) << shift;
		unpacked_buf[2 * i] = unpack;

		unpack = ((buf[i] >> 3) & 1) << (6 + shift);
		unpack |= ((buf[i] >> 2) & 1) << (4 + shift);
		unpack |= ((buf[i] >> 1) & 1) << (2 + shift);
		unpack |= (buf[i] & 1) << shift;
		unpacked_buf[2 * i + 1] = unpack;
	}

	return 0;
}

int unpack_quad(uint8_t *buf, uint8_t *unpacked_buf, int count, int start_on_mosi)
{
	uint8_t unpack;
	int i;
	int shift = start_on_mosi ? 1 : 0;

	for (i = 0; i < count; i++)
	{
		unpack = ((buf[i] >> 7) & 1) << (4 + shift);
		unpack |= ((buf[i] >> 6) & 1) << shift;
		unpacked_buf[4 * i] = unpack;

		unpack = ((buf[i] >> 5) & 1) << (4 + shift);
		unpack |= ((buf[i] >> 4) & 1) << shift;
		unpacked_buf[4 * i + 1] = unpack;

		unpack = ((buf[i] >> 3) & 1) << (4 + shift);
		unpack |= ((buf[i] >> 2) & 1) << shift;
		unpacked_buf[4 * i + 2] = unpack;

		unpack = ((buf[i] >> 1) & 1) << (4 + shift);
		unpack |= (buf[i] & 1) << shift;
		unpacked_buf[4 * i + 3] = unpack;
	}

	return 0;
}
