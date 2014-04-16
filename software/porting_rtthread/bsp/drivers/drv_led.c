#include "drv_led.h"

#define RT_DEVICE_CTRL_RTC_GET_COUNT     0x81        /**< get count                                   */

#define LED_NUM    1
struct led_ctrl
{
    rt_uint32_t num;
    volatile unsigned port;
};

struct lpc_led
{
    /* inherit from rt_device */
    struct rt_device parent;

    struct led_ctrl ctrl[LED_NUM];
};

static struct lpc_led led;

static rt_err_t rt_led_init(rt_device_t dev)
{
    /* led0 :GPE2*/
    GPECON&=~(0x03<<4);   //设置GPE2为GPIO输出
    GPECON|=(0x01<<4);   //设置GPE2为GPIO输出
    GPEDAT&=~(0x01<<2);      //设置GPE2输出高电平，关闭LED
    led.ctrl[0].num = 2;
    led.ctrl[0].port = GPEDAT;
    return RT_EOK;
}

static rt_err_t rt_led_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_led_close(rt_device_t dev)
{
    return RT_EOK;
}

static rt_size_t rt_led_read(rt_device_t dev, rt_off_t pos, void *buffer,
                             rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nr = size;
	rt_uint8_t *value = (rt_uint8_t*)buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nr; index++)
    {
        if ((led.ctrl[pos + index].port) & (1 << led.ctrl[pos + index].num))
        {
            *value = 0;
        }
        else
        {
            *value = 1;
        }
        value++;
    }
    return index;
}

static rt_size_t rt_led_write(rt_device_t dev, rt_off_t pos,
                              const void *buffer, rt_size_t size)
{
    rt_ubase_t index = 0;
    rt_ubase_t nw = size;
    const rt_uint8_t *value = (rt_uint8_t*)buffer;

    RT_ASSERT(dev == &led.parent);
    RT_ASSERT((pos + size) <= LED_NUM);

    for (index = 0; index < nw; index++)
    {
        if (*value++)
        {
            led.ctrl[pos + index].port |= (1 << led.ctrl[pos + index].num);
        }
        else
        {
            led.ctrl[pos + index].port &= ~(1 << led.ctrl[pos + index].num);
        }
    }
    return index;
}

static rt_err_t rt_led_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    RT_ASSERT(dev == &led.parent);

    if (cmd == RT_DEVICE_CTRL_RTC_GET_COUNT)
    {
        rt_uint32_t *led_num = (rt_uint32_t *)args;
        *led_num = LED_NUM;
    }
    return RT_EOK;
}

void rt_hw_led_init(void)
{
    led.parent.type         = RT_Device_Class_Char;
    led.parent.rx_indicate  = RT_NULL;
    led.parent.tx_complete  = RT_NULL;
    led.parent.init         = rt_led_init;
    led.parent.open         = rt_led_open;
    led.parent.close        = rt_led_close;
    led.parent.read         = rt_led_read;
    led.parent.write        = rt_led_write;
    led.parent.control      = rt_led_control;
    led.parent.user_data    = RT_NULL;

    /* register a character device */
    rt_device_register(&led.parent, "led", RT_DEVICE_FLAG_RDWR);
    /* init led device */
    rt_led_init(&led.parent);
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void led_test(rt_uint32_t led_num, rt_uint32_t value)
{
    rt_uint8_t led_value = value;
    rt_led_write(&led.parent, led_num, &led_value, 1);
}
FINSH_FUNCTION_EXPORT(led_test, e.g: led_test(0, 100).)
#endif
