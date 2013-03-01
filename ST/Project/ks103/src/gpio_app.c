/********************** (C) COPYRIGHT 2013 AEE ********************************/
/*!
 * @file      gpio_app.c
 * @brief     gpio app。
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/03/01
 *
 * 版本历史:
 * - <meegoo tsui，2013/03/01>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gpio_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @fn     void gpio_config(void)
  * @brief  gpio config.
  * @retval None
  */
void gpio_config(void)
{
	/* Enable GPIOC, GPIOE */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC 
		                 | RCC_APB2Periph_GPIOD 
		                 | RCC_APB2Periph_GPIOE, ENABLE);

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

	/* Config key2 - PD3 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
