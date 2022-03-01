/*
 * hw.c
 *
 *  Created on: Feb 24, 2022
 *      Author: lucas
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"
extern TIM_HandleTypeDef htim10; // led time
extern TIM_HandleTypeDef htim1; // time debouncing

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_0){
		hw_disable_exti();
		app_switch_interrupt();
	}
}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}

void hw_cpu_sleep(void){
	__WFI();
}

void hw_timer_start(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Start_IT(htim);
}

void hw_timer_stop(TIM_HandleTypeDef *htim){
	hw_reset_timer(htim);
	HAL_TIM_Base_Stop_IT(htim);
}

void hw_set_timer(uint16_t time){
    __HAL_TIM_SET_AUTORELOAD(&htim10, time);
    hw_reset_timer(&htim10);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim10){
		hw_led_toggle();
		hw_reset_timer(&htim10);
	}
	else if(htim == &htim1){
		hw_timer_stop(&htim1);
		app_change_time();
		hw_enable_exti();
	}
}

HAL_TIM_StateTypeDef hw_get_state_time(TIM_HandleTypeDef *htim){
	return HAL_TIM_Base_GetState(htim);
}

void hw_disable_exti(void){
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
}

void hw_enable_exti(void){
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

void hw_reset_timer(TIM_HandleTypeDef *htim){
	__HAL_TIM_SET_COUNTER(htim, 0);
}
