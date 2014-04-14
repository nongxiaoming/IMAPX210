#ifndef __INTERRUPT_H
#define __INTERRUPT_H

typedef enum 
{
 EINT0_IRQ=0,
 EINT1_IRQ=1,
 EINT2_IRQ=2,
 EINT3_IRQ=3,
 EINT4_IRQ=4,
 EINT5_IRQ=5,
 AC97_IRQ=6,
 IIS_IRQ=7,
 RTC_TICK_IRQ=8,
 WDT_IRQ=9,
 PWM0_IRQ=10,
 PWM1_IRQ=11,
 PWM2_IRQ=12,
 UART2_IRQ=13,
 IIC0_IRQ=14,
 PWM3_IRQ=15,
 IDS_IRQ=16,
 CAM_IRQ=17,
 TIM0_IRQ=18,
 TIM1_IRQ=19,
 DMA_IRQ=20,
 SSI_MST0_IRQ=21,
 SSI_MST2_IRQ=22,
 UART1_IRQ=23,
 NFCON_IRQ=24,
 USBOTG_IRQ=25,
 OHCI_IRQ=26,
 RESERVED0_IRQ=27,
 DRAM_IRQ=28,
 MONDBG_IRQ=29,
 POWERMODE_IRQ=30,
 RESERVED1_IRQ=31,
 ETH_IRQ=32,
 UART3_IRQ=33,
 IIC1_IRQ=34,
 IDE_IRQ=35,
 SDIO1_IRQ=36,
 SDIO2_IRQ=37,
 PWM4_IRQ=38,
 RESERVED2_IRQ=39,
 VENC_IRQ=40,
 VDEC_IRQ=41,
 RESERVED3_IRQ=42,
 MPOOL_IRQ=43,
 EHCI_IRQ=44,
 PS2_0_IRQ=45,
 KB_IRQ=46,
 GPIO_IRQ=47,
 SDIO0_IRQ=48,
 RESERVED4_IRQ=49,
 PS2_1_IRQ=50,
 UART0_IRQ=51,
 SSI_MST1_IRQ=52,
 RTC_IRQ=53,
 GPU_IRQ=54,
 RESERVED5_IRQ=55,

} VIC_IRQ_NUM;
void interrupt_init(void);
void interrupt_enableVIC(void);
void interrupt_disableVIC(void);
void interrupt_enableIRQ(void);
void interrupt_disableIRQ(void);
void interrupt_enableFIQ(void);
void interrupt_disableFIQ(void);
void interrupt_enable(VIC_IRQ_NUM irq_num);
void interrupt_disable(VIC_IRQ_NUM irq_num);
void interrupt_set_handler(VIC_IRQ_NUM irq_num,void (*handler)(void)); //__irq);

#endif
