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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_GPIO_APP_H
#define __APP_GPIO_APP_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_gpio.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define SCL_H                          GPIOB->BSRR = GPIO_Pin_6
#define SCL_L                          GPIOB->BRR  = GPIO_Pin_6
#define SDA_H                          GPIOB->BSRR = GPIO_Pin_7
#define SDA_L                          GPIOB->BRR  = GPIO_Pin_7
#define SCL_READ                       ((GPIOB->IDR& GPIO_Pin_6) >> 6)
#define SDA_READ                       ((GPIOB->IDR& GPIO_Pin_7) >> 7)

/* External variables --------------------------------------------------------*/
extern GPIO_InitTypeDef  GPIO_InitStructure;

/* Exported functions --------------------------------------------------------*/
extern void    gpio_config(void);
extern void    gpio_i2c_delay(uint32_t time);
extern bool    gpio_i2c_start(void);
extern void    gpio_i2c_stop(void);
extern void    gpio_i2c_write(uint8_t data_write);
extern uint8_t gpio_i2c_read(void);
extern uint8_t gpio_i2c_get_ack(void);
extern void    gpio_i2c_set_ack(uint8_t ack);
extern void    sys_int_delay_ms(uint32_t nMS);

#endif /* __APP_GPIO_APP_H */
/********************** (C) COPYRIGHT 2013 AEE  *****************END OF FILE***/
