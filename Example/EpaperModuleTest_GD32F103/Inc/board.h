#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "gd32f10x.h"

void board_usart0_init(void);
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
