#ifndef __IMAPX_SSI__
#define __IMAPX_SSI__

#define MSSI0_BASE 0x20DF0000
#define MSSI1_BASE 0x20DF1000
#define MSSI2_BASE 0x20DF2000
#define SSSI_BASE  0x20DF3000

typedef struct
{
	unsigned long CTRLR0;   /* RW Control Register 0 */
	unsigned long CTRLR1;   /*  RW Control Register 1 */
	unsigned long MSSIENR;  /*  RW MSSI Enable Register */
	unsigned long MWCR;     /*  RW Microwire Control Register */
	unsigned long SER;      /*  RW Slave Enable Register Width : MSSI_NUM_SLAVES */
	unsigned long BAUDR;    /*  RW Baud Rate Select */
	unsigned long TXFTLR;   /*  RW Transmit FIFO Threshold Level */
	unsigned long RXFTLR;   /*  RW Receive FIFO Threshold Level */
	unsigned long TXFLR;    /*  RW Transmit FIFO Level Register Width : TX_ABW + 1 */
	unsigned long RXFLR;    /*  RW Receive FIFO Level Register Width : RX_ABW + 1 */
	unsigned long SR;       /*  R Status Register */
	unsigned long IMR;      /*  RW Interrupt Mask Register */
	unsigned long ISR;      /*  R Interrupt Status Register */
	unsigned long RISR;     /*  R Raw Interrupt Status Register */
	unsigned long TXOICR;   /*  R Transmit FIFO Overflow Interrupt Clear Register */
	unsigned long RXOICR;   /*  R Receive FIFO Overflow Interrupt Clear Register */
	unsigned long RXUICR;   /*  R Receive FIFO Underflow Interrupt Clear Register */
	unsigned long MSTICR;   /*  R Multi - Master Interrupt Clear Register */
	unsigned long ICR;      /*  R Interrupt Clear Register */
	unsigned long DMACR;    /*  RW DMA Control Register */
	unsigned long DMATDLR;  /*  RW DMA Transmit Data Level */
	unsigned long DMARDLR;  /*  RW DMA Receive Data Level */
	unsigned long IDR;
	unsigned long VERSION;
	unsigned long DR;       /*  RW Data Register */
}IMAP_SSI_TypeDef;

#define IMAP_MSSI0 ((IMAP_SSI_TypeDef*)MSSI0_BASE)
#define IMAP_MSSI1 ((IMAP_SSI_TypeDef*)MSSI1_BASE)
#define IMAP_MSSI2 ((IMAP_SSI_TypeDef*)MSSI2_BASE)
#define IMAP_SSSI  ((IMAP_SSI_TypeDef*)SSSI_BASE)

#endif
