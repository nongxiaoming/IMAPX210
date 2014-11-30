/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-02     Aozima       add led function
 */

#include <rtthread.h>

#include <board.h>
#include "drv_led.h"
//#include <components.h>
#ifdef RT_USING_LWIP
#include <drv_emac.h>
#endif
#ifdef RT_USING_SPI
#include "drv_ssi.h"
#include "drv_spi.h"
#endif
#ifdef RT_USING_I2C
#include "drivers/i2c.h"
#endif
#ifdef RT_USING_RTGUI
#include "drv_lcd.h"
#include "drv_key.h"
#include "drv_touch.h"
#endif
/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_SPI
	rt_hw_ssi_init();
#endif
//#ifdef RT_USING_I2C
//    {
//        extern void rt_hw_i2c_init(void);
//        rt_i2c_core_init();
//        rt_hw_i2c_init();
//    }
//#endif
#ifdef  RT_USING_LIBC
	/* init libc */
	libc_system_init(RT_CONSOLE_DEVICE_NAME);
#endif

    /* Filesystem Initialization */
#ifdef RT_USING_DFS
    {
        /* init the device filesystem */
        dfs_init();

        /* init the elm FAT filesystam*/
        elm_init();

        /* mount sd card fat partition 1 as root directory */
        if (dfs_mount("sd0", "/", "elm", 0, 0) == 0)
            rt_kprintf("File System initialized!\n");
        else
            rt_kprintf("File System init failed!\n");
    }
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);
        extern void lpc17xx_emac_hw_init(void);

        eth_system_device_init();

        /* register ethernetif device */
        lpc_emac_hw_init();
        /* init all device */
        rt_device_init_all();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif

#ifdef RT_USING_RTGUI
    {
        extern void rtgui_system_server_init(void);
        extern void application_init(void);
		struct rtgui_calibration_ops *ops;
        rt_device_t lcd;

        /* init lcd */
        rt_hw_lcd_init();
        /* re-init device driver */
        rt_device_init_all();
        /* find lcd device */
        lcd = rt_device_find("lcd");
        if (lcd != RT_NULL)
        {
            /* set lcd device as rtgui graphic driver */
            rtgui_graphic_set_device(lcd);
            /* init rtgui system server */
            rtgui_system_server_init();
            rt_hw_key_init();
			rtgui_touch_hw_init("ssi00");
			ops = calibration_get_ops();
			rtgui_touch_init(ops);
            /* startup rtgui in demo of RT-Thread/GUI examples */
            application_init();
        }

    }
#endif

#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
    finsh_set_device(FINSH_DEVICE_NAME);
#endif
}
/* thread phase init */
void rt_led_thread_entry(void *parameter)
{
	/* initialize led*/
	rt_led_hw_init();
    while (1)
    {
		led_on();
        rt_thread_delay(RT_TICK_PER_SECOND);
		led_off();
		rt_thread_delay(RT_TICK_PER_SECOND);
    }
}
int rt_application_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);
    tid = rt_thread_create("led",
		                   rt_led_thread_entry, RT_NULL,
                           1024, 20, 5);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}
