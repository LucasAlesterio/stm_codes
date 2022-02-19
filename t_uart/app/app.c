/*
 * app.c
 *
 *  Created on: Feb 18, 2022
 *      Author: LucasAlesterio
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cbf.h"
#include "shell.h"
#include "app.h"
#include "hw.h"


#define APP_DEBOUCING_TIME_MS 50
#define APP_UART_BUFFER_MAX   64
#define APP_CHAR_TO_INT 48
#define SHELL_MAX_ARGS        5
#define APP_PARSER_SIZE 16
static cbf_t cbf;
static uint8_t cbf_area[APP_UART_BUFFER_MAX];
static bool app_started = false;

void app_switch_interrupt(void)
{
	static uint32_t deboucing_time_ms = 0;

	if(!app_started)
		return;

	if((hw_tick_ms_get() - deboucing_time_ms) >= APP_DEBOUCING_TIME_MS)
	{
		deboucing_time_ms = hw_tick_ms_get();
	}
}

void app_tick_1ms(void)
{
	if(!app_started)
		return;
}
void app_init(void)
{
	shell_init();
	cbf_init(&cbf,cbf_area,APP_UART_BUFFER_MAX);
	hw_uart_init(&cbf);
	app_started = true;
}

void app_loop(void)
{
	uint8_t argv[SHELL_MAX_ARGS];
	static uint8_t tx_buffer[APP_UART_BUFFER_MAX];
	static uint8_t rx_buffer[APP_UART_BUFFER_MAX];
	uint8_t data = 0;
	uint32_t tx_size;
	uint32_t rx_size;
	cbf_status_t status;
	int time = 0;
	uint32_t init_time = 0;
	int index = 0;

	tx_size = snprintf((char *)tx_buffer, APP_UART_BUFFER_MAX - 1, "get time\n");
	hw_uart_tx(tx_buffer,tx_size);
		// aguardando o ultimo byte ser transmitido pois caso contrario
		// o processador eh tao rapido que vai fazer o loop abaixo inteiro sem o ultimo
		// caracter ter chegado ainda
	rx_size = 0;
	hw_delay_ms(50);

	while(true)  //le o que tá no buffer circular
	{
		status = cbf_get(&cbf,&data);

		if((status == CBF_EMPTY) || (rx_size >= APP_UART_BUFFER_MAX))
			break;

		rx_buffer[rx_size++] = data;
	}
	while(rx_buffer[init_time] != ' ' && init_time < rx_size){
		init_time++;
	}
	init_time++;
	if(init_time == rx_size){
		return;
	}
	while(rx_buffer[init_time] != '\n') {
			argv[index++] = rx_buffer[init_time];
			init_time++;
		}
	while(index < SHELL_MAX_ARGS){
		argv[index++] = '\0';
	}
	init_time = 0;
	if(sscanf((char*)argv,"%d",&time) == 1)
	{
		// 100 200 400 800 1600 3200
		if(time >= 3200){
			time = 100;
		} else {
			time *= 2;
		}
		tx_size = snprintf((char *)tx_buffer, APP_UART_BUFFER_MAX - 1, "set time %d\n", time);
		hw_uart_tx(tx_buffer, tx_size);
		hw_delay_ms(time*2*5);
	}
}



