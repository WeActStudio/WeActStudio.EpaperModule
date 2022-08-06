/********************************** (C) COPYRIGHT *******************************
 * File Name          : usb_pwr.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : Connection/disconnection & power management
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_pwr.h"
#include "hw_config.h"

__IO uint32_t bDeviceState = UNCONNECTED; 
__IO bool fSuspendEnabled = TRUE;  
__IO uint32_t EP[8];

struct
{
  __IO RESUME_STATE eState;
  __IO uint8_t bESOFcnt;
}
ResumeS;

__IO uint32_t remotewakeupon=0;

/*********************************************************************
 * @fn      PowerOn
 *
 * @brief   Enable power on.
 *
 * @return  USB_SUCCESS.
 */
RESULT PowerOn(void)
{
  uint16_t wRegVal;

  wRegVal = CNTR_FRES;
  _SetCNTR(wRegVal);
  wInterrupt_Mask = 0;
  _SetCNTR(wInterrupt_Mask);
  _SetISTR(0);
  wInterrupt_Mask = CNTR_RESETM | CNTR_SUSPM | CNTR_WKUPM;
  _SetCNTR(wInterrupt_Mask);
  
  return USB_SUCCESS;
}

/*********************************************************************
 * @fn      PowerOff
 *
 * @brief   handles switch-off conditions
 *
 * @return  USB_SUCCESS.
 */
RESULT PowerOff()
{
  _SetCNTR(CNTR_FRES); 
  _SetISTR(0); 
  _SetCNTR(CNTR_FRES + CNTR_PDWN);

  return USB_SUCCESS;
}

/*********************************************************************
 * @fn      Suspend
 *
 * @brief   sets suspend mode operating conditions
 *
 * @return  USB_SUCCESS.
 */
void Suspend(void)
{
	uint32_t i =0;
	uint16_t wCNTR; 
  __IO uint32_t savePWR_CR=0;

	wCNTR = _GetCNTR();  
  for (i=0;i<8;i++) EP[i] = _GetENDPOINT(i);
	
	wCNTR|=CNTR_RESETM;
	_SetCNTR(wCNTR);
	
	wCNTR|=CNTR_FRES;
	_SetCNTR(wCNTR);
	
	wCNTR&=~CNTR_FRES;
	_SetCNTR(wCNTR);

	while((_GetISTR()&ISTR_RESET) == 0);
	
	_SetISTR((uint16_t)CLR_RESET);
	
	for (i=0;i<8;i++)
	_SetENDPOINT(i, EP[i]);
	
	wCNTR |= CNTR_FSUSP;
	_SetCNTR(wCNTR);
	
	wCNTR = _GetCNTR();
	wCNTR |= CNTR_LPMODE;
	_SetCNTR(wCNTR);

	Enter_LowPowerMode();
}

/*********************************************************************
 * @fn      Resume_Init
 *
 * @brief   Handles wake-up restoring normal operations
 *
 * @return  USB_SUCCESS.
 */
void Resume_Init(void)
{
  uint16_t wCNTR;
  
  wCNTR = _GetCNTR();
  wCNTR &= (~CNTR_LPMODE);
  _SetCNTR(wCNTR);      
  Leave_LowPowerMode();
  _SetCNTR(IMR_MSK);
}

/*********************************************************************
 * @fn      Resume
 *
 * @brief   This is the state machine handling resume operations and
 *          timing sequence. The control is based on the Resume structure
 *          variables and on the ESOF interrupt calling this subroutine
 *          without changing machine state.
 *
 * @param   a state machine value (RESUME_STATE)
 *         RESUME_ESOF doesn't change ResumeS.eState allowing
 *         decrementing of the ESOF counter in different states.
 *
 * @return  none
 */
void Resume(RESUME_STATE eResumeSetVal)
{
  uint16_t wCNTR;

  if (eResumeSetVal != RESUME_ESOF)
	{
   ResumeS.eState = eResumeSetVal;
	}
	
  switch (ResumeS.eState)
  {
    case RESUME_EXTERNAL:
      if (remotewakeupon ==0)
      {
        Resume_Init();
        ResumeS.eState = RESUME_OFF;
      }
      else 
      {
        ResumeS.eState = RESUME_ON;
      }
      break;
			
    case RESUME_INTERNAL:
      Resume_Init();
      ResumeS.eState = RESUME_START;
      remotewakeupon = 1;
      break;
		
    case RESUME_LATER:
      ResumeS.bESOFcnt = 2;
      ResumeS.eState = RESUME_WAIT;
      break;
		
    case RESUME_WAIT:
      ResumeS.bESOFcnt--;
      if (ResumeS.bESOFcnt == 0)
        ResumeS.eState = RESUME_START;
      break;
			
    case RESUME_START:
      wCNTR = _GetCNTR();
      wCNTR |= CNTR_RESUME;
      _SetCNTR(wCNTR);
      ResumeS.eState = RESUME_ON;
      ResumeS.bESOFcnt = 10;
      break;
		
    case RESUME_ON:    
      ResumeS.bESOFcnt--;
      if (ResumeS.bESOFcnt == 0)
      {
        wCNTR = _GetCNTR();
        wCNTR &= (~CNTR_RESUME);
        _SetCNTR(wCNTR);
        ResumeS.eState = RESUME_OFF;
        remotewakeupon = 0;
      }
      break;
			
    case RESUME_OFF:
			
    case RESUME_ESOF:
			
    default:
      ResumeS.eState = RESUME_OFF;
      break;
  }
}






