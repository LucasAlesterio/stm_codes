/*
 * hw.c
 *
 *  Created on: Mar 1, 2022
 *      Author: lucas
 */
#include <stdbool.h>
#include "main.h"
#include "hw.h"
#include "app.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;

void hw_timer_start(){
	// hw_calibration();
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
}

void hw_cpu_sleep(void){
	__WFI();
}

void hw_adc_start(void){
	HAL_ADC_Start(&hadc1);
}

void hw_calibration(void){
	// Dont't work
	// HAL_ADCEx_Calibration_Start(&hadc1);
}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}

bool hw_adc_read(uint16_t *value_ch){
	HAL_StatusTypeDef adc_hal_status;
	while(1){
		adc_hal_status = HAL_ADC_PollForConversion(&hadc1, 100);
		if(adc_hal_status == HAL_OK){
			*value_ch = (uint16_t) HAL_ADC_GetValue(&hadc1);
			return true;
		}
		else if(adc_hal_status != HAL_OK){
			return false;
		}
	}
}

void hw_reset_timer(TIM_HandleTypeDef *htim){
	__HAL_TIM_SET_COUNTER(htim, 0);
}

void hw_set_timer(uint16_t time){
    __HAL_TIM_SET_AUTORELOAD(&htim2, ((time*2)-1));
    hw_reset_timer(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	uint16_t value_ch_1, value_ch_2;
	if(htim == &htim1){
		hw_adc_start();
		hw_adc_read(&value_ch_1);
		hw_adc_start();
		hw_adc_read(&value_ch_2);
		app_handle_analog_inputs(value_ch_1, value_ch_2);
	} else if(htim == &htim2){
		hw_led_toggle();
	}
}
