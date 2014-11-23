#ifndef __IMAPX_SSI__
#define __IMAPX_SSI__

#define MSSI0_BASE 0x20DF0000
#define MSSI1_BASE 0x20DF1000
#define MSSI2_BASE 0x20DF2000
#define SSSI_BASE  0x20DF3000

typedef struct
{
 unsigned long CTLR0;
 unsigned long CTLR1;
 unsigned long ENR;
 unsigned long MWCR;
 unsigned long SER;
 unsigned long BAUDR;
 unsigned long TXFTLR;
 unsigned long RXFTLR;
 unsigned long TXFLR;
 unsigned long RXFLR;
 unsigned long SR;
 unsigned long IMR;
 unsigned long ISR;
 unsigned long RISR;
 unsigned long TXOICR;
 unsigned long RXOICR;
 unsigned long RXUICR;
 unsigned long MSTICR;
 unsigned long ICR;
 unsigned long DMACR;
 unsigned long DMATDLR;
 unsigned long DMARDLR;
 unsigned long DR;
}IMAP_SSI_TypeDef;

#define IMAP_MSSI0 ((IMAP_SSI_TypeDef*)MSSI0_BASE)
#define IMAP_MSSI1 ((IMAP_SSI_TypeDef*)MSSI1_BASE)
#define IMAP_MSSI2 ((IMAP_SSI_TypeDef*)MSSI2_BASE)
#define IMAP_SSSI  ((IMAP_SSI_TypeDef*)SSSI_BASE)

#endif
