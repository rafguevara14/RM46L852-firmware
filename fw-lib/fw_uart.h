#ifndef FW_UART_H
#define FW_UART_H

#include "hardware_peripherals.h"

void PCInit(uint32 baud);
void fwprintf(const char* _format, ...);

#endif
