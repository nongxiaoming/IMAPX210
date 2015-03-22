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


#include "board.h"
#include "drv_i2c.h"

#ifdef RT_USING_I2C


/* I2C clock is set to 1.8MHz */
#define I2C_CLK_DIVIDER         (40)
/* 400KHz I2C bit-rate */
#define I2C_BITRATE         (400000)
/* Standard I2C mode */
#define I2C_MODE    (0)

#define I2CM_STATUS_OK              0x01        /*!< Requested Request was executed successfully. */
#define I2CM_STATUS_ERROR           0x02        /*!< Unknown error condition. */
#define I2CM_STATUS_NAK_ADR         0x04        /*!< No acknowledgement received from slave during address phase. */
#define I2CM_STATUS_BUS_ERROR       0x08        /*!< I2C bus error */
#define I2CM_STATUS_NAK_DAT         0x10        /*!< No acknowledgement received from slave during address phase. */
#define I2CM_STATUS_ARBLOST         0x20        /*!< Arbitration lost. */


struct lpc_i2c_bus
{
    LPC_I2C0_Type *I2C;
    struct rt_i2c_msg *msgs;
    rt_uint32_t num;
    rt_event_t event;

};

static struct lpc_i2c_bus lpc_i2c0;

static  void i2c_set_clock_div(LPC_I2C0_Type *I2Cx, uint32_t clkdiv)
{
    if ((clkdiv >= 1) && (clkdiv <= 65536))
    {
        I2Cx->DIV = clkdiv - 1;
    }
    else
    {
        I2Cx->DIV = 0;
    }
}

static void i2c_set_speed(LPC_I2C0_Type *I2Cx, uint32_t speed)
{
    uint32_t scl;

    scl = SystemCoreClock / ((I2Cx->DIV & 0xFFFF) + 1) / speed;

    I2Cx->MSTTIME = ((((scl >> 1) - 2) & 0x07) << 4) | ((scl - (scl >> 1) - 2) & 0x07);

}

static rt_size_t lpc_i2c_xfer(struct rt_i2c_bus_device *bus,
                              struct rt_i2c_msg msgs[], rt_uint32_t num)
{
	  struct lpc_i2c_bus *lpc_i2c = RT_NULL;
	  rt_uint32_t ev = 0;
	  rt_err_t ret = RT_EOK;
    RT_ASSERT(bus->priv != RT_NULL);
    lpc_i2c = (struct lpc_i2c_bus *)bus->priv;
    lpc_i2c->msgs = &msgs[0];
	  lpc_i2c->num = num;
	 	/* Clear controller state. */
	 lpc_i2c->I2C->STAT = I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR;
	/* Write Address and RW bit to data register */
	 lpc_i2c->I2C->MSTDAT = (lpc_i2c->msgs->addr<<1);

	/* Enter to Master Transmitter mode */
	 lpc_i2c->I2C->MSTCTL = I2C_MSTCTL_MSTSTART;
	 lpc_i2c->num--;
    /* Enable Master Interrupts */
	 lpc_i2c->I2C->INTENSET = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
	 /* Wait for transfer completion */
	 ret = rt_event_recv(lpc_i2c->event,0xff,RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR,bus->timeout,&ev);
	if(ret == RT_EOK)
	{
	 if(ev&I2CM_STATUS_OK)
	 {
		return num;
	 }else
   {
		rt_kprintf("i2c error!\n");
	 return 0;
	 }
	}else
  {
	 lpc_i2c->I2C->MSTCTL = I2C_MSTCTL_MSTSTOP;
	 /* Clear all Interrupts */
	 lpc_i2c->I2C->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
	 return 0;
	}
    
}

/**
 * @brief   Handle I2C0 interrupt by calling I2CM interrupt transfer handler
 * @return  Nothing
 */
