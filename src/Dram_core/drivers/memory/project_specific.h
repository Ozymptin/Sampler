#ifndef PS_H_
#define PS_H_

#include <stdint.h>

#include "nds36p_driver.h"

union porta {
	struct {
		uint8_t ras : 1;
		uint8_t dq5 : 1;
		uint8_t dq3 : 1;
		uint16_t reserved1 : 1;
		uint8_t a10 : 1;
		uint16_t reserved2 : 7;
		uint8_t ba1 : 1;
		uint16_t reserved3 : 5;
		uint8_t dq15 : 1;
		uint8_t dq14 : 1;
		uint8_t dq13 : 1;
		uint16_t reserved4 : 3;
		uint8_t dq12 : 1;
		uint8_t dq11 : 1;
		uint8_t dq10 : 1;
	};
	uint32_t reg;
};

union portb {
	struct {
		uint16_t reserved1 : 6;
		uint8_t dq2 : 1;
		uint8_t dq1 : 1;
		uint8_t a2 : 1;
		uint8_t a8 : 1;
		uint8_t a9 : 1;
		uint8_t a11 : 1;
		uint8_t a12 : 1;
		uint8_t a0 : 1;
		uint8_t dq8 : 1;
		uint8_t dq9 : 1;
		uint8_t dq6 : 1;
		uint8_t dq4 : 1;
		uint8_t dq0 : 1;
		uint8_t a1 : 1;
		uint8_t cs : 1;
		uint8_t ba0 : 1;
		uint8_t a3 : 1;
		uint16_t reserved2 : 1;
		uint8_t a6 : 1;
		uint8_t a5 : 1;
		uint8_t we : 1;
		uint8_t cas : 1;
		uint8_t dq7 : 1;
		uint8_t a7 : 1;
		uint8_t a4 : 1;
	};
	uint32_t reg;
};

union portc {
	struct {
		uint16_t reserved : 9;
		uint16_t clk : 1;
	};
	uint32_t reg;
};

struct pinout {
	union porta a;
	union portb b;
	union portc c;
	uint16_t *data;
};

void map_control_pins(struct pinout *pinouts, struct control_pin input);
void map_address_pins(struct pinout *pinouts, struct address_pin input);
void map_data_pins(struct pinout *pinouts, uint16_t input);

#endif