/********************************** (C) COPYRIGHT *******************************
 * File Name          : hw_config.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2019/10/15
 * Description        : USB configuration file.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
*******************************************************************************/ 
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_istr.h"
#include "hw_config.h"
#include "usb_pwr.h"  
#include "string.h"	
#include "stdarg.h"		 
#include "stdio.h"	

/*********************************************************************
 * @fn      USBWakeUp_IRQHandler
 *
 * @brief   This function handles USB wake up exception.
 *
 * @return  none
 */
void USBWakeUp_IRQHandler(void) 
{
	EXTI_ClearITPendingBit(EXTI_Line18);
} 

/*********************************************************************
 * @fn      USBWakeUp_IRQHandler
 *
 * @brief   This function handles USB exception.
 *
 * @return  none
 */
void USB_LP_CAN1_RX0_IRQHandler(void) 
{
	USB_Istr();
} 

/*********************************************************************
 * @fn      Set_USBConfig
 *
 * @brief   Set_USBConfig.
 *
 * @return  none
 */
void Set_USBConfig( )
{
	
	RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);	 		 
}

/*********************************************************************
 * @fn      Enter_LowPowerMode
 *
 * @brief   Enter low power mode.
 *
 * @return  none
 */
void Enter_LowPowerMode(void)
{  
 	printf("usb enter low power mode\r\n");
	bDeviceState=SUSPENDED;
} 

/*********************************************************************
 * @fn      Leave_LowPowerMode
 *
 * @brief   Leave low power mode.
 *
 * @return  none
 */
void Leave_LowPowerMode(void)
{
	DEVICE_INFO *pInfo=&Device_Info;
	printf("leave low power mode\r\n"); 
	if (pInfo->Current_Configuration!=0)bDeviceState=CONFIGURED; 
	else bDeviceState = ATTACHED; 
} 

/*********************************************************************
 * @fn      USB_Interrupts_Config
 *
 * @brief   Configrate USB interrupt.
 *
 * @return  none
 */
void USB_Interrupts_Config(void)
{ 
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	EXTI_ClearITPendingBit(EXTI_Line18);
	EXTI_InitStructure.EXTI_Line = EXTI_Line18; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure); 	 

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&NVIC_InitStructure);   
}	

/*********************************************************************
 * @fn      USB_Port_Set
 *
 * @brief   Set USB IO port.
 *
 * @param   NewState - DISABLE or ENABLE.
 *          Pin_In_IPU - Enables or Disables intenal pull-up resistance.
 *
 * @return  none
 */
void USB_Port_Set(FunctionalState NewState, FunctionalState Pin_In_IPU)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	if(NewState) {
		_SetCNTR(_GetCNTR()&(~(1<<1)));
		GPIOA->CFGHR&=0XFFF00FFF;
		GPIOA->OUTDR&=~(3<<11);	//PA11/12=0
		GPIOA->CFGHR|=0X00088000;	// IPD
	}
	else
	{	  
		_SetCNTR(_GetCNTR()|(1<<1));  
		GPIOA->CFGHR&=0XFFF00FFF;
		GPIOA->OUTDR&=~(3<<11);	//PA11/12=0
		GPIOA->CFGHR|=0X00033000;	// LOW
	}
	
	if(Pin_In_IPU) (EXTEN->EXTEN_CTR) |= EXTEN_USBD_PU_EN; 
	else (EXTEN->EXTEN_CTR) &= ~EXTEN_USBD_PU_EN;
}  








