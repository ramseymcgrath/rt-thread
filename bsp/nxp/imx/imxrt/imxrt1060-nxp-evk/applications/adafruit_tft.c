#include "adafruit_tft.h"
#include <rtthread.h>
#include <rtdevice.h>
#include <ili9341.h>
#ifndef ILI9341_LCD_WIDTH
#define ILI9341_LCD_WIDTH 320
#endif
#ifndef ILI9341_LCD_HEIGHT
#define ILI9341_LCD_HEIGHT 240
#endif
#define TFT_RST_PIN 26
#define TFT_DC_PIN 27
#define TFT_SPI_BUS "spi0" // SPI bus name, change as needed

// Device handler and SPI handler
static struct rt_device_graphic_info _graphic_info;

static struct ili9341_device ili9341;

// Initialize the adafruit and related RT-Thread device
rt_err_t adafruit_tft_init(void)
{
    rt_err_t result = RT_EOK;

    // Initialize Reset pin if any
    rt_pin_mode(TFT_RST_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(TFT_DC_PIN, PIN_MODE_OUTPUT);

    ili9341.dc_pin = TFT_DC_PIN;

    rt_spi_bus_attach_device(&ili9341.spi_device,
                             "ili9341",
                             TFT_SPI_BUS,
                             (void *)0);

    _graphic_info.bits_per_pixel = 16;
    _graphic_info.width = ILI9341_LCD_WIDTH;
    _graphic_info.height = ILI9341_LCD_HEIGHT;
    _graphic_info.framebuffer = rt_malloc(_graphic_info.width * _graphic_info.height * 2);

    if (_graphic_info.framebuffer == RT_NULL)
    {
        LOG_E("No memory for framebuffer!");
        return -RT_ENOMEM;
    }

    ili9341_init(&ili9341);

    return result;
}

void adafruit_tft_fillScreen(uint16_t color) {
    ili9341_fill_screen(&ili9341, color);
}

void adafruit_tft_setCursor(int16_t x, int16_t y) {
    ili9341_set_cursor(&ili9341, x, y);
}

void adafruit_tft_setTextColor(uint16_t color) {
    ili9341_set_text_color(&ili9341, color);
}

void adafruit_tft_setTextSize(uint8_t size) {
    ili9341_set_text_size(&ili9341, size);
}

void adafruit_tft_print(const char *str) {
    ili9341_write_string(&ili9341, str);
}
