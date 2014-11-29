#ifndef __IMAP_RTC_H
#define __IMAP_RTC_H

#define RTC_BASE (0x20dc0040)


typedef struct 
{
	unsigned long RTCCON;     /* R / W RTC control register */
	unsigned long TICNT;      /*  R / W RTC Tick time count register */
	unsigned long Reserved0[2];
	unsigned long RTCALM;     /*   R / W RTC alarm control register */
	unsigned long ALMSEC;     /*   R / W RTC Alarm second register */
	unsigned long ALMMIN;     /*  R / W RTC Alarm minute register */
	unsigned long ALMHOUR;    /*  R / W RTC Alarm hour register */
	unsigned long ALMDATE;    /*  R / W RTC alarm date register */
	unsigned long ALMMON;     /*  R / W RTC Alarm month register */
	unsigned long ALMYEAR;    /*  R / W Alarm year register */
	unsigned long Reserved1;
	unsigned long BCDSEC;     /*  R / W BCD second register */
	unsigned long BCDMIN;     /*  R / W BCD minute register */
	unsigned long BCDHOUR;    /*  R / W BCD hour register */
	unsigned long BCDDATE;    /*  R / W BCD day register */
	unsigned long BCDDAY;     /*  R / W BCD date register */
	unsigned long BCDMON;     /*  R / W BCD month register */
	unsigned long BCDYEAR;    /*  R / W BCD year register */
	unsigned long ALMDAY;     /*  R / W Alarm day register */
}IMAP_RTC_TypeDef;

#define IMAP_RTC ((IMAP_RTC_TypeDef*)RTC_BASE)

#endif
