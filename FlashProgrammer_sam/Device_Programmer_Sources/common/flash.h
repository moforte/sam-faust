/********************************************************************************
Copyright(c) 2012-2015 Analog Devices, Inc. All Rights Reserved.

This software is proprietary.  By using this software you agree
to the terms of the associated Analog Devices License Agreement.

*********************************************************************************/

#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

typedef enum {
	STANDARD = 1,
	DUAL_OUTPUT = 2,
	QUAD_OUTPUT = 4,
	QUAD_INPUT = 4,
	DUAL_IO = 8,
	QUAD_IO = 16,
} spi_mode_t;

typedef enum {
	ERASE_4KB,
	ERASE_32KB,
	ERASE_64KB,
	ERASE_CHIP,
} erase_type_t;

struct erase_block_region
{
	uint32_t block_size;
	int number_of_blocks;
};

struct flash_info
{
	const char *name;
	const char *mname;
	uint8_t mid;
	uint8_t did;
	uint8_t memory_type_id;
	uint8_t capacity_id;
	int modes;

	/* Geometry */
	uint32_t size;
	int number_of_regions;
	struct erase_block_region *erase_block_regions;

	/* The max clock frequency (MHz) */
	uint32_t max_freq;
	/* The max clock frequency for quad instructions (MHz) */
	uint32_t max_quad_freq;
	/* The max clock frequency for Read Data instruction (MHz) */
	uint32_t max_read_data_freq;

	int cpha;
	int cpol;
	int lsb_first;
	int start_on_mosi;

	uint32_t frequency;
	spi_mode_t current_mode;

	int (*flash_open)(struct flash_info *fi);
	int (*flash_close)(struct flash_info *fi);

	int (*flash_read_mid_did)(struct flash_info *fi, uint8_t *mid, uint8_t *did);
	int (*flash_read_uid)(const struct flash_info *fi, uint64_t *uid);
	int (*flash_read_jedec_id)(const struct flash_info *fi, uint8_t *mid,
			uint8_t *memory_type_id, uint8_t *capacity_id);
	int (*flash_read_status1)(const struct flash_info *fi, uint8_t *status1);
	int (*flash_read_status2)(const struct flash_info *fi, uint8_t *status2);
	int (*flash_write_status)(const struct flash_info *fi, uint8_t status1, uint8_t status2);
	int (*flash_enable_quad_mode)(const struct flash_info *fi);
	int (*flash_disable_quad_mode)(const struct flash_info *fi);
	int (*flash_read)(const struct flash_info *fi, uint32_t addr, uint8_t *buf, int size);
	int (*flash_write_enable)(const struct flash_info *fi);
	int (*flash_write_disable)(const struct flash_info *fi);
	int (*flash_erase)(const struct flash_info *fi, uint32_t addr, int size);
	int (*flash_erase_chip)(const struct flash_info *fi);
	int (*flash_program)(struct flash_info *fi, uint32_t addr, const uint8_t *buf, int size);
	int (*flash_reset)(const struct flash_info *fi);
};

extern struct flash_info *flash_info;

extern int flash_name(const struct flash_info *fi, const char **name);
extern int flash_company(const struct flash_info *fi, const char **company);
extern int flash_open(struct flash_info *fi);
extern int flash_close(struct flash_info *fi);
extern int flash_read_mid_did(struct flash_info *fi, uint8_t *mid, uint8_t *did);
extern int flash_read_uid(const struct flash_info *fi, uint64_t *uid);
extern int flash_read_jedec_id(const struct flash_info *fi, uint8_t *mid,
		uint8_t *memory_type_id, uint8_t *capacity_id);
extern int flash_read(const struct flash_info *fi, uint32_t addr, uint8_t *buf, int size);
extern int flash_write_enable(const struct flash_info *fi);
extern int flash_write_disable(const struct flash_info *fi);
extern int flash_erase(const struct flash_info *fi, uint32_t addr, int size);
extern int flash_erase_chip(const struct flash_info *fi);
extern int flash_program(struct flash_info *fi, uint32_t addr, const uint8_t *buf, int size);
extern int flash_reset(const struct flash_info *fi);

extern int flash_set_mode(struct flash_info *fi, spi_mode_t mode);
extern int flash_enable_quad_mode(const struct flash_info *fi);
extern int flash_disable_quad_mode(const struct flash_info *fi);
extern int flash_read_status1(const struct flash_info *fi, uint8_t *status1);
extern int flash_read_status2(const struct flash_info *fi, uint8_t *status2);
#define flash_read_status flash_read_status1

extern int assign_instruction(const struct flash_info *fi, uint8_t *buf, uint8_t insn, int *count);
extern int assign_address(const struct flash_info *fi, uint8_t *buf, uint32_t addr, int *count);
extern int select_flash(void);
extern int unselect_flash(void);
extern int generic_write_enable(const struct flash_info *fi, uint8_t insn);
extern int generic_write_disable(const struct flash_info *fi, uint8_t insn);
extern int generic_read_jedec_id(const struct flash_info *fi, uint8_t insn, uint8_t *mid, uint8_t *memory_type_id, uint8_t *capacity_id);

extern int flash_num_of_sectors(const struct flash_info *fi, int *num);
extern int flash_sector_start_end(const struct flash_info *fi, int block, uint32_t *start, uint32_t *end);
extern int flash_erase_sector(const struct flash_info *fi, int block);
extern int flash_sector_number(const struct flash_info *fi, uint32_t addr, int *block);

#endif /* FLASH_H */
