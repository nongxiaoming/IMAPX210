#ifndef __LED_H
#define __LED_H

#include "imapx200.h"

#define ON  1
#define OFF 0

#define LED1_BIT  (0x01<<2)


#define LED1(x) (x?(GPEDAT&=~LED1_BIT):(GPEDAT|=LED1_BIT))


void LED_GPIO_Config(void);
#endif /*½áÊø__LED_H*/
