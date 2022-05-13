#include "states.h"

static volatile enum state state_current;

void states_init()
{
	state_current = STATE_IDLE;
}

void states_run()
{
	while (1) {
		switch (state_current) {
			case STATE_IDLE:
				while (state_current == STATE_IDLE) {
					
				}
				break;

			case STATE_RECORDING:
				while (state_current == STATE_RECORDING) {
					state_recording_run();
				}
				
				// cleanup
				break;

			case STATE_PLAYING:
				while (state_current == STATE_PLAYING) {
					state_playing_run();
				}
				
				// cleanup
				break;
		}
	}
}

void state_change(enum state new_state)
{
	state_current = new_state;
}