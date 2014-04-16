#ifndef __IMAP_IRQ_H
#define __IMAP_IRQ_H

#define IRQ_BASE        0x20cb0000
#define SRCPND1     					 (*(volatile unsigned *)(IRQ_BASE+0x00 ))	//Interrupt request status
#define INTMOD1     					 (*(volatile unsigned *)(IRQ_BASE+0x04 ))	//Interrupt mode control
#define INTMSK1     					 (*(volatile unsigned *)(IRQ_BASE+0x08 ))	//Interrupt mask control
#define PRIORITY1   					 (*(volatile unsigned *)(IRQ_BASE+0x0c ))	//IRQ priority control
#define INTPND1     					 (*(volatile unsigned *)(IRQ_BASE+0x10 ))	//Interrupt request status
#define INTOFFSET  					   (*(volatile unsigned *)(IRQ_BASE+0x14 ))	//Interruot request source offset
#define SUBSRCPND  					   (*(volatile unsigned *)(IRQ_BASE+0x18 ))	//Sub source pending
#define INTSUBMSK  					   (*(volatile unsigned *)(IRQ_BASE+0x1c ))	//Interrupt sub mask
#define INTCON						     (*(volatile unsigned *)(IRQ_BASE+0x20 ))
#define SRCPND2    					   (*(volatile unsigned *)(IRQ_BASE+0x24 ))  //Interrupt reguest status 2
#define INTMOD2    					   (*(volatile unsigned *)(IRQ_BASE+0x28 ))  //Interrupt mode control 2  
#define INTMSK2    					   (*(volatile unsigned *)(IRQ_BASE+0x2c ))  //Interrupt mask control 2  
#define PRIORITY2  					   (*(volatile unsigned *)(IRQ_BASE+0x30 ))  //IRQ prioity control 2     
#define INTPND2    					   (*(volatile unsigned *)(IRQ_BASE+0x34 ))  //Interrupt request status 2
#define DEINTMSK1    					 (*(volatile unsigned *)(IRQ_BASE+0x38 ))
#define DEINTMSK2    					 (*(volatile unsigned *)(IRQ_BASE+0x3C ))

#define IRQ_ADR_BASE        0x20cb1000
#define VICVECTADDR(x)				    (*(volatile unsigned *)(IRQ_ADR_BASE+4*x))   /*Ê¸Á¿µØÖ·¼Ä´æÆ÷,¶ÁÐ´*/
#endif
