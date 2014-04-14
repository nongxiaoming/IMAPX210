#ifndef __X200_H
#define __X200_H

#include <stdint.h>
#include "imapx200_gpio.h"
#include "imapx200_uart.h"
#include "imapx200_lcd.h"
#include "imapx200_clock.h"
#ifdef __cplusplus
extern "C" {
#endif

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



/*定时器寄存器*/
#define TCFG0				    (*(volatile unsigned *)(0x7F006000))   /*定时器配置寄存器0,读写*/
#define TCFG1				    (*(volatile unsigned *)(0x7F006004))   /*定时器配置寄存器1,读写*/
#define TCON				    (*(volatile unsigned *)(0x7F006008))   /*定时器控制寄存器,读写*/
/*定时器0*/
#define TCNTB0				    (*(volatile unsigned *)(0x7F00600C))   /*定时器0计数缓冲器,读写*/
#define TCMPB0				    (*(volatile unsigned *)(0x7F006010))   /*定时器0比较缓冲寄存器,读写*/
#define TCNTO0				    (*(volatile unsigned *)(0x7F006014))   /*定时器0计数观察寄存器,读*/
/*定时器1*/
#define TCNTB1				    (*(volatile unsigned *)(0x7F006018))   /*定时器1计数缓冲器,读写*/
#define TCMPB1				    (*(volatile unsigned *)(0x7F00601C))   /*定时器1比较缓冲寄存器,读写*/
#define TCNTO1				    (*(volatile unsigned *)(0x7F006020))   /*定时器1计数观察寄存器,读*/
/*定时器2*/
#define TCNTB2				    (*(volatile unsigned *)(0x7F006024))   /*定时器2计数缓冲器,读写*/
#define TCMPB2				    (*(volatile unsigned *)(0x7F006028))   /*定时器2比较缓冲寄存器,读写*/
#define TCNTO2				    (*(volatile unsigned *)(0x7F00602C))   /*定时器2计数观察寄存器,读*/
/*定时器3*/
#define TCNTB3				    (*(volatile unsigned *)(0x7F006030))   /*定时器3计数缓冲器,读写*/
#define TCMPB3				    (*(volatile unsigned *)(0x7F006034))   /*定时器3比较缓冲寄存器,读写*/
#define TCNTO3				    (*(volatile unsigned *)(0x7F006038))   /*定时器3计数观察寄存器,读*/
/*定时器4*/
#define TCNTB4				    (*(volatile unsigned *)(0x7F00603C))   /*定时器4计数缓冲器,读写*/
#define TCNTO4				    (*(volatile unsigned *)(0x7F006040))   /*定时器4计数观察寄存器,读*/

#define TINT_CSTAT				(*(volatile unsigned *)(0x7F006044))   /*定时器中断控制和状态寄存器,读写*/

/*中断使能寄存器*/
#define VIC0ADDRESS				(*(volatile unsigned *)(0x71200f00))   /*矢量地址寄存器0,读写*/
#define VIC1ADDRESS			  (*(volatile unsigned *)(0x71300f00))   /*矢量地址寄存器1,读写*/


#define VIC0VECTADDR				    (*(volatile unsigned *)(0x71200100))   /*矢量地址寄存器0,读写*/
#define VIC1VECTADDR				    (*(volatile unsigned *)(0x71300100))   /*矢量地址寄存器1,读写*/

#define VIC0INTENABLE				    (*(volatile unsigned *)(0x71200010))   /*中断使能寄存器0,读写*/
#define VIC1INTENABLE				    (*(volatile unsigned *)(0x71300010))   /*中断使能寄存器1,读写*/

#define VIC0INTENCLEAR				    (*(volatile unsigned *)(0x71200014))   /*中断使能清除寄存器0,写*/
#define VIC1INTENCLEAR				    (*(volatile unsigned *)(0x71300014))   /*中断使能清除寄存器1,写*/

#ifdef __cplusplus
}
#endif
#endif /*end __S3C6410_H*/
