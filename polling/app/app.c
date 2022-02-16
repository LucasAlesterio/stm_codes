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

void app_init(void){

}

void app_loop(void){
	uint32_t let_time_on, led_time_off;

	bool switch_state_A0 = hw_switch_state_get(0);
	bool switch_state_A1 = hw_switch_state_get(1);

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


	hw_led_state_set(true);
	hw_delay_ms(let_time_on);

	hw_led_state_set(false);
	hw_delay_ms(led_time_off);
}
