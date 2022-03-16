/*
 * hw.c
 *
 *  Created on: Mar 9, 2022
 *      Author: lucas
 */
#include "main.h"
#include "app.h"
#include "hw.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == KEY_A_Pin){
		app_add_digit(A);
	} else if(GPIO_Pin == KEY_B_Pin){
		app_add_digit(B);
	} else if(GPIO_Pin == KEY_C_Pin){
		app_add_digit(C);
	} else if(GPIO_Pin == KEY_D_Pin){
		app_add_digit(D);
	}
}

void hw_disable_gpio_it(void){
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_NVIC_DisableIRQ(EXTI1_IRQn);
	HAL_NVIC_DisableIRQ(EXTI2_IRQn);
	HAL_NVIC_DisableIRQ(EXTI3_IRQn);
}

void hw_enable_gpio_it(void){
	HAL_NVIC_ClearPendingIRQ(EXTI0_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI1_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI2_IRQn);
	HAL_NVIC_ClearPendingIRQ(EXTI3_IRQn);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	HAL_NVIC_EnableIRQ(EXTI1_IRQn);
	HAL_NVIC_EnableIRQ(EXTI2_IRQn);
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}

void hw_cpu_sleep(void){
	__WFI();
}
