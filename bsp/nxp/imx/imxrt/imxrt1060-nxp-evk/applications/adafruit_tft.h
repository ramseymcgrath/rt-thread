#ifndef ADAFRUIT_TFT_H__
#define ADAFRUIT_TFT_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

// Define color code for TFT
#define ILI9341_BLACK 0x0000
#define ILI9341_WHITE 0xFFFF
#define ILI9341_RED 0xF800

rt_err_t adafruit_tft_init(void);
void adafruit_tft_fillScreen(uint16_t color);
void adafruit_tft_setCursor(int16_t x, int16_t y);
void adafruit_tft_setTextColor(uint16_t color);
void adafruit_tft_setTextSize(uint8_t size);
void adafruit_tft_print(const char *str);

#ifdef __cplusplus
}
#endif

#endif
