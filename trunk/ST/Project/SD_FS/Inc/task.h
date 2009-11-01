/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : task.h
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file contains all the functions prototypes for
*                      project main task.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define __TASK_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern void MainTask(void);
extern void Dir_SD(char *param);
extern void Type_SD(char *param);
extern void Speed_SD(char *param);

#endif /* __TASK_H */
/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
