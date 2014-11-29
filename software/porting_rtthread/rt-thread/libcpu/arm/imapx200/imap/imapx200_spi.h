#ifndef __IMAPX_SPI__
#define __IMAPX_SPI__

#define IMAP_SPI_BASE 0x20DF4000
typedef struct
{
	unsigned long SPCON;  /* R / W SPI control register */
	unsigned long SPSTA;  /*  RC SPI status register */
	unsigned long SPPIN;  /*  R / W SPI pin control register */
	unsigned long SPPRE;  /*  R / W SPI baud rate prescaler register */
	unsigned long SPTDAT; /*  R / W SPI Tx data register */
	unsigned long SPRDAT; /*  R SPI Rx data register */
}IMAP_SPI_TypeDef;

#define IMAP_SPI ((IMAP_SPI_TypeDef*)IMAP_SPI_BASE)

#endif
