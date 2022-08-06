/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_init.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Initialization routines & global variables
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"

uint8_t	EPindex;
DEVICE_INFO *pInformation;
DEVICE_PROP *pProperty;
uint16_t	SaveState ;
uint16_t  wInterrupt_Mask;
DEVICE_INFO	Device_Info;
USER_STANDARD_REQUESTS  *pUser_Standard_Requests;

/*********************************************************************
 * @fn      USB_Init
 *
 * @brief   USB system initialization
 *
 * @return  none
 */
void USB_Init(void)
{
  pInformation = &Device_Info;
  pInformation->ControlState = 2;
  pProperty = &Device_Property;
  pUser_Standard_Requests = &User_Standard_Requests;
  pProperty->Init();
}





