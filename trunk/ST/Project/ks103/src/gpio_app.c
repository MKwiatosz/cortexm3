/********************** (C) COPYRIGHT 2013 AEE ********************************/
/*!
 * @file      gpio_app.c
 * @brief     gpio app。
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/03/01
 *
 * 版本历史:
 * - <meegoo tsui，2013/03/01>：初始版本；
 */
/******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "gpio_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define I2C_NOP()                      gpio_i2c_delay(200)

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

	/* Config key2 - PD3 */
	GPIO_InitStructure.GPIO_Pin	= GPIO_Pin_3;
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
  * @fn     void gpio_i2c_init(void)
  * @brief  gpio i2c init.
  * @retval None
  */
void gpio_i2c_init(void)
{
	SDA_H;
	SCL_H;
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_start(void)
  * @brief  gpio i2c start.
  * @retval None
  */
void gpio_i2c_start(void)
{
	SDA_H;
	I2C_NOP();
	SCL_H;
	I2C_NOP();
	SDA_L;
	I2C_NOP();
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_stop(void)
  * @brief  gpio i2c stop.
  * @retval None
  */
void gpio_i2c_stop(void)
{
	SDA_L;
	I2C_NOP();
	SCL_H;
	I2C_NOP();
	SDA_H;
	I2C_NOP();
}

/******************************************************************************/
/**
  * @fn     void gpio_i2c_ack(void)
  * @brief  gpio i2c ack.
  * @retval None
  */
void gpio_i2c_ack(void)
{
	uint32_t timeout = 0;

	SCL_H;
	I2C_NOP();
	while(SDA_READ == 1 && timeout < 2000){
		timeout++;
	}
	SCL_L;
	I2C_NOP();
}


/******************************************************************************/
/**
  * @fn     void gpio_i2c_nack(void)
  * @brief  gpio i2c nack.
  * @retval None
  */
void gpio_i2c_nack(void)
{
	SDA_H;
	I2C_NOP();
	SCL_H;
	I2C_NOP();
	SCL_L;
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

	SCL_L;
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
	SCL_H;
	I2C_NOP();
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

	SCL_L;
	I2C_NOP();
	SDA_H;
	I2C_NOP();
	for(i = 0; i < 8; i++){
		SCL_H;
		I2C_NOP();
		data_read = data_read << 1;
		if(SDA_READ == 1)
			data_read++;
		SCL_L;
		I2C_NOP();
	}

	return data_read;
}

/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
