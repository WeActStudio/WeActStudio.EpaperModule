#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "apm32f10x.h"
#include <stdio.h>

#define _value(value) #value
#define printf_name(name) printf(_value(> #name)), printf("\r\n");
#define printf_value(name, value) printf(_value(> #name)), printf(" "), printf(#value), printf(" :%d\r\n", value);

    void board_usart_init(void);
    void board_led_init(void);
    void board_led_on(void);
    void board_led_off(void);
    void board_led_toggle(void);
    void board_button_init(void);
    uint8_t board_button_state_get(void);

#ifdef __cplusplus
}
#endif

#endif
