/********************** (C) COPYRIGHT 2013 AEE ********************************/
/*!
 * @file      nvic_app.c
 * @brief     nvic app。
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/03/01
 *
 * 版本历史:
 * - <meegoo tsui，2013/03/01>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "nvic_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
NVIC_InitTypeDef NVIC_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @fn     void nvic_config(void)
  * @brief  nvic config.
  * @retval None
  */
void nvic_config(void)
{
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}

/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
