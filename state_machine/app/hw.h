/*
 * hw.h
 *
 *  Created on: Mar 9, 2022
 *      Author: lucas
 */

#ifndef HW_H_
#define HW_H_

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void hw_led_toggle(void);
uint32_t hw_tick_ms_get(void);
void hw_cpu_sleep(void);
void hw_disable_gpio_it(void);
void hw_enable_gpio_it(void);

#endif /* HW_H_ */
