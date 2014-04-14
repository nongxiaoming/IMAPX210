#ifndef __LED_H
#define __LED_H
/************************************************************************************
*文件名  ：led.h																	                                  *
*文件作用：led驱动头文件													                                    *
*作者    ：农晓明																	                                  *
*作者QQ  ：382421307																                                  *
*文件创建时间：2013/05/9			  												                              *	
*************************************************************************************/
#include "imapx200.h"

#define ON  1
#define OFF 0

#define LED1_BIT  (0x01<<2)


#define LED1(x) (x?(GPEDAT&=~LED1_BIT):(GPEDAT|=LED1_BIT))


void LED_GPIO_Config(void);
#endif /*结束__LED_H*/
