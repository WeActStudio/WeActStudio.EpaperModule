/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_int.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Endpoint CTR (Low and High) interrupt's service routines
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"

/* Private variables */
__IO uint16_t SaveRState;
__IO uint16_t SaveTState;

/* Extern variables */
extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */

/*********************************************************************
 * @fn      CTR_LP.
 *
 * @brief   Low priority Endpoint Correct Transfer interrupt's service routine.
 *
 * @return  none
 */
void CTR_LP(void)
{
  __IO uint16_t wEPVal = 0;
	
  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
  {
    EPindex = (uint8_t)(wIstr & ISTR_EP_ID);
		
    if (EPindex == 0)
    {
	    SaveRState = _GetENDPOINT(ENDP0);
	    SaveTState = SaveRState & EPTX_STAT;
	    SaveRState &=  EPRX_STAT;	

	    _SetEPRxTxStatus(ENDP0,EP_RX_NAK,EP_TX_NAK);
			
      if ((wIstr & ISTR_DIR) == 0)
      {
        _ClearEP_CTR_TX(ENDP0);
        In0_Process();

        _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
				
				return;
      }
      else
      {
        wEPVal = _GetENDPOINT(ENDP0);
        
        if ((wEPVal &EP_SETUP) != 0)
        {
          _ClearEP_CTR_RX(ENDP0);
          Setup0_Process();
		      _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
					
          return;
        }
        else if ((wEPVal & EP_CTR_RX) != 0)
        {
          _ClearEP_CTR_RX(ENDP0);
          Out0_Process();
		     _SetEPRxTxStatus(ENDP0,SaveRState,SaveTState);
					
          return;
        }
      }
    }
    else
    {
      wEPVal = _GetENDPOINT(EPindex);
      if ((wEPVal & EP_CTR_RX) != 0)
      {
        _ClearEP_CTR_RX(EPindex);
        (*pEpInt_OUT[EPindex-1])();
      } 

      if ((wEPVal & EP_CTR_TX) != 0)
      {
        _ClearEP_CTR_TX(EPindex);     
        (*pEpInt_IN[EPindex-1])();
      }
    }
  }
}

/*********************************************************************
 * @fn      CTR_HP.
 *
 * @brief   High Priority Endpoint Correct Transfer interrupt's service routine.
 *
 * @return  none
 */
void CTR_HP(void)
{
  uint32_t wEPVal = 0;

  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
  {
    _SetISTR((uint16_t)CLR_CTR); 
    EPindex = (uint8_t)(wIstr & ISTR_EP_ID);   
    wEPVal = _GetENDPOINT(EPindex);
		
    if ((wEPVal & EP_CTR_RX) != 0)
    {
      _ClearEP_CTR_RX(EPindex); 
      (*pEpInt_OUT[EPindex-1])();
    } 
    else if ((wEPVal & EP_CTR_TX) != 0)
    {
      _ClearEP_CTR_TX(EPindex);   
      (*pEpInt_IN[EPindex-1])();
    } 
  }
}









