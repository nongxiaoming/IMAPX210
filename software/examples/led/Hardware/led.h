#ifndef __LED_H
#define __LED_H

#define GPEDAT        (*(volatile unsigned *)(0x20e10040))
#define GPECON        (*(volatile unsigned *)(0x20e10044))
#define GPEPUD        (*(volatile unsigned *)(0x20e10048))

#define ON  1
#define OFF 0

#define LED1_BIT  (0x01<<2)


#define LED1(x) (x?(GPEDAT&=~LED1_BIT):(GPEDAT|=LED1_BIT))


void LED_GPIO_Config(void);
#endif /*½áÊø__LED_H*/
