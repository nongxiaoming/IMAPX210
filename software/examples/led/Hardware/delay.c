#include "delay.h"

void delay_ms(unsigned long n)
{
  unsigned long a,b;
  for (a=0;a<n;a++)
	  for (b=0;b<7000;b++);
}
