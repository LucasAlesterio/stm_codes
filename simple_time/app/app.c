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
extern TIM_HandleTypeDef htim10;
extern TIM_HandleTypeDef htim1; // time debouncing
#define new_time(old_time) (old_time == 499 ? 999 : 499)
uint16_t time = 499;
bool app_started = false;

void app_init(void){
	hw_timer_start(&htim10);
	app_started = true;
}

void app_switch_interrupt(){
	if(!app_started)
		return;
	hw_timer_start(&htim1);
}

void app_change_time(void){
	time = new_time(time);
	hw_set_timer(time);
}

void app_loop(void){
	hw_cpu_sleep();
}
