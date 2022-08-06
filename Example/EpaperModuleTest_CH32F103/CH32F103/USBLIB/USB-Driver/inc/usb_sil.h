/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_sil.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file contains all the functions prototypes for the  
 *                      USB Simplified Interface Layer firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#ifndef __USB_SIL_H
#define __USB_SIL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32f10x.h"

uint32_t USB_SIL_Init(void);
uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize);
uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer);
	 
#ifdef __cplusplus
}

#endif

#endif /* __USB_SIL_H */





