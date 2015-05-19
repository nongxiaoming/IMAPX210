/*
 * File      : startup.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-06-10     xiaonong      The first version for IMAPX200
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "mmu.h"

#if (defined (__GNUC__))
extern unsigned char __bss_start;
extern unsigned char __bss_end;

#define HEAP_BEGIN      (0x4B000000)
#define HEAP_END        (0x4C000000)
#endif

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    /* initialize board */
    rt_hw_board_init();

    /* show version */
    rt_show_version();

#ifdef RT_USING_HEAP
    rt_system_heap_init((void *)HEAP_BEGIN, (void *)HEAP_END);
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();

    /* initialize application */
    rt_application_init();

    rt_system_timer_init();

    /* initialize timer thread */
    rt_system_timer_thread_init();

    /* initialize idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    while (1);

}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* startup RT-Thread RTOS */
    rtthread_startup();

    return 0;
}
