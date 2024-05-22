/*---------------------------------------
- WeAct Studio Official Link
- taobao: weactstudio.taobao.com
- aliexpress: weactstudio.aliexpress.com
- github: github.com/WeActTC
- gitee: gitee.com/WeAct-TC
- blog: www.weact-tc.cn
---------------------------------------*/

#include "epaper.h"
#include "epdfont.h"

#include "delay.h"

// epaper module
// res pin  -> pa8
// busy pin -> pa9
// d/c pin  -> pb14
// cs pin   -> pb12
// sck pin  -> pb13
// mosi pin -> pb15

EPD_PAINT EPD_Paint;

static uint8_t _hibernating = 1;

static const unsigned char lut_partial[] =
{
  0x0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0A, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2,
  0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0, 0x0,
};

void epd_delay(uint16_t ms)
{
  delay_ms(ms);
}

void epd_res_set()
{
  gpio_bits_set(GPIOA, GPIO_PINS_8);
}

void epd_res_reset()
{
  gpio_bits_reset(GPIOA, GPIO_PINS_8);
}

void epd_dc_set()
{
  gpio_bits_set(GPIOB, GPIO_PINS_14);
}

void epd_dc_reset()
{
  gpio_bits_reset(GPIOB, GPIO_PINS_14);
}

void epd_cs_set()
{
  gpio_bits_set(GPIOB, GPIO_PINS_12);
}

void epd_cs_reset()
{
  gpio_bits_reset(GPIOB, GPIO_PINS_12);
}

uint8_t epd_is_busy()
{
  return gpio_input_data_bit_read(GPIOA, GPIO_PINS_9) == RESET ? 0 : 1;
}

void epd_io_init(void)
{
  gpio_init_type gpio_init_struct;

  /* enable gpioa gpiob clock */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
  crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* configure the epaper module res pin */
  gpio_bits_reset(GPIOA, GPIO_PINS_8);
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pins = GPIO_PINS_8;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);

  /* configure the epaper module busy pin */
  gpio_init_struct.gpio_mode = GPIO_MODE_INPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_UP;
  gpio_init_struct.gpio_pins = GPIO_PINS_9;
  gpio_init(GPIOA, &gpio_init_struct);

  /* configure the epaper module d/c pin */
  gpio_bits_set(GPIOB, GPIO_PINS_14);
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pins = GPIO_PINS_14;
  gpio_init(GPIOB, &gpio_init_struct);

  /* configure the epaper module spi2 sck pin */
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_13;
  gpio_init(GPIOB, &gpio_init_struct);

  /* configure the epaper module spi2 mosi pin */
  //  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  //  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_15;
  gpio_init(GPIOB, &gpio_init_struct);

  /* configure the epaper module cs pin */
  gpio_bits_set(GPIOB, GPIO_PINS_12);
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pins = GPIO_PINS_12;
  gpio_init(GPIOB, &gpio_init_struct);

  /* configure spi2 */
  spi_init_type spi_init_struct;
  crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK, TRUE);
  spi_default_para_init(&spi_init_struct);
  spi_init_struct.transmission_mode = SPI_TRANSMIT_HALF_DUPLEX_TX;
  spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_64;
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
  spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
  spi_init(SPI2, &spi_init_struct);
  spi_enable(SPI2, TRUE);
}

void epd_write_reg(uint8_t reg)
{
  epd_dc_reset();
  epd_cs_reset();

  spi_i2s_data_transmit(SPI2, reg);
  while (spi_i2s_flag_get(SPI2, SPI_I2S_BF_FLAG) != RESET)
    ;

  epd_cs_set();
  epd_dc_set();
}

void epd_write_data(uint8_t data)
{
  epd_cs_reset();

  spi_i2s_data_transmit(SPI2, data);
  while (spi_i2s_flag_get(SPI2, SPI_I2S_BF_FLAG) != RESET)
    ;

  epd_cs_set();
}

void _epd_write_data(uint8_t data)
{
  while (spi_i2s_flag_get(SPI2, SPI_I2S_TDBE_FLAG) == RESET)
    ;
  spi_i2s_data_transmit(SPI2, data);
}

void _epd_write_data_over()
{
  while (spi_i2s_flag_get(SPI2, SPI_I2S_BF_FLAG) != RESET)
    ;
}

