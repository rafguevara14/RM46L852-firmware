#ifndef FW_TIMERS_H
#define FW_TIMERS_H

#include "hardware_peripherals.h"

typedef void (*callback)();

void fw_timer_init(uint32 block, callback func);
void fw_timer_counter(uint32 block, uint8_t start);

#endif
