#ifndef FW_HARDWARE_PERIPHERALS_H
#define FW_HARDWARE_PERIPHERALS_H

#include "stdbool.h"

#include "gio.h"
#include "sci.h"
#include "rti.h"
#include "adc.h"
#include "het.h"
#include "mibspi.h"
#include "sys_vim.h"

typedef void (*callback)();

/*
*	Official schematic: https://www.ti.com/lit/df/sprr399/sprr399.pdf?ts=1614825263664
*/

void halcogen_init();

/*
*   SCI peripheral
*   Configure driver code generation: 
*   - Enable SCI driver
*/
#define PC_UART scilinREG

/*
*   GIO peripheral
*   Configure driver code generation: 
*   - Enable GIO driver
*/
#define USER_LEDA gioPORTB, 1
#define USER_LEDB gioPORTB, 2 // used as gpio interrupt for button. can only be changed in halcogen


/*
*   MIBSPI peripheral (as GIO)
*   Configure driver code generation: 
* 	- Go to MIBSPI Port tab
*   - Ensure the CS pins are set in GIO mode
*/
#define USER_SWITCHA mibspiPORT3, 0 
#define USER_SWITCHB mibspiPORT1, 4 

/*
*   ADC peripheral
*   Configure driver code generation: 
*   - Enable channel selection (ADC1 Group 1, Pin 6 pg 10)
*	- Enable Continuous Conversion
*	- Set FiFo size (1)
* 	https://www.youtube.com/watch?v=YOBWhFE0LZg
*/
#define LIGHT_REG adcREG1
#define LIGHT_SENSOR LIGHT_REG, adcGROUP1 
#define LIGHT_MAX_VAL 4095
#define LIGHT_REFERENCE_MV 3300
#define ADC_TO_VOLTAGE(VAL, MAX_BITS, MAX_MILLIVOLTS) (100*VAL / MAX_BITS) * (MAX_MILLIVOLTS / 100)


/*
*   RTI peripheral
*   Configure driver code generation: 
*   - Enable RTI driver
*	- Enable VIM interrupt compare block
*	- Set a desired compare period
*/
#define NUMBER_OF_HARDWARE_TIMERS 3
#define HW_TIMER0_PERIOD_MS 1
#define MS_TO_HW_TICKS(PERIOD_MS, TICK_PERIOD_MS) PERIOD_MS / TICK_PERIOD_MS
#define HW_TIMER_COMPARE0 rtiNOTIFICATION_COMPARE0
#define HW_TIMER_COUNTER0 rtiNOTIFICATION_COUNTER0

#endif
