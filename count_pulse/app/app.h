/*
 * app.h
 *
 *  Created on: Feb 24, 2022
 *      Author: lucas
 */
#include <stdbool.h>
#ifndef APP_H_
#define APP_H_

void app_init(void);
void app_loop(void);
void app_switch_interrupt(void);
void app_set_full(bool state);

#endif /* APP_H_ */
