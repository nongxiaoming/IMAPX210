#include "imapx200.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "clock.h"

int main(void)
{ uint32_t i=0;
	clock_init();
	LED_GPIO_Config();
	while (1)
	{ 	
     debug("hello,I am xiaonong! This is line %d\r\n",++i);
		 delay_ms(500);
		 LED1(OFF);
		 delay_ms(500);
		 LED1(ON);
	}
}
