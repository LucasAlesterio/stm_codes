/*
 * app.c
 *
 *  Created on: Feb 24, 2022
 *      Author: lucas
 */
#include <stdint.h>
#include <stdbool.h>
#include "app.h"
#include "main.h"
#include "hw.h"
extern TIM_HandleTypeDef htim2; // time debouncing
extern TIM_HandleTypeDef htim1;
bool app_started = false;
uint16_t count = 0;
static bool full = false;
#define max_itens 10

void app_init(void){
	hw_timer_start(&htim1);
	app_started = true;
}

void app_set_full(bool state){
	full = state;
}

void app_switch_interrupt(void){
	count = hw_get_time(&htim1);
	if(!app_started && !full){
		hw_enable_exti();
		return;
	}
	hw_timer_start_interruption(&htim2);
}

void app_loop(void){
	count = hw_get_time(&htim1);
	if(count > max_itens && !full){
		hw_timer_stop(&htim1);
		hw_led_state_set(true);
		full = true;
	}
}


