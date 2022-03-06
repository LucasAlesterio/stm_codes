/*
 * hw.h
 *
 *  Created on: Mar 1, 2022
 *      Author: lucas
 */
#include <stdint.h>
#include "main.h"
#include <stdbool.h>

#ifndef HW_H_
#define HW_H_

void hw_timer_start();
void hw_cpu_sleep(void);
void hw_calibration(void);
void hw_adc_start(void);
void hw_led_toggle(void);
void hw_reset_timer(TIM_HandleTypeDef *htim);
void hw_calibration(void);
bool hw_adc_read(uint16_t *value_ch);
void hw_set_timer(uint16_t time);

#endif /* HW_H_ */
