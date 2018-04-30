/********************************************************************************
Copyright(c) 2012-2015 Analog Devices, Inc. All Rights Reserved.

This software is proprietary.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

#include "flash.h"
#include "spi.h"

struct flash_info *flash_info;

int flash_name(const struct flash_info *fi, const char **name)
{
	*name = fi->name;
	return 0;
}

int flash_company(const struct flash_info *fi, const char **company)
{
	*company = fi->mname;
	return 0;
}

int flash_open(struct flash_info *fi)
{
	return fi->flash_open(fi);
}

int flash_close(struct flash_info *fi)
{
	return fi->flash_close(fi);
}

int flash_read_mid_did(struct flash_info *fi, uint8_t *mid, uint8_t *did)
{
	return fi->flash_read_mid_did(fi, mid, did);
}

int flash_read_uid(const struct flash_info *fi, uint64_t *uid)
{
	return fi->flash_read_uid(fi, uid);
}

int flash_read_jedec_id(const struct flash_info *fi, uint8_t *mid,
		uint8_t *memory_type_id, uint8_t *capacity_id)
{
	return fi->flash_read_jedec_id(fi, mid, memory_type_id, capacity_id);
}

int flash_read_status1(const struct flash_info *fi, uint8_t *status1)
{
	return fi->flash_read_status1(fi, status1);
}

int flash_read_status2(const struct flash_info *fi, uint8_t *status2)
{
	if (fi->flash_read_status2)
		return fi->flash_read_status2(fi, status2);
	else
		return -1;
}

int flash_write_status(struct flash_info *fi, uint8_t status1, uint8_t status2)
{
	return fi->flash_write_status(fi, status1, status2);
}

int flash_enable_quad_mode(const struct flash_info *fi)
{
	return fi->flash_enable_quad_mode(fi);
}

int flash_disable_quad_mode(const struct flash_info *fi)
{
	return fi->flash_disable_quad_mode(fi);
}

int flash_read(const struct flash_info *fi, uint32_t addr, uint8_t *buf, int size)
{
	return fi->flash_read(fi, addr, buf, size);
}

int flash_write_enable(const struct flash_info *fi)
{
	return fi->flash_write_enable(fi);
}

int flash_write_disable(const struct flash_info *fi)
{
	return fi->flash_write_disable(fi);
}

int flash_erase(const struct flash_info *fi, uint32_t addr, int size)
{
	return fi->flash_erase(fi, addr, size);
}

int flash_erase_chip(const struct flash_info *fi)
{
	return fi->flash_erase_chip(fi);
}

int flash_program(struct flash_info *fi, uint32_t addr, const uint8_t *buf, int size)
{
	return fi->flash_program(fi, addr, buf, size);
}

int flash_reset(const struct flash_info *fi)
{
	return fi->flash_reset(fi);
}

int flash_set_mode(struct flash_info *fi, spi_mode_t mode)
{
	spi_set_mode(mode);
	fi->current_mode = mode;

	return 0;
}

int assign_instruction(const struct flash_info *fi, uint8_t *buf, uint8_t insn, int *count)
{
	switch (fi->current_mode)
	{
	case STANDARD:
		buf[*count] = insn;
		*count += 1;
		break;

	case DUAL_OUTPUT:
	case DUAL_IO:
		unpack_dual(&insn, buf + *count, 1, fi->start_on_mosi);
		*count += 2;
		break;

	case QUAD_OUTPUT:
	case QUAD_IO:
		unpack_quad(&insn, buf + *count, 1, fi->start_on_mosi);
		*count += 4;
		break;

	default:
		return -1;
	}

	return 0;
}

int assign_address(const struct flash_info *fi, uint8_t *buf, uint32_t addr, int *count)
{
	uint8_t addr_buf[3];

	addr_buf[0] = (addr >> 16) & 0xff;
	addr_buf[1] = (addr >> 8) & 0xff;
	addr_buf[2] = addr & 0xff;

	switch (fi->current_mode)
	{
	case STANDARD:
	case DUAL_IO:
	case QUAD_IO:
		buf[*count] = addr_buf[0];
		buf[*count + 1] = addr_buf[1];
		buf[*count + 2] = addr_buf[2];
		*count += 3;
		break;

	case DUAL_OUTPUT:
		unpack_dual(addr_buf, buf + *count, 3, fi->start_on_mosi);
		*count += 6;
		break;

	case QUAD_OUTPUT:
		unpack_quad(addr_buf, buf + *count, 3, fi->start_on_mosi);
		*count += 12;
		break;

	default:
		return -1;
	}

	return 0;
}

int select_flash(void)
{
	spi_select_slave(1);
	spi_enable();
	return 0;
}

int unselect_flash(void)
{
	spi_disable();
	spi_select_slave(0);
	return 0;
}

int generic_write_enable(const struct flash_info *fi, uint8_t insn)
{
	uint8_t tbuf[1];
	int count;

	/* Only for STANDARD mode */
	if (fi->current_mode != STANDARD)
		return -1;

	select_flash();

	count = 0;
	assign_instruction(fi, tbuf, insn, &count);
	spi_send(tbuf, count);

	unselect_flash();

	return 0;
}

