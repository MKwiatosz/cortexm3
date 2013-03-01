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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_GPIO_APP_H
#define __APP_GPIO_APP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern GPIO_InitTypeDef  GPIO_InitStructure;

/* Exported functions --------------------------------------------------------*/
extern void gpio_config(void);

#endif /* __APP_GPIO_APP_H */
/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
