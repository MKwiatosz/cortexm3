/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : hw_config.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides APIs for hardware configure.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "hw_config.h"
#include "uart_app.h"
#include "gpio_app.h"
#include "nvic_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : HardwareConfigure
* Description    : Configure system hard ware.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void hardware_config(void)
{
	/* Setup STM32 system (clock, PLL and Flash configuration) */
	SystemInit();

	/* Init UART1 and UART2 */
	uartx_config(1, 115200);
	uartx_config(2, 9600);

	/* Init gpio */
	gpio_config();

	/* init nvic */
	nvic_config();

	/* Setup SysTick Timer for 1 sec interrupts */
	if(SysTick_Config(SystemFrequency / 1000)){ 
		printf("\r\nCapture error.");
		while (1);
	}

	/* Print system info */
	print_sys_info();
}

/*******************************************************************************
* Function Name  : PrintSysInfo
* Description    : Print system info.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void print_sys_info(void)
{
  /* Print project info */
  printf("\r\n###########################################################");
  printf("\r\n# [ks103]                                                 #");
  printf("\r\n#   author: meegoo tsui                                   #");
  printf("\r\n###########################################################");
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
