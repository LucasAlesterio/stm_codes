/*
 * hw.h
 *
 *  Created on: Feb 24, 2022
 *      Author: lucas
 */

#ifndef HW_H_
#define HW_H_

void hw_led_toggle(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void hw_cpu_sleep(void);
void hw_timer_start(TIM_HandleTypeDef *htim);
void hw_set_timer(uint16_t time);
void hw_timer_stop(TIM_HandleTypeDef *htim);
HAL_TIM_StateTypeDef hw_get_state_time(TIM_HandleTypeDef *htim);
void hw_disable_exti(void);
void hw_enable_exti(void);
void hw_reset_timer(TIM_HandleTypeDef *htim);
void hw_timer_start_interruption(TIM_HandleTypeDef *htim);
uint16_t hw_get_time(TIM_HandleTypeDef *htim);
void hw_timer_stop_interruption(TIM_HandleTypeDef *htim);
void hw_led_state_set(bool state);

#endif /* HW_H_ */