uint8_t epd_wait_busy()
{
  uint32_t timeout = 0;
  while (epd_is_busy())
  {
    timeout++;
    if (timeout > 40000)
    {
      return 1;
    }
    epd_delay(1);
  }
  return 0;
}

void epd_reset(void)
{
  epd_res_reset();
  epd_delay(50);
  epd_res_set();
  epd_delay(50);
  _hibernating = 0;
}

uint8_t epd_init(void)
{
  if (_hibernating)
    epd_reset();

  if (epd_wait_busy())
    return 1;

  epd_write_reg(0x12); // SWRESET
	
	epd_delay(10);

  if (epd_wait_busy())
    return 1;
	
	#if defined(EPD_29) || defined(EPD_213) || defined(EPD_154) 
		epd_write_reg(0x01); // Driver output control
		#if defined(EPD_29) || defined(EPD_213)
		epd_write_data(0x27);
		epd_write_data(0x01);
		epd_write_data(0x01);
		#else
		epd_write_data(0xC7);
		epd_write_data(0x00);
		epd_write_data(0x01);
		#endif

		epd_write_reg(0x11); // data entry mode
		epd_write_data(0x01);

		#ifdef EPD_154
		epd_write_reg(0x44); // set Ram-X address start/end position
		epd_write_data(0x00);
		epd_write_data(0x18);

		epd_write_reg(0x45);  // set Ram-Y address start/end position
		epd_write_data(0xC7);
		epd_write_data(0x00);
		epd_write_data(0x00);
		epd_write_data(0x00);
		#else
		epd_write_reg(0x44); // set Ram-X address start/end position
		epd_write_data(0x00);
		epd_write_data(0x0F); // 0x0F-->(15+1)*8=128

		epd_write_reg(0x45);  // set Ram-Y address start/end position
		epd_write_data(0x27); // 0x127-->(295+1)=296
		epd_write_data(0x01);
		epd_write_data(0x00);
		epd_write_data(0x00);
		#endif

		epd_write_reg(0x3C); // BorderWavefrom
		epd_write_data(0x05);

		#if defined(EPD_29) || defined(EPD_213)
		epd_write_reg(0x21); //  Display update control
		epd_write_data(0x00);
		epd_write_data(0x80);
		#endif

	#elif defined(EPD_42)
		epd_write_reg(0x21); // Display Update Controll
		epd_write_data(0x40);
		epd_write_data(0x00);
		epd_write_reg(0x01);  // Set MUX as 300
		epd_write_data(0x2B);
		epd_write_data(0x01);
		epd_write_data(0x00);
		epd_write_reg(0x3C); //BorderWavefrom
		epd_write_data(0x01);	
		epd_write_reg(0x11);	// data  entry  mode
		epd_write_data(0x03);		// X-mode
		epd_address_set(0,0,EPD_W-1,EPD_H-1);
	#endif

	epd_write_reg(0x18); // Read built-in temperature sensor
	epd_write_data(0x80);
		
	epd_setpos(0,0);

  if (epd_power_on())
    return 1;

  return 0;
}

uint8_t epd_init_partial(void)
{
  if (epd_init())
    return 1;
	
	#if defined(EPD_29) || defined(EPD_213)
  epd_write_reg(0x32);
  epd_cs_reset();
  for (int j = 0; j < sizeof(lut_partial); j++)
  {
    _epd_write_data(lut_partial[j]);
  }
  _epd_write_data_over();
  epd_cs_set();
	#elif defined(EPD_42)
	epd_write_reg(0x3C); //BorderWavefrom
	epd_write_data(0x80);	
	epd_write_reg(0x21); // Display Update Controll
  epd_write_data(0x00);    // RED normal
  epd_write_data(0x00);    // single chip application
	#endif

  return 0;
}

void epd_enter_deepsleepmode(uint8_t mode)
{
	epd_power_off();
  epd_write_reg(0x10);
  epd_write_data(mode);
  _hibernating = 1;
}

uint8_t epd_power_on(void)
{
	#if defined EPD_42
	epd_write_reg(0x22); // Display Update Control
	epd_write_data(0xe0);
	#else
	epd_write_reg(0x22); // Display Update Control
	epd_write_data(0xf8);
	#endif
  epd_write_reg(0x20); // Activate Display Update Sequence

  return epd_wait_busy();
}

