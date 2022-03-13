/*
 * app.c
 *
 *  Created on: Mar 9, 2022
 *      Author: lucas
 */
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "app.h"
#include "hw.h"

#define N_DIGITS 5
#define TIME_DEBOUNCING 5000
#define MAX_TIME 5000

uint8_t password[N_DIGITS] = {1, 1, 1, 1, 1};
bool app_started = false;
volatile uint32_t tick_debouncing = 0;
volatile uint32_t time_out = 0;

typedef enum sm_state_e {
	SM_RESET = 0,
	SM_WAIT_DIGITS,
	SM_CHECK_CODE
} sm_state_t;

typedef struct sm_state_var_s {
	uint8_t pos;
	sm_state_t state;
	uint8_t code[N_DIGITS];
} sm_state_var_t;

typedef struct led_s {
	uint8_t repetitions;
	uint32_t current_time;
	uint32_t initial_time;
} led_t;

led_t led;
sm_state_var_t st;

void app_add_digit(keys_t digit){
	if (!app_started || tick_debouncing > 0)
		return;
	hw_disable_gpio_it();
	tick_debouncing = TIME_DEBOUNCING;
	time_out = 0;
	if(st.pos < N_DIGITS){
		st.code[st.pos] = digit;
		st.pos++;
	}
}

void app_led_set(led_t* led, uint8_t repetitions, uint32_t time){
	led->initial_time = time;
	led->repetitions = repetitions * 2;
}

bool app_handle_led(led_t* led) {
	if(led->repetitions > 0){
		if(led->current_time > 0){
			led->current_time--;
		} else {
			hw_led_toggle();
			led->repetitions--;
			led->current_time = led->initial_time;
		}
		return true;
	}
	return false;
}

void sm_reset_state(sm_state_var_t* st, led_t* led) {
	sm_state_t next_state = st->state;
	if(!app_handle_led(led)){
		next_state = SM_WAIT_DIGITS;
		st->pos = 0;
		tick_debouncing = 0;
		time_out = 0;
		led->repetitions = 0;
		led->current_time = 0;
		led->initial_time = 0;
		uint8_t index = 0;
		while(index < N_DIGITS)
			st->code[index++] = 0;
		st->state = next_state;
	}
	st->state = next_state;
}

void sm_wait_digits_state(sm_state_var_t* st,led_t* led ) {
	sm_state_t next_state = st->state;
	if(tick_debouncing > 1){
		tick_debouncing--;
	} else if(tick_debouncing == 1){
		tick_debouncing--;
		hw_enable_gpio_it();
	} else {
		if(time_out >= MAX_TIME){
			app_led_set(led, 2, 200);
			next_state = SM_RESET;
		} else if(st->pos >= N_DIGITS){
			next_state = SM_CHECK_CODE;
		}
	}
	time_out += 1;
	st->state = next_state;
}

void sm_check_code_state(sm_state_var_t* st,led_t* led) {
	sm_state_t next_state = SM_RESET;
	if(memcmp(st->code,password,N_DIGITS) == 0) {
		app_led_set(led,1, 2000);
	} else {
		app_led_set(led,3, 200);
	}
	st->state = next_state;
}

void app_init(void){
	app_started = true;
}

void app_tick_1ms(void) {
	if (!app_started)
		return;
	switch(st.state) {
		case SM_RESET:
			sm_reset_state(&st, &led);
			break;
		case SM_WAIT_DIGITS:
			sm_wait_digits_state(&st, &led);
			break;
		case SM_CHECK_CODE:
			sm_check_code_state(&st, &led);
			break;
		default:
			st.state = SM_RESET;
			break;
	}
}

void app_loop(void){
	hw_cpu_sleep();
}
