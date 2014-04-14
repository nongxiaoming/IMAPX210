#include "timer.h"

#define VIC0VECTADDR23		(*(volatile unsigned *)(0x71200100+4*23))
#define VIC0VECTADDR7		(*(volatile unsigned *)(0x71200100+4*7))
int i=0;
//定时器服务例程
void __irq Isr_Timer0(void)
{ 

	TCON |=0;
	TINT_CSTAT |=1<<5;		//清除定时器状态位
	i++;
	VIC0ADDRESS=0xffffffff;//清除中断标志位
	TCON |=1;
    //debug("timer:%d\n",i);
}

//extern void OS_CPU_IRQ_ISR(void);
 void timer_init(void)
 {
    TINT_CSTAT=1<<5;			//清除定时器状态位
	 TINT_CSTAT |= 1<<0;       //开timer0中断,允许timer0中断发生
	 VIC0INTENABLE |= 1<<23;   //开timer0的使能
	 VIC0VECTADDR23=(volatile unsigned )Isr_Timer0;//中断服务函数入口
	 
	// VIC0VECTADDR7=(volatile unsigned long)OS_CPU_IRQ_ISR;
	 TCFG0 =65;   			// 设置分频因子(66分频), 定时器时钟频率为1Mhz
	 TCNTB0 = 1000;     //设置初值，用于TCTB0
	 TCON |= 1<<1;      	//设置初值后要更新TCNTB
	 TCON |= 1<<3;     	//自动重装开启
	 TCON &= ~(1<<1);   	//不再Update TCNTB0,TCMPB0
	 TCON |= 1<<0;       	//timer0 open;
 }
