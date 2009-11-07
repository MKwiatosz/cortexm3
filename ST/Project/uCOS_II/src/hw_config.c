/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : hw_config.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides APIs for hardware configure.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : HardwareConfigure
* Description    : Configure system hard ware.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void HardwareConfigure(void)
{
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  SystemInit();

  /* Config UART1 for print */
  UART_Printf_Config();

  /* Print system info */
  PrintSysInfo();
}

/*******************************************************************************
* Function Name  : PrintSysInfo
* Description    : Print system info.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void PrintSysInfo(void)
{
  printf("\n#################################################");
  printf("\n# uCOS-II for STM32F103                         #");
  printf("\n# Author: Xu Mingfeng                           #");
  printf("\n# Email : developer.cortex@gmail.com            #");
  printf("\n# Date  : 2009-11-07                            #");
  printf("\n#################################################");
}

/*******************************************************************************
* Function Name  : UART_Printf_Config
* Description    : Config UART1 for printf function.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void UART_Printf_Config(void)
{
  /* Enable GPIOA and USART1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);

  /* Configure USART1 Rx (PA.10) as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure USART1 Tx (PA.09) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USARTx configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(USART1, &USART_InitStructure);
  /* Enable the USARTx */
  USART_Cmd(USART1, ENABLE);
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
