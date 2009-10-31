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
#include "hw_config.h"
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
* Function Name  : Dir_SD
* Description    : Dir command for SD.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Dir_SD(char *param)
{
  if(ls_openDir(&list, &(efs.myFs), "/") != 0)
  {
    printf_1("\r\nCould not open the selected directory.\n");
    return;
  }

  /* Dir */
  while(ls_getNext(&list) == 0)
    printf_1("\r\n%.11s (%li bytes)\n",list.currentEntry.FileName,
                                       list.currentEntry.FileSize);
}

/*******************************************************************************
* Function Name  : Type_SD
* Description    : Type command for SD.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Type_SD(char *param)
{
  EmbeddedFile file_r;
  uint32_t size,i,l;
	char buf[512];

  if(file_fopen(&file_r,&efs.myFs,param,'r')!=0)
  {
    printf("\r\nOpen file %s failt.",param);
    return;
  }
  
  /* Display the file */
  size = file_r.FileSize;
  printf_1("\r\nFile size: %d bytes",size);
  printf_1("\r\n-= data start =-\r\n");
  while(size)
  {
    if(size > 512)
    {
      l = 512;
      size = size - 512;
    }
    else
    {
      l = size;
      size = 0;
    }
    
    /* read and printf */
    file_read(&file_r,l,(uint8_t*)buf);
    for(i=0;i<l;i++)
      printf("%c",buf[i]);
  }
  printf_1("\r\n-= data end =-");
	file_fclose(&file_r);
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
