/*
 * app.h
 *
 *  Created on: Mar 9, 2022
 *      Author: lucas
 */

#ifndef APP_H_
#define APP_H_

typedef enum keys_e {
	A = 1,
	B,
	C,
	D
} keys_t;

void app_init(void);
void app_tick_1ms(void);
void app_loop(void);
void app_add_digit(keys_t digit);

#endif /* APP_H_ */
