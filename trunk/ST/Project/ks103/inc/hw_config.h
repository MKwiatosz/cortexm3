/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : hw_config.h
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file contains all the functions prototypes for
*                      hardware configure.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void hardware_config(void);
extern void print_sys_info(void);

#endif /* __HW_CONFIG_H */
/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
