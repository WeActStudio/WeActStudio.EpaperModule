/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_mem.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : This file contains all the functions prototypes for the  
 *                      USB Initialization firmware library.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#ifndef __USB_MEM_H
#define __USB_MEM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32f10x.h"

void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes);


#ifdef __cplusplus
}
#endif

#endif  /*__USB_MEM_H*/






