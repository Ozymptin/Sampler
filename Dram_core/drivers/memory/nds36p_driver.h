#ifndef NDS36p_DRIVER_H_
#define NDS36p_DRIVER_H_

#include <stdint.h>

#include "nds36p_commands.h"

#define DRAM_CLOCK_SPEED	6000000

#define DRAM_PIN_CLOCK		4
#define DRAM_PIN_CS			5
#define DRAM_PIN_RAS		6
#define DRAM_PIN_CAS		7
#define DRAM_PIN_WE			8
#define DRAM_PIN_BANK		9

#define DRAM_SHIFT_ADDRESS	3
#define DRAM_SHIFT_CONTROL	5

struct PINOUT {
	uint32_t data;
	uint32_t address;
	uint32_t control;	
};

void nds36p_prepare(struct CMD *cmds, uint16_t count);
void nds36p_execute_write();
void nds36p_execute_read();

#endif