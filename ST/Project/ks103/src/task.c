/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : task.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides main task for project.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "task.h"
#include "cmd.h"
#include "hw_config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include "uart_app.h"
#include "gpio_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define KS103_DATA_ERROR               0xFFFFFFFF
#define KS103_READ_DELAY_x_MS          100
#define KS103_ERROR_STR                "ERR."

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void ks103_send_cmd_uart(uint8_t addr, uint8_t reg, uint8_t cmd)
{
	sendchar_uart2(addr);
	sendchar_uart2(reg);
	sendchar_uart2(cmd);
}

static uint32_t ks103_send_cmd_i2c(uint8_t addr, uint8_t reg, uint8_t cmd)
{
	gpio_i2c_start();
	gpio_i2c_write(addr);
	if(gpio_i2c_ack() != 0){ /* 无应答 */
		return KS103_DATA_ERROR;
	}
	gpio_i2c_write(reg);
	if(gpio_i2c_ack() != 0){ /* 无应答 */
		return KS103_DATA_ERROR;
	}
	gpio_i2c_write(cmd);
	gpio_i2c_ack();
	gpio_i2c_stop();
	return 0;
}

static uint32_t ks103_read_reg_i2c(uint8_t addr, uint8_t reg)
{
	uint8_t data_read;

	/* 需要读取的寄存器 */
	gpio_i2c_start();
	gpio_i2c_write(addr);
	if(gpio_i2c_ack() != 0){ /* 无应答 */
		return KS103_DATA_ERROR;
	}
	gpio_i2c_write(reg);
	if(gpio_i2c_ack() != 0){ /* 无应答 */
		return KS103_DATA_ERROR;
	}

	/* 读取寄存器的数值 */
	gpio_i2c_start();
	gpio_i2c_write(addr + 1);
	if(gpio_i2c_ack() != 0){ /* 无应答 */
		return KS103_DATA_ERROR;
	}
	data_read = gpio_i2c_read();
	gpio_i2c_ack();
	gpio_i2c_stop();

	return (uint32_t) data_read;
}

static void ks103_delay(void)
{
	uint32_t timeout;

	timeout = SysTick_1ms + KS103_READ_DELAY_x_MS;
	while(SysTick_1ms < timeout){
	}
}

void main_task(void)
{
	/* Init console */
	cmdHelpInit();
	cmdBasicInit();

	/* main task */
	lcdClr();
	lcdWrStr("0000");
	while(1){
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0){
			auto_detect_uart("");
		}
		else if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4) == 0){
			auto_detect_i2c("");
		}

		cmdMonitor();
	}
}

void detect_uart(char *param)
{
	uint32_t i, distance;
	char buf[16];

	UART2_RxT_Index = 0;
	ks103_send_cmd_uart(0xE8, 0x02, 0xBC);
	ks103_delay();

	if(UART2_RxT_Index == 2){
		distance = UART2_RxT_BUF[0];
		distance = distance << 8;
		distance = distance + UART2_RxT_BUF[1];
		printf("\r\ndistance: %d mm", distance);
		sprintf(buf,"%4d",distance);
		lcdWrStr(buf);
	} else {
		printf("\r\nError Data: ");
		for(i=0; i<UART2_RxT_Index; i++){
			printf("0x%02x ", UART2_RxT_BUF[i%16]);
		}
		lcdWrStr(KS103_ERROR_STR);
	}
}

void auto_detect_uart(char *param)
{
	while(1){
		detect_uart("");
	}
}

void detect_i2c(char *param)
{
	uint32_t distance1, distance2;
	char buf[16];

	if(ks103_send_cmd_i2c(0xe8, 0x02, 0xbc) == KS103_DATA_ERROR){
		printf("\r\nks103_send_cmd_i2c: bus error!");
		lcdWrStr(KS103_ERROR_STR);
		return;
	}
	ks103_delay();
	distance1 = ks103_read_reg_i2c(0xe8, 0x02);
	if(distance1 == KS103_DATA_ERROR){
		printf("\r\nks103_read_reg_i2c - 0x02: bus error!");
		lcdWrStr(KS103_ERROR_STR);
		return;		
	}
	distance2 = ks103_read_reg_i2c(0xe8, 0x03);
	if(distance2 == KS103_DATA_ERROR){
		printf("\r\nks103_read_reg_i2c - 0x03: bus error!");
		lcdWrStr(KS103_ERROR_STR);
		return;		
	}
	distance2 = distance2 + (distance1 << 8);
	printf("\r\ndistance: %d mm", distance2);
	sprintf(buf,"%4d",distance2);
	lcdWrStr(buf);
}

void auto_detect_i2c(char *param)
{
	while(1){
		detect_i2c("");
	}
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
