/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : task.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides main task for project.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "task.h"
#include "cmd.h"
#include <stdio.h>
#include <stdlib.h>

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
  /* Init console */
  cmdHelpInit();
  cmdBasicInit();

  /* Main task */
  while(1)
  {
    cmdMonitor();
  }
}

/*******************************************************************************
* Function Name  : MainTask
* Description    : Main task for the project.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Read_SD(char *param)
{
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
