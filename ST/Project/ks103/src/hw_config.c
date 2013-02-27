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
NVIC_InitTypeDef NVIC_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : UARTxConfig
* Description    : Init UART1 or UART2.
* Input          : x = 1 UART1
                   x = 2 UART2
* Output         : None.
* Return         : None.
*******************************************************************************/
void UARTxConfig(uint32_t x, uint32_t rate)
{
	if(x == 1){
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
		USART_InitStructure.USART_BaudRate = rate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* Configure the USART1 */
		USART_Init(USART1, &USART_InitStructure);
		/* Enable the USARTx */
		USART_Cmd(USART1, ENABLE);
	} else {
		/* Enable GPIOA and USART1 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD , ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);  

		/* Configure USART1 Rx (PA.10) as input floating */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		/* Configure USART1 Tx (PA.09) as alternate function push-pull */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

		/* USARTx configured as follow:
					- BaudRate = 115200 baud  
					- Word Length = 8 Bits
					- One Stop Bit
					- No parity
					- Hardware flow control disabled (RTS and CTS signals)
					- Receive and transmit enabled
		*/
		USART_InitStructure.USART_BaudRate = rate;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		/* Configure the USART2 */
		USART_Init(USART2, &USART_InitStructure);
		/* Enable the USARTx */
		USART_Cmd(USART2, ENABLE);
	}
}

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

	/* Init UART1 and UART2 */
	UARTxConfig(1, 115200);
	UARTxConfig(2, 9600);

  /* Setup SysTick Timer for 1 sec interrupts  */
  if(SysTick_Config(SystemFrequency / 1000))
  { 
    printf("\r\nCapture error.");
    while (1);
  }

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

  /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);
	
  /* Configure LCD COMx as output */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure LCD SEGx as output */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

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
  /* Print project info */
  printf("\r\n###########################################################");
  printf("\r\n# [ks103]                                                 #");
  printf("\r\n#   author: meegoo tsui                                   #");
  printf("\r\n###########################################################");
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
