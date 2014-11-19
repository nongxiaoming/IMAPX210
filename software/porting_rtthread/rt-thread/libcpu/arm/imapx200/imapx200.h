#ifndef __X200_H
#define __X200_H

#include <rtthread.h>
#include "imapx200_gpio.h"
#include "imapx200_uart.h"
#include "imapx200_lcd.h"
#include "imapx200_clock.h"
#include "imapx200_rtc.h"
#include "imapx200_irq.h"
#include "imapx200_timer.h"

/*定义位操作*/
#define BIT(x) (BIT0<<x)
#define BIT0            0x00000001   
#define BIT1            0x00000002   
#define BIT2            0x00000004   
#define BIT3            0x00000008   
#define BIT4            0x00000010   
#define BIT5            0x00000020   
#define BIT6            0x00000040   
#define BIT7            0x00000080   
#define BIT8            0x00000100   
#define BIT9            0x00000200   
#define BIT10           0x00000400   
#define BIT11           0x00000800   
#define BIT12           0x00001000   
#define BIT13           0x00002000   
#define BIT14           0x00004000   
#define BIT15           0x00008000   
#define BIT16           0x00010000   
#define BIT17           0x00020000   
#define BIT18           0x00040000   
#define BIT19           0x00080000   
#define BIT20           0x00100000   
#define BIT21           0x00200000   
#define BIT22           0x00400000   
#define BIT23           0x00800000   
#define BIT24           0x01000000   
#define BIT25           0x02000000   
#define BIT26           0x04000000   
#define BIT27           0x08000000   
#define BIT28           0x10000000   
#define BIT29           0x20000000   
#define BIT30           0x40000000   
#define BIT31           0x80000000      

	/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE		0x10
#define FIQMODE			0x11
#define IRQMODE			0x12
#define SVCMODE			0x13
#define ABORTMODE		0x17
#define UNDEFMODE		0x1b
#define MODEMASK		0x1f
#define NOINT			0xc0

struct rt_hw_register
{
	rt_uint32_t r0;
	rt_uint32_t r1;
	rt_uint32_t r2;
	rt_uint32_t r3;
	rt_uint32_t r4;
	rt_uint32_t r5;
	rt_uint32_t r6;
	rt_uint32_t r7;
	rt_uint32_t r8;
	rt_uint32_t r9;
	rt_uint32_t r10;
	rt_uint32_t fp;
	rt_uint32_t ip;
	rt_uint32_t sp;
	rt_uint32_t lr;
	rt_uint32_t pc;
	rt_uint32_t cpsr;
	rt_uint32_t ORIG_r0;
};

#endif /*end __IMAPX200_H*/
