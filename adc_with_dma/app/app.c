/*
 * app.c
 *
 *  Created on: Mar 4, 2022
 *      Author: lucas
 */

#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "app.h"
#include "hw.h"

#define ADC_SAMPLE_N 10
#define ADC_CHANEL_N 2
#define DELAY_MAX 600
#define DELAY_MIN 200

uint16_t adc_raw_data[ADC_SAMPLE_N] = {0};
uint32_t led_delay = 200;

void app_init(void){
	hw_adc_calibration();
	hw_time_start();
}

void app_handle_analog_inputs(uint32_t value_ch_1, uint32_t value_ch_2){
	uint16_t average = (value_ch_1 + value_ch_2)/2;
	if(average >= 4095)
		led_delay = DELAY_MAX;
	else if(average == 0)
		led_delay = DELAY_MIN;
	else
		led_delay = DELAY_MIN + (average*(DELAY_MAX - DELAY_MIN))/4095;
	hw_set_timer(led_delay);
}

void app_average_adc_value(uint16_t *adc_raw_data, uint16_t *adc_avg_ch1, uint16_t *adc_avg_ch2){
	uint32_t sum[ADC_CHANEL_N] = {0,0};
	uint32_t average[ADC_CHANEL_N] = {0,0};
	uint8_t index = 0;
	uint8_t index_chanel = 0;
	while(index < ADC_SAMPLE_N){
		while(index_chanel < ADC_CHANEL_N){
			sum[index_chanel++] += adc_raw_data[index++];
		}
		index_chanel = 0;
	}
	while(index_chanel < ADC_CHANEL_N){
		average[index_chanel] = sum[index_chanel]/(ADC_SAMPLE_N/ADC_CHANEL_N);
		index_chanel++;
	}
	app_handle_analog_inputs(average[0], average[1]);
}

void app_set_adc_finished(void){
	uint16_t adc_avg_val_1, adc_avg_val_2;
	app_average_adc_value(adc_raw_data, &adc_avg_val_1, &adc_avg_val_2);
}

void app_get_values_adc(void){
	hw_adc_start(adc_raw_data, ADC_SAMPLE_N);
	//hw_cpu_sleep();
}

void app_loop(void){
	//hw_cpu_sleep();
}
