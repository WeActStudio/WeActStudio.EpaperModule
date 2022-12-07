/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "debug.h"
#include "board.h"
#include "systick.h"

#include "epaper.h"
#include "bmp.h"

// define for White Black Red Epaper Module
#define EPD_BWR

uint8_t image_bw[EPD_W_BUFF_SIZE * EPD_H];
#ifdef EPD_BWR
uint8_t image_red[EPD_W_BUFF_SIZE * EPD_H];
#endif

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
    uint8_t text[20];

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    SystemCoreClockUpdate();

    systick_config();

    USART_Printf_Init(115200);

    board_button_init();
    board_led_init();

    printf("\r\nWeAct Studio Core Board\r\n");
    printf("weactstudio.taobao.com\r\n");
    printf("weactstudio.aliexpress.com\r\n");
    printf("wwww.weact-tc.cn\r\n\r\n");
    printf("SystemClk:%d\r\n", SystemCoreClock);
    printf("Epaper Module Test\r\n");

    epd_io_init();

    epd_init();

#ifdef EPD_BWR
    epd_paint_newimage(image_bw, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

    epd_paint_newimage(image_red, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

    epd_paint_selectimage(image_bw);
    epd_paint_clear(EPD_COLOR_WHITE);

    epd_paint_selectimage(image_red);
    epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showPicture((EPD_H - 250) / 2, (EPD_W - 122) / 2, 250, 122, gImage_4, EPD_COLOR_WHITE);

    epd_display(image_bw, image_red);
	epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

    delay(8000);

	epd_init();

    epd_paint_selectimage(image_bw);
    epd_paint_clear(EPD_COLOR_WHITE);
#ifdef EPD_213
    epd_paint_showString(10, 0, (uint8_t *)&"2.13 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
    epd_paint_showString(10, 50, (uint8_t *)&"with 250 x 122 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
#ifdef EPD_29
	epd_paint_showString(10, 0, (uint8_t *)&"2.9 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
	epd_paint_showString(10, 50, (uint8_t *)&"with 296 x 128 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
	epd_paint_showString(10, 29, (uint8_t *)&"Designed By WeAct Studio", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);

    epd_paint_selectimage(image_red);
    epd_paint_clear(EPD_COLOR_WHITE);

    sprintf((char *)&text, ">> Hello World.");
    epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_RED);

#if 0
    epd_paint_showString(10,100,(uint8_t *)&"CH32V103C8T6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_RED);
#else
	epd_paint_drawRectangle(10, 103, EPD_H - 10, 116, EPD_COLOR_RED, 1);
#endif

    epd_display(image_bw, image_red);
#else
    epd_paint_newimage(image_bw, EPD_W, EPD_H, EPD_ROTATE_180, EPD_COLOR_WHITE);

    epd_paint_selectimage(image_bw);
    epd_paint_clear(EPD_COLOR_WHITE);
	epd_paint_showPicture((EPD_H - 250) / 2, (EPD_W - 122) / 2, 250, 122, gImage_4, EPD_COLOR_WHITE);

    epd_displayBW(image_bw);
	epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

    delay(5000);

	epd_init_partial();

    epd_paint_selectimage(image_bw);
    epd_paint_clear(EPD_COLOR_WHITE);
#ifdef EPD_213
    epd_paint_showString(10, 0, (uint8_t *)&"2.13 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
    epd_paint_showString(10, 50, (uint8_t *)&"with 250 x 122 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
#ifdef EPD_29
	epd_paint_showString(10, 0, (uint8_t *)&"2.9 Epaper Module", EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
	epd_paint_showString(10, 50, (uint8_t *)&"with 296 x 128 resolution", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);
#endif
	epd_paint_showString(10, 29, (uint8_t *)&"Designed By WeAct Studio", EPD_FONT_SIZE16x8, EPD_COLOR_BLACK);

#if 0
    epd_paint_showString(10,100,(uint8_t *)&"CH32V103C8T6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_BLACK);
#else
	epd_paint_drawRectangle(10, 103, EPD_H - 10, 116, EPD_COLOR_BLACK, 1);
#endif

	sprintf((char *)&text, ">> Partial Mode");
	epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);

	epd_displayBW_partial(image_bw);

	delay(1000);

	for (uint32_t i = 123; i < 8 * 123; i += 123)
	{
		sprintf((char *)&text, ">> Num=%d     ", i);
		epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);

		epd_displayBW_partial(image_bw);

		delay(100);
	}

	sprintf((char *)&text, ">> Hello World.");
	epd_paint_showString(10, 71, text, EPD_FONT_SIZE24x12, EPD_COLOR_BLACK);
	epd_displayBW_partial(image_bw);

	delay(1000);

	epd_update();
#endif

    epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);

    uint32_t tick, toggle_tick;
    tick = 0;
    toggle_tick = 250;
    while (1)
    {
        tick++;
        if (tick % toggle_tick == 0)
        {
            board_led_toggle();
        }
        if (board_button_getstate())
        {
            while (board_button_getstate())
            {
                Delay_Ms(50);
            }
            if (toggle_tick == 250)
            {
                toggle_tick = 100;
            }
            else
            {
                toggle_tick = 250;
            }
        }
        delay(1);
    }
}
