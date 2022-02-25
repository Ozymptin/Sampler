#ifndef NDS36p_API_H_
#define NDS36p_API_H_

#include <stdint.h>

#define nds36p_write_buffer(loc, data, len) nds36p_rw_buffer((uint32_t) loc, (uint16_t *) data, (uint8_t) len, 0)
#define nds36p_read_buffer(loc, data, len) nds36p_rw_buffer((uint32_t) loc, (uint16_t *) data, (uint8_t) len, 1)

void nds36p_init();

void nds36p_rw_buffer(uint32_t loc, uint16_t *data, int16_t len, uint8_t read);

#endif