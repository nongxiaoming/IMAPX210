#include "drv_led.h"


void rt_led_hw_init(void)
{
	/* led0 :GPE2*/
	IMAP_GPE->CON &= ~(0x03 << 4);   //设置GPE2为GPIO输出
	IMAP_GPE->CON |= (0x01 << 4);   //设置GPE2为GPIO输出
	IMAP_GPE->DAT &= ~(0x01 << 2);      //设置GPE2输出高电平，关闭LED
	
}

#ifdef RT_USING_FINSH
#include <finsh.h>
void led_test(rt_uint32_t value)
{
	if (value)
	{
		led_on();
	}
	else
	{
		led_off();
	}
}
FINSH_FUNCTION_EXPORT(led_test, e.g: led_test(1).)
#endif
