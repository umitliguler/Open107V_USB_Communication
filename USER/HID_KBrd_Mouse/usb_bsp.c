/**
  ******************************************************************************
  * @file    usb_bsp.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/29/2010
  * @brief   This file implement the usb host board support package
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbh_usr.h"
#include "usb_bsp.h"
#include "usbh_usr_lcd.h"
#include "LCD.h" 


/** @addtogroup USBH_USER
* @{
*/

/** @defgroup USB_BSP
  * @brief This file is responsible to offer board support package
  * @{
  */ 

/** @defgroup USB_BSP_Private_Defines
  * @{
  */ 
#define USE_ACCURATE_TIME
#define TIM_MSEC_DELAY       0x01
#define TIM_USEC_DELAY       0x02

/**
  * @}
  */ 


/** @defgroup USB_BSP_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 



/**
  * @}
  */ 

/** @defgroup USBH_BSP_Private_Variables
  * @{
  */ 
ErrorStatus HSEStartUpStatus;
/**
  * @}
  */ 

/** @defgroup USBH_BSP_Private_FunctionPrototypes
  * @{
  */ 

#ifdef USE_ACCURATE_TIME 
__IO uint32_t BSP_delay = 0;
static void BSP_SetTime(uint8_t Unit);
static void BSP_Delay(uint32_t nTime,uint8_t Unit);
#endif

__IO uint32_t BSP_TimeOutsec  = 0;
__IO uint32_t BSP_TimeOutmsec = 0;

/**
  * @}
  */ 

/** @defgroup USB_BSP_Private_Functions
  * @{
  */ 

/**
  * @brief  BSP_Init
  *         Configures Main system clocks & power
  * @param  None
  * @retval None
  */
void BSP_Init(void)
{
  /* Configure the LEDs */
//  STM_EVAL_LEDInit(LED1);
//  STM_EVAL_LEDInit(LED2);
//  STM_EVAL_LEDInit(LED3); 
//  STM_EVAL_LEDInit(LED4); 

  /* Initialize the STM3210C-EVAL's LCD */
  LCD_Initializtion();
  
  /* Display message on STM3210X-EVAL LCD */
  /* Clear the LCD */
  LCD_Clear(Black);

  /* Set the LCD Back Color */
  LCD_SetBackColor(Black);

  /* Set the LCD Text Color */
  LCD_SetTextColor(White);
  
  /* Configure PB9 pin: User Key pin */
//   STM_EVAL_PBInit(Button_KEY, Mode_GPIO);
}

/**
  * @brief  USB_OTG_BSP_Init
  *         Initilizes BSP configurations
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Select USBCLK source */
  RCC_OTGFSCLKConfig(RCC_OTGFSCLKSource_PLLVCO_Div3);

  /* Enable the USB clock */ 
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_OTG_FS, ENABLE) ;

  RCC_APB2PeriphClockCmd( KEYA_PORT_RCC | KEYB_PORT_RCC | KEYC_PORT_RCC, ENABLE); 	

#ifdef SOF_OUTPUT_ENABLED
  /* To enable SOF pulse out on PAD */
  
  RCC_APB2PeriphClockCmd(HOST_SOF_OUTPUT_RCC, ENABLE);
  
  /* Configure SOF Pin */
  GPIO_InitStructure.GPIO_Pin = HOST_SOF_SIGNAL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(HOST_SOF_PORT, &GPIO_InitStructure);
#endif  
  
  /* Configure pin for overcurrent detection */

