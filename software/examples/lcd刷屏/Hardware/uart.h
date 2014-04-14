#ifndef __UART_H
#define __UART_H
/************************************************************************************
*文件名  ：uart.h																	                                  *
*文件作用：uart驱动头文件													                                    *
*作者    ：农晓明																	                                  *
*作者QQ  ：382421307																                                  *
*文件创建时间：2013/05/9			  												                              *	
*************************************************************************************/
#include "imapx200.h"
#include "stdio.h"

void uart0_init(uint32_t baudrate);
void uart0_send_byte(uint8_t data);
void uart0_send_string(const  uint8_t *pt);
void debug(char* fmt, ...);
#endif /*__UART_H*/
