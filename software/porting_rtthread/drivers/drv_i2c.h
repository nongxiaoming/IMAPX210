/*
 * File      : drv_i2c.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-22    xiaonong       The first version for IMAPX200
 */

#ifndef __DRV_I2C_H
#define __DRV_I2C_H

#include <rtthread.h>
#include <rtdevice.h>

#include "imapx200.h"






int rt_hw_i2c_init(void);

#endif // __DRV_I2C_H
