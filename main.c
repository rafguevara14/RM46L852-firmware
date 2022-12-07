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

volatile uint32_t ticks = 0; // used as a global clock with resolution of HW_TIMER0_PERIOD_MS (1000)

volatile bool print_flag = false; // IRQ flag to signal main loop printing 

void global_clock()
{
	if (ticks % MS_TO_HW_TICKS(1000, HW_TIMER0_PERIOD_MS) == 0)
	{
		#ifndef USE_BUTTONS 
		fw_gpio_set(USER_LEDA, FW_GPIO_TOGGLE);
		fw_gpio_set(USER_LEDB, FW_GPIO_TOGGLE);
		#endif 
	}

	if (ticks % MS_TO_HW_TICKS(2000, HW_TIMER0_PERIOD_MS) == 0)
	{
		print_flag = true;
	}

	ticks++;
}


int main(void)
{
	/*
	Enable default halcogen configurations; as much as possible is done in code. 
	Calling this anywhere other than the beginning of the program may overwrite 
	confiugurations set in the user code.
	*/
	halcogen_init();

	/* Initialize hardware according to hardware_peripherals.h */
	fw_timer_init(HW_TIMER_COMPARE0, global_clock);
	fw_adc_init();
	PCInit(9600);

	/* Initialize buttons */
	fw_gpio_button_init(FW_GPIO_PULLDOWN, FW_GPIO_PULLUP);

	/* Initialize leds */
	fw_gpio_led_init();

	/* Set leds to opposite values */
	fw_gpio_set(USER_LEDA, FW_GPIO_OFF);
	fw_gpio_set(USER_LEDB, FW_GPIO_ON);

	/* start hardware timer */
	fw_timer_counter(HW_TIMER_COUNTER0, true);

	while(1)
	{
		if (print_flag)
		{ 
			uint16_t value = fw_poll_light_sensor();
			
			fwprintf("Hello World! (%d) (%d) [%d] [%d]", fw_gpio_get(USER_SWITCHA) , fw_gpio_get(USER_SWITCHB), value, ticks);

			print_flag = false;
		}
	}

    return 0;
}


