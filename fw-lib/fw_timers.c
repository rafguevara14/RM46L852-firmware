
#include "fw_timers.h"

static callback functions[3];

void fw_timer_init(uint32 compare, callback func)
{
	rtiInit();
	rtiEnableNotification(compare);
	_enable_IRQ();

	functions[compare] = func;
}

void fw_timer_counter(uint32 counter, uint8_t start)
{	
	if (start)
	{
		rtiStartCounter(counter); 
	}
	else
	{
		rtiStopCounter(counter);
	}
}

void rtiNotification(uint32 notification)
{
	if ( 0 < notification && notification < 3)
	{
		functions[notification]();
	}
}
