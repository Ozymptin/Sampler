#include <stdint.h>

#include "nds36p_commands.h"
#include "nds36p_driver.h"
#include "project_specific.h"

void map_control_pins(struct pinout *pinouts, struct control_pin input)
{
	pinouts->b.cs = input.cs;
	pinouts->a.ras = input.ras;
	pinouts->b.cas = input.cas;
	pinouts->b.we = input.we;
}

void map_address_pins(struct pinout *pinouts, union address_pin input)
{
	pinouts->b.a0 = input.a0;
	pinouts->b.a1 = input.a1;
	pinouts->b.a2 = input.a2;
	pinouts->b.a3 = input.a3;
	pinouts->b.a4 = input.a4;
	pinouts->b.a5 = input.a5;
	pinouts->b.a6 = input.a6;
	pinouts->b.a7 = input.a7;
	pinouts->b.a8 = input.a8;
	pinouts->b.a9 = input.a9;
	pinouts->a.a10 = input.precharge;
	pinouts->b.a11 = input.a11;
	pinouts->b.a12 = input.a12;
}

void map_data_pins(struct pinout *pinouts, uint16_t input)
{
	pinouts->b.dq0 = input & (1 << 0);
	pinouts->b.dq1 = input & (1 << 1);
	pinouts->b.dq2 = input & (1 << 2);
	pinouts->a.dq3 = input & (1 << 3);
	pinouts->b.dq4 = input & (1 << 4);
	pinouts->a.dq5 = input & (1 << 5);
	pinouts->b.dq6 = input & (1 << 6);
	pinouts->b.dq7 = input & (1 << 7);
	pinouts->b.dq8 = input & (1 << 8);
	pinouts->b.dq9 = input & (1 << 9);
	pinouts->a.dq10 = input & (1 << 10);
	pinouts->a.dq11 = input & (1 << 11);
	pinouts->a.dq12 = input & (1 << 12);
	pinouts->a.dq13 = input & (1 << 13);
	pinouts->a.dq14 = input & (1 << 14);
	pinouts->a.dq15 = input & (1 << 15);
}