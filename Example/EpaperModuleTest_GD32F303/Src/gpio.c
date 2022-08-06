#include "gpio.h"

void gpio_config(void)
{
	/* enable  clock */
	rcu_periph_clock_enable(RCU_AF);

	rcu_periph_clock_enable(KEY_RCU);
	rcu_periph_clock_enable(LED_PB2_RCU);
	
	/* JTAG-DP disabled and SW-DP enabled */
	gpio_pin_remap_config(GPIO_SWJ_SWDPENABLE_REMAP,ENABLE);
	
	/* configure button pin as input */
  gpio_init(KEY_PORT, GPIO_MODE_IPD, GPIO_OSPEED_50MHZ, KEY_PIN);
	/* configure led pin as output */
	gpio_init(LED_PB2_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, LED_PB2_PIN);
	gpio_bit_reset(LED_PB2_PORT,LED_PB2_PIN);
}
