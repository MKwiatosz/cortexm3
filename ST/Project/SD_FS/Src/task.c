/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : task.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides main task for project.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "task.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MainTask
* Description    : Main task for the project.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void MainTask(void)
{
  char C;
  
  while(1)
  {
    C = getchar();
    if(C == '\r')
      printf("\n");
  }
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
