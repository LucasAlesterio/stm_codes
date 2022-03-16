/*
 * app.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lucas
 */
#include <stdbool.h>
#include <stdint.h>
#include "hw.h"
#define DEBOUCING_TIME 50
#define PRESSED_MAX_TIME 3000

bool app_started = false;

void app_init(void) {
	hw_pwm_init();
	app_started = true;
}

void app_handle_button(uint8_t pressed) {
	static uint32_t deboucing_time_ms = 0;
	static uint32_t init_button_time_ms = 0;
	if(!app_started)
		return;
	if(pressed == 0) {
		if((hw_tick_ms_get() - deboucing_time_ms) >= DEBOUCING_TIME) {
			init_button_time_ms = hw_tick_ms_get();
			deboucing_time_ms = hw_tick_ms_get();
		}
	} else if((hw_tick_ms_get() - init_button_time_ms) >= PRESSED_MAX_TIME) {
		hw_reset_brightness();
	} else if((hw_tick_ms_get() - deboucing_time_ms) >= DEBOUCING_TIME) {
		deboucing_time_ms = hw_tick_ms_get();
		hw_increment_brightness();
	}
}

void app_loop(void) {
	hw_cpu_sleep();
}
