#include "timer.h"
#include "interrupt.h"

int i=0;
//定时器服务例程
void  Isr_Timer0(void)
{ 

	INTPND1=(0x01UL<<TIM0_IRQ);
	SRCPND1=(0x01UL<<TIM0_IRQ);
 	i++;
  debug("timer:%d\n",i);
}

//extern void OS_CPU_IRQ_ISR(void);
 void timer_init(void)
 {
    TCR0&=~(0x01);			   //失能timer0
	  TLC0 = 5000000;
	// VICVECTADDR(TIM0_IRQ)=(volatile unsigned long)Isr_Timer0;
	interrupt_set_handler(TIM0_IRQ,Isr_Timer0);//中断服务函数入口
  interrupt_enable(TIM0_IRQ);
	TCR0=0x03;
 }

 void timer_delay(uint32_t n)
 {
    TCR0&=~(0x01);			   //失能timer0
	TLC0 =  000*n;
	TCR0=0x05;
	 while(TCV0);
}
