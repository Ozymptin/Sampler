#include <stdint.h>

union porta {
	struct {
		uint16_t reserved1 : 6;
		uint8_t DQ2 : 1;
		uint8_t DQ1 : 1;
		uint32_t reserved2 : 10;
		uint8_t DQ0 : 1;
	};
	uint32_t reg;
};

union portb {
	struct {
		uint16_t reserved1 : 6;
		uint8_t DQ2 : 1;
		uint8_t DQ1 : 1;
		uint32_t reserved2 : 10;
		uint8_t DQ0 : 1;
	};
	uint32_t reg;
};

union portc {
	struct {
		uint16_t reserved1 : 6;
		uint8_t DQ2 : 1;
		uint8_t DQ1 : 1;
		uint32_t reserved2 : 10;
		uint8_t DQ0 : 1;
	};
	uint32_t reg;
};


uint32_t map_data_pins(uint32_t input)
{
	union porta tmp;
	tmp.reg = 0;

	tmp.DQ0 = input & (1 << 0);
	tmp.DQ1 = input & (1 << 1);
	tmp.DQ2 = input & (1 << 2);

	return tmp.reg;
}

uint32_t map_address_pins(uint32_t input)
{
	union portb tmp;
	tmp.reg = 0;

	tmp.DQ0 = input & (1 << 0);
	tmp.DQ1 = input & (1 << 1);
	tmp.DQ2 = input & (1 << 2);

	return tmp.reg;
}

uint32_t map_control_pins(uint32_t input)
{
	union portc tmp;
	tmp.reg = 0;

	tmp.DQ0 = input & (1 << 0);
	tmp.DQ1 = input & (1 << 1);
	tmp.DQ2 = input & (1 << 2);

	return tmp.reg;
}