uint8_t epd_power_off(void)
{
	epd_write_reg(0x22); // Display Update Control
	epd_write_data(0x83);
  epd_write_reg(0x20); // Activate Display Update Sequence

  return epd_wait_busy();
}

void epd_init_internalTempSensor(void)
{
  epd_write_reg(0x18);
  epd_write_data(0x80);

  epd_write_reg(0x1A);
  epd_write_data(0x7F);
//  epd_write_data(0xF0);
}

void epd_update(void)
{
  
	#ifdef EPD_154
	epd_write_reg(0x22); // Display Update Control
	epd_write_data(0xF4);
	#elif defined EPD_42
	epd_write_reg(0x22); // Display Update Control
  epd_write_data(0xF7);
	#else
	epd_write_reg(0x22); // Display Update Control
  epd_write_data(0xF7);
	#endif
  epd_write_reg(0x20); // Activate Display Update Sequence

  epd_wait_busy();
}

void epd_update_partial(void)
{
  #ifdef EPD_154
	epd_write_reg(0x22); // Display Update Control
	epd_write_data(0xFC);
	#elif defined EPD_42
	epd_write_reg(0x22); // Display Update Control
	epd_write_data(0xFF);
	#else
	epd_write_reg(0x22); // Display Update Control
  epd_write_data(0xCC);
	#endif
  epd_write_reg(0x20); // Activate Display Update Sequence

  epd_wait_busy();
}

