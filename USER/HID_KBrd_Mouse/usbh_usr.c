/**
  ******************************************************************************
  * @file    usbh_usr.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11/29/2010
  * @brief   This file includes the user application layer
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
#include "usbh_hid_mouse.h"
#include "usbh_hid_keybd.h"
#include "LCD.h" 


/** @addtogroup USBH_USER
* @{
*/

/** @addtogroup USBH_HID_DEMO_USER_CALLBACKS
* @{
*/

/** @defgroup USBH_USR
* @brief This file is the Header file for usbh_usr.c
* @{
*/ 


/** @defgroup USBH_CORE_Exported_TypesDefinitions
* @{
*/ 
#define KYBRD_FIRST_COLUMN               48
#define KYBRD_LAST_COLUMN                240
#define KYBRD_FIRST_LINE                 0
#define KYBRD_LAST_LINE                  320


/**
* @}
*/ 
int16_t  KeybrdCharXpos           = 0;
int16_t  KeybrdCharYpos           = 0;
extern  int16_t  x_loc, y_loc; 
extern __IO int16_t  prev_x, prev_y;
extern uint8_t Line;
extern uint16_t TextColor,BackColor;

/** @addtogroup USER
* @{
*/

/** @defgroup USBH_USR 
* @brief    This file includes the user application layer
* @{
*/ 

/** @defgroup USBH_CORE_Exported_Types
* @{
*/ 



/** @defgroup USBH_USR_Private_Defines
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Macros
* @{
*/ 
/**
* @}
*/ 

/** @defgroup USBH_USR_Private_Variables
* @{
*/

/*  Points to the DEVICE_PROP structure of current device */
/*  The purpose of this register is to speed up the execution */

USBH_Usr_cb_TypeDef USR_Callbacks =
{
  USBH_USR_Init,
  USBH_USR_DeviceAttached,
  USBH_USR_ResetDevice,
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,
  USBH_USR_Device_DescAvailable,
  USBH_USR_DeviceAddressAssigned,
  USBH_USR_Configuration_DescAvailable,
  USBH_USR_Manufacturer_String,
  USBH_USR_Product_String,
  USBH_USR_SerialNum_String,
  USBH_USR_EnumerationDone,
  USBH_USR_UserInput,
  USBH_USR_DeviceNotSupported,
  USBH_USR_UnrecoveredError
};

/**
* @}
*/

/** @defgroup USBH_USR_Private_Constants
* @{
*/ 
/*--------------- LCD Messages ---------------*/
const uint8_t MSG_HOST_INIT[]          = "> HOST LIBRARY INITIALIZED          ";
const uint8_t MSG_DEV_ATTACHED[]       = "> DEVICE ATTACHED                   ";
const uint8_t MSG_DEV_DISCONNECTED[]   = "> DEVICE DISCONNECTED               ";
const uint8_t MSG_DEV_ENUMERATED[]     = "> ENUMERATION COMPLETED             ";
const uint8_t MSG_DEV_FULLSPEED[]      = "> DEVICE IS FULL SPEED              ";
const uint8_t MSG_DEV_LOWSPEED[]       = "> DEVICE IS LOW SPEED              " ;
const uint8_t MSG_DEV_ERROR[]          = "> DEVICE ERROR";

const uint8_t MSG_MSC_CLASS[]          = "> DEVICE SUPPORTS MASS STORAGE CLASS";
const uint8_t MSG_HID_CLASS[]          = "> DEVICE SUPPORTS HID CLASS";



const uint8_t USB_HID_Title[]     = "            USB HOST HID DEMO            ";
const uint8_t USB_HID_Mode[]           = "USB HOST Mode";
const uint8_t USB_HID_MouseStatus[]    = "HID Demo Device : Mouse";
const uint8_t USB_HID_KeybrdStatus[]   = "HID Demo Device : Keyboard";
const uint8_t MSG_UNREC_ERROR[]     = "> UNRECOVERED ERROR STATE              ";
/**
* @}
*/



