#ifndef STATES_H_
#define STATES_H_

#include <stdint.h>

#define STATE_IDLE		0
#define STATE_RECORDING 1
#define STATE_PLAYING	2

#define BUTTON_RECORD	29
#define BUTTON_PLAY		30
#define BUTTON_STOP		31

uint8_t state_current;
volatile uint8_t state_changed;
volatile uint8_t state_new;

void states_init();
void states_run();

#endif