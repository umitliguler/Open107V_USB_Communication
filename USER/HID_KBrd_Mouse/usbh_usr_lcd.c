/**
  ******************************************************************************
  * @file    usbh_usr_lcd.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/29/2010
  * @brief   This file includes the some user routines for LCD 
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
#include "usbh_usr_lcd.h"
#include "LCD.h"


/** @addtogroup USBH_USER
* @{
*/


/** @defgroup USBH_USR_LCD 
* @brief    This file includes the some user routines for LCD 
* @{
*/ 

/** @defgroup USBH_USR_LCD_Private_TypesDefinitions
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_LCD_Private_Defines
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_LCD_Private_Macros
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_LCD_Private_Variables
* @{
*/ 

int16_t  x_loc  = 0, y_loc  = 0; 
int16_t  prev_x = 0, prev_y = 0;
extern uint16_t TextColor,BackColor;
/**
* @}
*/ 

/** @defgroup USBH_USR_LCD_Exported_Variables
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_LCD_Private_FunctionPrototypes
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_LCD_Private_Functions
* @{
*/ 

/**
* @brief  HID_MOUSE_UpdatePosition
*         The function is to handle mouse scroll to upadte the mouse position 
*         on display window
* @param   x : USB HID Mouse X co-ordinate
* @param   y :  USB HID Mouse Y co-ordinate
* @retval None
*/
void HID_MOUSE_UpdatePosition (int8_t x, int8_t y)
{
   /* Set the color for button press status */
  LCD_SetTextColor(Green);
  LCD_SetBackColor(Black);
  
  if ((x != 0) || (y != 0)) 
  {
	    
    x_loc += x/2;
    y_loc += y/2;
    
    if(y_loc > ( MOUSE_WINDOW_Y + MOUSE_WINDOW_HEIGHT - 18 ) ){
      y_loc = MOUSE_WINDOW_Y + MOUSE_WINDOW_HEIGHT - 18 ;
    }
    if(y_loc < ( MOUSE_WINDOW_Y + 1 ) ){
      y_loc = MOUSE_WINDOW_Y + 1;
    }  
	  
    if(x_loc > ( MOUSE_WINDOW_X + MOUSE_WINDOW_WIDTH - 8 ) ){
      x_loc = MOUSE_WINDOW_X + MOUSE_WINDOW_WIDTH - 8 ;
    }  

    if(x_loc < ( MOUSE_WINDOW_X + 1 ) ){
      x_loc = MOUSE_WINDOW_X + 1;
    }  
 
    if ((prev_x != 0) && (prev_y != 0))
    {
      PutChar( prev_x , prev_y , ' ' , TextColor , BackColor);
    }
    
    PutChar  ( x_loc , y_loc , 'x' , TextColor , BackColor);
    
    prev_x = x_loc;
    prev_y = y_loc;
  }
}  

/**
* @brief  HID_MOUSE_ButtonPressed
*         The function is to handle mouse button press
* @param  button_idx : mouse button pressed
* @retval None
*/

void HID_MOUSE_ButtonPressed(uint8_t button_idx)
{
  
  /* Set the color for button press status */
  LCD_SetTextColor(Green);
  LCD_SetBackColor(Green);
  
  /* Change the color of button pressed to indicate button press*/
  switch (button_idx)
  {
    /* Left Button Pressed */
  case 0 :
    LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON1_YCHORD,\
    HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT );
    break;
    
    
    /* Right Button Pressed */  
  case 1 :
    LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD,HID_MOUSE_BUTTON2_YCHORD,\
       HID_MOUSE_BUTTON_WIDTH,HID_MOUSE_BUTTON_HEIGHT);
    break; 
    
    /* Middle button Pressed */  
  case 2 :
    LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD,HID_MOUSE_BUTTON3_YCHORD,\
      HID_MOUSE_BUTTON_WIDTH,HID_MOUSE_BUTTON_HEIGHT);
    break;
    
  }
}

/**
* @brief  HID_Mouse_ButtonReleased
*         The function is to handle mouse button release
* @param  button_idx : mouse button released
* @retval None
*/

void HID_MOUSE_ButtonReleased(uint8_t button_idx)
{
  
  /* Set the color for release status */
  LCD_SetTextColor(White);
  LCD_SetBackColor(White);
  
  /* Change the color of button released to default button color*/
  switch (button_idx)
  {
    
    /* Left Button Released */
  case 0 :
    LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON1_YCHORD,\
       HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
    break;
    
    /* Right Button Released */  
  case 1 :
    LCD_DrawFullRect(HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON2_YCHORD,\
       HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
    break;
    
    /* Middle Button Released */  
  case 2 :
    LCD_DrawFullRect (HID_MOUSE_BUTTON_XCHORD, HID_MOUSE_BUTTON3_YCHORD,\
       HID_MOUSE_BUTTON_WIDTH, HID_MOUSE_BUTTON_HEIGHT);
    break;
  }
}

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
