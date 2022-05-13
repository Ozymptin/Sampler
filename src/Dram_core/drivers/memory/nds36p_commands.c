#include <stdint.h>

#include "nds36p_commands.h"

static const struct CMD bank_activate = {
	.cs = 0,
	.ras = 0,
	.cas = 1,
	.we = 1
};

static const struct CMD bank_precharge = {
	.cs = 0,
	.ras = 0,
	.cas = 1,
	.we = 0,

	.precharge = 0
};

static const struct CMD precharge_all = {
	.cs = 0,
	.ras = 0,
	.cas = 1,
	.we = 0,
	
	.precharge = 1
};

static const struct CMD read = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 1,
	
	.precharge = 0
};

static const struct CMD read_precharge = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 1,
	
	.precharge = 1
};

static const struct CMD write = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 0
};

static const struct CMD write_precharge = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 0,
	
	.precharge = 1
};

static const struct CMD modereg_set = {
	.cs = 0,
	.ras = 0,
	.cas = 0,
	.we = 0
};

static const struct CMD nop = {
	.cs = 0,
	.ras = 1,
	.cas = 1,
	.we = 1
};

static const struct CMD burst_stop = {
	.cs = 0,
	.ras = 1,
	.cas = 1,
	.we = 0
};

void nds36p_struct_create_bank_activate(struct CMD *cmd, uint8_t bank, uint16_t row)
{
	*cmd = bank_activate;
	cmd->bank = bank;
	cmd->address = row;
}

void nds36p_struct_create_bank_precharge(struct CMD *cmd, uint8_t bank)
{
	*cmd = bank_precharge;
	cmd->bank = bank;
}

void nds36p_struct_create_bank_precharge_all(struct CMD *cmd)
{
	*cmd = precharge_all;
}

void nds36p_struct_create_read(struct  CMD *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len)
{
	*cmd = read;
	cmd->bank = bank;
	cmd->address_col = col;
	cmd->is_read = 1;
	cmd->data = data;
	cmd->len = len;
}

void nds36p_struct_create_read_precharge(struct CMD *cmd, uint8_t bank, uint16_t col)
{
	*cmd = read_precharge;
	cmd->bank = bank;
	cmd->address_col = col;
}

void nds36p_struct_create_write(struct  CMD *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len)
{
	*cmd = write;
	cmd->bank = bank;
	cmd->address_col = col;
	cmd->is_write = 1;
	cmd->data = data;
	cmd->len = len;
}

void nds36p_struct_create_write_precharge(struct CMD *cmd, uint8_t bank, uint16_t col, uint16_t *data)
{
	*cmd = write_precharge;
	cmd->bank = bank;
	cmd->address_col = col;
	cmd->data = data;
}

void nds36p_struct_create_modereg_set(struct CMD *cmd, uint16_t settings)
{
	*cmd = modereg_set;
	cmd->address = settings;
}

void nds36p_struct_create_nop(struct CMD *cmd)
{
	*cmd = nop;
}

void nds36p_struct_create_burst_stop(struct CMD *cmd)
{
	*cmd = burst_stop;
}