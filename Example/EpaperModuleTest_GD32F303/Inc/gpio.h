#ifndef gpio_H
#define gpio_H

#ifdef __cplusplus
extern "C" {
#endif
	
#include "gd32f30x.h"

#define KEY_RCU  RCU_GPIOA
#define KEY_PORT GPIOA
#define KEY_PIN GPIO_PIN_0

#define LED_PB2_RCU  RCU_GPIOB
#define LED_PB2_PORT GPIOB
#define LED_PB2_PIN  GPIO_PIN_2

void gpio_config(void);

#ifdef __cplusplus
}
#endif

#endif