void I2C0_IRQHandler(void)
{
    uint32_t status = LPC_I2C0->STAT;
   rt_interrupt_enter();
    /* Master Lost Arbitration */
    if (status & I2C_STAT_MSTRARBLOSS)
    {
        /* send transfer status as Arbitration Lost */
        rt_event_send(lpc_i2c0.event, I2CM_STATUS_ARBLOST);
			  rt_kprintf("i2c Arbitration Lost!\n");
        /* Clear Status Flags */
        LPC_I2C0->STAT = I2C_STAT_MSTRARBLOSS ;
    }
    /* Master Start Stop Error */
    else if (status & I2C_STAT_MSTSTSTPERR)
    {
        /* send transfer status as Bus Error */
        rt_event_send(lpc_i2c0.event, I2CM_STATUS_BUS_ERROR);
			  rt_kprintf("i2c Bus Error!\n");
        /* Clear Status Flags */
        LPC_I2C0->STAT = I2C_STAT_MSTSTSTPERR ;
    }
    /* Master is Pending */
    else if (status & I2C_STAT_MSTPENDING)
    { 
			 
        uint32_t mstatus = (LPC_I2C0->STAT & I2C_STAT_MSTSTATE) >> 1;
        /* Branch based on Master State Code */
        switch (mstatus)
        {
            /* Master idle */
        case I2C_STAT_MSTCODE_IDLE:

            break;

            /* Receive data is available */
        case I2C_STAT_MSTCODE_RXREADY:
            /* Read Data */
            *lpc_i2c0.msgs->buf++ = LPC_I2C0->MSTDAT;
            lpc_i2c0.msgs->len--;
            if (lpc_i2c0.msgs->len)
            {
                /* Set Continue if there is more data to read */
                LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
            }
            else
            {
                /* Set transfer status as OK */
                rt_event_send(lpc_i2c0.event, I2CM_STATUS_OK);
                /* No data to read send Stop */
                LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTSTOP;
							  LPC_I2C0->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
            }

            break;
            /* Master Transmit available */
        case I2C_STAT_MSTCODE_TXREADY:
            if (((lpc_i2c0.msgs->flags & RT_I2C_RD)==0x00) && (lpc_i2c0.msgs->len))
            {
                /* If Tx data available transmit data and continue */
                LPC_I2C0->MSTDAT = *lpc_i2c0.msgs->buf++;
                lpc_i2c0.msgs->len--;
                LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
            }
            else
            {
                if (((lpc_i2c0.msgs->flags & RT_I2C_RD)==0x00) && lpc_i2c0.num)
                {
                    lpc_i2c0.msgs++;
                    lpc_i2c0.num--;
                    if (lpc_i2c0.msgs->len)
                  {
                    /* If receive queued after transmit then initiate master receive transfer*/
                    if (lpc_i2c0.msgs->flags & RT_I2C_RD)
                        {
                            /* Write Address and RW bit to data register */
                            LPC_I2C0->MSTDAT = ((lpc_i2c0.msgs->addr << 1) | 0x1);
                           
                        }
                        else
                        {
                          /* If Tx data available transmit data and continue */
                          LPC_I2C0->MSTDAT = *lpc_i2c0.msgs->buf++;
                          lpc_i2c0.msgs->len--;
                          LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
                        }
												if(!(lpc_i2c0.msgs->flags & RT_I2C_NO_START))
												{
												 /* Enter to Master Transmitter mode */
                            LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTSTART;
												}
                    }else
                    {
										/* If no receive queued then set transfer status as OK */
                    rt_event_send(lpc_i2c0.event, I2CM_STATUS_OK);
                    /* Send Stop */
                    LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTSTOP;
										LPC_I2C0->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
										}
                }
                else
                {
                    /* If no receive queued then set transfer status as OK */
                    rt_event_send(lpc_i2c0.event, I2CM_STATUS_OK);
                    /* Send Stop */
                    LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTSTOP;
									  LPC_I2C0->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
                }
            }
            break;

        case I2C_STAT_MSTCODE_NACKADR:
            /* Set transfer status as NACK on address */
            rt_event_send(lpc_i2c0.event, I2CM_STATUS_NAK_ADR);
            LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTSTOP;
				    LPC_I2C0->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
            break;

        case I2C_STAT_MSTCODE_NACKDAT:
            /* Set transfer status as NACK on data */
            rt_event_send(lpc_i2c0.event, I2CM_STATUS_NAK_DAT);
            LPC_I2C0->MSTCTL = I2C_MSTCTL_MSTSTOP;
				    LPC_I2C0->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
            break;

        default:
            /* Default case should not occur*/
            rt_event_send(lpc_i2c0.event, I2CM_STATUS_ERROR);
				    LPC_I2C0->INTENCLR = I2C_INTENSET_MSTPENDING | I2C_INTENSET_MSTRARBLOSS | I2C_INTENSET_MSTSTSTPERR;
            break;
        }
    }
    else
    {
        /* Default case should not occur */
        rt_event_send(lpc_i2c0.event, I2CM_STATUS_ERROR);
			 rt_kprintf("should not occur!\n");
    }
		rt_interrupt_leave();
}

static const struct rt_i2c_bus_device_ops i2c_ops =
{
    lpc_i2c_xfer,
    RT_NULL,
    RT_NULL
};


int rt_hw_i2c_init(void)
{
    static struct rt_i2c_bus_device device;
	  /* Enable I2C clock */
	  LPC_SYSCON->SYSAHBCLKCTRL1 |= (0x01<<13);
	  /* Enable the clock for Switch Matrix */
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1UL << 12);
	
	  LPC_IOCON->PIO0_22 = (0x01 << 7) | I2C_MODE;
	  LPC_IOCON->PIO0_23 = (0x01 << 7) | I2C_MODE;
	
    LPC_SWM->PINENABLE1 &= ~(0x01<<3);
	  LPC_SWM->PINENABLE1 &= ~(0x01<<4);

	  /* Peripheral reset control to I2C */
	  LPC_SYSCON->PRESETCTRL1 |= (1 << 13);
	  LPC_SYSCON->PRESETCTRL1 &= ~(1 << 13);
	
   /* Disable the clock to the Switch Matrix to save power */
    LPC_SYSCON->SYSAHBCLKCTRL0 &=  ~(1UL << 12);
    /* Setup clock rate for I2C */
    i2c_set_clock_div(LPC_I2C0, I2C_CLK_DIVIDER);

    /* Setup I2CM transfer rate */
    i2c_set_speed(LPC_I2C0, I2C_BITRATE);

    /* Enable Master Mode */
    LPC_I2C0->CFG = (LPC_I2C0->CFG & I2C_CFG_MASK) | I2C_CFG_MSTEN;
    
		/* preemption = 1, sub-priority = 1 */
    NVIC_SetPriority(I2C0_IRQn, ((0x01 << 3) | 0x01));

    /* Enable Interrupt for I2C0 channel */
    NVIC_EnableIRQ(I2C0_IRQn);
		
    rt_memset((void *)&lpc_i2c0, 0, sizeof(struct lpc_i2c_bus));
		lpc_i2c0.I2C = LPC_I2C0;
		lpc_i2c0.event = rt_event_create("i2c0",RT_IPC_FLAG_FIFO);
		
    device.ops = &i2c_ops;
		device.priv = &lpc_i2c0;

		rt_i2c_bus_device_register(&device, "i2c0");
		
		return 0;
}
INIT_BOARD_EXPORT(rt_hw_i2c_init);

#endif
