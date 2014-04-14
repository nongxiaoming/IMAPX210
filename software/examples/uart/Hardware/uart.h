#ifndef __UART_H
#define __UART_H

#include "imapx200.h"
#include "stdio.h"

void uart0_init(uint32_t baudrate);
void uart0_send_byte(uint8_t data);
void uart0_send_string(const  uint8_t *pt);
void debug(char* fmt, ...);
#endif /*__UART_H*/
