#ifndef __IMAP_TIMER_H
#define __IMAP_TIMER_H

#define WDT_BASE     0x20D90000
#define WDT_CR             (*(volatile unsigned *)(WDT_BASE+0x00))    //Watch Dog? Control register
#define WDT_TORR           (*(volatile unsigned *)(WDT_BASE+0x04))    //Watch Dog? Timeout Range register
#define WDT_CCVR           (*(volatile unsigned *)(WDT_BASE+0x08))    //Watch Dog? current counter value register
#define WDT_CRR            (*(volatile unsigned *)(WDT_BASE+0x0C))    //Watch Dog? Counter restart register
#define WDT_STAT           (*(volatile unsigned *)(WDT_BASE+0x10))    //Watch Dog?interrupt status register
#define WDT_EOI            (*(volatile unsigned *)(WDT_BASE+0x14))    //Watch Dog? interrupt clear register

#define TIMER_BASE     0x20D30000
#define TLC0             (*(volatile unsigned *)(TIMER_BASE+0x00))    //timer0 Load Count register
#define TCV0             (*(volatile unsigned *)(TIMER_BASE+0x04))    //timer0 Current Value register
#define TCR0             (*(volatile unsigned *)(TIMER_BASE+0x08))    //timer0 Control register
#define TEOI0            (*(volatile unsigned *)(TIMER_BASE+0x0C))    //timer0 End-of-Interrupt register
#define TINTST0          (*(volatile unsigned *)(TIMER_BASE+0x10))    //timer0 Interrupt Status register

#define TLC1             (*(volatile unsigned *)(TIMER_BASE+0x14))    //timer1 Load Count register
#define TCV1             (*(volatile unsigned *)(TIMER_BASE+0x18))    //timer1 Current Value register
#define TCR1             (*(volatile unsigned *)(TIMER_BASE+0x1C))    //timer1 Control register
#define TEOI1            (*(volatile unsigned *)(TIMER_BASE+0x20))    //timer1 End-of-Interrupt register
#define TINTST1          (*(volatile unsigned *)(TIMER_BASE+0x24))    //timer1 Interrupt Status register

#define TSINTST          (*(volatile unsigned *)(TIMER_BASE+0xA0))    //Timers Interrupt Status register
#define ITSEOI            (*(volatile unsigned *)(TIMER_BASE+0xA4))    //Timers End-of-Interrupt register
#define TSRINTST         (*(volatile unsigned *)(TIMER_BASE+0xA8))    //Timers Raw Interrupt Status register
#define TSCOMPVERSION    (*(volatile unsigned *)(TIMER_BASE+0xAC))    //Timers Component Version

#define IMAP_TCR_TIMER_EN          (1<<0)
#define IMAP_TCR_TIMER_MD          (1<<1)
#define IMAP_TCR_TIMER_INTMASK     (1<<2)



#endif
