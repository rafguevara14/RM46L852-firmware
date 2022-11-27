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
	if (tick % MS_TO_HW_TICKS(1000, HW_TIMER0_PERIOD_MS) == 0)
	{
		fw_gpio_set(USER_LEDA, FW_GPIO_TOGGLE);
		fw_gpio_set(USER_LEDB, FW_GPIO_TOGGLE);
	}
	

	tick++;
}


int main(void)
{
	/* Initialize hardware according to hardware_peripherals.h */
	fw_timer_init(HW_TIMER_COMPARE0, global_clock);
	fw_gpio_init();
	PCInit(9600);

	/* Set leds to opposite values */
	fw_gpio_set(USER_LEDA, FW_GPIO_OFF);
	fw_gpio_set(USER_LEDB, FW_GPIO_ON);

	/* start hardware timer */
	fw_timer_counter(HW_TIMER_COUNTER0, true);

	while(1)
	{
        fwprintf("Hello World! (%d)", tick);
	}

    return 0;
}


