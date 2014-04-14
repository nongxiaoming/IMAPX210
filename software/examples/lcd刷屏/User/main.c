#include "imapx200.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "clock.h"
#include "glcd.h"

int main(void)
{ uint32_t color=0;
	clock_init();
	LED_GPIO_Config();
	glcd_init();
  glcd_clear(BLUE);
	while (1)
	{ 	
     debug("hello,I am xiaonong!\r\n");
		 delay_ms(500);
		 LED1(OFF);
		 delay_ms(500);
		 LED1(ON);
		color = rand()%0xffffffff;
		 glcd_clear(color);
	}
}
