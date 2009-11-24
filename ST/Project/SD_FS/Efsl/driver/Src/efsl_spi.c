/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : efsl_spi.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "efsl_spi.h"
#include "sd.h"
#include "stm32f10x_spi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : SPI_Config
* Description    : Initializes the SPI1 and CS pins.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI_Config(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /* GPIOA and GPIOC Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);
  /* SPI1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

  /* Configure SPI1 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* 
   * Configure PD9 pin: CS pin
   * Configure PD10 pin: PWR pin 
  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOD, GPIO_Pin_10); /* GPIO_Pin_10 = Lo,Power On */

  /* SPI1 Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  /* SPI1 enable */
  SPI_Cmd(SPI1, ENABLE);
}

/*****************************************************************************/
esint8 if_readBuf(hwInterface* file,euint32 address,euint8* buf)
{
	return(sd_readSector(file,address,buf,512));
}

/*****************************************************************************/
esint8 if_writeBuf(hwInterface* file,euint32 address,euint8* buf)
{
	return(sd_writeSector(file,address, buf));
}

/*****************************************************************************/ 
esint8 if_setPos(hwInterface* file,euint32 address)
{
	return(0);
}

/*****************************************************************************/
// Utility-functions which does not toogle CS.
// Only needed during card-init. During init
// the automatic chip-select is disabled for SSP
static euint8 my_if_spiSend(hwInterface *iface, euint8 outgoing)
{
	euint8 incoming;

	SPI_I2S_SendData(SPI1, outgoing);
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	incoming = SPI_I2S_ReceiveData(SPI1);

	return(incoming);
}

/*****************************************************************************/ 
void if_spiInit(hwInterface *iface)
{
	euint8 i; 

	SPI_Config();
	MSD_CS_HIGH();

	/* Send 20 spi commands with card not selected */
	for(i=0;i<21;i++)
		my_if_spiSend(iface,0xff);
		
  /* Speed up */
	if_spiSetSpeed(SPI_BaudRatePrescaler_2); 
}

/*****************************************************************************/
void if_spiSetSpeed(euint8 speed)
{
  SPI_InitTypeDef   SPI_InitStructure;

  /* SPI1 Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = speed;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStructure);

  /* SPI1 enable */
  SPI_Cmd(SPI1, ENABLE);
}

/*****************************************************************************/
euint8 if_spiSend(hwInterface *iface, euint8 outgoing)
{
	euint8 incoming;

	MSD_CS_LOW();
	SPI1->DR = outgoing; /* SPI_I2S_SendData(SPI1, outgoing); */
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
	incoming = SPI1->DR; /* SPI_I2S_ReceiveData(SPI1);        */
	MSD_CS_HIGH();

	return(incoming);
}

/*****************************************************************************/
esint8 if_initInterface(hwInterface* file, eint8* opts)
{
	euint32 sc;
	
	if_spiInit(file); 
	
	if(sd_Init(file)<0)	{
		return(-1);
	}
	if(sd_State(file)<0){
		
		return(-2);
	}

	sd_getDriveSize(file, &sc);
	file->sectorCount = sc/512;
	if( (sc%512) != 0) {
		file->sectorCount--;
	}

	return(0);
}

/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
