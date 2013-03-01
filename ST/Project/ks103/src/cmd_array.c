/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : cmd_array.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides command array.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "cmd.h"
#include "task.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/***** base command structure *****/
cmd_t basic_cmd_array[] =
{
  {
    "ver",
    (cmdHandler)cmdVersion,    
    "Get the version of some important library. Usage: ver",   
    NULL
  },

  {
    "detect_uart",
    (cmdHandler)detect_uart,    
    "detect distance from ks103 via uart",   
    NULL
  },

  {
    "auto_uart",
    (cmdHandler)auto_detect_uart,    
    "auto detect distance from ks103 via uart",   
    NULL
  },

  { NULL,NULL,NULL,NULL}
};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
