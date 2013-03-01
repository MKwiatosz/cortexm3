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

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MainTask
* Description    : Main task for the project.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void main_task(void)
{
	/* Init console */
	cmdHelpInit();
	cmdBasicInit();

	/* Main task */
	lcdClr();
	lcdWrStr("0000");
	while(1){
		if(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0){
			auto_detect_uart("");
		}
		cmdMonitor();
	}
}

void detect_uart(char *param)
{
	uint32_t i, timeline, distance;

	UART2_RxT_Index = 0;
	sendchar_uart2(0xE8);
	sendchar_uart2(0x02);
	sendchar_uart2(0xbc);
	timeline = SysTick_1ms + 100;
	printf("\r\nWait %d ms ...", timeline - SysTick_1ms);
	while(SysTick_1ms < timeline){
	}

	if(UART2_RxT_Index == 2){
		distance = UART2_RxT_BUF[0];
		distance = distance << 8;
		distance = distance + UART2_RxT_BUF[1];
		printf("\r\ndistance: %d mm", distance);
	} else {
		printf("\r\nError Data: ");
		for(i=0; i<UART2_RxT_Index; i++){
			printf("0x%02x ", UART2_RxT_BUF[i%16]);
		}
	}

	i = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);
	printf("\r\nPD3 - %d", i);

}

void auto_detect_uart(char *param)
{
	uint32_t i, timeline, distance;
	char buf[10];

	while(1){
		UART2_RxT_Index = 0;
		sendchar_uart2(0xE8);
		sendchar_uart2(0x02);
		sendchar_uart2(0xbc);
		timeline = SysTick_1ms + 100;
		printf("\r\nWait %d ms ...", timeline - SysTick_1ms);
		while(SysTick_1ms < timeline){
		}

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
				lcdWrStr("0000");
			}
		}
	}
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
