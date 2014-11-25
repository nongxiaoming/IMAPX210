#ifndef __IMAP_GPIO_H
#define __IMAP_GPIO_H

typedef struct
{
unsigned long DAT;
unsigned long CON;
unsigned long PUD;
} IMAP_GPIO_TypeDef;

typedef struct
{
	unsigned long  EINTCON;       /* R/W  External Interrupt configuration Register  */
	unsigned long  EINTFLTCON0;   /* R/W  External Interrupt Filter Control Register 0 */
    unsigned long  EINTFLTCON1;   /* R/W  External Interrupt Filter Control Register 1 */
	unsigned long  EINTGCON;      /* R/W  External Interrupt Group configuration Register */
	unsigned long  EINTGFLTCON0;  /* R/W  External Interrupt Group Filter Control Register 0 */
	unsigned long  EINTGFLTCON1;  /* R/W  External Interrupt Group Filter Control Register 1 */
	unsigned long  EINTG1MASK;    /* R/W  External Interrupt Group 1 Mask register */
	unsigned long  EINTG2MASK;    /* R/W  External Interrupt Group 2 Mask register */
	unsigned long  EINTG3MASK;    /* R/W  External Interrupt Group 3 Mask register */
	unsigned long  EINTG4MASK;    /* R/W  External Interrupt Group 4 Mask register */
	unsigned long  EINTG5MASK;    /* R/W  External Interrupt Group 5 Mask register */
	unsigned long  EINTG6MASK;    /* R/W  External Interrupt Group 6 Mask register */
	unsigned long  EINTG1PEND;    /* R/W  External Interrupt Group 1 Pending register */
	unsigned long  EINTG2PEND;    /* R/W  External Interrupt Group 2 Pending register */
	unsigned long  EINTG3PEND;    /* R/W  External Interrupt Group 3 Pending register */
	unsigned long  EINTG4PEND;    /* R/W  External Interrupt Group 4 Pending register */
	unsigned long  EINTG5PEND;    /* R/W  External Interrupt Group 5 Pending register */
	unsigned long  EINTG6PEND;    /* R/W  External Interrupt Group 6 Pending register */
} IMAP_EINT_TypeDef;

#define GPA_BASE      (0x20e10000)
#define GPB_BASE      (0x20e10010)
#define GPC_BASE      (0x20e10020)
#define GPD_BASE      (0x20e10030)
#define GPE_BASE      (0x20e10040)
#define GPF_BASE      (0x20e10050)
#define GPG_BASE      (0x20e10060)
#define GPH_BASE      (0x20e10070)
#define GPI_BASE      (0x20e10080)
#define GPJ_BASE      (0x20e10090)
#define GPK_BASE      (0x20e100A0)
#define GPL_BASE      (0x20e100B0)
#define GPM_BASE      (0x20e100C0)
#define GPN_BASE      (0x20e100D0)
#define GPO_BASE      (0x20e100E0)
#define GPP_BASE      (0x20e100F0)
#define GPQ_BASE      (0x20e10100)
#define GPR_BASE      (0x20e10110)
#define EINT_BASE     (0x20E10200)

/*GPIOA*/
#define IMAP_GPA           ((IMAP_GPIO_TypeDef*)GPA_BASE)

/*GPIOB*/
#define IMAP_GPB           ((IMAP_GPIO_TypeDef*)GPB_BASE)

/*GPIOC*/
#define IMAP_GPC           ((IMAP_GPIO_TypeDef*)GPC_BASE)

/*GPIOD*/
#define IMAP_GPD           ((IMAP_GPIO_TypeDef*)GPD_BASE)

/*GPIOE*/
#define IMAP_GPE           ((IMAP_GPIO_TypeDef*)GPE_BASE)

/*GPIOF*/
#define IMAP_GPF           ((IMAP_GPIO_TypeDef*)GPF_BASE)

/*GPIOG*/
#define IMAP_GPG           ((IMAP_GPIO_TypeDef*)GPG_BASE)

/*GPIOH*/
#define IMAP_GPH          ((IMAP_GPIO_TypeDef*)GPH_BASE)

/*GPIOI*/
#define IMAP_GPI           ((IMAP_GPIO_TypeDef*)GPI_BASE)

/*GPIOJ*/
#define IMAP_GPJ           ((IMAP_GPIO_TypeDef*)GPJ_BASE)

/*GPIOK*/
#define IMAP_GPK           ((IMAP_GPIO_TypeDef*)GPK_BASE)

/*GPIOL*/
#define IMAP_GPL           ((IMAP_GPIO_TypeDef*)GPL_BASE)

/*GPIOM*/
#define IMAP_GPM           ((IMAP_GPIO_TypeDef*)GPM_BASE)

/*GPION*/
#define IMAP_GPN           ((IMAP_GPIO_TypeDef*)GPN_BASE)

/*GPIOO*/
#define IMAP_GPO           ((IMAP_GPIO_TypeDef*)GPO_BASE)

/*GPIOP*/
#define IMAP_GPP           ((IMAP_GPIO_TypeDef*)GPP_BASE)

/*GPIOQ*/
#define IMAP_GPQ           ((IMAP_GPIO_TypeDef*)GPQ_BASE)

/*GPIOR*/
#define IMAP_GPR           ((IMAP_GPIO_TypeDef*)GPR_BASE)
/*EINT*/
#define IMAP_EINT     ((IMAP_EINT_TypeDef*)EINT_BASE)

#endif

