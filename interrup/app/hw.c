/*
 * hw.c
 *
 *  Created on: Feb 11, 2022
 *      Author: LucasAlesterio
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

bool switch_state_A0 = true;
bool switch_state_A1 = true;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	if(GPIO_Pin == GPIO_PIN_0){

		switch_state_A0 = !switch_state_A0;
	}

	else if(GPIO_Pin == GPIO_PIN_1){

		switch_state_A1 = !switch_state_A1;
	}

	app_switch_interrupt(switch_state_A0, switch_state_A1);
}


void hw_led_toggle(void){

	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}

uint32_t hw_tick_ms_get(void){

	return HAL_GetTick();
}

void hw_cpu_sleep(void){
	__WFI();
}





