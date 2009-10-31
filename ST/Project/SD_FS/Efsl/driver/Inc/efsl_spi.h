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
/* Select MSD Card: ChipSelect pin low  */
#define MSD_CS_LOW()     GPIO_ResetBits(GPIOD, GPIO_Pin_9)
/* Deselect MSD Card: ChipSelect pin high */
#define MSD_CS_HIGH()    GPIO_SetBits(GPIOD, GPIO_Pin_9)

/* External variables --------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
extern esint8 if_initInterface(hwInterface* file,eint8* opts);
extern esint8 if_readBuf(hwInterface* file,euint32 address,euint8* buf);
extern esint8 if_writeBuf(hwInterface* file,euint32 address,euint8* buf);
extern esint8 if_setPos(hwInterface* file,euint32 address);

extern void if_spiInit(hwInterface *iface);
extern void if_spiSetSpeed(euint8 speed);
extern euint8 if_spiSend(hwInterface *iface, euint8 outgoing);
extern void SPI_Config(void);

#endif /* __EFSL_SPI_H */
/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
