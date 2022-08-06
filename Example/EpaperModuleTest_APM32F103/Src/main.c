/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "main.h"
#include "board.h"
#include "systick.h"

#include "epaper.h"
#include "bmp.h"

#define EPD_BWR

uint8_t image_bw[4000];
#ifdef EPD_BWR
uint8_t image_red[4000];
#endif

/*!
 * @brief       Main program
 *
 * @param       None
 *
 * @retval      None
 *
 */
int main(void)
{
    uint8_t text[20];

    systick_config();

    board_led_init();
    board_button_init();
    board_usart_init();

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
    epd_paint_showString(10,100,(uint8_t *)&"APM32F103CBT6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_RED);
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
    epd_paint_showString(10,100,(uint8_t *)&"APM32F103CBT6 Example",EPD_FONT_SIZE16x8,EPD_COLOR_BLACK);
#else
    epd_paint_drawRectangle(10, 103, 240, 116, EPD_COLOR_BLACK, 1);
#endif
    epd_displayBW(image_bw);
#endif

    epd_enter_deepsleepmode(EPD_DEEPSLEEP_MODE1);
    while (1)
    {
        if (!board_button_state_get())
        {
            delay(100);
            board_led_toggle();
        }
        else
        {
            board_led_off();
        }
    }
}