/*
 * File      : interrupt.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-23     xiaonong      first version
 */

#include <rtthread.h>
#include <rthw.h>
#include "imapx200.h"
#include "interrupt.h"

#define MAX_HANDLERS    56

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc isr_table[MAX_HANDLERS];
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

/**
 * @addtogroup IMAPX200
 */
/*@{*/

static void rt_hw_interrupt_handle(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    register rt_uint32_t idx;

    /* all clear source pending */
    SRCPND1 = 0x0;
    SRCPND2 = 0x0;
    /* all clear sub source pending */
    SUBSRCPND = 0x0;

    /* all=IRQ mode */
    INTMOD1 = 0x0;
    INTMOD2 = 0x0;
    /* all interrupt disabled include global bit */
    INTMSK1 = 0xffffffff;
    INTMSK2 = 0xffffffff;
    /* all sub interrupt disable */
    INTSUBMSK = 0xffffffff;

    /* all clear interrupt pending */
    INTPND1 = 0x00000000;
    INTPND2 = 0x00000000;

    /* init exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));
    for (idx = 0; idx < MAX_HANDLERS; idx++)
    {
        isr_table[idx].handler = rt_hw_interrupt_handle;
    }

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    if (vector < 32)
    {
        INTMSK1 |= (1UL << vector);
    }
    else
    {
        vector -= 32;
        INTMSK2 |= (1UL << vector);
    }
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    if (vector == RESERVED0_IRQ || vector == RESERVED1_IRQ || vector == RESERVED2_IRQ || vector == RESERVED3_IRQ || vector == RESERVED4_IRQ || vector == RESERVED5_IRQ)
    {
        rt_kprintf("Interrupt vec %d is not used!\n", vector);
        while (1);
    }
    else  if (vector < 32)
    {
        SRCPND1 = (1UL << vector);
        INTPND1 = (1UL << vector);
        INTMSK1 &= ~(1UL << vector);
    }
	else if (vector<MAX_HANDLERS)
    {
        vector -= 32;
        SRCPND2 = (1UL << vector);
        INTPND2 = (1UL << vector);
        INTMSK2 &= ~(1UL << vector);
    }
	else
	{
		rt_kprintf("Wrong interrupt vec %d\n", vector);
	}
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < MAX_HANDLERS)
    {
        old_handler = isr_table[vector].handler;

        if (handler != RT_NULL)
        {
#ifdef RT_USING_INTERRUPT_INFO
            rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
            isr_table[vector].handler = handler;
            isr_table[vector].param = param;
        }
    }

    return old_handler;
}

/*@}*/
