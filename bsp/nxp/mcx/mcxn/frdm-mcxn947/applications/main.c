/*
 * main.c - Sample RT-Thread Application with CherryUSB Host Initialization
 *
 * Copyright (c) 2006-2024, RT-Thread Development Team
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date          Author       Notes
 * 2025-03-30    Your Name    New sample file for CherryUSB host initialization
 */

 #include <rtdevice.h>
 #include <rtthread.h>
 #include "drv_pin.h"
 #include "usb_config.h"
 #include "usbh_core.h"
 #include "usbh_hid.h"
 #include "fsl_device_registers.h" // Adjust based on your board/platform
 
 #define LEDB_PIN        ((1 * 32) + 2)
 #define BUTTON_PIN      ((0 * 32) + 23)
 
 static void sw_pin_cb(void *args)
 {
     rt_kprintf("Button pressed\r\n");
 }
 
 int main(void)
 {
 #if defined(__CC_ARM)
     rt_kprintf("using armcc, version: %d\n", __ARMCC_VERSION);
 #elif defined(__clang__)
     rt_kprintf("using armclang, version: %d\n", __ARMCC_VERSION);
 #elif defined(__ICCARM__)
     rt_kprintf("using iccarm, version: %d\n", __VER__);
 #elif defined(__GNUC__)
     rt_kprintf("using gcc, version: %d.%d\n", __GNUC__, __GNUC_MINOR__);
 #endif
 
     /* Initialize board peripherals */
     rt_pin_mode(LEDB_PIN, PIN_MODE_OUTPUT);
     rt_pin_mode(BUTTON_PIN, PIN_MODE_INPUT_PULLUP);
     rt_pin_attach_irq(BUTTON_PIN, PIN_IRQ_MODE_FALLING, sw_pin_cb, RT_NULL);
     rt_pin_irq_enable(BUTTON_PIN, 1);
 
     rt_kprintf("Starting CherryUSB host initialization...\n");
 
 #ifdef RT_USING_CHERRYUSB_HOST
     /* Initialize the USB host core */
     int ret = usbh_core_init();
     if (ret != RT_EOK)
     {
         rt_kprintf("USB host core initialization failed! Error code: %d\n", ret);
         return ret;
     }
     rt_kprintf("USB host core initialized successfully!\n");
 
     /* Initialize the USB HID class driver if using HID devices */
     ret = usbh_hid_init();
     if (ret != RT_EOK)
     {
         rt_kprintf("USB HID initialization failed! Error code: %d\n", ret);
         return ret;
     }
     rt_kprintf("USB HID class driver initialized successfully!\n");
 #else
     rt_kprintf("RT_USING_CHERRYUSB_HOST not defined, skipping USB host initialization.\n");
 #endif
 
 #ifdef RT_USING_SDIO
     /* Optional: Mount SD card filesystem if needed */
     rt_thread_mdelay(2000);
     if (dfs_mount("sd", "/", "elm", 0, RT_NULL) == 0)
     {
         rt_kprintf("SD card mounted successfully to '/'\n");
     }
     else
     {
         rt_kprintf("SD card mount failed!\n");
     }
 #endif
 
     /* Main loop: Blink LED */
     while (1)
     {
         rt_pin_write(LEDB_PIN, PIN_HIGH);
         rt_thread_mdelay(500);
         rt_pin_write(LEDB_PIN, PIN_LOW);
         rt_thread_mdelay(500);
     }
 }
 