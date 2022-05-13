#include <stdint.h>

#include "sam.h"

#include "nds36p_driver.h"

#define SIZEOF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

static struct PINOUT pinout[1+512+2]; // Activate + read 512 words + burst stop + precharge
static uint16_t pinout_count;

void nds36p_prepare(struct CMD *cmd, uint16_t cmd_count)
{
	if (cmd_count < SIZEOF_ARRAY(pinout)) {
		pinout_count = 0;
		return;
	}
	
	uint16_t i, j;
	for (i = 0, j = 0; i < cmd_count; i++) {
		pinout[i+j].address = cmd[i].address << DRAM_SHIFT_ADDRESS;
		pinout[i+j].control = cmd[i].flags << DRAM_SHIFT_CONTROL;
		
		if (cmd[i].is_write) {
			pinout[i].data = cmd[i].data[j];
			for (j = 1; j < cmd[i].len; j++) {
				pinout[i+j].data = cmd[i].data[j];
				pinout[i+j].control = 14 << DRAM_SHIFT_CONTROL; // Hard coded NOP operation
			}
		} else if (cmd[i].is_read) {
			for (j = 1; j < cmd[i].len; j++) {
				pinout[i+j].control = 14 << DRAM_SHIFT_CONTROL; // Hard coded NOP operation
			}
		}
	}
	pinout_count = i+j;
}

__attribute__((optimize("O3"))) void nds36p_execute_write()
{
	for (uint16_t i = 0; i < pinout_count; i++) {
		// Set output pins
		REG_PIOA_SODR = pinout[i].data;
		REG_PIOB_SODR = pinout[i].address;
		REG_PIOB_SODR = pinout[i].control;

		while (!(REG_TC0_SR0 & TC_SR_COVFS)); // Wait until the clock period is over
		REG_PIOA_SODR = DRAM_PIN_CLOCK; // Set clock pin high
		while (!(REG_TC0_SR0 & TC_SR_CPAS)); // Wait until half of the clock period is over
		REG_PIOA_CODR = DRAM_PIN_CLOCK; // Set clock pin low

		// Clear output pins
		REG_PIOA_CODR = pinout[i].data;
		REG_PIOB_CODR = pinout[i].address;
		REG_PIOB_CODR = pinout[i].control;
	}
}

__attribute__((optimize("O3"))) void nds36p_execute_read()
{
	for (uint16_t i = 0; i < pinout_count; i++) {
		// Set output pins
		REG_PIOB_SODR = pinout[i].address;
		REG_PIOB_SODR = pinout[i].control;

		while (!(REG_TC0_SR0 & TC_SR_COVFS)); // Wait until the clock period is over
		REG_PIOA_SODR = DRAM_PIN_CLOCK; // Set clock pin high
		while (!(REG_TC0_SR0 & TC_SR_CPAS)); // Wait until half of the clock period is over
		REG_PIOA_CODR = DRAM_PIN_CLOCK; // Set clock pin low

		// Read data pins
		pinout[i].data = REG_PIOA_PDSR;

		// Clear output pins
		REG_PIOB_CODR = pinout[i].address;
		REG_PIOB_CODR = pinout[i].control;
	}
}