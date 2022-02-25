#include "sam.h"

#include "states.h"

void states_init()
{
	state_current = STATE_IDLE;
	state_changed = 0;
	state_new = STATE_IDLE;
}

void states_run()
{
	while (1) {
		switch (state_current) {
			case STATE_IDLE:
				if (state_changed) {
					state_current = state_new;
					state_changed = 0;
					break;
				}

				break;

			case STATE_RECORDING:
				if (state_changed) {
					// Disable DMA and ADC
					
					state_current = state_new;
					state_changed = 0;
					break;
				}

				// Enable spi slave and dma
				// Enable timer
				
				break;

			case STATE_PLAYING:
				if (state_changed) {
					// Disable DMA and DAC
									
					state_current = state_new;
					state_changed = 0;
					break;
				}
				break;
		}
	}
}

void PIOA_Handler()
{
	state_changed = 1;
	switch (REG_PIOA_ISR) {
		case (1<<BUTTON_RECORD):
			state_new = STATE_RECORDING;
			break;

		case (1<<BUTTON_PLAY):
			state_new = STATE_PLAYING;
			break;

		case (1<<BUTTON_STOP):
			state_new = STATE_IDLE;
			break;	
	}
}