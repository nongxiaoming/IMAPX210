#ifndef __CLOCK_H
#define __CLOCK_H
#include "imapx200.h"

/*APLL_FOUT=12*333/(3*2)=666Mhz*/
#define APLL_CON_VAL  ((1<<31) | (333 << 16) | (3 << 8) |(1))
/*MPLL_FOUT=12*266/(3*2^2)=266Mhz*/
#define MPLL_CON_VAL  ((1<<31) | (266 << 16) | (3 << 8) | (2))
/*EPLL_FOUT=12*(32+0)/(1*2^2)=96Mhz*/
#define EPLL_CON0_VAL  ((1<<31) | (32 << 16) | (1 << 8) | (2))
#define EPLL_CON1_VAL  0

/*CLK_SRC时钟选择寄存器的配置值，ACLK,MCLK,ECLK都使用PLL*/
#define CLK_SRC_VAL   0x07  
/*配置ARMCLK=667Mhz，HCLKX2=266Mhz，HCLK=133Mhz，
PCLK=66Mhz，CLKSECUR=66Mhz，CLKJPEG=66Mhz*/
#define CLK_DIV0_VAL     ((3<<24) | (3<<20) | (3<<18) | (3<<12) | (1<<8)) 

/*定义配置的一些时钟频率，这里和时钟配置无关
，只是定义给外部使用的相关的时钟值*/
#define APLL 1584000000UL
#define DPLL 1200000000UL
#define EPLL 480000000UL
#define HCLKX2 264000000UL
#define HCLK   132000000UL
#define PCLK   66000000UL

#define TIM0_CLK  60000000UL
#define TIM1_CLK  60000000UL
#define CAM_CLK   80000000UL
#define UART_CLK  80000000UL
#define GPU_CLK   12000000UL
#define USB_CLK   48000000UL
#define IIS_CLK   80000000UL
#define SD0_CLK   12000000UL
#define SD1_CLK   12000000UL
#define SD2_CLK   12000000UL

void rt_hw_clock_init(void);
#endif /*__CORECLOCK_H*/
