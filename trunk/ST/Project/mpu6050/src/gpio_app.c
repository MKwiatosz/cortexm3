/********************** (C) COPYRIGHT 2013 AEE ********************************/
/*!
 * @file      gpio_app.c
 * @brief     gpio app��
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/03/01
 *
 * �汾��ʷ:
 * - <meegoo tsui��2013/03/01>����ʼ�汾��
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gpio_app.h"
#include "stm32f10x_it.h"
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define I2C_NOP()                      gpio_i2c_delay(500)

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef  GPIO_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @fn     void gpio_config(void)
  * @brief  gpio config.
  * @retval None
  */
void gpio_config(void)
{
	/* Enable GPIOC, GPIOE */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB
	                     | RCC_APB2Periph_GPIOC 
		                 | RCC_APB2Periph_GPIOD 
		                 | RCC_APB2Periph_GPIOE, ENABLE);

	/* Configure LCD COMx as output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/* Configure LCD SEGx as output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* Config key2 - PD3,  key3 - PD4 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Configure I2C1 pins: SCL and SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_delay(void)
  * @brief  gpio i2c delay.
  * @retval None
  */
void gpio_i2c_delay(uint32_t time)
{
	uint32_t timeout = time;
	if(timeout){
		while(timeout--){
		}
	}
}

/******************************************************************************/
/**
  * @fn     bool gpio_i2c_start(void)
  * @brief  gpio i2c start.
  * @retval None
  */
bool gpio_i2c_start(void)
{
	SDA_H;                                        /* ������ʼ�����������ź�   */
	I2C_NOP();
	SCL_H;
	I2C_NOP();                                    /* ��ʼ��������ʱ�� > 4.7us */
	if(!SDA_READ){                              /* SDA��Ϊ�͵�ƽ������æ,�˳� */
		printf("\r\ngpio_i2c_start - bus busy !");
		return FALSE;
	}
	SDA_L;                                        /* ������ʼ�ź�             */
	I2C_NOP();                                    /* ��ʼ�ź�����ʱ�� > 4us   */
	if(SDA_READ){                             /* SDA��Ϊ�ߵ�ƽ�����߳���,�˳� */
		printf("\r\ngpio_i2c_start - bus error !");
		return FALSE;
	}
	SCL_L;                                        /* ǯסI2C���ߣ�׼��������  */
	I2C_NOP();
	return TRUE;
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_stop(void)
  * @brief  gpio i2c stop.
  * @retval None
  */
void gpio_i2c_stop(void)
{
	SDA_L;                                          /* ���ͽ��������������ź� */
	I2C_NOP();
	SCL_H;                                          /* ���ͽ���������ʱ���ź� */
	I2C_NOP();
	SDA_H;                                          /* ����I2C���߽����ź�    */
	I2C_NOP();
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_write(void)
  * @brief  gpio i2c write.
  * @retval None
  */
void gpio_i2c_write(uint8_t data_write)
{
	uint8_t i;

	/* ��ʱSCL_L��ǯסI2C���� */
	for(i = 0; i < 8; i++){
		if(data_write & 0x80)
			SDA_H;
		else
			SDA_L;
		data_write = data_write << 1;
		I2C_NOP();
		SCL_H;
		I2C_NOP();
		SCL_L;
		I2C_NOP();
	}
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_read(void)
  * @brief  gpio i2c read.
  * @retval None
  */
uint8_t gpio_i2c_read(void)
{
	uint8_t i, data_read = 0;

	SDA_H;                                              /* ��������Ϊ����ģʽ */
	for(i = 0; i < 8; i++){
		SCL_H;                                        /* ��ʱ��Ϊ�ߣ�������Ч */
		I2C_NOP();
		data_read = data_read << 1;
		if(SDA_READ == 1)
			data_read++;
		SCL_L;                                        /* ��ʱ��Ϊ�ͣ�׼������ */
		I2C_NOP();
	}

	return data_read;
}

/******************************************************************************/
/**
  * @fn     uint8_t gpio_i2c_ack(void)
  * @brief  gpio i2c ack.
  * @retval None
  */
uint8_t gpio_i2c_ack(void)
{
	uint8_t ack;

	SDA_H;                                      /* �ͷ������ߣ�׼������Ӧ��λ */
	I2C_NOP();
	SCL_H;                                      
	I2C_NOP();
	ack = SDA_READ;                                             /* ��ȡӦ��λ */
	SCL_L;
	I2C_NOP();
	return ack;
}

/******************************************************************************/
/**
  * @fn     uint8_t gpio_i2c_get_ack(void)
  * @brief  gpio get i2c ack.
  * @retval None
  */
uint8_t gpio_i2c_get_ack(void)
{
	uint8_t ack;

	SDA_H;                                      /* �ͷ������ߣ�׼������Ӧ��λ */
	I2C_NOP();
	SCL_H;                                      
	I2C_NOP();
	ack = SDA_READ;                                             /* ��ȡӦ��λ */
	SCL_L;
	I2C_NOP();
	return ack;
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_get_ack(void)
  * @brief  gpio get i2c ack.
  * @retval None
  */
void gpio_i2c_set_ack(uint8_t ack)
{	
	/* ����Ӧ���ź� */
	if(ack){
		SDA_L;
	}else{
		SDA_H;
	}
	I2C_NOP();
	SCL_H;
	I2C_NOP();
	SDA_L;                           /* ��ʱ�����ߣ�ǯסi2c���ߣ��Ա�������� */
}

/******************************************************************************/
/**
  * @fn     void sys_int_delay_ms(uint32_t timeout)
  * @brief  delay n ms via int.
  * @retval None
  */
void sys_int_delay_ms(uint32_t nMS)
{
	uint32_t timeout;
	timeout = SysTick_1ms + nMS;
	while(SysTick_1ms < timeout){
	}
}

/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
