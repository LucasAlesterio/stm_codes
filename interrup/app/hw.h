/*
 * hw.h
 *
 *  Created on: Feb 11, 2022
 *      Author: LucasAlesterio
 */

#ifndef HW_H_
#define HW_H_

bool hw_switch_state_get(uint32_t input_pin);

void hw_led_state_set(bool state);

void hw_delay_ms(uint32_t time_ms);

void hw_led_toggle(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

void hw_cpu_sleep(void);

uint32_t hw_tick_ms_get(void);

#endif /* HW_H_ */