/** @defgroup USBH_USR_Private_FunctionPrototypes
* @{
*/ 
/**
* @}
*/ 


/** @defgroup USBH_USR_Private_Functions
* @{
*/ 





/**
* @brief  USBH_USR_Init 
*         Displays the message on LCD for host lib initialization
* @param  None
* @retval None
*/
void USBH_USR_Init(void)
{
  /* Set default screen color*/
  LCD_Clear(Black);
 
  Line = 0;

  /* Display the application header */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  
  LCD_DisplayStringLine( Line++ , "       STM32F105/7 USB HOST DEMO       ");
  
  LCD_SetBackColor(Black);  
}

/**
* @brief  USBH_USR_DeviceAttached 
*         Displays the message on LCD on device attached
* @param  None
* @retval None
*/
void USBH_USR_DeviceAttached(void)
{
  
  LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_DEV_ATTACHED);
  
}


/**
* @brief  USBH_USR_UnrecoveredError
* @param  None
* @retval None
*/
void USBH_USR_UnrecoveredError (void)
{
  
  /* Set default screen color*/
  LCD_Clear(Black);

  Line = 0;
  
  /* Display the application header */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  
  LCD_DisplayStringLine( Line++ , "       STM32F105/7 USB HOST DEMO       ");
  
  LCD_SetBackColor(Red); 
  
  LCD_DisplayStringLine( Line++ ,  (uint8_t *)MSG_UNREC_ERROR);
  
  LCD_SetBackColor(Black); 
}

/**
* @brief  USBH_USR_DeInit
*         Deint User state and associated variables
* @param  None
* @retval None
*/
void USBH_USR_DeInit(void)
{
  
}


/**
* @brief  USBH_DisconnectEvent
*         Device disconnect event
* @param  None
* @retval None
*/
void USBH_USR_DeviceDisconnected (void)
{
  
  /* Set default screen color*/
  LCD_Clear(Black);
  
  Line = 0;

  /* Display the application header */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  
  LCD_DisplayStringLine( Line++ , "       STM32F105/7 USB HOST DEMO       ");
  
  LCD_SetBackColor(Black);  
  
  LCD_DisplayStringLine( Line++ ,"> DEVICE DISCONNECTED!");
}

/**
* @brief  USBH_USR_ResetUSBDevice 
*         Reset USB Device
* @param  None
* @retval None
*/
void USBH_USR_ResetDevice(void)
{
  /* Users can do their application actions here for the USB-Reset */
}


/**
* @brief  USBH_USR_DeviceSpeedDetected 
*         Displays the message on LCD for device speed
* @param  Devicespeed : Device Speed
* @retval None
*/
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
  if(DeviceSpeed == HPRT0_PRTSPD_FULL_SPEED)
  {
    LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_DEV_FULLSPEED);
  }
  else if(DeviceSpeed == HPRT0_PRTSPD_LOW_SPEED)
  {
    LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_DEV_LOWSPEED);
  }
  else
  {
    LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_DEV_ERROR);
  }
}

/**
* @brief  USBH_USR_Device_DescAvailable 
*         Displays the message on LCD for device descriptor
* @param  DeviceDesc : device descriptor
* @retval None
*/
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{
  uint8_t temp[50];    
  USBH_DevDesc_TypeDef *hs;
  hs = DeviceDesc;  
  
  
  sprintf((char *)temp , "VID = %04Xh" , (uint32_t)(*hs).idVendor); 
  LCD_DisplayStringLine( Line++ , temp);
  
  
  sprintf((char *)temp , "PID = %04Xh" , (uint32_t)(*hs).idProduct); 
  LCD_DisplayStringLine( Line++ , temp);
}

/**
* @brief  USBH_USR_DeviceAddressAssigned 
*         USB device is successfully assigned the Address 
* @param  None
* @retval None
*/
void USBH_USR_DeviceAddressAssigned(void)
{
  
}