#ifdef   OVERCURRENT_DET
  RCC_APB2PeriphClockCmd(HOST_OVRCURR_PORT_RCC, ENABLE);
  
  /* Configure SOF Pin */
  GPIO_InitStructure.GPIO_Pin = HOST_OVRCURR_LINE;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(HOST_OVRCURR_PORT, &GPIO_InitStructure);
  
  /* Connect Button EXTI Line to Button GPIO Pin */
  GPIO_EXTILineConfig(HOST_OVRCURR_PORT_SOURCE, HOST_OVRCURR_PIN_SOURCE);  
  
  /* Configure Button EXTI line */
  EXTI_InitStructure.EXTI_Line = HOST_OVRCURR_EXTI_LINE;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;  
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
#endif  

  GPIO_InitStructure.GPIO_Pin = KEYA_PORT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; ; 
  GPIO_Init(KEYA_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = KEYB_PORT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; ; 
  GPIO_Init(KEYB_PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = KEYC_PORT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; ; 
  GPIO_Init(KEYC_PORT, &GPIO_InitStructure);
}

/**
  * @brief  USB_OTG_BSP_EnableInterrupt
  *         Configures USB Global interrupt
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_EnableInterrupt(void)
{

  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable USB Interrupt */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

#ifdef   OVERCURRENT_DET
  
  /* Enable the Overcurrent Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = HOST_OVRCURR_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStructure);  

#endif
}

/**
  * @brief  BSP_Drive_VBUS
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */

void USB_OTG_BSP_DriveVBUS(uint8_t state)
{
  /*
  On-chip 5 V VBUS generation is not supported. For this reason, a charge pump 
  or, if 5 V are available on the application board, a basic power switch, must 
  be added externally to drive the 5 V VBUS line. The external charge pump can 
  be driven by any GPIO output. When the application decides to power on VBUS 
  using the chosen GPIO, it must also set the port power bit in the host port 
  control and status register (PPWR bit in OTG_FS_HPRT).
  
  Bit 12 PPWR: Port power
  The application uses this field to control power to this port, and the core 
  clears this bit on an overcurrent condition.
  */
  if (0 == state)
  { 
    /* DISABLE is needed on output of the Power Switch */
    GPIO_SetBits(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
  }
  else
  {
    /*ENABLE the Power Switch by driving the Enable LOW */
    GPIO_ResetBits(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
  }
}

/**
  * @brief  USB_OTG_BSP_ConfigVBUS
  *         Configures the IO for the Vbus and OverCurrent
  * @param  None
  * @retval None
  */

void  USB_OTG_BSP_ConfigVBUS(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  
  
  RCC_APB2PeriphClockCmd(HOST_POWERSW_PORT_RCC, ENABLE);
  
  
  /* Configure Power Switch Vbus Pin */
  GPIO_InitStructure.GPIO_Pin = HOST_POWERSW_VBUS;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(HOST_POWERSW_PORT, &GPIO_InitStructure);
  
  /* By Default, DISABLE is needed on output of the Power Switch */
  GPIO_SetBits(HOST_POWERSW_PORT, HOST_POWERSW_VBUS);
  
  USB_OTG_BSP_mDelay(200);   /* Delay is need for stabilising the Vbus Low 
  in Reset Condition, when Vbus=1 and Reset-button is pressed by user */  
}

/**
  * @brief  USB_OTG_BSP_TimeInit
  *         Initialises delay unit Systick timer /Timer2
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_TimeInit ( void )
{
#ifdef USE_ACCURATE_TIME   
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
  
  /* Configure the Priority Group to 2 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  
  NVIC_Init(&NVIC_InitStructure);
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  
#endif  
}

/**
  * @brief  USB_OTG_BSP_uDelay
  *         This function provides delay time in micro sec
  * @param  usec : Value of delay required in micro sec
  * @retval None
  */
void USB_OTG_BSP_uDelay (const uint32_t usec)
{
  
#ifdef USE_ACCURATE_TIME   
  
  BSP_Delay(usec,TIM_USEC_DELAY); 
#else
  uint32_t count = 0;
  const uint32_t utime = (120 * usec / 7);
  do
  {
    if ( ++count > utime )
    {
      return ;
    }
  }
  while (1);
#endif   
  
}


/**
  * @brief  USB_OTG_BSP_mDelay
  *          This function provides delay time in milli sec
  * @param  msec : Value of delay required in milli sec
  * @retval None
  */
void USB_OTG_BSP_mDelay (const uint32_t msec)
{
   
#ifdef USE_ACCURATE_TIME  
     BSP_Delay(msec,TIM_MSEC_DELAY);   
#else
    USB_OTG_BSP_uDelay(msec * 1000);   
#endif    

}


/**
  * @brief  USB_OTG_BSP_TimerIRQ
  *         Time base IRQ
  * @param  None
  * @retval None
  */

void USB_OTG_BSP_TimerIRQ (void)
{
#ifdef USE_ACCURATE_TIME 
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    
    if(BSP_delay > 0x00)
    { 
      BSP_delay--;
    }
         
    if(BSP_TimeOutsec > 0x00)
    { 
      BSP_TimeOutsec--;
    }
         
   if(BSP_TimeOutmsec > 0x00)
    { 
      BSP_TimeOutmsec--;
    }     
         
    
    if((BSP_TimeOutsec <= 0) && (BSP_delay <= 0) && (BSP_TimeOutmsec <= 0))
    {
      TIM_Cmd(TIM2,DISABLE);
    }
      
  }
#endif  
} 


/**
  * @brief  BSP_secTimeoutStart
  *         Start timer 2 to implement USB timeout
  * @param  nTime :  TimeOut interval
  * @retval None
  */
void BSP_secTimeoutStart(uint32_t nTime)
{
  BSP_TimeOutsec = (nTime*1000);
  BSP_SetTime(TIM_MSEC_DELAY);  
}
   
/**
  * @brief  BSP_secTimeout
  *         Start timer 2 to implement USB Standard request sec timeout
  * @param  None
  * @retval BSP_TimeoutStatus : Timeout Status
  *                             Timeout   : Timeout Complete
  *                             NoTimeout : Timeout Not complete
  */
BSP_TimeoutStatus BSP_secTimeout(void)
{
  
  BSP_TimeoutStatus status;
  
  if(BSP_TimeOutsec == 0)
  {
    status = Timeout;
    
  }
  else
  {
    status = NoTimeout;
  }
  
  return status;
    
}         

/**
  * @brief  BSP_msecTimeoutStart
  *         Start timer 2 to implement USB timeout
  * @param   nTime :  TimeOut interval
  * @retval None
  */
void BSP_msecTimeoutStart(uint32_t nTime)
{
  BSP_TimeOutmsec = nTime;
  BSP_SetTime(TIM_MSEC_DELAY);  
}
   
/**
  * @brief  BSP_msecTimeout
  *         Start timer 2 to implement USB Standard request msec timeout
  * @param  None
  * @retval BSP_TimeoutStatus : Timeout Status
  *                             Timeout   : Timeout Complete
  *                             NoTimeout : Timeout Not complete
  */
BSP_TimeoutStatus BSP_msecTimeout(void)
{
  
  BSP_TimeoutStatus status;
  
  if(BSP_TimeOutmsec == 0)
  {
    status = Timeout;
    
  }
  else
  {
    status = NoTimeout;
  }
  
  return status;
    
}        
         


#ifdef USE_ACCURATE_TIME 
/**
  * @brief  BSP_Delay
  *         Delay routine based on TIM2
  * @param  nTime : Delay Time 
  * @param  unit : Delay Time unit : mili sec / micro sec
  * @retval None
  */
static void BSP_Delay(uint32_t nTime, uint8_t unit)
{
  BSP_delay = nTime;
  BSP_SetTime(unit);  
  while(BSP_delay != 0);
  TIM_Cmd(TIM2,DISABLE);
}

/**
  * @brief  BSP_SetTime
  *         Configures TIM2 for delay routine based on TIM2
  * @param  unit : msec /usec
  * @retval None
  */
static void BSP_SetTime(uint8_t unit)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  TIM_Cmd(TIM2,DISABLE);
  TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE); 
  
  
  if(unit == TIM_USEC_DELAY)
  {  
    TIM_TimeBaseStructure.TIM_Period = 11;
  }
  else if(unit == TIM_MSEC_DELAY)
  {
    TIM_TimeBaseStructure.TIM_Period = 11999;
  }
  
  TIM_TimeBaseStructure.TIM_Prescaler = 5;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  
  /* TIM IT enable */
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  
  /* TIM2 enable counter */ 
  TIM_Cmd(TIM2, ENABLE);  
  
} 

#endif

/**
* @}
*/ 

/**
* @}
*/ 

/**
* @}
*/

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
