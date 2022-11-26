/*
 * main.c
 *
 *  Created on: Nov 26, 2022
 *      Author: rafgu
 */


#include "fw_gpio.h"
#include "fw_uart.h"
#include "fw_timers.h"

volatile uint32_t tick = 0;
void global_clock()
{
	if (tick % MS_TO_HW_TICKS(100, HW_TIMER0_PERIOD_MS) == 0)
	{
		gioToggleBit(USER_LEDA);
	}
	tick++;
}


int main(void)
{
	fw_gpio_init();
	PCInit(9600);

	gioSetBit(USER_LEDA, 0);
	gioSetBit(USER_LEDB, 1);

	fw_timer_init(HW_TIMER_COMPARE0, global_clock, 1);
	
	_enable_IRQ();

	fw_timer_counter(HW_TIMER_COUNTER0, true);
	while(1)
	{
        fwprintf("Hello World! (%d)", tick);
	}



    return 0;
}


