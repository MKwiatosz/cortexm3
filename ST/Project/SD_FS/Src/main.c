/**
  ******************************************************************************
  * @file    main.c 
  * @author  Xu Mingfeng
  * @version V1.0
  * @date    10/26/2009
  * @brief   Main program body
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "hw_config.h"
#include "task.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure hardware */
  HardwareConfigure();

  /* Main task */
  MainTask();

  /* Never run to here ! */
  printf_1("\r\nMake sure all task done !");
  while(1){};
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  printf("Wrong parameters value: file %s on line %d\r\n", file, line);
  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  char for printf
  * @retval None
  */
int  sendchar(int ch)
{
  /* Write a character to the USART */
  USART_SendData(USART1, (u8) ch);

  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {
  }

  return ch;
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
int  getkey(void)
{
  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
  {
  }

  return ((int)USART_ReceiveData(USART1));
}

/**
  * @}
  */
/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
