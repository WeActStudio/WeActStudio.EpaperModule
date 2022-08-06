/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_prop.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : All processing related to Virtual COM Port Demo (Endpoint 0) 
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/
#ifndef __usb_prop_H
#define __usb_prop_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "ch32f10x.h"

#define USBD_GetConfiguration          NOP_Process
//#define USBD_SetConfiguration          NOP_Process
#define USBD_GetInterface              NOP_Process
#define USBD_SetInterface              NOP_Process
#define USBD_GetStatus                 NOP_Process
#define USBD_ClearFeature              NOP_Process
#define USBD_SetEndPointFeature        NOP_Process
#define USBD_SetDeviceFeature          NOP_Process
//#define USBD_SetDeviceAddress          NOP_Process

#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04
#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23


void USBD_init(void);
void USBD_Reset(void);
void USBD_SetConfiguration(void);
void USBD_SetDeviceAddress (void);
void USBD_Status_In (void);
void USBD_Status_Out (void);
RESULT USBD_Data_Setup(uint8_t);
RESULT USBD_NoData_Setup(uint8_t);
RESULT USBD_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *USBD_GetDeviceDescriptor(uint16_t );
uint8_t *USBD_GetConfigDescriptor(uint16_t);
uint8_t *USBD_GetStringDescriptor(uint16_t);
        
uint8_t *USBD_GetLineCoding(uint16_t Length);
uint8_t *USBD_SetLineCoding(uint16_t Length);

#ifdef __cplusplus
}
#endif

#endif /* __usb_prop_H */







