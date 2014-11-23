#ifndef __IMAPX_SPI__
#define __IMAPX_SPI__

#define IMAP_SPI_BASE 0x20DF4000
typedef struct
{
 unsigned long CON;	//SPI control
 unsigned long STA;	//SPI status
 unsigned long PIN;    //SPI pin control
 unsigned long PRE;	//SPI baud rate prescaler
 unsigned long TDAT;	//SPI Tx data
 unsigned long RDAT;	//SPI Rx data
}IMAP_GPIO_TypeDef;

#define IMAP_SPI ((IMAP_GPIO_TypeDef*)IMAP_SPI_BASE)

#endif
