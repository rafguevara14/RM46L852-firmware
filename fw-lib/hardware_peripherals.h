#ifndef FW_HARDWARE_PERIPHERALS_H
#define FW_HARDWARE_PERIPHERALS_H

#include "gio.h"
#include "sci.h"
#include "rti.h"
#include "stdbool.h"

// https://www.ti.com/lit/df/sprr399/sprr399.pdf?ts=1614825263664

#define USER_LEDA gioPORTB, 1
#define USER_LEDB gioPORTB, 2

#define PC_UART scilinREG


/*
*   Configure driver code generation: 
*   - Enable RTI driver
*	- Enable VIM interrupt compare block
*	- Set a desired compare period
*/
#define HW_TIMER0_PERIOD_MS 1
#define MS_TO_HW_TICKS(PERIOD_MS, TICK_PERIOD_MS) PERIOD_MS / TICK_PERIOD_MS
#define HW_TIMER_COMPARE0 rtiNOTIFICATION_COMPARE0
#define HW_TIMER_COUNTER0 rtiNOTIFICATION_COUNTER0

#endif
