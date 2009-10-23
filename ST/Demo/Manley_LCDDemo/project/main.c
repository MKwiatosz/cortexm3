/******************** (C) COPYRIGHT 2007 STMicroelectronics ********************
* File Name          : main.c
* Author             : David JIANG
* Date First Issued  : 2007.9.17
* Description        : Main program body
********************************************************************************
* History:
* 2007.9.17: V1.0
********************************************************************************
* THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "lcd.h"

/* Local includes ------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
vu32 ret; /* for return of the interrupt handling */
volatile TestStatus TestRx;

/* Private functions ---------------------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void CAN_Config(void);
TestStatus CAN_Polling(void);
TestStatus CAN_Interrupt(void);
void SysTick_Config(void);
void LcdShow_Init(void);

void Led_Config(void);
void Button_Config(void);
void Led_RW_ON(void);
void Led_RW_OFF(void);

void delay(void);
void delay()
{
  int i,j;
  j=0;
  for (i=0; i<0xfffff; i++)
    j++;
}
EXTI_InitTypeDef EXTI_InitStructure;
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{

#ifdef DEBUG
  debug();
#endif

  /* System Clocks Configuration */
  RCC_Configuration();

  /* GPIO ports pins Configuration */
  GPIO_Configuration();

  /* NVIC Configuration */
  NVIC_Configuration();

  /* Configure the systick */
  SysTick_Config();

  LcdShow_Init();
  Led_Config();
  Button_Config();

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource3);
  /* Configure EXTI Line9 to generate an interrupt on falling edge */
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource4);
  /* Configure EXTI Line9 to generate an interrupt on falling edge */
  EXTI_InitStructure.EXTI_Line = EXTI_Line4;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  while(1)
  {
      write_string("STM3");  /*STM32 LCD demo*/
      delay();
      write_string("TM32");
      delay();
      write_string("M32 ");
      delay();
      write_string("32 L");
      delay();
      write_string("2 LC");
      delay();
      write_string(" LCD");
      delay();
      write_string("LCD ");
      delay();
      write_string("CD D");
      delay();
      write_string("D DE");
      delay();
      write_string(" DEM");
      delay();
      write_string("DEMO");
      delay();
  }
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;

  /* RCC system reset(for debug purpose) */
//  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* ADCCLK = PCLK2/6 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 4MHz * 9 = 36 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }

  /* Enable GPIOA, GPIOB, GPIOC, GPIOD, GPIOE and AFIO clocks */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |RCC_APB2Periph_GPIOC
         | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);

  /* TIM2 clocks enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* CAN Periph clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN, ENABLE);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC.04 -- PC.11 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_6 | GPIO_Pin_7
        | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Configure PD.03, PC.04, PC.11 -- PC.15 as input floating */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_11 | GPIO_Pin_12 |
      GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Configure CAN pin: RX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* Configure CAN pin: TX */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  /* CAN pin remap to PD0/PD1 */
  GPIO_PinRemapConfig(GPIO_Remap2_CAN,ENABLE);

  /* Configure PE.00 -- PE.15 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the NVIC and Vector Table base address.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* enabling interrupt */
  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


    /* Enable the EXTI3 Interrupt on PD.3 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

    /* Enable the EXTI4 Interrupt on PD.4 */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Configure the SysTick handler priority */
  NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 2, 0);
}

/*******************************************************************************
* Function Name  : LcdShow_Init
* Description    : Configure the lcd dispaly: TIM2 initialize in Output Compare
*                  Timing Mode
* Input          : None
* Return         : None
* Comment        : TIM2 Configuration: Output Compare Timing Mode:
                   TIM2CLK = 36 *2 =72MHz, Prescaler = 17, TIM2 counter clock = 4 MHz
                   TIM2 update Period = ARR / TIM2 counter Period = 2 ms
                   CC1 OC period = 1ms
*******************************************************************************/
void LcdShow_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 8000;
  TIM_TimeBaseStructure.TIM_Prescaler = 17;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ARRPreloadConfig(TIM2,DISABLE);
  /* only counter overflow/underflow generate U interrupt */
  TIM_UpdateRequestConfig(TIM2,TIM_UpdateSource_Regular);

  /* Output Compare Timing Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_Channel = TIM_Channel_1;
  TIM_OCInitStructure.TIM_Pulse = 4000;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInit(TIM2, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Disable);

  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_CC1 | TIM_IT_Update, ENABLE);

  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);
}

/*******************************************************************************
* Function Name  : SysTick_Config
* Description    : Configure a SysTick Base time to 10 ms.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTick_Config(void)
{
  /* Configure HCLK clock as SysTick clock source */
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);

  /* SysTick interrupt each 100 Hz with HCLK equal to 72MHz */
  SysTick_SetReload(720000);

  /* Enable the SysTick Interrupt */
  SysTick_ITConfig(ENABLE);

  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
}

void Button_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOD clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  /* Configure PD.03, PD.04 as output push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_4 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Led_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PC.06, PC.07, PC.08 and PC.09 as output push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Led_RW_ON(void)
{
  GPIO_SetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4 | GPIO_Pin_5);
}

void Led_RW_OFF(void)
{
  GPIO_ResetBits(GPIOC, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_4 | GPIO_Pin_5);
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {

  }
}
#endif
/******************* (C) COPYRIGHT 2007 STMicroelectronics *****END OF FILE****/
