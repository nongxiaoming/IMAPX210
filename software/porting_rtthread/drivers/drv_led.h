#ifndef __DRV_LED_H
#define __DRV_LED_H
#include "board.h"

#define led_on()   IMAP_GPE->DAT|=(0x01 << 2)
#define led_off()  IMAP_GPE->DAT&=~(0x01 << 2)

void rt_led_hw_init(void);

#endif
