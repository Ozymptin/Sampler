#ifndef NDS36p_COMMANDS_H_
#define NDS36p_COMMANDS_H_

#include <stdint.h>

struct control_pin {
	uint8_t cs : 1;
	uint8_t ras : 1;
	uint8_t cas : 1;
	uint8_t we : 1;
};

struct address_pin {
	union {
		struct {
			union {
				struct {
					uint8_t a0 : 1;
					uint8_t a1 : 1;
					uint8_t a2 : 1;
					uint8_t a3 : 1;
					uint8_t a4 : 1;
					uint8_t a5 : 1;
					uint8_t a6 : 1;
					uint8_t a7 : 1;
					uint8_t a8 : 1;
				};
				uint16_t address_lower : 9;
			};
			uint8_t a9 : 1;
			uint8_t precharge : 1; // A10
			uint16_t a11 : 1; // A11
			uint16_t a12 : 1; // A12
		};
		uint16_t address_full : 13;
	};
	uint8_t bank : 2;
};


struct cmd {
	struct control_pin control;
	struct address_pin address;

	uint8_t write : 1;
	uint8_t read : 1;

	uint16_t *data;
	uint16_t len;
};

void nds36p_struct_create_bank_activate(struct cmd *cmd, uint8_t bank, uint16_t row);
void nds36p_struct_create_bank_precharge(struct cmd *cmd, uint8_t bank);
void nds36p_struct_create_bank_precharge_all(struct cmd *cmd);
void nds36p_struct_create_write(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len);
void nds36p_struct_create_write_precharge(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len);
void nds36p_struct_create_read(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len);
void nds36p_struct_create_read_precharge(struct cmd *cmd, uint8_t bank, uint16_t col, uint16_t *data, uint16_t len);
void nds36p_struct_create_modereg_set(struct cmd *cmd, uint16_t settings);
void nds36p_struct_create_nop(struct cmd *cmd);
void nds36p_struct_create_burst_stop(struct cmd *cmd);

#endif