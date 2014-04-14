#include "led.h"


void LED_GPIO_Config(void)
{
//ÉèÖÃGPE[2]ÎªGPIOÊä³ö
 GPECON&=~(0x03<<4);   
 GPECON|=(0x01<<4);   
 GPEDAT|=0x01<<2;      
}
