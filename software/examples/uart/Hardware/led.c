#include "led.h"


void LED_GPIO_Config(void)
{
 GPECON&=~(0x03<<4);   //设置GPE的高四位为GPIO输出
 GPECON|=(0x01<<4);   //设置GPE的高四位为GPIO输出
 GPEDAT|=0x01<<2;      //设置GPK的高四位输出高电平，关闭LED

}
