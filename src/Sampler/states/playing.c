#include <stdint.h>

#include "states.h"
#include "util.h"

static uint32_t buffer_input[2][512];
static uint8_t buffer_filled[2];
static uint8_t buffer_ready[2];
static uint8_t buffer_current;

static uint8_t dac_ready;

void state_playing_run()
{
	if (!buffer_filled[buffer_current]) {
		// record(&buffer_input[buffer_current], 512, &buffer_filled[buffer_current]);
		buffer_filled[buffer_current] = 1;
	}
	
	for (uint8_t i = 0; i < sizeof(buffer_filled); i++) {
		if (buffer_filled[i] && !buffer_ready[i]) {
			// effect();
			buffer_ready[i] = 1;
		}
	}
	
	if (dac_ready) {
		if (buffer_ready[buffer_current]) {
			dac_ready = 0;
			// playback(buffer_input[buffer_current], 512, &dac_ready);
			buffer_current = !buffer_current;
		}
	}
}