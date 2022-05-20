#ifndef NDS36p_COMMANDS_H_
#define NDS36p_COMMANDS_H_

#include <stdint.h>

struct CMD {
	uint8_t 
};

struct CMD {
	union {
		struct {
			uint8_t cs : 1;
			uint8_t ras : 1;
			uint8_t cas : 1;
			uint8_t we : 1;
			uint8_t bank : 2;
		};
		uint8_t flags;
	};

	union {
		struct {
			uint16_t address_col : 9; // A0-A8
			uint8_t anine : 1; // A9
			uint8_t precharge : 1; // A10
			uint8_t aeleven : 1; // A11
			uint8_t atwelve : 1; // A12
		};
		uint16_t address;
	};

	uint8_t is_write : 1;
	uint8_t is_read : 1;

	uint16_t *data;
	uint16_t len;
};

void nds36p_struct_create_bank_activate(struct CMD *cmd, uint8_t bank, uint16_t row);
void nds36p_struct_create_bank_precharge(struct CMD *cmd, uint8_t bank);
void nds36p_struct_create_bank_precharge_all(struct CMD *cmd);
void nds36p_struct_create_read(struct CMD *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len);
void nds36p_struct_create_read_precharge(struct CMD *cmd, uint8_t bank, uint16_t col);
void nds36p_struct_create_write(struct CMD *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len);
void nds36p_struct_create_write_precharge(struct CMD *cmd, uint8_t bank, uint16_t col, uint16_t *data);
void nds36p_struct_create_modereg_set(struct CMD *cmd, uint16_t settings);
void nds36p_struct_create_nop(struct CMD *cmd);
void nds36p_struct_create_burst_stop(struct CMD *cmd);

#endif