/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_endp.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Endpoint routines
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_mem.h"
#include "hw_config.h"
#include "usb_istr.h"
#include "usb_pwr.h"

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define IN_FRAME_INTERVAL             5

/* Private variables */
uint8_t USB_Rx_Buffer[USBD_DATA_SIZE];
u16 USB_Rx_Cnt=0; 

/*********************************************************************
 * @fn      EP2_IN_Callback
 *
 * @brief   Endpoint 2 IN.
 *
 * @return  none
 */
void EP2_IN_Callback (void)
{ 
	UserToPMABufferCopy(USB_Rx_Buffer, ENDP2_TXADDR, USB_Rx_Cnt);
	SetEPTxCount(ENDP2, USB_Rx_Cnt);
	SetEPTxValid(ENDP2);   
}

/*********************************************************************
 * @fn      EP2_OUT_Callback
 *
 * @brief   Endpoint 2 IN.
 *
 * @return  none
 */
void EP2_OUT_Callback(void)
{
	uint8_t i; 
	
	USB_Rx_Cnt = USB_SIL_Read(EP2_OUT, USB_Rx_Buffer);	
	
  for(i=0;i<USB_Rx_Cnt;i++)
	{
    USB_Rx_Buffer[i] = ~USB_Rx_Buffer[i];
	}
	
  EP2_IN_Callback(); 
	SetEPRxValid(ENDP2);													
}

/*********************************************************************
 * @fn      SOF_Callback
 *
 * @brief   SOF call back.
 *
 * @return  none
 */
void SOF_Callback(void)
{
	static uint32_t FrameCount = 0;

	if(bDeviceState == CONFIGURED)
	{
		if (FrameCount++ == IN_FRAME_INTERVAL)
		{		
			FrameCount = 0;
			//Handle_USBAsynchXfer();
		}
	}  
}






