/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-23     xiaonong      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include "mmu.h"

#include "drv_uart.h"
#include "drv_led.h"

/**
 * This function will handle rtos timer
 */
static void rt_timer_handler(int vector, void *param)
{
    volatile rt_uint32_t dummy;
    rt_tick_increase();
    dummy = TEOI0;
}

void rt_timer_hw_init()
{
    TCR0 &= ~(0x01);
    TLC0 = (66 * 1000000UL) / RT_TICK_PER_SECOND;

    /* install interrupt handler */
    rt_hw_interrupt_install(TIM0_IRQ, rt_timer_handler, RT_NULL, "tick");
    rt_hw_interrupt_umask(TIM0_IRQ);

    TCR0 = 0x03;
}

/**
 * This function will initial imapx200 board.
 */
void rt_hw_board_init()
{

    /* initialize system clock */
    rt_hw_clock_init();
    rt_kprintf("init hardware interrupt\r\n");
    /* init hardware interrupt */
    rt_hw_interrupt_init();

    MEM_SWAP = 0x01;
    rt_kprintf("initialize uart\r\n");
    /* initialize uart */
    rt_hw_uart_init();
    //rt_kprintf("enable cpu cache\r\n");
    /* enable cpu cache */
    //rt_hw_cpu_icache_enable();
    //rt_hw_cpu_dcache_enable();
    //rt_kprintf("initialize mmu\r\n");
    /* initialize mmu */
    //rt_hw_mmu_init();

    /* set the console device*/
    //rt_console_set_device(RT_CONSOLE_DEVICE_NAME);
    rt_kprintf("initialize timer0\r\n");
    /* initialize timer0 */
    rt_timer_hw_init();

    /* initialize led*/
    //rt_led_hw_init();

    return;
}
