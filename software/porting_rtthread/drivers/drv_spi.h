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

#ifndef __DRV_SPI_H
#define __DRV_SPI_H

#include <stdint.h>
#include <rtthread.h>
#include <drivers/spi.h>

#include "imapx200.h"

typedef struct
{
	rt_uint32_t SPCON;
	rt_uint32_t SPSTA;
	rt_uint32_t SPPIN;
	rt_uint32_t SPPRE;
	rt_uint32_t SPTDAT;
	rt_uint32_t SPRDAT;
}imapx200_spi_t;

struct imapx200_spi_bus
{
    struct rt_spi_bus parent;
	imapx200_spi_t *spi;
};

struct imapx200_spi_cs
{
    rt_uint32_t port;
    uint8_t pin;
};

int rt_hw_spi_init(void);

#endif // __DRV_SPI_H
