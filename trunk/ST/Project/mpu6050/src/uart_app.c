/********************** (C) COPYRIGHT 2013 AEE ********************************/
/*!
 * @file      uart_app.c
 * @brief     uart app。
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/03/01
 *
 * 版本历史:
 * - <meegoo tsui，2013/03/01>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "uart_app.h"
#include "gpio_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @fn     void uartx_config(uint32_t x, uint32_t rate)
  * @brief  Retargets the C library printf function to the USART.
  * @retval None
  */
void uartx_config(uint32_t x, uint32_t rate)
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

/******************************************************************************/
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  char for printf
  * @retval None
  */
int  sendchar_uart1(int ch)
{
  /* Write a character to the USART */
  USART_SendData(USART1, (u8) ch);

  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  }

  return ch;
}

/******************************************************************************/
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int  getkey_uart1(void)
{
  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
  {
  }

  return ((int)USART_ReceiveData(USART1));
}

/******************************************************************************/
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  char for printf
  * @retval None
  */
int  sendchar_uart2(int ch)
{
  /* Write a character to the USART */
  USART_SendData(USART2, (u8) ch);

  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)
  {
  }

  return ch;
}

/******************************************************************************/
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int  getkey_uart2(void)
{
  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) == RESET)
  {
  }

  return ((int)USART_ReceiveData(USART2));
}

/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
