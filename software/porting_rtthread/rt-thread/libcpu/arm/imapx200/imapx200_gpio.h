#ifndef __IMAP_GPIO_H
#define __IMAP_GPIO_H
typedef struct
{
 unsigned long DAT;
 unsigned long CON;
 unsigned long PUD;
} IMAP_GPIO_TypeDef;

#define GPA_BASE      (0x20e10000))
#define GPB_BASE      (0x20e10010))
#define GPC_BASE      (0x20e10020))
#define GPD_BASE      (0x20e10030))
#define GPE_BASE      (0x20e10040))
#define GPF_BASE      (0x20e10050))
#define GPG_BASE      (0x20e10060))
#define GPH_BASE      (0x20e10070))
#define GPI_BASE      (0x20e10080))
#define GPJ_BASE      (0x20e10090))
#define GPK_BASE      (0x20e100A0))
#define GPL_BASE      (0x20e100B0))
#define GPM_BASE      (0x20e100C0))
#define GPN_BASE      (0x20e100D0))
#define GPO_BASE      (0x20e100E0))
#define GPP_BASE      (0x20e100F0))
#define GPQ_BASE      (0x20e10100))
#define GPR_BASE      (0x20e10110))

/*GPIOA*/
#define GPADAT        (*(volatile unsigned *)(0x20e10000))
#define GPACON        (*(volatile unsigned *)(0x20e10004))
#define GPAPUD        (*(volatile unsigned *)(0x20e10008))
#define GPA           ((IMAP_GPIO_TypeDef*)GPA_BASE)

/*GPIOB*/
#define GPBDAT        (*(volatile unsigned *)(0x20e10010))
#define GPBCON        (*(volatile unsigned *)(0x20e10014))
#define GPBPUD        (*(volatile unsigned *)(0x20e10018))
#define GPB           ((IMAP_GPIO_TypeDef*)GPB_BASE)

/*GPIOC*/
#define GPCDAT        (*(volatile unsigned *)(0x20e10020))
#define GPCCON        (*(volatile unsigned *)(0x20e10024))
#define GPCPUD        (*(volatile unsigned *)(0x20e10028))
#define GPC           ((IMAP_GPIO_TypeDef*)GPC_BASE)

/*GPIOD*/
#define GPDDAT        (*(volatile unsigned *)(0x20e10030))
#define GPDCON        (*(volatile unsigned *)(0x20e10034))
#define GPDPUD        (*(volatile unsigned *)(0x20e10038))
#define GPD           ((IMAP_GPIO_TypeDef*)GPD_BASE)

/*GPIOE*/
#define GPEDAT        (*(volatile unsigned *)(0x20e10040))
#define GPECON        (*(volatile unsigned *)(0x20e10044))
#define GPEPUD        (*(volatile unsigned *)(0x20e10048))
#define GPE           ((IMAP_GPIO_TypeDef*)GPE_BASE)

/*GPIOF*/
#define GPFDAT        (*(volatile unsigned *)(0x20e10050))
#define GPFCON        (*(volatile unsigned *)(0x20e10054))
#define GPFPUD        (*(volatile unsigned *)(0x20e10058))
#define GPF           ((IMAP_GPIO_TypeDef*)GPF_BASE)

/*GPIOG*/
#define GPGDAT        (*(volatile unsigned *)(0x20e10060))
#define GPGCON        (*(volatile unsigned *)(0x20e10064))
#define GPGPUD        (*(volatile unsigned *)(0x20e10068))
#define GPG           ((IMAP_GPIO_TypeDef*)GPG_BASE)

/*GPIOH*/
#define GPHDAT        (*(volatile unsigned *)(0x20e10070))
#define GPHCON        (*(volatile unsigned *)(0x20e10074))
#define GPHPUD        (*(volatile unsigned *)(0x20e10078))
#define GPH          ((IMAP_GPIO_TypeDef*)GPH_BASE)

/*GPIOI*/
#define GPIDAT        (*(volatile unsigned *)(0x20e10080))
#define GPICON        (*(volatile unsigned *)(0x20e10084))
#define GPIPUD        (*(volatile unsigned *)(0x20e10088))
#define GPI           ((IMAP_GPIO_TypeDef*)GPI_BASE)

/*GPIOJ*/
#define GPJDAT        (*(volatile unsigned *)(0x20e10090))
#define GPJCON        (*(volatile unsigned *)(0x20e10094))
#define GPJPUD        (*(volatile unsigned *)(0x20e10098))
#define GPJ           ((IMAP_GPIO_TypeDef*)GPJ_BASE)

/*GPIOK*/
#define GPKDAT        (*(volatile unsigned *)(0x20e100A0))
#define GPKCON        (*(volatile unsigned *)(0x20e100A4))
#define GPKPUD        (*(volatile unsigned *)(0x20e100A8))
#define GPK           ((IMAP_GPIO_TypeDef*)GPK_BASE)

/*GPIOL*/
#define GPLDAT        (*(volatile unsigned *)(0x20e100B0))
#define GPLCON        (*(volatile unsigned *)(0x20e100B4))
#define GPLPUD        (*(volatile unsigned *)(0x20e100B8))
#define GPL           ((IMAP_GPIO_TypeDef*)GPL_BASE)

/*GPIOM*/
#define GPMDAT        (*(volatile unsigned *)(0x20e100C0))
#define GPMCON        (*(volatile unsigned *)(0x20e100C4))
#define GPMPUD        (*(volatile unsigned *)(0x20e100C8))
#define GPM           ((IMAP_GPIO_TypeDef*)GPM_BASE)

/*GPION*/
#define GPNDAT        (*(volatile unsigned *)(0x20e100D0))
#define GPNCON        (*(volatile unsigned *)(0x20e100D4))
#define GPNPUD        (*(volatile unsigned *)(0x20e100D8))
#define GPN           ((IMAP_GPIO_TypeDef*)GPN_BASE)

/*GPIOO*/
#define GPODAT        (*(volatile unsigned *)(0x20e100E0))
#define GPOCON        (*(volatile unsigned *)(0x20e100E4))
#define GPOPUD        (*(volatile unsigned *)(0x20e100E8))
#define GPO           ((IMAP_GPIO_TypeDef*)GPO_BASE)

/*GPIOP*/
#define GPPDAT        (*(volatile unsigned *)(0x20e100F0))
#define GPPCON        (*(volatile unsigned *)(0x20e100F4))
#define GPPPUD        (*(volatile unsigned *)(0x20e100F8))
#define GPP           ((IMAP_GPIO_TypeDef*)GPP_BASE)

/*GPIOQ*/
#define GPQDAT        (*(volatile unsigned *)(0x20e10100))
#define GPQCON        (*(volatile unsigned *)(0x20e10104))
#define GPQPUD        (*(volatile unsigned *)(0x20e10108))
#define GPQ           ((IMAP_GPIO_TypeDef*)GPQ_BASE)

/*GPIOR*/
#define GPRDAT        (*(volatile unsigned *)(0x20e10110))
#define GPRCON        (*(volatile unsigned *)(0x20e10114))
#define GPRPUD        (*(volatile unsigned *)(0x20e10118))
#define GPR           ((IMAP_GPIO_TypeDef*)GPR_BASE)


#endif

