#include "sam.h"

#include <stdint.h>

#include "nds36p_driver.h"

#define SIZEOF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

static struct PINOUT pinouts[1+512+2]; // Activate + read 512 words + burst stop + precharge
static uint16_t pinout_count;

void nds36p_prepare(struct CMD *cmds, uint16_t cmd_count)
{
	uint16_t i, j;
	for (i = 0, j = 0; i < cmd_count; i++) {
		pinouts[i+j].address = cmds[i].address << DRAM_SHIFT_ADDRESS;
		pinouts[i+j].control = cmds[i].flags << DRAM_SHIFT_CONTROL;
		
		if (cmds[i].is_write) {
			for (j = 0; j < cmds[i].len; j++) {
				pinouts[i+j].data = *(cmds[i].data + j);

				if (j > 0) {
					pinouts[i+j].control = 14 << DRAM_SHIFT_CONTROL; // Hard coded NOP operation
				}
			}
		} else if (cmds[i].is_read) {
			for (j = 1; j <= (cmds[i].len+1); j++) {
				pinouts[i+j].control = 14 << DRAM_SHIFT_CONTROL; // Hard coded NOP operation
			}
		}
	}
	pinout_count = i+j;
}

__attribute__((optimize("O3"))) void nds36p_execute_write()
{
	for (uint16_t i = 0; i < pinout_count; i++) {
		// Set output pins
		REG_PIOA_SODR = pinouts[i].data;
		REG_PIOB_SODR = pinouts[i].address;
		REG_PIOB_SODR = pinouts[i].control;

		while (!(REG_TC0_SR0 & TC_SR_COVFS)); // Wait until the clock period is over
		REG_PIOA_SODR = DRAM_PIN_CLOCK; // Set clock pin high
		while (!(REG_TC0_SR0 & TC_SR_CPAS)); // Wait until half of the clock period is over
		REG_PIOA_CODR = DRAM_PIN_CLOCK; // Set clock pin low

		// Clear output pins
		REG_PIOA_CODR = pinouts[i].data;
		REG_PIOB_CODR = pinouts[i].address;
		REG_PIOB_CODR = pinouts[i].control;
	}
}

__attribute__((optimize("O3"))) void nds36p_execute_read()
{
	for (uint16_t i = 0; i < pinout_count; i++) {
		// Set output pins
		REG_PIOB_SODR = pinouts[i].address;
		REG_PIOB_SODR = pinouts[i].control;

		while (!(REG_TC0_SR0 & TC_SR_COVFS)); // Wait until the clock period is over
		REG_PIOA_SODR = DRAM_PIN_CLOCK; // Set clock pin high
		while (!(REG_TC0_SR0 & TC_SR_CPAS)); // Wait until half of the clock period is over
		REG_PIOA_CODR = DRAM_PIN_CLOCK; // Set clock pin low

		// Read data pins
		pinouts[i].data = REG_PIOA_PDSR;

		// Clear output pins
		REG_PIOB_CODR = pinouts[i].address;
		REG_PIOB_CODR = pinouts[i].control;
	}
}