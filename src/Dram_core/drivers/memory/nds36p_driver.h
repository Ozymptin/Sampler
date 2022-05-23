#ifndef NDS36p_DRIVER_H_
#define NDS36p_DRIVER_H_

#include <stdint.h>

#include "nds36p_commands.h"
#include "project_specific.h"

void nds36p_prepare(struct cmd *cmd, uint16_t count);
void nds36p_execute_write();
void nds36p_execute_read();

#endif