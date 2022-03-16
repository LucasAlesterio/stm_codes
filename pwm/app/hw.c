/*
 * hw.c
 *
 *  Created on: Mar 15, 2022
 *      Author: lucas
 */
#include <stdint.h>
#include "main.h"
#include "app.h"
#define MAX_VALUE_PWM 20

extern TIM_HandleTypeDef htim1;
volatile uint16_t led_brightness = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == GPIO_PIN_0) {
		app_handle_button( HAL_GPIO_ReadPin(USER_SWT_GPIO_Port, USER_SWT_Pin));
	}
}

void hw_pwm_init(void) {
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
}

void hw_reset_brightness(void) {
	led_brightness = 0;
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
}

void hw_increment_brightness(void) {
	if(led_brightness < MAX_VALUE_PWM) {
		led_brightness += (0.1 * MAX_VALUE_PWM);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, (led_brightness - 1));
	} else {
		hw_reset_brightness();
	}
}

uint32_t hw_tick_ms_get(void) {
	return HAL_GetTick();
}

void hw_cpu_sleep(void) {
	__WFI();
}