void epd_address_set(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{
	epd_write_reg(0x44); // SET_RAM_X_ADDRESS_START_END_POSITION
	epd_write_data((x_start>>3) & 0xFF);
	epd_write_data((x_end>>3) & 0xFF);

	epd_write_reg(0x45); // SET_RAM_Y_ADDRESS_START_END_POSITION
	epd_write_data(y_start & 0xFF);
	epd_write_data((y_start >> 8) & 0xFF);
	epd_write_data(y_end & 0xFF);
	epd_write_data((y_end >> 8) & 0xFF);
}

void epd_setpos(uint16_t x, uint16_t y)
{
  uint8_t _x;
  uint16_t _y;

  _x = x / 8;

	#ifdef EPD_154
	_y = 199 - y;
	#elif defined(EPD_29) || defined(EPD_213)
	_y = 295 - y;
	#elif defined(EPD_42)
	_y = y;
	#endif

  epd_write_reg(0x4E); // set RAM x address count to 0;
  epd_write_data(_x);
  epd_write_reg(0x4F); // set RAM y address count to 0x127;
  epd_write_data(_y & 0xff);
  epd_write_data(_y >> 8 & 0x01);
}

void epd_writedata(uint8_t *Image1, uint32_t length)
{
  epd_cs_reset();
  for (uint32_t j = 0; j < length; j++)
  {
    _epd_write_data(Image1[j]);
  }
  _epd_write_data_over();
  epd_cs_set();
}

void epd_writedata2(uint8_t data, uint32_t length)
{
  epd_cs_reset();
  for (uint32_t j = 0; j < length; j++)
  {
    _epd_write_data(data);
  }
  _epd_write_data_over();
  epd_cs_set();
}

void epd_display(uint8_t *Image1, uint8_t *Image2)
{
  uint32_t Width, Height, i, j;
  uint32_t k = 0;
  Width = EPD_H;
  Height = EPD_W_BUFF_SIZE;

  epd_setpos(0, 0);

  epd_write_reg(0x24);
  epd_writedata(Image1, Width * Height);

  epd_setpos(0, 0);

  epd_write_reg(0x26);
  k = 0;
  epd_cs_reset();
  for (j = 0; j < Height; j++)
  {
    for (i = 0; i < Width; i++)
    {
      _epd_write_data(~Image2[k]);
      k++;
    }
  }
  _epd_write_data_over();
  epd_cs_set();

	#if defined EPD_42
	epd_write_reg(0x21); // Display Update Controll
  epd_write_data(0x00);    // RED normal
  epd_write_data(0x00);    // single chip application
	#endif
	
  epd_update();
}

void epd_displayBW(uint8_t *Image)
{
  uint32_t Width, Height;
  
  Width = EPD_H;
  Height = EPD_W_BUFF_SIZE;

  epd_setpos(0, 0);
  epd_write_reg(0x26);
  epd_writedata(Image, Width * Height);

  epd_setpos(0, 0);
  epd_write_reg(0x24);
  epd_writedata(Image, Width * Height);

  epd_update();
}

void epd_displayBW_partial(uint8_t *Image)
{
  uint32_t Width, Height;

  Width = EPD_H;
  Height = EPD_W_BUFF_SIZE;

  epd_setpos(0, 0);
  epd_write_reg(0x24);
  epd_writedata(Image, Width * Height);

  epd_update_partial();

  epd_setpos(0, 0);
  epd_write_reg(0x26);
  epd_writedata(Image, Width * Height);
}

void epd_displayRED(uint8_t *Image)
{
  uint32_t Width, Height;

  Width = EPD_H;
  Height = EPD_W_BUFF_SIZE;

  epd_setpos(0, 0);

  epd_write_reg(0x26);
  epd_writedata(Image, Width * Height);

	#if defined EPD_42
	epd_write_reg(0x21); // Display Update Controll
  epd_write_data(0x00);    // RED normal
  epd_write_data(0x00);    // single chip application
	#endif
  epd_update();
}

void epd_paint_newimage(uint8_t *image, uint16_t Width, uint16_t Height, uint16_t Rotate, uint16_t Color)
{
  EPD_Paint.Image = 0x00;
  EPD_Paint.Image = image;

  EPD_Paint.WidthMemory = Width;
  EPD_Paint.HeightMemory = Height;
  EPD_Paint.Color = Color;
  EPD_Paint.WidthByte = (Width % 8 == 0) ? (Width / 8) : (Width / 8 + 1);
  EPD_Paint.HeightByte = Height;
  EPD_Paint.Rotate = Rotate;
  if (Rotate == EPD_ROTATE_0 || Rotate == EPD_ROTATE_180)
  {

    EPD_Paint.Width = Height;
    EPD_Paint.Height = Width;
  }
  else
  {
    EPD_Paint.Width = Width;
    EPD_Paint.Height = Height;
  }
}

void epd_paint_setpixel(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color)
{
  uint16_t X, Y;
  uint32_t Addr;
  uint8_t Rdata;
  switch (EPD_Paint.Rotate)
  {
  case 0:

    X = EPD_Paint.WidthMemory - Ypoint - 1;
    Y = Xpoint;
    break;
  case 90:
    X = EPD_Paint.WidthMemory - Xpoint - 1;
    Y = EPD_Paint.HeightMemory - Ypoint - 1;
    break;
  case 180:
    X = Ypoint;
    Y = EPD_Paint.HeightMemory - Xpoint - 1;
    break;
  case 270:
    X = Xpoint;
    Y = Ypoint;
    break;
  default:
    return;
  }
  Addr = X / 8 + Y * EPD_Paint.WidthByte;
  Rdata = EPD_Paint.Image[Addr];
  if (Color == EPD_COLOR_BLACK)
  {
    EPD_Paint.Image[Addr] = Rdata & ~(0x80 >> (X % 8));
  }
  else
    EPD_Paint.Image[Addr] = Rdata | (0x80 >> (X % 8));
}

void epd_paint_clear(uint16_t color)
{
  uint16_t X, Y;
  uint32_t Addr;

  for (Y = 0; Y < EPD_Paint.HeightByte; Y++)
  {
    for (X = 0; X < EPD_Paint.WidthByte; X++)
    { // 8 pixel =  1 byte
      Addr = X + Y * EPD_Paint.WidthByte;
      EPD_Paint.Image[Addr] = color;
    }
  }
}

void epd_paint_selectimage(uint8_t *image)
{
  EPD_Paint.Image = image;
}

void epd_paint_drawPoint(uint16_t Xpoint, uint16_t Ypoint, uint16_t Color)
{
  epd_paint_setpixel(Xpoint - 1, Ypoint - 1, Color);
}

void epd_paint_drawLine(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color)
{
  uint16_t Xpoint, Ypoint;
  int32_t dx, dy;
  int32_t XAddway, YAddway;
  int32_t Esp;
  char Dotted_Len;
  Xpoint = Xstart;
  Ypoint = Ystart;
  dx = (int)Xend - (int)Xstart >= 0 ? Xend - Xstart : Xstart - Xend;
  dy = (int)Yend - (int)Ystart <= 0 ? Yend - Ystart : Ystart - Yend;

  XAddway = Xstart < Xend ? 1 : -1;
  YAddway = Ystart < Yend ? 1 : -1;

  Esp = dx + dy;
  Dotted_Len = 0;

  for (;;)
  {
    Dotted_Len++;
    epd_paint_drawPoint(Xpoint, Ypoint, Color);
    if (2 * Esp >= dy)
    {
      if (Xpoint == Xend)
        break;
      Esp += dy;
      Xpoint += XAddway;
    }
    if (2 * Esp <= dx)
    {
      if (Ypoint == Yend)
        break;
      Esp += dx;
      Ypoint += YAddway;
    }
  }
}

void epd_paint_drawRectangle(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend, uint16_t Color, uint8_t mode)
{
  uint16_t i;
  if (mode)
  {
    for (i = Ystart; i < Yend; i++)
    {
      epd_paint_drawLine(Xstart, i, Xend, i, Color);
    }
  }
  else
  {
    epd_paint_drawLine(Xstart, Ystart, Xend, Ystart, Color);
    epd_paint_drawLine(Xstart, Ystart, Xstart, Yend, Color);
    epd_paint_drawLine(Xend, Yend, Xend, Ystart, Color);
    epd_paint_drawLine(Xend, Yend, Xstart, Yend, Color);
  }
}

void epd_paint_drawCircle(uint16_t X_Center, uint16_t Y_Center, uint16_t Radius, uint16_t Color, uint8_t mode)
{
  uint16_t Esp, sCountY;
  uint16_t XCurrent, YCurrent;
  XCurrent = 0;
  YCurrent = Radius;
  Esp = 3 - (Radius << 1);
  if (mode)
  {
    while (XCurrent <= YCurrent)
    { // Realistic circles
      for (sCountY = XCurrent; sCountY <= YCurrent; sCountY++)
      {
        epd_paint_drawPoint(X_Center + XCurrent, Y_Center + sCountY, Color); // 1
        epd_paint_drawPoint(X_Center - XCurrent, Y_Center + sCountY, Color); // 2
        epd_paint_drawPoint(X_Center - sCountY, Y_Center + XCurrent, Color); // 3
        epd_paint_drawPoint(X_Center - sCountY, Y_Center - XCurrent, Color); // 4
        epd_paint_drawPoint(X_Center - XCurrent, Y_Center - sCountY, Color); // 5
        epd_paint_drawPoint(X_Center + XCurrent, Y_Center - sCountY, Color); // 6
        epd_paint_drawPoint(X_Center + sCountY, Y_Center - XCurrent, Color); // 7
        epd_paint_drawPoint(X_Center + sCountY, Y_Center + XCurrent, Color);
      }
      if ((int)Esp < 0)
        Esp += 4 * XCurrent + 6;
      else
      {
        Esp += 10 + 4 * (XCurrent - YCurrent);
        YCurrent--;
      }
      XCurrent++;
    }
  }
  else
  { // Draw a hollow circle
    while (XCurrent <= YCurrent)
    {
      epd_paint_drawPoint(X_Center + XCurrent, Y_Center + YCurrent, Color); // 1
      epd_paint_drawPoint(X_Center - XCurrent, Y_Center + YCurrent, Color); // 2
      epd_paint_drawPoint(X_Center - YCurrent, Y_Center + XCurrent, Color); // 3
      epd_paint_drawPoint(X_Center - YCurrent, Y_Center - XCurrent, Color); // 4
      epd_paint_drawPoint(X_Center - XCurrent, Y_Center - YCurrent, Color); // 5
      epd_paint_drawPoint(X_Center + XCurrent, Y_Center - YCurrent, Color); // 6
      epd_paint_drawPoint(X_Center + YCurrent, Y_Center - XCurrent, Color); // 7
      epd_paint_drawPoint(X_Center + YCurrent, Y_Center + XCurrent, Color); // 0
      if ((int)Esp < 0)
        Esp += 4 * XCurrent + 6;
      else
      {
        Esp += 10 + 4 * (XCurrent - YCurrent);
        YCurrent--;
      }
      XCurrent++;
    }
  }
}

void epd_paint_showChar(uint16_t x, uint16_t y, uint16_t chr, uint16_t size1, uint16_t color)
{
  uint16_t i, m, temp, size2, chr1;
  uint16_t x0, y0;
  x += 1, y += 1, x0 = x, y0 = y;
  if (x - size1 > EPD_H)
    return;
  if (size1 == 8)
    size2 = 6;
  else
    size2 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * (size1 / 2);
  chr1 = chr - ' ';
  for (i = 0; i < size2; i++)
  {
    if (size1 == 8)
    {
      temp = asc2_0806[chr1][i];
    } // 0806
    else if (size1 == 12)
    {
      temp = asc2_1206[chr1][i];
    } // 1206
    else if (size1 == 16)
    {
      temp = asc2_1608[chr1][i];
    } // 1608
    else if (size1 == 24)
    {
      temp = asc2_2412[chr1][i];
    } // 2412
    else
      return;
    for (m = 0; m < 8; m++)
    {
      if (temp & 0x01)
        epd_paint_drawPoint(x, y, color);
      else
        epd_paint_drawPoint(x, y, !color);
      temp >>= 1;
      y++;
    }
    x++;
    if ((size1 != 8) && ((x - x0) == size1 / 2))
    {
      x = x0;
      y0 = y0 + 8;
    }
    y = y0;
  }
}

void epd_paint_showString(uint16_t x, uint16_t y, uint8_t *chr, uint16_t size1, uint16_t color)
{
  while (*chr != '\0')
  {
    epd_paint_showChar(x, y, *chr, size1, color);
    chr++;
    if (size1 == 8)
    {
      x += 6;
			if(x > EPD_H-6)
				break;
    }
    else
    {
      x += size1 / 2;
			if(x > EPD_H-size1 / 2)
				break;
    }
  }
}

// m^n
static uint32_t _Pow(uint16_t m, uint16_t n)
{
  uint32_t result = 1;
  while (n--)
  {
    result *= m;
  }
  return result;
}

void epd_paint_showNum(uint16_t x, uint16_t y, uint32_t num, uint16_t len, uint16_t size1, uint16_t color)
{
  uint8_t t, temp, m = 0;
  if (size1 == 8)
    m = 2;
  for (t = 0; t < len; t++)
  {
    temp = (num / _Pow(10, len - t - 1)) % 10;
    if (temp == 0)
    {
      epd_paint_showChar(x + (size1 / 2 + m) * t, y, '0', size1, color);
    }
    else
    {
      epd_paint_showChar(x + (size1 / 2 + m) * t, y, temp + '0', size1, color);
    }
  }
}

void epd_paint_showChinese(uint16_t x, uint16_t y, uint16_t num, uint16_t size1, uint16_t color)
{
  uint16_t m, temp;
  uint16_t x0, y0;
  uint16_t i, size3 = (size1 / 8 + ((size1 % 8) ? 1 : 0)) * size1;
  x += 1, y += 1, x0 = x, y0 = y;
  for (i = 0; i < size3; i++)
  {
    if (size1 == 16)
    {
      temp = Hzk1[num][i];
    } // 16*16
    else if (size1 == 24)
    {
      temp = Hzk2[num][i];
    } // 24*24
    else if (size1 == 32)
    {
      temp = Hzk3[num][i];
    } // 32*32
    else if (size1 == 64)
    {
      temp = Hzk4[num][i];
    } // 64*64
    else
      return;
    for (m = 0; m < 8; m++)
    {
      if (temp & 0x01)
        epd_paint_drawPoint(x, y, color);
      else
        epd_paint_drawPoint(x, y, !color);
      temp >>= 1;
      y++;
    }
    x++;
    if ((x - x0) == size1)
    {
      x = x0;
      y0 = y0 + 8;
    }
    y = y0;
  }
}

void epd_paint_showPicture(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, const uint8_t BMP[], uint16_t Color)
{
  uint16_t j = 0;
  uint16_t i, n = 0, temp = 0, m = 0;
  uint16_t x0 = 0, y0 = 0;
  x += 1, y += 1, x0 = x, y0 = y;
  sizey = sizey / 8 + ((sizey % 8) ? 1 : 0);
  for (n = 0; n < sizey; n++)
  {
    for (i = 0; i < sizex; i++)
    {
      temp = BMP[j];
      j++;
      for (m = 0; m < 8; m++)
      {
        if (temp & 0x01)
          epd_paint_drawPoint(x, y, !Color);
        else
          epd_paint_drawPoint(x, y, Color);
        temp >>= 1;
        y++;
      }
      x++;
      if ((x - x0) == sizex)
      {
        x = x0;
        y0 = y0 + 8;
      }
      y = y0;
    }
  }
}
