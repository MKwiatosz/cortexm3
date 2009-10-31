/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : efsl_spi.h
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file contains all the functions prototypes for
*
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EFSL_SPI_H
#define __EFSL_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "config.h"
#include "debug.h"

/* Exported types ------------------------------------------------------------*/
/*************************************************************\
              hwInterface
               ----------
* FILE* 	imagefile		File emulation of hw interface.
* long		sectorCount		Number of sectors on the file.
\*************************************************************/
struct  hwInterface{
	/*FILE 	*imageFile;*/
	eint32  	sectorCount;
};
typedef struct hwInterface hwInterface;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
esint8 if_initInterface(hwInterface* file,eint8* opts);
esint8 if_readBuf(hwInterface* file,euint32 address,euint8* buf);
esint8 if_writeBuf(hwInterface* file,euint32 address,euint8* buf);
esint8 if_setPos(hwInterface* file,euint32 address);

void if_spiInit(hwInterface *iface);
void if_spiSetSpeed(euint8 speed);
euint8 if_spiSend(hwInterface *iface, euint8 outgoing);

#endif /* __EFSL_SPI_H */
/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
