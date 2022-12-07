
#include "fw_timers.h"

static callback functions[NUMBER_OF_HARDWARE_TIMERS];

void fw_timer_init(uint32 compare, callback func)
{
	rtiEnableNotification(compare);
	_enable_IRQ();

	functions[compare] = func;
}

void fw_timer_counter(uint32 counter, uint8_t start)
{	
	start ? rtiStartCounter(counter) : rtiStopCounter(counter);
}

void rtiNotification(uint32 notification)
{
	if ( 0 < notification && notification < NUMBER_OF_HARDWARE_TIMERS)
	{
		functions[notification]();
	}
}
