#ifndef __KEY_H
#define __KEY_H

#include "s3c6410.h"

#define KEY1   0x01
#define KEY2   0x02
#define KEY3   0x04
#define KEY4   0x08
#define KEY5   0x10
#define KEY6   0x20
#define KEY7   0x800
#define KEY8   0x1000

void key_init(void);
int key_scanf(void);

#endif
