#ifndef __CLOCK_H
#define __CLOCK_H

/************************************************************************************
*文件名  ：clock.h																                                  *
*文件作用：时钟配置头文件													                                    *
*作者    ：农晓明																	                                  *
*作者QQ  ：382421307																                                  *
*文件创建时间：2013/05/10			  												                            *	
*************************************************************************************/

/*定义配置的一些时钟频率，这里和时钟配置无关
，只是定义给外部使用的相关的时钟值*/
#define APLL 1584000000
#define DPLL 1200000000
#define EPLL 480000000
#define HCLKX2 264000000
#define HCLK   132000000
#define PCLK   66000000

#define TIM0_CLK  60000000
#define TIM1_CLK  60000000
#define CAM_CLK   80000000
#define UART_CLK  80000000
#define GPU_CLK   12000000
#define USB_CLK   48000000
#define IIS_CLK   80000000
#define SD0_CLK   12000000
#define SD1_CLK   12000000
#define SD2_CLK   12000000
void clock_init(void);

#endif /*__CORECLOCK_H*/