/**
* @brief  USBH_USR_Conf_Desc 
*         Displays the message on LCD for configuration descriptor
* @param  ConfDesc : Configuration descriptor
* @retval None
*/
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
  USBH_InterfaceDesc_TypeDef *id;
  uint8_t temp[50];
  
  id = itfDesc;
  
  sprintf ((char *)temp, "NumEndpoints = %d" , (uint32_t)(*id).bNumEndpoints);
  LCD_DisplayStringLine( Line++ , temp);
  
  
  if((*id).bInterfaceClass  == 0x08)
  {
    
    LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_MSC_CLASS);
  }
  else if((*id).bInterfaceClass  == 0x03)
  {
    
    LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_HID_CLASS);
  }    
}

/**
* @brief  USBH_USR_Manufacturer_String 
*         Displays the message on LCD for Manufacturer String 
* @param  ManufacturerString : Manufacturer String of Device
* @retval None
*/
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
  char temp[100];
  sprintf(temp, "Manufacturer : %s", (char *)ManufacturerString);
  LCD_DisplayStringLine( Line++ , (uint8_t *)temp);
  
}

/**
* @brief  USBH_USR_Product_String 
*         Displays the message on LCD for Product String
* @param  ProductString : Product String of Device
* @retval None
*/
void USBH_USR_Product_String(void *ProductString)
{
  char temp[100];
  sprintf((char *)temp, "Product : %s", (char *)ProductString);  
  LCD_DisplayStringLine( Line++ , (uint8_t *)temp);
  
}

/**
* @brief  USBH_USR_SerialNum_String 
*         Displays the message on LCD for SerialNum_String 
* @param  SerialNumString : SerialNum_String of device
* @retval None
*/
void USBH_USR_SerialNum_String(void *SerialNumString)
{
  uint8_t temp[100];
  sprintf((char *)temp, "Serial Number : %x", SerialNumString);    
  LCD_DisplayStringLine( Line++, temp);
} 

/**
* @brief  USBH_USR_EnumDone 
*         Device enumeration is complete
* @param  None
* @retval None
*/
void USBH_USR_EnumDone(void)
{
  /* Enumeration complete */
  LCD_DisplayStringLine( Line++ , (uint8_t *)MSG_DEV_ENUMERATED);  
  
}


/**
* @brief  EnumerationDone 
*         User response request is displayed to ask for
*         application jump to class
* @param  None
* @retval None
*/
void USBH_USR_EnumerationDone(void)
{
  /* Ask for user respinse to execute jump to application display */
  LCD_DisplayStringLine\
    ( Line++ , "----------------------------------------");  
  LCD_DisplayStringLine\
    ( Line++ , " To see HID device operation            ");
  LCD_DisplayStringLine\
    ( Line++ , " Press Key                              ");    
  
} 

/**
* @brief  USBH_USR_DeviceNotSupported
*         Device is not supported
* @param  None
* @retval None
*/
void USBH_USR_DeviceNotSupported(void)
{
  
  /* Set default screen color*/
  LCD_Clear(Black);
  
  Line = 0;

  /* Display the application header */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  
  LCD_DisplayStringLine( Line++ , "       STM32F105/7 USB HOST DEMO       ");
  
  LCD_SetBackColor(Black);  
  LCD_DisplayStringLine( Line++ ,">\
    THE FIRMWARE SUPPORTS HID CLASS DEVICES!");       
  LCD_DisplayStringLine( Line++ ,">\
    ATTACHED DEVICE IS NOT SUPPORTED!");               
  
}  

