/******************** (C) COPYRIGHT 2009 developer.cortex **********************
* File Name          : cmd.h
* Author             : Xu Mingfeng
* Version            : V1.0.0
* Date               : 2009-10-28
* Description        : This file contains all the functions prototypes for
*                      all command.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMD_H
#define __CMD_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "uart_app.h"

/* Exported types ------------------------------------------------------------*/
typedef void (*cmdHandler)(char *param);
typedef struct cmd_s {
  const char   *cmd;
  cmdHandler   phandler;
  const char   *phelp;
  struct cmd_s *pnext;
} cmd_t;

/* Exported constants --------------------------------------------------------*/
//Define the console version
#define  CONSOLE_VER_MAJOR         1
#define  CONSOLE_VER_SUB           0
#define  CONSOLE_VER_MINOR         0

#ifndef NULL
#define NULL  ((void *)0)
#endif

#ifndef TRUE
#define TRUE  (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif

#ifndef SUCCESS
#define SUCCESS (0)
#endif
#ifndef FAIL
#define FAIL  (1)
#endif

/* Exported macro ------------------------------------------------------------*/
#define getkey()                       getkey_uart1()

/* External variables --------------------------------------------------------*/
extern cmd_t basic_cmd_array[];

/* Exported functions ------------------------------------------------------- */
extern void cmdVersion(char *param);
extern void cmdHelpInit(void);
extern void cmdBasicInit(void);
extern void cmdRegister(cmd_t *bc);
extern void cmdMonitor(void);

#endif /* __CMD_H */
/******************* (C) COPYRIGHT 2009 developer.cortex *******END OF FILE****/
