#ifndef __UART_H__
#define __UART_H__
#include <rtthread.h>

/*UART寄存器*/
typedef struct imapx200_uart
{
rt_uint32_t DBUF;       /*LCR[7]=0,接收缓冲区寄存器，只读*/
rt_uint32_t IER ;      /*LCR[7]=0,中断使能寄存器，读写*/
rt_uint32_t IIR;       /*中断辨别寄存器，只读*/
rt_uint32_t LCR;       /*线控制寄存器，读写*/
rt_uint32_t MCR;       /*模式制寄存器，读写*/
rt_uint32_t LSR;       /*线状态寄存器，只读*/
rt_uint32_t CSR;       /*CTS状态寄存器，只读*/
rt_uint32_t LPDLL;     /*低功耗时钟分频寄存器L，读写*/
rt_uint32_t LPDLH;     /*低功耗时钟分频寄存器H，读写*/
}UART_TypeDef;

void rt_hw_uart_init(void);

#endif
