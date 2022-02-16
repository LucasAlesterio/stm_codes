/*
 * hw.c
 *
 *  Created on: Feb 11, 2022
 *      Author: LucasAlesterio
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

bool hw_switch_state_get(uint32_t input_pin){

	GPIO_PinState switch_state;

	if(input_pin == 0)
		switch_state = HAL_GPIO_ReadPin(USER_SW_0_GPIO_Port, USER_SW_0_Pin);
	else
		switch_state = HAL_GPIO_ReadPin(USER_SW_1_GPIO_Port, USER_SW_1_Pin);

	if(switch_state == GPIO_PIN_SET)
		return true;
	else
		return false;
}

void hw_led_state_set(bool state){

	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;

	HAL_GPIO_WritePin(USER_LED_GPIO_Port,USER_LED_Pin,led_state);
}

void hw_delay_ms(uint32_t time_ms){

	HAL_Delay(time_ms);
}


