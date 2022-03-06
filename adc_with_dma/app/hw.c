/*
 * hw.c
 *
 *  Created on: Mar 4, 2022
 *      Author: lucas
 */
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

// callback called when finish dma request
void hw_time_start(void){
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
}

void hw_time_stop(void){
	HAL_TIM_Base_Stop_IT(&htim1);
	HAL_TIM_Base_Stop_IT(&htim2);
}

void hw_adc_start(uint16_t *values, uint32_t size){
	HAL_TIM_Base_Start(&htim3);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)values, size);
}

void hw_adc_stop(void){
	HAL_TIM_Base_Stop(&htim3);
	HAL_ADC_Stop_DMA(&hadc1);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
	hw_adc_stop();
	app_set_adc_finished();
}

void hw_adc_calibration(void){
	// Don't work
	// HAL_ADCEx_Calibration_Start(&hadc1);
	__HAL_DMA_DISABLE_IT(&hdma_adc1, DMA_IT_HT);
}

void hw_cpu_sleep(void){
	HAL_SuspendTick();
	HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
	HAL_ResumeTick();
}

void hw_led_toggle(void){
	HAL_GPIO_TogglePin(USER_LED_GPIO_Port,USER_LED_Pin);
}

void hw_reset_timer(TIM_HandleTypeDef *htim){
	__HAL_TIM_SET_COUNTER(htim, 0);
}

void hw_set_timer(uint32_t time){
    __HAL_TIM_SET_AUTORELOAD(&htim2, ((time*2)-1));
    hw_reset_timer(&htim2);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim1){
		app_get_values_adc();
	} else if(htim == &htim2){
		hw_led_toggle();
	}
}