/**
* @brief  USBH_USR_UserInput
*         User Action for application state entry
* @param  None
* @retval USBH_USR_Status : User response for key button
*/
USBH_USR_Status USBH_USR_UserInput(void)
{
  USBH_USR_Status usbh_usr_status;
  
  usbh_usr_status = USBH_USR_NO_RESP;  
  
  /*Key is in polling mode to detect user action */
  if( !GPIO_ReadInputDataBit(KEYA_PORT, KEYA_PORT_PIN) || GPIO_ReadInputDataBit(KEYB_PORT, KEYB_PORT_PIN) || \
       GPIO_ReadInputDataBit(KEYC_PORT, KEYC_PORT_PIN) ) 
  {
 
    usbh_usr_status = USBH_USR_RESP_OK;
    
  } 
  return usbh_usr_status;
}  

/**
* @brief  USBH_USR_OverCurrentDetected
*         Device Overcurrent detection event
* @param  None
* @retval None
*/
void USBH_USR_OverCurrentDetected (void)
{
  
  /*Display color on LCD------------------------------------------------------*/
  LCD_Clear(Black);
  
  Line = 0;

  /* Display the application header */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  
  LCD_DisplayStringLine( Line++ , "       STM32F105/7 USB HOST DEMO       ");
  
  LCD_SetBackColor(Black); 
  
  /*Display Title------------------------------------------------------------*/
  /* Set the LCD Text Color */
  LCD_SetTextColor(White);
  LCD_DisplayStringLine( Line++ , "ERR : OVERCURRENT DETECTED ");
  
  
}

/**
* @brief  USR_MOUSE_Init
*         Init Mouse window
* @param  None
* @retval None
*/
void USR_MOUSE_Init	(void)
{
  /* Set default screen color*/
  LCD_Clear(Black);
  
  Line = 0;

  /* Display the application header */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  LCD_DisplayStringLine( Line++ ,(uint8_t*)USB_HID_Title);
  
  
  LCD_SetBackColor(Black); 
  
  LCD_DisplayStringLine( Line++ ,\
    (uint8_t*)USB_HID_Mode);
  
  LCD_DisplayStringLine( Line++ ,\
    (uint8_t*)USB_HID_MouseStatus);  
  
  LCD_SetTextColor(White);    
  
  /* Display Mouse Window */
  LCD_DrawRect(MOUSE_WINDOW_X,
               MOUSE_WINDOW_Y, 
               MOUSE_WINDOW_WIDTH,
               MOUSE_WINDOW_HEIGHT);
  
  HID_MOUSE_ButtonReleased(0);
  HID_MOUSE_ButtonReleased(1);
  HID_MOUSE_ButtonReleased(2);
  

  LCD_SetTextColor(Green);
  LCD_SetBackColor(Black);
 
  PutChar( MOUSE_WINDOW_X + MOUSE_WINDOW_WIDTH / 2 - 4 , MOUSE_WINDOW_Y + MOUSE_WINDOW_HEIGHT / 2 - 8  , 'x' , TextColor , BackColor);	  

  x_loc  = MOUSE_WINDOW_X + MOUSE_WINDOW_WIDTH / 2 - 4 ;
  y_loc  = MOUSE_WINDOW_Y + MOUSE_WINDOW_HEIGHT / 2 - 8; 
  prev_x = x_loc;
  prev_y = y_loc;
  
}

/**
* @brief  USR_MOUSE_ProcessData
*         Process Mouse data
* @param  data : Mouse data to be displayed
* @retval None
*/
void USR_MOUSE_ProcessData(HID_MOUSE_Data_TypeDef *data)
{
  
  uint8_t idx = 1;   
  static uint8_t b_state[3] = { 0, 0 , 0};
  
  if ((data->x != 0) && (data->y != 0))
  {
    HID_MOUSE_UpdatePosition(data->x , data->y);
  }
  
  for ( idx = 0 ; idx < 3 ; idx ++)
  {
    

    if(data->button & 1 << idx) 
    {
      if(b_state[idx] == 0)
      {
        HID_MOUSE_ButtonPressed (idx);
        b_state[idx] = 1;
      }
    }
    else
    {
      if(b_state[idx] == 1)
      {
        HID_MOUSE_ButtonReleased (idx);
        b_state[idx] = 0;
      }
    }
  }
  
  
}

