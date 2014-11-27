/*
 * File      : stm32f20x_40x_spi.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-06-10    xiaonong       The first version for LPC40xx
 */

#ifndef __DRV_SSI_H
#define __DRV_SSI_H

#include <stdint.h>
#include <rtthread.h>
#include <drivers/spi.h>

#include "imapx200.h"


struct imapx200_ssi_bus
{
    struct rt_spi_bus parent;
	IMAP_SSI_TypeDef *ssi;
};

struct imapx200_ssi_cs
{
	IMAP_GPIO_TypeDef *port;
    uint8_t pin;
};

int rt_hw_ssi_init(void);

#endif // __DRV_SSI_H
