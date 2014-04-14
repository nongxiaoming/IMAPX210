#include "interrupt.h"
#include "imapx200.h"
#include "uart.h"

//#define POW_STB         			     (*(volatile unsigned *)(0x20c00208 ))
void (*isr_handle_array[55])(void) ;// __irq; //º¯ÊýÖ¸Õë

void  Dummy_isr(void)
{
    while(1)
			{
      debug("error interrupt\r\n");
     }
}

void interrupt_enableVIC(void){
	 register uint32_t value;
	__asm{
		mrc 	p15,0,value,c1,c0,0
		orr 	value,value,#(1<<24)
		mcr 	p15,0,value,c1,c0,0
	}
}
void interrupt_disableVIC(void){
	register uint32_t value;
	__asm{
		mrc 	p15,0,value,c1,c0,0
		bic 	value,value,#(1<<24)
	    mcr 	p15,0,value,c1,c0,0
	}
}
void interrupt_enableIRQ(void){
	register uint32_t value;
	__asm{
		mrs		value,cpsr
		bic		value,value,#(1<<7)
		msr		cpsr_cxsf,value
	}
}
void interrupt_disableIRQ(void){
	register uint32_t value;
	__asm{
		mrs		value,cpsr
		orr		value,value,#(1<<7)
		msr		cpsr_cxsf,value 
	}
}
void interrupt_enableFIQ(void){
	register uint32_t value;
	__asm{
		mrs		value,cpsr
		bic		value,value,#(1<<6)
		msr		cpsr_cxsf,value
	}
}
void interrupt_disableFIQ(void){
	register uint32_t value;
	__asm{
		mrs		value,cpsr
		orr		value,value,#(1<<6)
		msr		cpsr_cxsf,value  
	}
}
void interrupt_enable(VIC_IRQ_NUM irq_num){
	if (irq_num<32)
	{
		INTMSK1&=~(0x01<<irq_num);
	}
	else if(irq_num<56)
    {   
		irq_num-=32;
		INTMSK2&=~(0x01<<irq_num);
    }else
		{
      debug("error interrupt number:%d\r\n",irq_num);
    }
}
void interrupt_disable(VIC_IRQ_NUM irq_num){
if (irq_num<32)
	{
		INTMSK1|=(0x01<<irq_num);
		INTPND1=(0x01<<irq_num);
	  SRCPND1=0x00;
	}
	else if(irq_num<56)
    {   
		irq_num-=32;
		INTMSK2|=(0x01<<irq_num);
		INTPND2=(0x01<<irq_num);
	  SRCPND2=0x00;
    }else
		{
      debug("error interrupt number:%d\r\n",irq_num);
    }
}
void interrupt_set_handler(VIC_IRQ_NUM irq_num,void (*handler)(void)) //__irq)
{
		isr_handle_array[irq_num]=handler;

}
void interrupt_handler(void)  
{
   uint32_t offset = INTOFFSET;
	debug("interrupt number:%d\r\n",offset);
	// (*isr_handle_array[offset])();
}
void interrupt_init(void)
{  
	 unsigned char i;
   INTMSK1=0xffffffff;
	 INTMSK2=0xffffffff;
	 SRCPND1=0xffffffff;
	 SRCPND2=0xffffffff;
	 INTPND1=0xffffffff;
	 INTPND2=0xffffffff;
	for(i=0;i<56;i++)
		{
    switch (i) {
// 			case IRQ_RESERVED0:
// 			case IRQ_RESERVED1:
// 			case IRQ_RESERVED2:
// 			case IRQ_RESERVED3:
// 				/* No irq */
// 				break;
// 			case IRQ_TIMER0:
// 				set_irq_chip(irqno, &imapx200_timer_chip);
// 				set_irq_handler(irqno, handle_edge_irq);
// 				set_irq_flags(irqno, IRQF_VALID);
// 				break;
			default:
		interrupt_set_handler((VIC_IRQ_NUM)i,Dummy_isr);
				break;
		}
   }
 	 interrupt_enableVIC();
 	 //interrupt_enableIRQ();
	 interrupt_enableFIQ();
	 POW_STB=0x04;
}