/**
* @brief  USR_KEYBRD_Init
*         Init Keyboard window
* @param  None
* @retval None
*/
void  USR_KEYBRD_Init (void)
{
  /*Display color on LCD------------------------------------------------------*/
  LCD_Clear(Black);
  
  Line = 0;

  /*Display Title------------------------------------------------------------*/
  /* Set the LCD Text Color */
  LCD_SetBackColor(Blue);  
  LCD_SetTextColor(White);
  LCD_DisplayStringLine( Line++ ,(uint8_t*)USB_HID_Title);
  
  /* Set the LCD Text Color */
  LCD_SetBackColor(Black); 
  
  /* Display application mode title------------------------------------------*/
  /* For smaller font display ,Line co-ordinate is calculated in terms of 
  line0+(SMALL_FONT_LINE_WIDTH*line number)*-------------------------------*/
  LCD_DisplayStringLine( Line++ ,\
    (uint8_t*)USB_HID_Mode);
  
  LCD_DisplayStringLine( Line++ ,\
    (uint8_t*)USB_HID_KeybrdStatus);  
  
  /* Uncomment below line to display pressed characters in Green color--------*/
  LCD_SetTextColor(Green);
  
  KeybrdCharXpos = KYBRD_FIRST_LINE ;
  KeybrdCharYpos = KYBRD_FIRST_COLUMN;
}


/**
* @brief  USR_KEYBRD_ProcessData
*         Process Keyboard data
* @param  data : Keyboard data to be displayed
* @retval None
*/
void  USR_KEYBRD_ProcessData (uint8_t data)
{
  
  
  if(data == '\n')			 /* »Ø³µ */
  {   
    KeybrdCharYpos += 16; 
   /*Check if the Y position has reached the last column*/
    if( KeybrdCharYpos >= KYBRD_LAST_COLUMN )
    {
      KeybrdCharYpos = KYBRD_FIRST_COLUMN;
   
	}    
  }
  else if (data == '\r')	 /* ÍËÐÐ */
  {    
	PutChar(KeybrdCharXpos,KeybrdCharYpos, ' ' , TextColor , BackColor);

	if( KeybrdCharYpos == KYBRD_FIRST_COLUMN )
	{
	   if( KeybrdCharXpos != KYBRD_FIRST_LINE  )
	   {
          /*Increment char X position*/
          KeybrdCharXpos -= 8;
	   }
	}
	else
	{
	   KeybrdCharXpos -= 8;
	}
    /*Check if the X position has reached the last line*/
    if( KeybrdCharXpos < KYBRD_FIRST_LINE )
    {
	  KeybrdCharXpos = KYBRD_LAST_LINE;
      KeybrdCharYpos -= 16;   
    }

    /*Check if the Y position has reached the last column*/
    if( KeybrdCharYpos < KYBRD_FIRST_COLUMN )
    {
      KeybrdCharYpos = KYBRD_FIRST_COLUMN; 
	}
  }
  else
  {
	if (data == '\0')
	{
	   data = '?'; 
	}

	/* Update the cursor position on LCD */
	PutChar( KeybrdCharXpos , KeybrdCharYpos  , data , TextColor , BackColor);	  

	/*Increment char X position*/
    KeybrdCharXpos += 8;

    /*Check if the X position has reached the last line*/
    if( KeybrdCharXpos >= KYBRD_LAST_LINE )
    {
	  KeybrdCharXpos = KYBRD_FIRST_LINE;
      KeybrdCharYpos += 16;   
    }

    /*Check if the Y position has reached the last column*/
    if( KeybrdCharYpos >= KYBRD_LAST_COLUMN )
    {
      KeybrdCharYpos = KYBRD_FIRST_COLUMN; 
	}

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

/**
* @}
*/
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/







