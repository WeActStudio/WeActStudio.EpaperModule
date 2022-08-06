#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "ch32f10x.h"

    void board_button_init(void);
    uint8_t board_button_getstate(void);
    void board_led_init(void);
    void board_led_toggle(void);
    void board_led_set(uint8_t set);

#ifdef __cplusplus
}
#endif

#endif
