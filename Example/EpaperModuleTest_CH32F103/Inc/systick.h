
#ifndef __SYS_TICK_H
#define __SYS_TICK_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define SysTick_Freq (1000U) // Hz
#define SysTick_Tick (1000U / SysTick_Freq)

    /* configure systick */
    void systick_config(void);
    /* delay a time in milliseconds */
    void delay(uint32_t count);
    /* delay a time in milliseconds with low power */
    void delay_lp(uint32_t count);
    /* delay decrement */
    void delay_decrement(void);
    /* get system tick */
    uint32_t systick_get_tick(void);
    /* suspend system tick */
    void systick_DisableIRQ(void);
    /* resume system tick */
    void systick_EnableIRQ(void);

    void systick_Disable(void);
    void systick_Enable(void);
    void systick_deinit(void);

#ifdef __cplusplus
}
#endif

#endif /* SYS_TICK_H */
