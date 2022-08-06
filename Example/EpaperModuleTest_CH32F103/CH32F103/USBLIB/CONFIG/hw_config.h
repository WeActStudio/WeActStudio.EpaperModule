/********************************** (C) COPYRIGHT *******************************
 * File Name          : hw_config.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Configuration file for USB.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "usb_type.h" 
 
#ifdef	DEBUG
#define printf_usb(X...) printf(X)
#else
#define printf_usb(X...)
#endif 


void Set_USBConfig(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void USB_Port_Set(FunctionalState NewState, FunctionalState Pin_In_IPU);

#endif /* __HW_CONFIG_H */ 








