#ifndef STATES_H_
#define STATES_H_

enum state {
	STATE_IDLE,
	STATE_RECORDING,
	STATE_PLAYING
};

void states_init();
void states_run();

void state_change(enum state new_state);

void state_playing_run();
void state_recording_run();

#endif