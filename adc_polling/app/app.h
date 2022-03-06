/*
 * app.h
 *
 *  Created on: Mar 1, 2022
 *      Author: lucas
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_handle_analog_inputs(uint16_t value_ch_1, uint16_t value_ch_2);
void app_tick_1ms(void);

#endif /* APP_H_ */
