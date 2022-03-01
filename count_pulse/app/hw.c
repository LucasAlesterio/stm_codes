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
extern TIM_HandleTypeDef htim2; // time debouncing
extern TIM_HandleTypeDef htim1;
// #define max_itens 10
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

void hw_timer_start_interruption(TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Start_IT(htim);
}

void hw_timer_start(TIM_HandleTypeDef *htim){
	hw_reset_timer(htim);
	HAL_TIM_Base_Start(htim);
}

void hw_timer_stop(TIM_HandleTypeDef *htim){
	hw_reset_timer(htim);
	HAL_TIM_Base_Stop(htim);
}

void hw_timer_stop_interruption(TIM_HandleTypeDef *htim){
	hw_reset_timer(htim);
	HAL_TIM_Base_Stop_IT(htim);
}

void hw_set_timer(uint16_t time){
    __HAL_TIM_SET_AUTORELOAD(&htim2, time);
    hw_reset_timer(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim2){
		app_set_full(false);
		hw_led_state_set(false);
		hw_timer_start(&htim1);
		hw_enable_exti();
		hw_timer_stop_interruption(&htim2);
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

uint16_t hw_get_time(TIM_HandleTypeDef *htim){
	return __HAL_TIM_GET_COUNTER(htim);
}

void hw_led_state_set(bool state){
	GPIO_PinState led_state = state ? GPIO_PIN_RESET : GPIO_PIN_SET;
	HAL_GPIO_WritePin(USER_LED_GPIO_Port,USER_LED_Pin,led_state);
}

