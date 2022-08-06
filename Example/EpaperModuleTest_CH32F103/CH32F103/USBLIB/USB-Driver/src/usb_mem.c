/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_mem.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Utility functions for memory transfers to/from PMA
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"


/*********************************************************************
 * @fn      UserToPMABufferCopy
 *
 * @brief   Copy a buffer from user memory area to packet memory area (PMA)
 *
 * @param   pbUsrBuf - pointer to user memory area.
 *          wPMABufAddr - address into PMA.
 *          wNBytes - no. of bytes to be copied.
 *
 * @return  none
 */	
void UserToPMABufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  uint32_t n = (wNBytes + 1) >> 1;   
  uint32_t i, temp1, temp2;
  uint16_t *pdwVal;
  pdwVal = (uint16_t *)(wPMABufAddr * 2 + PMAAddr);
	
  for (i = n; i != 0; i--){
    temp1 = (uint16_t) * pbUsrBuf;
    pbUsrBuf++;
    temp2 = temp1 | (uint16_t) * pbUsrBuf << 8;
    *pdwVal++ = temp2;
    pdwVal++;
    pbUsrBuf++;
  }
}

/*********************************************************************
 * @fn      PMAToUserBufferCopy
 *
 * @brief   Copy a buffer from user memory area to packet memory area (PMA)
 *
 * @param   pbUsrBuf - pointer to user memory area.
 *          wPMABufAddr - address into PMA.
 *          wNBytes - no. of bytes to be copied.
 *
 * @return  none
 */
void PMAToUserBufferCopy(uint8_t *pbUsrBuf, uint16_t wPMABufAddr, uint16_t wNBytes)
{
  uint32_t n = (wNBytes + 1) >> 1;
  uint32_t i;
  uint32_t *pdwVal;
	
  pdwVal = (uint32_t *)(wPMABufAddr * 2 + PMAAddr);
	
  for (i = n; i != 0; i--){
    *(uint16_t*)pbUsrBuf++ = *pdwVal++;
    pbUsrBuf++;
  } 
}






