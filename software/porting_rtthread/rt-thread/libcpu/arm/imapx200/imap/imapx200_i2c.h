#ifndef __IMAPX_IIC__
#define __IMAPX_IIC__

#define I2C0_BASE 0x20DA0000
#define I2C1_BASE 0x20DA1000

typedef struct
{
unsigned long CON;                //IIC Control register
unsigned long TAR;              //IIC Targer address register
unsigned long SAR;              //IIC Slave address register
unsigned long HS_MADDR;         //IIC High speed master mode code address register
unsigned long DATA_CMD;         //IIC Rx/Tx data buffer and command register
unsigned long SS_SCL_HCNT;      //Standard speed IIC clock SCL high count register
unsigned long SS_SCL_LCNT;      //Standard speed IIC clock SCL low count register
unsigned long FS_SCL_HCNT;      //Fast speed IIC clock SCL high count register
unsigned long FS_SCL_LCNT;      //Fast speed IIC clock SCL low count register
unsigned long HS_SCL_HCNT;      //High speed IIC clock SCL high count register
unsigned long HS_SCL_LCNT;      //High speed IIC clock SCL low count register
unsigned long INTR_STAT;        //IIC Interrupt Status register
unsigned long INTR_MASK;        //IIC Interrupt Mask register
unsigned long RAW_INTR_STAT;    //IIC raw interrupt status register
unsigned long RX_TL;            //IIC receive FIFO Threshold register
unsigned long TX_TL;            //IIC transmit FIFO Threshold register
unsigned long CLR_INTR;         //clear combined and individual interrupt register
unsigned long CLR_RX_UNDER;     //clear RX_UNDER interrupt register
unsigned long CLR_RX_OVER;      //clear RX_OVER interrupt register
unsigned long CLR_TX_OVER;      //clear TX_OVER interrupt register
unsigned long CLR_RD_REQ;       //clear RD_REQ interrupt register
unsigned long CLR_TX_ABRT;      //clear TX_ABRT interrupt register
unsigned long CLR_RX_DONE;      //clear RX_DONE interrupt register
unsigned long CLR_ACTIVITY;     //clear ACTIVITY interrupt register
unsigned long CLR_STOP_DET;     //clear STOP_DET interrupt register
unsigned long CLR_START_DET;    //clear START_DET interrupt register
unsigned long CLR_GEN_CALL;     //clear GEN_CALL interrupt register
unsigned long ENABLE;           //IIC enable register
unsigned long STATUS;           //IIC status register
unsigned long TXFLR;            //IIC transmit FIFO level register
unsigned long RXFLR;            //IIC receive FIFO level register
unsigned long TX_ABRT_SOURCE;         //IIC transmit abort source register
unsigned long ACK_GENERAL_CALL;       //IIC ACK general call register
unsigned long ENABLE_STATUS;          //IIC enable status register
unsigned long SDA_CFG0;               //SDA Configuration Register
}IMAP_I2C_TypeDef;

#define IMAPX_I2C0 ((IMAP_I2C_TypeDef*)I2C0_BASE);
#define IMAPX_I2C1 ((IMAP_I2C_TypeDef*)I2C1_BASE);

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
