/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : hw_config.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides APIs for hardware configure.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "msd.h"
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
  
  /* Init SD via SPI */
  SD_Status = MSD_Init();

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
  printf_1("\r\n###########################################################");
  printf_1("\r\n# [SD File System]                                        #");
  printf_1("\r\n#   author: Xu Mingfeng                                   #");
  printf_1("\r\n#   e-mail: developer.cortex@gmail.com                    #");
  printf_1("\r\n#   date  : 2009-10-26                                    #");
  printf_1("\r\n###########################################################");
  
  /* Print SD info */
  printf_1("\r\nSD_Status: 0x%02x",SD_Status);
  if(SD_Status == MSD_RESPONSE_FAILURE)
    printf_1("\r\nSD sequence failed !");
  else if(SD_Status == MSD_RESPONSE_NO_ERROR)
  {
    Get_Medium_Characteristics();
    printf_1("\r\nSD sequence succeed .");
    printf_1("\r\nMsdBlockCount: 0x%08x",Mass_Block_Count);
    printf_1("\r\nMsdBlockSize : 0x%08x Byte",Mass_Block_Size);
    printf_1("\r\nMsdMemorySize: 0x%08x Byte",Mass_Memory_Size);
  }
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
