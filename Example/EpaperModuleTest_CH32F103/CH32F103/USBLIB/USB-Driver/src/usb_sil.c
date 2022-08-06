/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_sil.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Simplified Interface Layer for Global Initialization and 
 *			           Endpoint  Rea/Write operations.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"


/*********************************************************************
 * @fn      USB_SIL_Init
 *
 * @brief   Initialize the USB Device IP and the Endpoint 0.
 *
 * @return  Status.
 */
uint32_t USB_SIL_Init(void)
{
  _SetISTR(0);
  wInterrupt_Mask = IMR_MSK;
  _SetCNTR(wInterrupt_Mask);
	
  return 0;
}

/*********************************************************************
 * @fn      USB_SIL_Write
 *
 * @brief   Write a buffer of data to a selected endpoint.
 *
 * @param   bEpAddr - The address of the non control endpoint.
 *          pBufferPointer - The pointer to the buffer of data to be written
 *          to the endpoint.
 *
 * @return  Status.
 */
uint32_t USB_SIL_Write(uint8_t bEpAddr, uint8_t* pBufferPointer, uint32_t wBufferSize)
{
  UserToPMABufferCopy(pBufferPointer, GetEPTxAddr(bEpAddr & 0x7F), wBufferSize);
  SetEPTxCount((bEpAddr & 0x7F), wBufferSize);
  
  return 0;
}

/*********************************************************************
 * @fn      USB_SIL_Read
 *
 * @brief   Write a buffer of data to a selected endpoint.
 *
 * @param   bEpAddr - The address of the non control endpoint.
 *          pBufferPointer - The pointer to the buffer of data to be written
 *          to the endpoint.
 *
 * @return  Number of received data (in Bytes).
 */
uint32_t USB_SIL_Read(uint8_t bEpAddr, uint8_t* pBufferPointer)
{
  uint32_t DataLength = 0;

  DataLength = GetEPRxCount(bEpAddr & 0x7F); 
  PMAToUserBufferCopy(pBufferPointer, GetEPRxAddr(bEpAddr & 0x7F), DataLength);

  return DataLength;
}






