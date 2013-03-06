/********************** (C) COPYRIGHT 2013 AEE ********************************/
/*!
 * @file      uart_app.c
 * @brief     uart app。
 * @author    meegoo tsui
 * @version   1.0
 * @date      2013/03/01
 *
 * 版本历史:
 * - <meegoo tsui，2013/03/01>：初始版本；
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_UART_APP_H
#define __APP_UART_APP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
extern USART_InitTypeDef USART_InitStructure;

/* Exported functions --------------------------------------------------------*/
extern void uartx_config(uint32_t x, uint32_t rate);
extern int  sendchar_uart1(int ch);
extern int  getkey_uart1(void);
extern int  sendchar_uart2(int ch);
extern int  getkey_uart2(void);

#endif /* __APP_UART_APP_H */
/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
