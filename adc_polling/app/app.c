/*
 * app.c
 *
 *  Created on: Mar 1, 2022
 *      Author: lucas
 */
#include <stdbool.h>
#include "hw.h"
#include "app.h"

#define DELAY_MAX 600
#define DELAY_MIN 200
uint32_t led_delay = 200;

void app_init(){
	hw_timer_start();
}

void app_handle_analog_inputs(uint16_t value_ch_1, uint16_t value_ch_2){
	uint16_t average = (value_ch_1 + value_ch_2)/2;
	if(average >= 4095)
		led_delay = DELAY_MAX;
	else if(average == 0)
		led_delay = DELAY_MIN;
	else
		led_delay = DELAY_MIN + (average*(DELAY_MAX - DELAY_MIN))/4095;
	hw_set_timer(led_delay);
}


void app_loop(void){
	hw_cpu_sleep();
}
