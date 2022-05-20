#ifndef NDS36p_API_H_
#define NDS36p_API_H_

#include <stdint.h>

void nds36p_init();

void nds36p_rw_buffer(uint32_t loc, uint16_t *data, int16_t len, uint8_t rw);
void nds36p_write_buffer(uint32_t loc, uint16_t *data, int16_t len) { nds36p_rw_buffer(loc, data, len, 0); }
void nds36p_read_buffer(uint32_t loc, uint16_t *data, int16_t len)  { nds36p_rw_buffer(loc, data, len, 1); }

#endif