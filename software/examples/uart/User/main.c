#include "imapx200.h"
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "glcd.h"

int main(void)
{ uint32_t color=0,i=0;
	LED_GPIO_Config();
	glcd_init();
		glcd_clear(BLUE);
 //timer_init();
 
  glcd_set_colors(RED,BLUE);
  delay_ms(50);
	glcd_draw_hline(100,100,100);
	glcd_draw_hline(100,200,100);
	glcd_draw_vline(100,100,100);
	glcd_draw_vline(200,100,100);

  glcd_draw_string(1,1,"Hello My LCD");
   glcd_draw_num(10,50,12345,5);
  delay_ms(50);
   glcd_set_colors(RED,GREEN);
  delay_ms(50);
   glcd_draw_circle(200,100,50);
  delay_ms(50);
  glcd_fill_circle(100,100,50);
   delay_ms(50);
  glcd_draw_rect(300,50,100,80);
  delay_ms(50);
  glcd_fill_rect(300,150,100,80);
	while (1)
	{ 	
     debug("hello,I am xiaonong! This is line %d\r\n",++i);
		 delay_ms(500);
		 LED1(OFF);
		 delay_ms(500);
		 LED1(ON);
// 		color = rand()%0xffffffff;
// 		 glcd_clear(color);
	}
}
