/*!
    \file  systick.c
    \brief the systick configuration file

    \version 2017-02-10, V1.0.0, firmware for GD32F30x
    \version 2018-10-10, V1.1.0, firmware for GD32F30x
    \version 2018-12-25, V2.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "gd32f30x.h"
#include "systick.h"

volatile static uint32_t tick = 0;

/*!
    \brief      configure systick
    \param[in]  none
    \param[out] none
    \retval     none
*/
void systick_config(void)
{
    /* setup systick timer for (SysTick_Freq) Hz interrupts */
    if (SysTick_Config(SystemCoreClock / SysTick_Freq)){
        /* capture error */
        while (1){
        }
    }
    /* configure the systick handler priority */
    NVIC_SetPriority(SysTick_IRQn, 0x05U);
}

/*!
    \brief      delay a time in milliseconds
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay(uint32_t count)
{
		uint32_t utick;
    utick = count + get_tick();

    while(get_tick() < utick){
    }
}

/*!
    \brief      delay a time in milliseconds with low power
    \param[in]  count: count in milliseconds
    \param[out] none
    \retval     none
*/
void delay_lp(uint32_t count)
{
		uint32_t utick;
    utick = count + get_tick();

    while(get_tick() < utick){
			pmu_to_sleepmode(WFI_CMD);
    }
}

/*!
    \brief      delay decrement
    \param[in]  none
    \param[out] none
    \retval     none
*/
void delay_decrement(void)
{
		tick++;
}

/*!
    \brief      get systick tick
    \param[in]  none
    \param[out] none
    \retval     none
*/

uint32_t get_tick(void)
{
	return tick;
}

void systick_DisableIRQ(void)
{
  /* Disable SysTick Interrupt */
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}

void systick_EnableIRQ(void)
{
  /* Enable SysTick Interrupt */
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

void systick_Disable(void)
{
	/* Disable SysTick */
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void systick_Enable(void)
{
	/* Enable SysTick */
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void systick_deinit(void)
{
	SysTick->CTRL  = 0;
	SysTick->LOAD = 0;
	SysTick->VAL = 0;
}
