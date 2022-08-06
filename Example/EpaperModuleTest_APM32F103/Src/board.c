/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "board.h"
#include "apm32f10x_gpio.h"
#include "apm32f10x_rcm.h"
#include "apm32f10x_usart.h"

void board_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;
    USART_Config_T USART_ConfigStruct;
    
    RCM_EnableAPB2PeriphClock((RCM_APB2_PERIPH_T)(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_USART1));

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    USART_ConfigStruct.baudRate = 115200;
    USART_ConfigStruct.hardwareFlow = USART_HARDWARE_FLOW_NONE;
    USART_ConfigStruct.mode = USART_MODE_TX;
    USART_ConfigStruct.parity = USART_PARITY_NONE;
    USART_ConfigStruct.stopBits = USART_STOP_BIT_1;
    USART_ConfigStruct.wordLength = USART_WORD_LEN_8B;
    USART_Config(USART1, &USART_ConfigStruct);

    USART_Enable(USART1);
}

/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    USART_TxData(USART1, (uint8_t)ch);
    while (RESET == USART_ReadStatusFlag(USART1, USART_FLAG_TXBE))
        ;

    return ch;
}

void board_led_init(void)
{
    GPIO_Config_T configStruct;
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);

    configStruct.pin = GPIO_PIN_2;
    configStruct.mode = GPIO_MODE_OUT_PP;
    configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOB, &configStruct);
}

void board_led_on(void)
{
    GPIO_WriteBitValue(GPIOB, GPIO_PIN_2, BIT_SET);
}

void board_led_off(void)
{
    GPIO_WriteBitValue(GPIOB, GPIO_PIN_2, BIT_RESET);
}

void board_led_toggle(void)
{
    GPIOB->ODATA ^= GPIO_PIN_2;
}

void board_button_init(void)
{
    GPIO_Config_T configStruct;
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);

    configStruct.pin = GPIO_PIN_0;
    configStruct.mode = GPIO_MODE_IN_PD;
    configStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &configStruct);
}

uint8_t board_button_state_get(void)
{
    if(GPIO_ReadInputBit(GPIOA, GPIO_PIN_0) == BIT_RESET)
        return 0;
    else
        return 1;
}
