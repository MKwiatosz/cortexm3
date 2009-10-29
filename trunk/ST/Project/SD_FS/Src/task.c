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
#include "msd.h"
#include <stdio.h>
#include <stdlib.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t SD_Buffer[512];

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
  uint32_t i,from;
  
  /* Read data from SD */
  from      = strtoul(param,0,0);
  printf_1("\r+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf_1("\r\nrd %s",param);
  printf_1("\r\nRead data from 0x%x:",from);
  SD_Status = MSD_ReadBlock(SD_Buffer,from,BLOCK_SIZE);
  if(SD_Status == MSD_RESPONSE_FAILURE)
    printf_1("\r\nRead SD sequence failed !");
  else if(SD_Status == MSD_RESPONSE_NO_ERROR)
  {
    printf_1("\r\nRead SD sequence succeed .");
    for(i=0;i<BLOCK_SIZE;i++)
    {
      if(i%16 == 0)
        printf_1("\r\n");
      printf_1("0x%02x ",SD_Buffer[i]);
    }
  }
  printf_1("\r\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
