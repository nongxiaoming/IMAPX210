#include "delay.h"
#include "led.h"
//#include "uart.h"

int main(void)
{ 
	LED_GPIO_Config();
	while (1)
	{ 	
		 delay_ms(500);
		 LED1(OFF);
		 delay_ms(500);
		 LED1(ON);
		
	}
}
