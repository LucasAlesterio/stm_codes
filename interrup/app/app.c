/*
 * app.c
 *
 *  Created on: Feb 11, 2022
 *      Author: LucasAlesterio
 */
#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "main.h"
#include "hw.h"

#define APP_DEBOUNCING_TIME_MS 50

volatile uint32_t let_time_on = 900;
volatile uint32_t led_time_off = 450;
bool app_started = false;

void app_init(void){
	app_started = true;
}

void app_switch_interrupt(bool switch_state_A0, bool switch_state_A1){

	static uint32_t debouncing_time_ms = 0;

	if(!app_started)
			return;

	if((hw_tick_ms_get() - debouncing_time_ms) >= APP_DEBOUNCING_TIME_MS){

		if(!switch_state_A0 && !switch_state_A1){
			let_time_on = 100;
			led_time_off = 100;
		}
		else
		if(!switch_state_A0 && switch_state_A1){
			let_time_on = 300;
			led_time_off = 150;
		}
		else
		if(switch_state_A0 && !switch_state_A1){
			let_time_on = 600;
			led_time_off = 300;
		}
		else{
			let_time_on = 900;
			led_time_off = 450;
		}

		debouncing_time_ms = hw_tick_ms_get();
	}

}

void app_tick_1ms(void){

	static uint32_t led_time_cnt_ms = 0;

	if(!app_started)
		return;

	led_time_cnt_ms++;
	if(led_time_cnt_ms >= let_time_on){

		led_time_cnt_ms = 0;
		hw_led_toggle();
	}
	else
	if(led_time_cnt_ms >= led_time_off){

		hw_led_toggle();
	}
}

void app_loop(void){

	hw_cpu_sleep();
}

