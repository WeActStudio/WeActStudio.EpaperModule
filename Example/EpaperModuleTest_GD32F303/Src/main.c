/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "gd32f30x.h"
#include <stdio.h>

#include "systick.h"
#include "usart.h"
#include "gpio.h"

float temperature;
float vref_value;

void adc_config(void);
void jump_to_app(uint32_t addr);

#include "epaper.h"
#include "bmp.h"

// define for White Black Red Epaper Module
#define EPD_BWR

uint8_t image_bw[4000];
#ifdef EPD_BWR
uint8_t image_red[4000];
#endif

/*!
	\brief      main function
	\param[in]  none
	\param[out] none
	\retval     none
*/
int main(void)
{
	uint8_t text[20];

#ifdef HID_IAP
	/* Soft :GD32 MCU HID IAP Programmer, Bootloader Size :8KB */
	/* if use HID bootloader ,set ROM start addr 0x8002000 && set vector */
	/* if not use HID bootloader ,set ROM start addr 0x8000000 && Comment out the following code */
	// nvic_vector_table_set(NVIC_VECTTAB_FLASH,0x2000);
	nvic_vector_table_set(NVIC_VECTTAB_FLASH, 0x2000);
#endif

	rcu_all_reset_flag_clear();

	dbg_low_power_enable(DBG_LOW_POWER_SLEEP | DBG_LOW_POWER_DEEPSLEEP | DBG_LOW_POWER_STANDBY);

	systick_config();

	gpio_config();

	adc_config();

	usart0_config();

	FlagStatus sw_led = SET;

	uint32_t tick1, tick2;
	tick1 = tick2 = get_tick();

  printf("\r\nWeAct Studio Core Board\r\n");
  printf("weactstudio.taobao.com\r\n");
  printf("weactstudio.aliexpress.com\r\n");
  printf("wwww.weact-tc.cn\r\n\r\n");
  printf("SystemClk:%d\r\n", SystemCoreClock);
  printf("CK_AHB is %d\r\n", rcu_clock_freq_get(CK_AHB));
  printf("CK_APB1 is %d\r\n", rcu_clock_freq_get(CK_APB1));
  printf("CK_APB2 is %d\r\n", rcu_clock_freq_get(CK_APB2));
    
	printf("Epaper Module Test\r\n");

	epd_io_init();

	epd_init();

#ifdef EPD_BWR
	epd_paint_newimage(image_bw, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

	epd_paint_newimage(image_red, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

	epd_paint_selectimage(image_bw);
	epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showPicture(0, 0, 250, 122, gImage_2, EPD_COLOR_BLACK);

	epd_paint_selectimage(image_red);
	epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showPicture(0, 0, 250, 122, gImage_3, EPD_COLOR_WHITE);

	epd_display(image_bw, image_red);

	delay(8000);

	epd_paint_selectimage(image_bw);
	epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showString(10, 0, (uint8_t *)&"2.13 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
	epd_paint_showString(10, 29, (uint8_t *)&"Designed By WeAct Studio", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
	epd_paint_showString(10, 50, (uint8_t *)&"with 250 x 122 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);

	epd_paint_selectimage(image_red);
	epd_paint_clear(EPD_COLOR_WHITE);

	sprintf((char *)&text, ">> Hello World.");
	epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_RED);

#if 0
    epd_paint_showString(10,100,(uint8_t *)&"GD32F303CCT6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_RED);
#else
	epd_paint_drawRectangle(10, 103, 240, 116, EPD_COLOR_RED, 1);
#endif

	epd_display(image_bw, image_red);
#else
	epd_paint_newimage(image_bw, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

	epd_paint_selectimage(image_bw);
	epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showPicture(0, 0, 250, 122, gImage_1, EPD_COLOR_WHITE);

	epd_displayBW(image_bw);

	delay(5000);

	epd_paint_selectimage(image_bw);
	epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showString(10, 0, (uint8_t *)&"2.13 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
	epd_paint_showString(10, 29, (uint8_t *)&"Designed By WeAct Studio", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
	epd_paint_showString(10, 50, (uint8_t *)&"with 250 x 122 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);

	sprintf((char *)&text, ">> Hello World.");
	epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);

#if 0
    epd_paint_showString(10,100,(uint8_t *)&"GD32F303CCT6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_BLACK);
#else
	epd_paint_drawRectangle(10, 103, 240, 116, EPD_COLOR_BLACK, 1);
#endif
	epd_displayBW(image_bw);
#endif

	epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

	while (1)
	{

		if (get_tick() > tick1)
		{
			tick1 = get_tick() + 500 / SysTick_Tick;

			if (sw_led == SET)
			{
				/* toggle LED */
				gpio_bit_write(LED_PB2_PORT, LED_PB2_PIN, (gpio_output_bit_get(LED_PB2_PORT, LED_PB2_PIN)) == SET ? RESET : SET);
			}
			else
			{
				gpio_bit_reset(LED_PB2_PORT, LED_PB2_PIN);
			}
		}

		if (get_tick() > tick2)
		{
			tick2 = get_tick() + 10 / SysTick_Tick;

			static uint32_t PressTimeCount = 0;

			static FlagStatus IsPress = RESET;
			if (gpio_input_bit_get(KEY_PORT, KEY_PIN) != SET)
			{
				if (IsPress == SET)
				{
					IsPress = RESET;

					/* KEY click */
					sw_led = sw_led == SET ? RESET : SET;
					printf("Hello,WeAct Studio\r\n");

					/* ADC software trigger enable */
					adc_software_trigger_enable(ADC0, ADC_INSERTED_CHANNEL);
					/* delay a time in milliseconds */

					while (adc_flag_get(ADC0, ADC_FLAG_EOC) == RESET)
					{
						delay_lp(1);
					}
					adc_flag_clear(ADC0, ADC_FLAG_EOC);

					/* value convert */
					temperature = (1430.f - ADC_IDATA0(ADC0) * 3300 / 4096) / 4.3f + 25;
					vref_value = (ADC_IDATA1(ADC0) * 3300 / 4096.f);

					/* value print */
					printf("The temperature data is %2.1f degrees Celsius\r\n", temperature);
					printf("The reference voltage data is %5.3fmV \r\n", vref_value);
					printf("\r\n");

					PressTimeCount = 0;
				}
			}
			else
			{
				if (IsPress == RESET)
				{
					IsPress = SET;
				}
				PressTimeCount++;

				/*0.5s KEY long press */
				if (PressTimeCount >= 50)
				{
					/* long press , system reset and enter the IAP bootloader */
					if (SCB->VTOR != 0)
					{
						printf("Enter IAP Bootloader ...\r\n");
						NVIC_SystemReset();
					}
					else
					{
						printf("Enter system ISP Bootloader ...\r\n");

#define ISP_ADDR ((uint32_t)0x1FFFF000)

						systick_deinit();
						gpio_deinit(LED_PB2_PORT);
						gpio_deinit(KEY_PORT);
						jump_to_app(ISP_ADDR);
					}
				}
			}
		}
		pmu_to_sleepmode(WFI_CMD);
	}
}

/*!
	\brief      configure the ADC peripheral
	\param[in]  none
	\param[out] none
	\retval     none
*/
void adc_config(void)
{
	/* enable ADC clock */
	rcu_periph_clock_enable(RCU_ADC0);
	/* config ADC clock */
	rcu_adc_clock_config(RCU_CKADC_CKAPB2_DIV4);

	/* ADC SCAN function enable */
	adc_special_function_config(ADC0, ADC_SCAN_MODE, ENABLE);
	adc_special_function_config(ADC0, ADC_CONTINUOUS_MODE, DISABLE);
	/* ADC trigger config */
	adc_external_trigger_source_config(ADC0, ADC_INSERTED_CHANNEL, ADC0_1_2_EXTTRIG_INSERTED_NONE);
	/* ADC mode config */
	adc_mode_config(ADC_MODE_FREE);
	/* ADC data alignment config */
	adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
	/* ADC channel length config */
	adc_channel_length_config(ADC0, ADC_INSERTED_CHANNEL, 2);

	/* ADC temperature sensor channel config */
	adc_inserted_channel_config(ADC0, 0, ADC_CHANNEL_16, ADC_SAMPLETIME_239POINT5);
	/* ADC internal reference voltage channel config */
	adc_inserted_channel_config(ADC0, 1, ADC_CHANNEL_17, ADC_SAMPLETIME_239POINT5);

	adc_external_trigger_config(ADC0, ADC_INSERTED_CHANNEL, ENABLE);

	/* ADC temperature and Vrefint enable */
	adc_tempsensor_vrefint_enable();

	/* enable ADC interface */
	adc_enable(ADC0);
	delay(1);
	/* ADC calibration and reset calibration */
	adc_calibration_enable(ADC0);
}

void jump_to_app(uint32_t addr)
{
	uint32_t app_address;
	void *(*application)(void);

	/* test if user code is programmed starting from address */
	if (((*(__IO uint32_t *)addr) & 0x2FFE0000) == 0x20000000)
	{
		app_address = *(__IO uint32_t *)(addr + 4);
		application = (void *(*)(void))app_address;

		/* initialize user application's stack pointer */
		__set_MSP(*(__IO uint32_t *)addr);

		/* jump to application */
		application();
	}
}
