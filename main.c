/*
 * main.c
 *
 *  Created on: Nov 26, 2022
 *      Author: rafgu
 */


#include "fw_gpio.h"
#include "fw_uart.h"
#include "fw_timers.h"
#include "fw_adc.h"

volatile uint32_t tick = 0;
volatile bool print_flag = false;
void global_clock()
{
	if (tick % MS_TO_HW_TICKS(1000, HW_TIMER0_PERIOD_MS) == 0)
	{
		#ifndef USE_BUTTONS 
		fw_gpio_set(USER_LEDA, FW_GPIO_TOGGLE);
		fw_gpio_set(USER_LEDB, FW_GPIO_TOGGLE);
		#endif 
	}

	if (tick % MS_TO_HW_TICKS(2000, HW_TIMER0_PERIOD_MS) == 0)
	{
		print_flag = true;
	}
	

	tick++;
}


int main(void)
{
	/* Initialize hardware according to hardware_peripherals.h */
	fw_timer_init(HW_TIMER_COMPARE0, global_clock);
	fw_adc_init();
	PCInit(9600);

	/* Set leds to opposite values */
	#ifndef USE_BUTTONS
	fw_gpio_led_init();
	fw_gpio_set(USER_LEDA, FW_GPIO_OFF);
	fw_gpio_set(USER_LEDB, FW_GPIO_ON);
	#else
	fw_gpio_button_init(FW_GPIO_PULLDOWN, FW_GPIO_PULLUP);
	#endif

	/* start hardware timer */
	fw_timer_counter(HW_TIMER_COUNTER0, true);

	while(1)
	{
		if (print_flag)
		{ 
			uint16_t value = fw_poll_light_sensor();
			
			#ifdef USE_BUTTONS 
			fwprintf("Hello World! (%d) (%d)", fw_gpio_get(USER_SWITCHA) , fw_gpio_get(USER_SWITCHB));
			#else
			fwprintf("Hello World! (%d) (%d)", value , tick);
			#endif

			print_flag = false;
		}
	}

    return 0;
}


