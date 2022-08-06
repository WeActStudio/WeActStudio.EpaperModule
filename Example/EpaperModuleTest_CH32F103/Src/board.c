/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "board.h"

void board_button_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t board_button_getstate(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
}

void board_led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void board_led_toggle(void)
{
    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_2) == Bit_SET ? GPIO_ResetBits(GPIOB, GPIO_Pin_2) : GPIO_SetBits(GPIOB, GPIO_Pin_2);
}

void board_led_set(uint8_t set)
{
    if (set)
        GPIO_SetBits(GPIOB, GPIO_Pin_2);
    else
        GPIO_ResetBits(GPIOB, GPIO_Pin_2);
}