int generic_write_disable(const struct flash_info *fi, uint8_t insn)
{
	uint8_t tbuf[1];
	int count;

	/* Only for STANDARD mode */
	if (fi->current_mode != STANDARD)
		return -1;

	select_flash();

	count = 0;
	assign_instruction(fi, tbuf, insn, &count);
	spi_send(tbuf, count);

	unselect_flash();

	return 0;
}

int generic_read_jedec_id(const struct flash_info *fi, uint8_t insn,
		uint8_t *mid, uint8_t *memory_type_id, uint8_t *capacity_id)
{
	uint8_t tbuf[1];
	uint8_t rbuf[3];
	int count;

	/* Only for STANDARD mode */
	if (fi->current_mode != STANDARD)
		return -1;

	select_flash();

	count = 0;
	assign_instruction(fi, tbuf, insn, &count);
	spi_send(tbuf, count);

	spi_recv(rbuf, 3);
	*mid = rbuf[0];
	*memory_type_id = rbuf[1];
	*capacity_id = rbuf[2];

	unselect_flash();

	return 0;
}

/* This function has a bad name.  It really should be flash_num_of_blocks.  */
int flash_num_of_sectors(const struct flash_info *fi, int *num)
{
	int i;
	int total_blocks = 0;

	for (i = 0; i < fi->number_of_regions; i++)
		total_blocks += fi->erase_block_regions[i].number_of_blocks;

	*num = total_blocks;
	return 0;
}

/* This function has a bad name.  It really should be flash_block_start_end.  */
int flash_sector_start_end(const struct flash_info *fi, int block,
		uint32_t *start, uint32_t *end)
{
	uint32_t start_addr = 0;
	int i;

	if (block < 0)
		return -1;

	for (i = 0; i < fi->number_of_regions; i++)
	{
		if (block < fi->erase_block_regions[i].number_of_blocks)
		{
			*start = start_addr + fi->erase_block_regions[i].block_size * block;
			*end = *start + fi->erase_block_regions[i].block_size - 1;
			return 0;
		}
		block -= fi->erase_block_regions[i].number_of_blocks;
		start_addr += fi->erase_block_regions[i].block_size
				* fi->erase_block_regions[i].number_of_blocks;
	}

	return -1;
}

/* This function has a bad name.  It really should be flash_erase_block.  */
int flash_erase_sector(const struct flash_info *fi, int block)
{
	uint32_t start, end;
	int result;

	result = flash_sector_start_end(fi, block, &start, &end);
	if (result)
		return result;

	flash_erase(fi, start, end - start + 1);

	return 0;
}

/* This function has a bad name.  It really should be flash_block_number.  */
int flash_sector_number(const struct flash_info *fi, uint32_t addr, int *block)
{
	uint32_t region_start_addr;
	int block_num;
	int i;

	region_start_addr = 0;
	block_num = 0;

	for (i = 0; i < fi->number_of_regions; i++)
	{
		uint32_t region_size;

		region_size = fi->erase_block_regions[i].block_size
				* fi->erase_block_regions[i].number_of_blocks;
		if (addr >= region_start_addr
				&& addr < region_start_addr + region_size)
		{
			block_num += (addr - region_start_addr)
					/ fi->erase_block_regions[i].block_size;
			*block = block_num;
			return 0;
		}
		else
		{
			region_start_addr += region_size;
			block_num += fi->erase_block_regions[i].number_of_blocks;
		}
	}

	return -1;
}

