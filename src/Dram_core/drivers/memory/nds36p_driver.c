#include <string.h>
#include <stdint.h>

#include "sam.h"

#include "nds36p_commands.h"
#include "nds36p_driver.h"
#include "project_specific.h"

#define SIZEOF_ARRAY(x) (sizeof(x) / sizeof(x[0]))

static const struct control_pin nop = {
	.cs = 0,
	.ras = 1,
	.cas = 1,
	.we = 1
};

static struct pinout pinouts[1+512+2]; // Activate + read 512 words + burst stop + precharge
static uint16_t pinout_count;

void nds36p_prepare(struct cmd *cmd, uint16_t cmd_count)
{
	memset(pinouts, 0, sizeof(pinouts));

	for (uint16_t i = 0, k = 0; i < cmd_count; i++, k++) {
		map_control_pins(&pinouts[k], cmd[i].control);
		map_address_pins(&pinouts[k], cmd[i].address);

		if (cmd[i].write) {
			map_data_pins(&pinouts[k++], cmd[i].data[0]);
			for (uint16_t j = 1; j < cmd[i].len; j++, k++) {
				map_control_pins(&pinouts[k], nop);
				map_data_pins(&pinouts[k], cmd[i].data[j]);
			}
			k--;
		} else if (cmd[i].read) {
			for (uint16_t j = 1; j < cmd[i].len; j++, k++) {
				map_control_pins(&pinouts[k], nop);
				pinouts[k].data = &cmd[i].data[j];
			}
			k--;
		}
	}
}

__attribute__((optimize("O3"))) void nds36p_execute_write()
{
	for (uint16_t i = 0; i < pinout_count; i++) {
		// Set output pins
		REG_PIOA_SODR = pinouts[i].a.reg;
		REG_PIOB_SODR = pinouts[i].b.reg;

		while (!(REG_TC0_SR0 & TC_SR_COVFS)); // Wait until the clock period is over
		REG_PIOC_SODR = 23; // Set clock pin high
		while (!(REG_TC0_SR0 & TC_SR_CPAS)); // Wait until half of the clock period is over
		REG_PIOC_CODR = 23; // Set clock pin low

		// Clear output pins
		REG_PIOA_CODR = pinouts[i].a.reg;
		REG_PIOB_CODR = pinouts[i].b.reg;
	}
}

__attribute__((optimize("O3"))) void nds36p_execute_read()
{
	for (uint16_t i = 0; i < pinout_count; i++) {
		// Set output pins
		REG_PIOA_SODR = pinouts[i].a.reg;
		REG_PIOB_SODR = pinouts[i].b.reg;

		while (!(REG_TC0_SR0 & TC_SR_COVFS)); // Wait until the clock period is over
		REG_PIOC_SODR = 23; // Set clock pin high
		while (!(REG_TC0_SR0 & TC_SR_CPAS)); // Wait until half of the clock period is over
		REG_PIOC_CODR = 23; // Set clock pin low

		if (pinouts[i].data != NULL) {
			// Read data pins
			pinouts[i].a.reg = REG_PIOA_PDSR;
			pinouts[i].b.reg = REG_PIOB_PDSR;
		} else {
			// Clear output pins
			REG_PIOA_CODR = pinouts[i].a.reg;
			REG_PIOB_CODR = pinouts[i].b.reg;
		}
	}

	// unmap_data_pins();
}