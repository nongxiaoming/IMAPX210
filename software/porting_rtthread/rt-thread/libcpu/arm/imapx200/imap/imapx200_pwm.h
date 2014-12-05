#ifndef __IMAPX_PWM_H
#define __IMAPX_PWM_H

typedef struct
{
unsigned long  TCFG0;  /* R/W Timer configuration 0 register  */
unsigned long  TCFG1;  /*  R/W Timer configuration 1 register */
unsigned long  TCON;   /*  R/W Timer control register */
unsigned long  TCNTB0; /*  R/W Timer count buffer 0 register */
unsigned long  TCMPB0; /*  R/W Timer compare buffer 0 register */
unsigned long  TCNTO0; /*  R Timer count observation 0 register */
unsigned long  TCNTB1; /*  R/W Timer count buffer 1 register */
unsigned long  TCMPB1; /*  R/W Timer compare buffer 1 register */
unsigned long  TCNTO1; /*  R Timer count observation 1 register */
unsigned long  TCNTB2; /*  R/W Timer count buffer 2 register */
unsigned long  TCMPB2; /*  R/W Timer compare buffer 2 register */
unsigned long  TCNTO2; /*  R Timer count observation 2 register */
unsigned long  TCNTB3; /*  R/W Timer count buffer 3 register */
unsigned long  TCMPB3; /*  R/W Timer compare buffer 3 register */
unsigned long  TCNTO3; /*  R Timer count observation 3 register */
unsigned long  TCNTB4; /*  R/W Timer count buffer 4 register */
unsigned long  TCNTO4; /*  R Timer count observation 4 register */
}IMAP_PWM_TypeDef;

#define IMAP_PWM_BASE  (0x20D70000)

#define IMAP_PWM ((IMAP_PWM_TypeDef*)IMAP_PWM_BASE)

/*		IMAP_TCFG0              */
/*		imap_TCFG1		*/ 
#define		IMAP_TCFG1_DMA		(0x1111<<20)

/*        	IMAP_TCON		*/
#define		IMAP_TCON_T4RL_ON	(1<<22)
#define		IMAP_TCON_T4MU_ON	(1<<21)
#define		IMAP_TCON_T4START	(1<<20)
#define		IMAP_TCON_T3RL_ON	(1<<19)
#define		IMAP_TCON_T3OI_ON	(1<<18)
#define		IMAP_TCON_T3MU_ON	(1<<17)
#define		IMAP_TCON_T3START	(1<<16)
#define		IMAP_TCON_T2RL_ON	(1<<15)
#define     MAP_TCON_T2OI_ON       (1<<14)
#define		IMAP_TCON_T2MU_ON	(1<<13)
#define		IMAP_TCON_T2START	(1<<12)
#define		IMAP_TCON_T1RL_ON	(1<<11)
#define     IMAP_TCON_T1OI_ON       (1<<10)
#define		IMAP_TCON_T1MU_ON	(1<<9)
#define		IMAP_TCON_T1START	(1<<8)
#define		IMAP_TCON_DEADZ_ON	(1<<4)
#define		IMAP_TCON_T0RL_ON	(1<<3)
#define     IMAP_TCON_T0OI_ON       (1<<2)
#define		IMAP_TCON_T0MU_ON	(1<<1)
#define		IMAP_TCON_T0START	(1<<0)

#define		IMAP_TCNTB(channel)      (IMAP_TCNTB0 + (channel *0xC))
#define		IMAP_TCMPB(channel)	  (IMAP_TCMPB0 + (channel *0xC))   



#endif
