/**
  ******************************************************************************
  * @file    usbh_usr_lcd.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/29/2010
  * @brief   This file includes the declarations for user routines for LCD 
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
#ifndef __USBH_USR_LCD_H
#define __USBH_USR_LCD_H

/* Includes ------------------------------------------------------------------*/
#include "usbh_hid_core.h"

/** @addtogroup USBH_USER
  * @{
  */
  
/** @defgroup USBH_USR_LCD 
  * @brief This file is the header file for user LCD routines
  * @{
  */ 

/** @defgroup USBH_USR_LCD_Exported_Types
  * @{
  */ 


/**
  * @}
  */ 

/** @defgroup USBH_USR_LCD_Exported_Defines
  * @{
  */ 



/**
  * @}
  */ 

/** @defgroup USBH_USR_LCD_Exported_Constants
  * @{
  */ 
/*Left Button : Report data :0x01*/
#define HID_MOUSE_BUTTON1                0x01 
/*Right Button : Report data :0x02*/
#define HID_MOUSE_BUTTON2                0x02 
/*Middle Button : Report data : 0x04*/
#define HID_MOUSE_BUTTON3                0x04 

/* Mouse directions */
#define MOUSE_TOP_DIR                   0x80
#define MOUSE_BOTTOM_DIR                0x00
#define MOUSE_LEFT_DIR                  0x80
#define MOUSE_RIGHT_DIR                 0x00

#define MOUSE_WINDOW_X                  2
#define MOUSE_WINDOW_Y                  48
#define MOUSE_WINDOW_X_MAX              181
#define MOUSE_WINDOW_Y_MIN              101
#define MOUSE_WINDOW_HEIGHT             191
#define MOUSE_WINDOW_WIDTH              285

#define HID_MOUSE_BUTTON_HEIGHT         10
#define HID_MOUSE_BUTTON_WIDTH          24
#define HID_MOUSE_BUTTON_XCHORD         MOUSE_WINDOW_X + MOUSE_WINDOW_WIDTH + 6
#define HID_MOUSE_BUTTON1_YCHORD        210
#define HID_MOUSE_BUTTON3_YCHORD        136
#define HID_MOUSE_BUTTON2_YCHORD        68	   

#define MOUSE_LEFT_MOVE                  1
#define MOUSE_RIGHT_MOVE                 2
#define MOUSE_UP_MOVE                    3
#define MOUSE_DOWN_MOVE                  4

#define HID_MOUSE_HEIGHTLSB              2
#define HID_MOUSE_WIDTHLSB               2
#define HID_MOUSE_RES_X                  4  
#define HID_MOUSE_RES_Y                  4

/**
  * @}
  */ 

/** @defgroup USBH_USR_LCD_Exported_Variables
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBH_USR_LCD_Exported_Functions
  * @{
  */ 
void HID_MOUSE_UpdatePosition(int8_t x ,int8_t y);
void HID_MOUSE_ButtonReleased(uint8_t button_idx);
void HID_MOUSE_ButtonPressed (uint8_t button_idx);

/**
  * @}
  */ 

#endif /* __USBH_USR_LCD_H */

/**
  * @}
  */ 

/**
  * @}
  */ 
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
