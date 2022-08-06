#ifndef __BOARD_H
#define __BOARD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "at32f403a_407.h"

#define DELAY 100
#define FAST 1
#define SLOW 4

    void led_init(void);
    void led_toggle(void);
    void led_set(confirm_state bit_state);

    void button_init(void);
    flag_status button_getstate(void);

    void button_exint_init(void);
    void button_isr(void);

    extern uint8_t g_speed;

#ifdef __cplusplus
}
#endif

#endif
