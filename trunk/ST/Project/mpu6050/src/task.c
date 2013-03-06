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
#include <string.h>
#include "lcd.h"
#include "uart_app.h"
#include "gpio_app.h"
#include "MPU6050.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int16_t ax, ay, az;
int16_t gx, gy, gz;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void main_task(void)
{
	uint8_t  rev   = 0;
	uint16_t retry = 0;
	
	/* Init console */
	cmdHelpInit();
	cmdBasicInit();

	/* main task */
	lcdClr();
	lcdWrStr(" mpu");

	/* Wait device connect */
	printf("\r\n");
	while(1){
		if(readBytes(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, 1, &rev) == TRUE){
			printf("\r[%04x]rev: 0x%02x", retry++, rev);
			if(rev == 0x68){
				break;
			}
		}
		sys_int_delay_ms(1000);
	}

	/* init mpu6050 */
	initialize();

	/* main loop */
	while(1){
		cmdMonitor();
	}
}

/******************************************************************************/
void mpu6050_cmd(char *param)
{
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
