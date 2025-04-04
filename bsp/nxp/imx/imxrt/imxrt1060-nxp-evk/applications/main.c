#include <rtthread.h>
#include <rtdevice.h>
#include "tusb.h"  // TinyUSB definitions
#include "adafruit_tft.h" //Adafruit TFT header file

#ifdef RT_USING_CONSOLE
#include <stdio.h>
#endif

// Define your TFT pins and other settings based on your shield.
// #define TFT_DC_PIN   27
// #define TFT_RST_PIN   26

// Function prototypes (you'll implement these)
void usb_device_task(void *param);
void usb_host_task(void *param);

int main(void)
{
    // 1. Initialize the TFT display:
    if (adafruit_tft_init() != RT_EOK) {
        rt_kprintf("TFT initialization failed!\n");
        return -1;
    }
  adafruit_tft_fillScreen(ILI9341_BLACK); // Clear the screen to black
  adafruit_tft_setCursor(0, 0); // Set cursor to top-left
  adafruit_tft_setTextColor(ILI9341_WHITE); // white font
  adafruit_tft_setTextSize(2); //Large font

    // 2. Initialize and start TinyUSB:
    /* Initialize TinyUSB device stack */
    tusb_init();

    // 3. Create threads for USB device and host tasks:
     rt_thread_t usb_device_thread = rt_thread_create("usb_device", usb_device_task, RT_NULL, 2048, 5, 10); // Adjust stack size and priority as needed.
     if (usb_device_thread != RT_NULL) {
         rt_thread_startup(usb_device_thread);
     } else {
        rt_kprintf("Failed to create usb_device thread\n");
     }

     rt_thread_t usb_host_thread = rt_thread_create("usb_host", usb_host_task, RT_NULL, 2048, 5, 10); // Adjust stack size and priority as needed.
     if (usb_host_thread != RT_NULL) {
         rt_thread_startup(usb_host_thread);
     } else {
        rt_kprintf("Failed to create usb_host thread\n");
     }

     // Main loop (example - display a message):
     while (1) {
        adafruit_tft_fillScreen(ILI9341_BLACK); // Clear the screen to black
        adafruit_tft_setCursor(0, 0); // Set cursor to top-left
        adafruit_tft_print("RT-Thread + TinyUSB"); // Print a message
        rt_thread_mdelay(2000); // Delay for 2 seconds
     }

    return RT_EOK;
}

// USB Device Task (example - CDC ACM)
void usb_device_task(void *param) {
    while (1) {
        tud_task(); // TinyUSB device task
         rt_thread_mdelay(5);
    }
}

// USB Host Task (example)
void usb_host_task(void *param) {
    while (1) {
        thost_task(); // TinyUSB host task
        rt_thread_mdelay(5);
    }
}
