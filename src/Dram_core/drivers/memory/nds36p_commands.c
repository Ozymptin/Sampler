#include <stdint.h>

#include "nds36p_commands.h"

static const struct control_pin bank_activate = {
	.cs = 0,
	.ras = 0,
	.cas = 1,
	.we = 1
};

static const struct control_pin bank_precharge = {
	.cs = 0,
	.ras = 0,
	.cas = 1,
	.we = 0
};

static const struct control_pin precharge_all = {
	.cs = 0,
	.ras = 0,
	.cas = 1,
	.we = 0
};

static const struct control_pin write = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 0
};

static const struct control_pin write_precharge = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 0
};

static const struct control_pin read = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 1
};

static const struct control_pin read_precharge = {
	.cs = 0,
	.ras = 1,
	.cas = 0,
	.we = 1
};

static const struct control_pin modereg_set = {
	.cs = 0,
	.ras = 0,
	.cas = 0,
	.we = 0
};

static const struct control_pin nop = {
	.cs = 0,
	.ras = 1,
	.cas = 1,
	.we = 1
};

static const struct control_pin burst_stop = {
	.cs = 0,
	.ras = 1,
	.cas = 1,
	.we = 0
};

void nds36p_struct_create_bank_activate(struct cmd *cmd, uint8_t bank, uint16_t row)
{
	cmd->control = bank_activate;
	cmd->address.address_full = row;
	cmd->address.bank = bank;
}

void nds36p_struct_create_bank_precharge(struct cmd *cmd, uint8_t bank)
{
	cmd->control = bank_precharge;
	cmd->address.precharge = 0;
	cmd->address.bank = bank;
}

void nds36p_struct_create_bank_precharge_all(struct cmd *cmd)
{
	cmd->control = precharge_all;
	cmd->address.precharge = 1;
}

void nds36p_struct_create_write(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len)
{
	cmd->control = write;
	cmd->address.address_lower = col;
	cmd->address.precharge = 0;
	cmd->address.bank = bank;
	cmd->write = 1;
	cmd->data = data;
	cmd->len = len;
}

void nds36p_struct_create_write_precharge(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len)
{
	cmd->control = write_precharge;
	cmd->address.address_lower = col;
	cmd->address.precharge = 1;
	cmd->address.bank = bank;
	cmd->write = 1;
	cmd->data = data;
	cmd->len = len;
}

void nds36p_struct_create_read(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len)
{
	cmd->control = read;
	cmd->address.address_lower = col;
	cmd->address.precharge = 0;
	cmd->address.bank = bank;
	cmd->read = 1;
	cmd->data = data;
	cmd->len = len;
}

void nds36p_struct_create_read_precharge(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len)
{
	cmd->control = read_precharge;
	cmd->address.address_lower = col;
	cmd->address.precharge = 1;
	cmd->address.bank = bank;
	cmd->read = 1;
	cmd->data = data;
	cmd->len = len;
}

void nds36p_struct_create_modereg_set(struct cmd *cmd, uint16_t settings)
{
	cmd->control = modereg_set;
	cmd->address.address_full = settings;
}

void nds36p_struct_create_nop(struct cmd *cmd)
{
	cmd->control = nop;
}

void nds36p_struct_create_burst_stop(struct cmd *cmd)
{
	cmd->control = burst_stop;
}