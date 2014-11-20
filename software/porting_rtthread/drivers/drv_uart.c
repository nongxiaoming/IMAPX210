/*
 * File      : drv_uart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009-2013 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-11-23     xiaonong      The first version for LPC40xx
 */

#include <rthw.h>
#include <rtthread.h>
#include "board.h"
#include "drv_uart.h"

#if  defined(RT_USING_DEVICE) && defined(RT_USING_SERIAL)
#include <rtdevice.h>


struct imap_uart
{
    struct rt_serial_device serial;
	UART_TypeDef  *uart_device;
	VIC_IRQ_NUM   uart_irq;
};

static rt_err_t uart_configure(struct rt_serial_device *serial, struct serial_configure *cfg)
{

    return RT_EOK;
}

static rt_err_t uart_control(struct rt_serial_device *serial, int cmd, void *arg)
{
    struct imap_uart *uart;

    RT_ASSERT(serial != RT_NULL);
   uart = (struct imap_uart *)serial->parent.user_data;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_CLR_INT:
        /* disable uart recv irq */
		uart->uart_device->IER &= ~UART_RX_INT;
        break;
    case RT_DEVICE_CTRL_SET_INT:
        /* enable uart recv irq */
		uart->uart_device->IER |= UART_RX_INT;
        break;
    }

    return RT_EOK;
}

static int imapx200_putc(struct rt_serial_device *serial, char c)
{
    struct imap_uart *uart;

    uart = (struct imap_uart *)serial->parent.user_data;
	while((uart->uart_device->LSR&(0x01<<5))==0);
	uart->uart_device->DBUF=c;

    return 1;
}

static int imapx200_getc(struct rt_serial_device *serial)
{
    struct imap_uart *uart;

    uart = (struct imap_uart *)serial->parent.user_data;
	if ((uart->uart_device->LSR&(0x01 << 0)) == 0)
	{
		return -1;
	}
	else
	{
		return (uart->uart_device->DBUF & 0xff);
	}
}

static const struct rt_uart_ops imapx200_uart_ops =
{
    uart_configure,
    uart_control,
    imapx200_putc,
    imapx200_getc,
};

#if defined(RT_USING_UART3)
/* UART3 device driver structure */
struct imap_uart uart3;

/**
 * This function will handle serial
 */
static void rt_serial3_handler(int vector, void *param)
{
	rt_uint32_t int_id;

	int_id = uart3.uart_device->IIR & UART_IIR_IID_MASK;

	switch (int_id)
	{
	case UART_IIR_IID_NO_INT:
		break;
	case UART_IIR_IID_TX:

		break;
	case UART_IIR_IID_RX:
		rt_hw_serial_isr(&uart3.serial, RT_SERIAL_EVENT_RX_IND);
		break;
	case UART_IIR_IID_LINE_STATUS:
	case UART_IIR_IID_BUSY_DETECT:
	case UART_IIR_IID_TIMEOUT:
	default:
		break;
	}
}
#endif

void rt_hw_uart_init(void)
{
    struct imap_uart *uart;

#ifdef RT_USING_UART3

    uart = &uart3;
	uart->uart_device = (UART_TypeDef*)UART3_BASE;
    uart->uart_irq = UART3_IRQ;
	uart->serial.config.baud_rate = BAUD_RATE_115200;
    uart->serial.config.bit_order = BIT_ORDER_LSB;
    uart->serial.config.data_bits = DATA_BITS_8;
    uart->serial.config.parity    = PARITY_NONE;
    uart->serial.config.stop_bits = STOP_BITS_1;
    uart->serial.config.invert    = NRZ_NORMAL;
	uart->serial.config.bufsz = RT_SERIAL_RB_BUFSZ;
    uart->serial.ops = &imapx200_uart_ops;
	    /* register UART3 device */
    rt_hw_serial_register(&uart->serial,
                          "uart3",
                          RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX,
                          uart);
	/* disable uart recv irq */
	uart->uart_device->IER &= ~UART_RX_INT;
	rt_hw_interrupt_install(uart->uart_irq, rt_serial3_handler, RT_NULL, "UART3");
	rt_hw_interrupt_umask(uart->uart_irq);
#endif
}

#else
 void uart_putc(char c)
{
	while((LSR3&(0x01<<5))==0);
        THR3=c;
}

void rt_hw_console_output(const char *str)
{
    while(*str)
    {
        uart_putc(*str);
        str++;
    }
}

void rt_hw_uart_init(void)
{
}

#endif // #if  defined(RT_USING_DEVICE) && defined(RT_USING_SERIAL)

