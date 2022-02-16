/*
 * app.h
 *
 *  Created on: Feb 11, 2022
 *      Author: LucasAlesterio
 */

#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_tick_1ms(void);
void app_switch_interrupt(_Bool switch_state_A0, _Bool switch_state_A1);

#endif /* APP_H_ */
