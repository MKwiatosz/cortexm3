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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_NVIC_APP_H
#define __APP_NVIC_APP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern NVIC_InitTypeDef NVIC_InitStructure;

/* Exported functions --------------------------------------------------------*/
extern void nvic_config(void);

#endif /* __APP_NVIC_APP_H */
/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
