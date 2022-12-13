#ifndef FW_TIMERS_H
#define FW_TIMERS_H

#include "hardware_peripherals.h"

void fw_timer_init(uint32 compare, callback func);
void fw_timer_counter(uint32 counter, uint8_t start);

#endif
