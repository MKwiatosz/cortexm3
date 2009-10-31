/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : template.c
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file provides
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  :
* Description    :
* Input          :
* Output         :
* Return         :
*******************************************************************************/
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

	SPI_SendData(SPI1, outgoing);
	while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
	incoming = SPI_ReceiveData(SPI1);

	return(incoming);
}
/*****************************************************************************/ 

void if_spiInit(hwInterface *iface)
{
	euint8 i; 

  

	SPI_Config();
	
	
	MSD_CS_HIGH();

		// low speed during init
	if_spiSetSpeed(3); 

	/* Send 20 spi commands with card not selected */
	for(i=0;i<21;i++)
		my_if_spiSend(iface,0xff);

	
}

/*****************************************************************************/

void if_spiSetSpeed(euint8 speed)
{
	/*speed &= 0xFE;
	if ( speed < SPI_PRESCALE_MIN  ) speed = SPI_PRESCALE_MIN ;
	SPI_PRESCALE_REG = speed;*/
}

/*****************************************************************************/

euint8 if_spiSend(hwInterface *iface, euint8 outgoing)
{
	euint8 incoming;


	MSD_CS_LOW();
	SPI_SendData(SPI1, outgoing);
	while (SPI_GetFlagStatus(SPI1, SPI_FLAG_TXE) == RESET);
	incoming = SPI_ReceiveData(SPI1);
	MSD_CS_HIGH();
	

	return(incoming);
}

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
