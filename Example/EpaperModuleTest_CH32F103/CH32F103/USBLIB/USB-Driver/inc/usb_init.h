/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_init.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file contains all the functions prototypes for the  
 *                      USB Initialization firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#ifndef __USB_INIT_H
#define __USB_INIT_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "ch32f10x.h"

	 
void USB_Init(void);
extern uint8_t	EPindex;
extern DEVICE_INFO*	pInformation;
extern DEVICE_PROP*	pProperty;
extern USER_STANDARD_REQUESTS *pUser_Standard_Requests;
extern uint16_t	SaveState ;
extern uint16_t wInterrupt_Mask;

#ifdef __cplusplus
}

#endif


#endif /* __USB_INIT_H */





