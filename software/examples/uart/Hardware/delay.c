#include "delay.h"

void delay_ms(uint32_t n)
{
  uint32_t a,b;
  for (a=0;a<n;a++)
	  for (b=0;b<7000;b++);
}
