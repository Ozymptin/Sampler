#include <stdint.h>

#include "nds36p_api.h"
#include "nds36p_commands.h"
#include "nds36p_driver.h"

#define SIZEOF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

#define ROWS 4096
#define COLLUMS 512
#define BANK_SIZE (ROWS * COLLUMS)
#define NUM_OF_BANKS 4

static void nds36p_write_page(uint8_t bank, uint16_t row, uint16_t col, uint16_t *data, uint16_t len)
{
	struct CMD cmds[4];

	nds36p_struct_create_bank_activate(&cmds[0], bank, row);
	nds36p_struct_create_write(&cmds[1], bank, col, data, len);
	nds36p_struct_create_burst_stop(&cmds[2]);
	nds36p_struct_create_bank_precharge(&cmds[3], bank);

	nds36p_prepare(cmds, SIZEOF_ARRAY(cmds));
	nds36p_execute_write();
}

static void nds36p_read_page(uint8_t bank, uint16_t row, uint16_t col, uint16_t *data, uint16_t len)
{
	struct CMD cmds[4];

	nds36p_struct_create_bank_activate(&cmds[0], bank, row);
	nds36p_struct_create_read(&cmds[1], bank, col, data, len);
	nds36p_struct_create_burst_stop(&cmds[2]);
	nds36p_struct_create_bank_precharge(&cmds[3], bank);

	nds36p_prepare(cmds, SIZEOF_ARRAY(cmds));
	nds36p_execute_read();
}

void nds36p_init()
{
	struct CMD cmd;
	nds36p_struct_create_modereg_set(&cmd, 4);

	nds36p_prepare(&cmd, 1);
	nds36p_execute_write();
}

void nds36p_rw_buffer(uint32_t loc, uint16_t *data, int16_t len, uint8_t rw)
{
	if ((loc + len) > (NUM_OF_BANKS * BANK_SIZE)) {
		return;
	}

	do {
		uint8_t bank;
		uint16_t loc_in_bank, row, col, bytes_left_in_row, bytes;

		bank = loc / BANK_SIZE;
		loc_in_bank = loc - (bank * BANK_SIZE);
		row = loc_in_bank / COLLUMS;
		col = loc_in_bank - (row * COLLUMS);
		
		bytes_left_in_row = COLLUMS - col;
		bytes = (len <= bytes_left_in_row ? len : bytes_left_in_row);

		if (rw) {
			nds36p_read_page(bank, row, col, data, bytes);
		} else {
			nds36p_write_page(bank, row, col, data, bytes);
		}

		loc += bytes;
		len -= bytes;
	} while (len > 0);
}