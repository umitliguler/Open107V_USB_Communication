/**
  ******************************************************************************
  * @file    usbh_usr.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/29/2010
  * @brief   This file is the header file for usb usr file
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USH_USR_H__
#define __USH_USR_H__


/* Includes ------------------------------------------------------------------*/
#include "usbh_core.h"
#include "usbh_usr_lcd.h"
#include <stdio.h>

/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_HID_DEMO_USER_CALLBACKS
* @{
*/
  
/** @defgroup USBH_USR 
  * @brief This file is the header file for user action
  * @{
  */ 


/** @defgroup USBH_CORE_Exported_Variables
  * @{
  */ 

/** @defgroup USB_BSP_Private_Macros
  * @{
  */ 
//#define HOST_OVRCURR_PORT                  GPIOE
//#define HOST_OVRCURR_LINE                  GPIO_Pin_1
//#define HOST_OVRCURR_PORT_SOURCE           GPIO_PortSourceGPIOE
//#define HOST_OVRCURR_PIN_SOURCE            GPIO_PinSource1
//#define HOST_OVRCURR_PORT_RCC              RCC_APB2Periph_GPIOE
//#define HOST_OVRCURR_EXTI_LINE             EXTI_Line1
//#define HOST_OVRCURR_IRQn                  EXTI1_IRQn 

#define HOST_POWERSW_PORT_RCC              RCC_APB2Periph_GPIOA
#define HOST_POWERSW_PORT                  GPIOA
#define HOST_POWERSW_VBUS                  GPIO_Pin_3

#define HOST_SOF_OUTPUT_RCC                RCC_APB2Periph_GPIOA
#define HOST_SOF_PORT                      GPIOA
#define HOST_SOF_SIGNAL                    GPIO_Pin_8

#define KEYA_PORT_RCC					   RCC_APB2Periph_GPIOC
#define KEYA_PORT						   GPIOC
#define KEYA_PORT_PIN					   GPIO_Pin_13

#define KEYB_PORT_RCC					   RCC_APB2Periph_GPIOB
#define KEYB_PORT						   GPIOB
#define KEYB_PORT_PIN					   GPIO_Pin_2

#define KEYC_PORT_RCC					   RCC_APB2Periph_GPIOA
#define KEYC_PORT						   GPIOA
#define KEYC_PORT_PIN					   GPIO_Pin_0

extern  USBH_Usr_cb_TypeDef USR_Callbacks;


/**
  * @}
  */ 


/** @defgroup USBH_CORE_Exported_FunctionsPrototype
  * @{
  */ 

void USBH_USR_ApplicationSelected(void);
void USBH_USR_Init(void);
void USBH_USR_DeviceAttached(void);
void USBH_USR_ResetDevice(void);
void USBH_USR_DeviceDisconnected (void);
void USBH_USR_OverCurrentDetected (void);
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed); 
void USBH_USR_Device_DescAvailable(void *);
void USBH_USR_DeviceAddressAssigned(void);
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc);
void USBH_USR_Manufacturer_String(void *);
void USBH_USR_Product_String(void *);
void USBH_USR_SerialNum_String(void *);
void USBH_USR_EnumerationDone(void);
USBH_USR_Status USBH_USR_UserInput(void);
void USBH_USR_DeInit(void);
void USBH_USR_DeviceNotSupported(void);
void USBH_USR_UnrecoveredError(void);
/**
  * @}
  */ 

#endif /* __USBH_USR_H */
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
