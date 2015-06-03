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
 * 2013-06-10     xiaonong      The first version for LPC40xx
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"
#ifdef RT_USING_SPI
#include "drv_ssi.h"
#include "clock.h"
/* private rt-thread spi ops function */
static rt_err_t configure(struct rt_spi_device *device, struct rt_spi_configuration *configuration);
static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message);

static struct rt_spi_ops imapx200_spi_ops =
{
    configure,
    xfer
};

static rt_err_t configure(struct rt_spi_device *device,
                          struct rt_spi_configuration *configuration)
{
	struct imapx200_ssi_bus *spi_bus = (struct imapx200_ssi_bus *)device->bus;
	/* disable ssi */
	spi_bus->ssi->ENR = 0;
    /* data_width */
    if (configuration->data_width > 3 && configuration->data_width <= 16)
    {
		spi_bus->ssi->CTRLR0 &= ~(0x0f << 12);
		spi_bus->ssi->CTRLR0 |= ((configuration->data_width - 1) << 12);

    }
    else
    {
        return RT_EIO;
    }
    /* baudrate */
    {
        uint32_t ssi_max_clock;
        uint32_t max_hz;
         ssi_max_clock = 33000000;
        max_hz = configuration->max_hz;

		if (max_hz > ssi_max_clock)
        {
			max_hz = ssi_max_clock;
        }
	    spi_bus->ssi->BAUDR = PCLK / max_hz;

    }

    /* CPOL */
    if (configuration->mode & RT_SPI_CPOL)
    {
		spi_bus->ssi->CTRLR0 |= (0x01 << 7);
    }
    else
    {
		spi_bus->ssi->CTRLR0 &= ~(0x01 << 7);
    }
    /* CPHA */
    if (configuration->mode & RT_SPI_CPHA)
    {
		spi_bus->ssi->CTRLR0 |= (0x01 << 6);
    }
    else
    {
		spi_bus->ssi->CTRLR0 &= ~(0x01 << 6);
    }
	spi_bus->ssi->TXFTLR = 8;
	spi_bus->ssi->RXFTLR = 8;
    /* Clear the RxFIFO */
    {
        uint8_t i;
        uint16_t temp = temp;
        for (i = 0; i < 8; i++)
        {
            temp = spi_bus->ssi->DR;
        }
    }
	/* enable ssi */
	spi_bus->ssi->ENR = 1;
	/**/
	spi_bus->ssi->SER = 1;

    return RT_EOK;
}

static rt_uint32_t xfer(struct rt_spi_device *device, struct rt_spi_message *message)
{
    struct imapx200_ssi_bus *spi_bus = (struct imapx200_ssi_bus *)device->bus;
    struct rt_spi_configuration *config = &device->config;
    struct imapx200_ssi_cs *spi_cs = device->parent.user_data;
    rt_uint32_t size = message->length;

    /* take CS */
    if (message->cs_take)
    {
		spi_cs->port->DAT &= ~(0x01 << spi_cs->pin);
    }

    {
        if (config->data_width <= 8)
        {
            const rt_uint8_t *send_ptr = message->send_buf;
            rt_uint8_t *recv_ptr = message->recv_buf;
            //  rt_kprintf("size =%d",size);
            while (size--)
            {
                rt_uint8_t data = 0x00;

                if (send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                //Wait until the transmit buffer is empty
				while ((spi_bus->ssi->SR & (0x01 << 2)) == 0x00);
                // Send the byte
                spi_bus->ssi->DR = data;
                //Wait until a data is transmited
				while ((spi_bus->ssi->SR & 0x01) != 0x00);
				//Wait until a data is recv
				while ((spi_bus->ssi->SR & 0x08) == 0x00);
                // Get the received data
                data = spi_bus->ssi->DR;
                if (recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
        else if (config->data_width <= 16)
        {
            const rt_uint16_t *send_ptr = message->send_buf;
            rt_uint16_t *recv_ptr = message->recv_buf;

            while (size--)
            {
                rt_uint16_t data = 0xFF;

                if (send_ptr != RT_NULL)
                {
                    data = *send_ptr++;
                }

                //Wait until the transmit buffer is empty
				while ((spi_bus->ssi->SR & (0x01 << 2) ) == 0x00);
                // Send the byte
                spi_bus->ssi->DR = data;

                //Wait until a data is received
                //while ((spi_bus->ssi->SR & ((0x01 << 2) | (0x01 << 4))) != 0x04);
                // Get the received data
                data = spi_bus->ssi->DR;

                if (recv_ptr != RT_NULL)
                {
                    *recv_ptr++ = data;
                }
            }
        }
    }

    /* release CS */
    if (message->cs_release)
    {
        spi_cs->port->DAT |= (0x01 << spi_cs->pin);
    }

    return message->length;
};

static struct imapx200_ssi_bus imapx200_spi1;
static struct rt_spi_device spi_device;
static struct imapx200_ssi_cs  spi_cs1;
/* SPI
SPI_MOSI: XSSITXD <---> PE4
SPI_MISO: XSSIRXD <---> PE5
SPI_SCK : XSSICLK <---> PE6
CS0:  XSSICSN0 <---> PE7  Touch
*/
int rt_hw_ssi_init(void)
{

    /* register spi bus */
    {
      
		IMAP_GPE->CON &= ~((0x03 << 8) | (0x03 << 10) | (0x03 << 12));
		IMAP_GPE->CON |= (0x02 << 8) | (0x02 << 10) | (0x02 << 12);
		imapx200_spi1.ssi = IMAP_MSSI0;
		//rt_device_register(&imapx200_spi1.parent, "ssi0",)
		rt_spi_bus_register(&imapx200_spi1.parent, "ssi0", &imapx200_spi_ops);
    }
    /* attach cs */
    {
        /* spi10: PE7 */
		IMAP_GPE->CON &= ~(0x03 << 14);
		IMAP_GPE->CON |=  (0x01 << 14);
		IMAP_GPE->PUD |= (0x01 << 7);
		spi_cs1.port = IMAP_GPE;
        spi_cs1.pin = 7;
		spi_cs1.port->DAT |= (0x01 << spi_cs1.pin);

        rt_spi_bus_attach_device(&spi_device, "ssi00", "ssi0", (void *)&spi_cs1);
    }

    return 0;
}
INIT_BOARD_EXPORT(rt_hw_ssi_init);

#endif
