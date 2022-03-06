/*
 * hw.h
 *
 *  Created on: Mar 4, 2022
 *      Author: lucas
 */

#ifndef HW_H_
#define HW_H_

void hw_adc_start(uint16_t *values, uint32_t size);
void hw_adc_stop(void);
void hw_adc_calibration(void);
void hw_cpu_sleep(void);
void hw_led_toggle(void);
void hw_time_start(void);
void hw_set_timer(uint32_t time);

#endif /* HW_H_ */
