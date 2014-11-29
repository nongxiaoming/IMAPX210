#ifndef __IMAPX_IIC__
#define __IMAPX_IIC__

#define I2C0_BASE 0x20DA0000
#define I2C1_BASE 0x20DA1000

typedef struct
{
	unsigned long I2C_CON;           /* R / W I2C channel 0 control register */
	unsigned long I2C_TAR;           /* RC I2C channel 0 Target Address */
	unsigned long I2C_SAR;           /* R / W I2C channel 0 Slave Address */
	unsigned long I2C_HS_MADDR;      /* R / W I2C cannel 0 HS Master Mode Code Address */
	unsigned long I2C_DATA_CMD;      /* R / W I2C channel 0 Rx / Tx Data Buffer and Command */
	unsigned long I2C_SS_SCL_HCNT;   /* R / W I2C channel 0 Standard speed I2C Clock SCL High Count */
	unsigned long I2C_SS_SCL_LCNT;   /* R / W I2C channel 0 Standard speed I2C Clock SCL Low Count */
	unsigned long I2C_FS_SCL_HCNT;   /* R / W I2C channel 0 Fast speed I2C Clock SCL High Count */
	unsigned long I2C_FS_SCL_LCNT;   /* R / W I2C channel 0 Fast speed I2C Clock SCL Low Count */
	unsigned long I2C_HS_SCL_HCNT;   /* R / W I2C channel 0 High speed I2C Clock SCL High Count */
	unsigned long I2C_HS_SCL_LCNT;   /* R / W I2C channel 0 High speed I2C Clock SCL Low Count */
	unsigned long I2C_INTR_STAT;     /* R I2C channel 0 Interrupt Status */
	unsigned long I2C_INTR_MASK;     /* R / W I2C channel 0 Interrupt Mask */
	unsigned long I2C_RAW_INTR_STAT; /* R I2C channel 0 Raw Interrupt Status */
	unsigned long I2C_RX_TL;         /* R / W I2C channel 0 Receive FIFO Threshold */
	unsigned long I2C_TX_TL;         /* R / W I2C channel 0 Transmit FIFO Threshold */
	unsigned long I2C_CLR_INTR;      /*  R I2C channel 0 Clear Combined and Individual Interrupts */
	unsigned long I2C_CLR_RX_UNDER;  /*  R I2C channel 0 Clear RX_UNDER Interrupt */
	unsigned long I2C_CLR_RX_OVER;   /*  R I2C channel 0 Clear RX_OVER Interrupt */
	unsigned long I2C_CLR_TX_OVER;   /*  R I2C channel 0 Clear TX_OVER Interrupt */
	unsigned long I2C_CLR_RD_REQ;    /*  R I2C channel 0 Clear RD_REQ Interrupt */
	unsigned long I2C_CLR_TX_ABRT;   /*  R I2C channel 0 Clear TX_ABRT Interrupt */
	unsigned long I2C_CLR_RX_DONE;   /*  R I2C channel 0 Clear RX_DONE Interrupt */
	unsigned long I2C_CLR_ACTIVITY;  /*  R I2C channel 0 Clear ACTIVITY Interrupt */
	unsigned long I2C_CLR_STOP_DET;  /*  R I2C channel 0 Clear STOP_DET Interrupt */
	unsigned long I2C_CLR_START_DET; /*  R I2C channel 0 Clear START_DET Interrupt */
	unsigned long I2C_CLR_GEN_CALL;  /*  R I2C channel 0 Clear GEN_CALL Interrupt */
	unsigned long I2C_ENABLE;        /*  R / W I2C channel 0 Enable */
	unsigned long I2C_STATUS;        /*  R I2C channel 0 Status Register */
	unsigned long I2C_TXFLR;            /*  R I2C channel 0 Transmit FIFO Level Registers */
	unsigned long I2C_RXFLR;            /*  R I2C channel 0 Receive FIFO Level Register */
	unsigned long Reserved0;
	unsigned long I2C_TX_ABRT_SOURCE;   /*  R / W I2C channel 0 Transmit Abort Status Register */
	unsigned long Reserved1[5];
	unsigned long I2C_ACK_GENERAL_CALL; /*  R / W I2C channel 0 ACK General Call Register */
	unsigned long I2C_ENABLE_STATUS;    /*  R I2C channel 0 Enable Status Register */
	unsigned long I2C_SDA_CFG;          /*  R / W I2C channel 0 SDA Configuration Register */
}IMAP_I2C_TypeDef;

#define IMAP_I2C0 ((IMAP_I2C_TypeDef*)I2C0_BASE);
#define IMAP_I2C1 ((IMAP_I2C_TypeDef*)I2C1_BASE);

//Bit Control
#define I2C_ENABLE			(0x1)
#define I2C_DEFAULT_SS_SCL_HCNT	(0xf0)
#define I2C_DEFAULT_SS_SCL_LCNT	(0xf0)
#define I2C_DEFAULT_SS_SCL_HCNT_SLOW	(0x180)
#define I2C_DEFAULT_SS_SCL_LCNT_SLOW	(0x180)
#define I2C_DEFAULT_RX_TL		(0x0)
#define I2C_DEFAULT_TX_TL		(0x2)
#define I2C_DEFAULT_SDA 		(0x20)
#define I2C_STANDARD_SPEED			(0x1<<1)
#define I2C_MATER_MODE			(0x1)
#define I2C_SLAVE_DISABLE			(0x1<<6)
#define I2C_IGNOREACK			(0x1<<8)
#define I2C_RESTART_ENABLE			(0x1<<5)
#define I2C_MASK_ALL_INT			(0x0)
#define I2C_START_INT			(0x1<<10)
#define I2C_STOP_INT			(0x1<<9)
#define I2C_ACTIVITY_INT			(0x1<<8)
#define I2C_IIC_ENABLE			(0x1)
#define I2C_MSTART_INT			(0x1<<10)
#define I2C_STOP_INT			(0x1<<9)
#define I2C_ACTIVITY_INT			(0x1<<8)
#define I2C_TX_FIFO_DEPTH		(0x10)
#define I2C_RX_FIFO_DEPTH		(0x10)
#define I2C_READ_CMD			(0x1<<8)
#define I2C_RX_FULL			(0x1<<2)
#define I2C_TX_ABORT			(0x1<<6)
#define I2C_TX_EMPTY			(0x1<<4)
#define I2C_LOST_ARBITRATION		(0x1<<12)
// MASK BIT
#define INT_GEN_CALL    (0x1<<11)
#define INT_START_DET   (0x1<<10)
#define INT_STOP_DET    (0x1<<9)
#define INT_ACTIVE      (0x1<<8)
#define INT_RX_DONE     (0x1<<7)
#define INT_TX_ABORT    (0x1<<6)
#define INT_RD_REQ      (0x1<<5)
#define INT_TX_EMPTY    (0x1<<4)
#define INT_TX_OVER     (0x1<<3)
#define INT_RX_FULL     (0x1<<2)
#define INT_RX_OVER     (0x1<<1)
#define INT_RX_UNDER    (0x1<<0)

#endif
