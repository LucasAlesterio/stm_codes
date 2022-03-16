/*
 * hw.h
 *
 *  Created on: Mar 15, 2022
 *      Author: lucas
 */

#ifndef HW_H_
#define HW_H_

void hw_pwm_init(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void hw_increment_brightness(void);
void hw_reset_brightness(void);
void hw_cpu_sleep(void);
uint32_t hw_tick_ms_get(void);

#endif /* HW_H_ */
